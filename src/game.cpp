#include "game.h"
#include <iostream>
#include <chrono>
#include <string>
#include <sstream>
#include <thread>
#include <future>
#include "SDL.h"

Game::Game(std::size_t grid_width, std::size_t grid_height): grid_width(grid_width), grid_height(grid_height) {
  
  snake = std::shared_ptr<Snake>(new Snake(grid_width, grid_height));
  food = std::unique_ptr<Food>(new Food(grid_width, grid_height));
  bonus_food = std::unique_ptr<Food>(new Food(grid_width, grid_height));
}

void Game::ChooseLevel() {
    std::string input;
    std::cout << "Welcome to Snake!" << std::endl;
    std::cout << "Please enter a game level (1, 2, OR 3): ";

    int input_level;
    std::getline(std::cin, input);
    std::istringstream input_stream(input);
    input_stream >> input_level;

    bool validInput = input.length() == 1 && input_level >= 1 && input_level <= 3;

    while(!validInput) {
      std::cout << "BAD INPUT!" << std::endl;
      std::cout << "Please enter a VALID game level (1, 2, OR 3): ";
      std::getline(std::cin, input);
      input_stream = std::istringstream(input);
      input_stream >> input_level;
      validInput = input.length() == 1 && input_level >= 1 && input_level <= 3;
    }

   
    _curr_level = (GameLevel) input_level;
     std::cout << "Level: " << (int) (_curr_level) << std::endl;
     InitializeGameStates();
   

}

void Game::InitializeGameStates() {
  snake->SetGameLevel(_curr_level);
  snake->speed *= (int)(_curr_level);
  food->SetGameLevel(_curr_level);
  food->SetSnakeRef(snake);
  PlaceFood();

  if (_curr_level > GameLevel::kTWO) {
    bonus_food->SetSnakeRef(snake);
    bonus_food->SetGameLevel(_curr_level);
  } 
}

void Game::Run(Controller const &controller, Renderer &renderer,
               std::size_t target_frame_duration) {

  std::thread t;
  if (_curr_level > GameLevel::kTWO) {
    t = std::thread(&Game::RandomlyPlaceBonusFood, this);
  }

  Uint32 title_timestamp = SDL_GetTicks();
  Uint32 frame_start;
  Uint32 frame_end;
  Uint32 frame_duration;
  int frame_count = 0;
  running = true;

  while (running) {

    frame_start = SDL_GetTicks();

    // Input, Update, Render - the main game loop.
    controller.HandleInput(running, snake);
    Update();
    renderer.Render(_curr_level, *snake, food->GetSDL(), bonus_food->GetSDL());

    frame_end = SDL_GetTicks();

    // Keep track of how long each loop through the input/update/render cycle
    // takes.
    frame_count++;
    frame_duration = frame_end - frame_start;

    // After every second, update the window title.
    if (frame_end - title_timestamp >= 1000) {
      renderer.UpdateWindowTitle(score, frame_count);
      frame_count = 0;
      title_timestamp = frame_end;
    }

    // If the time for this frame is too small (i.e. frame_duration is
    // smaller than the target ms_per_frame), delay the loop to
    // achieve the correct frame rate.
    if (frame_duration < target_frame_duration) {
      SDL_Delay(target_frame_duration - frame_duration);
    }


   
    std::unique_lock<std::mutex> lck(_mutex);
    if (!snake->alive) {
      std::this_thread::sleep_for(std::chrono::milliseconds(500));
      running = false;
    }

    lck.unlock();
  }

   if (_curr_level > GameLevel::kTWO) {
     t.join();
  }
}

void Game::PlaceFood() {
  food->Update();
}

void Game::RandomlyPlaceBonusFood() {

  while(true) {
    std::unique_lock<std::mutex> lock(_mutex);
    if (!snake->alive || !running){
       lock.unlock();
       break;
    }

    lock.unlock();
   
    //std::cout << "Randomly placing bonus food concurrently...." << std::endl;
    
    std::random_device rd;
    std::mt19937 eng(rd());
    std::uniform_int_distribution<>distr(0, 1);
    int random_phase = distr(eng);
    lock.lock();
    bonus_food->Update();
   
    if (random_phase == 1) {
      bonus_food->is_bomb = !bonus_food->is_bomb;
    }  
    lock.unlock();
 //   std::cout << "Is the snake alive? " << snake->alive << std::endl;
    std::this_thread::sleep_for(std::chrono::milliseconds(4000));
  }
}

void Game::Update() {

  std::unique_lock<std::mutex> lock(_mutex);
  if (!snake->alive) {
    lock.unlock();
    return;
  }

  snake->Update();
  lock.unlock();
 

  int new_x = static_cast<int>(snake->head_x);
  int new_y = static_cast<int>(snake->head_y);

  // Check if there's food over here
  if (food->GetX() == new_x && food->GetY() == new_y) {
    score++;
    
    PlaceFood();
    lock.lock();
    // Grow snake and increase speed.
    snake->GrowBody();
    snake->speed += 0.02;
    lock.unlock();
  } 

  if (_curr_level > GameLevel::kTWO) {
    lock.lock();
    if (bonus_food->GetX() == new_x && bonus_food->GetY() == new_y) {
      if (bonus_food->is_bomb) {
        snake->alive = false;
      } else {
        score += 5;
        snake->speed += 0.005;
        bonus_food->Update();
        bonus_food->is_bomb = !bonus_food->is_bomb;
      }
     
    }
    lock.unlock();
  }

  if ((int) _curr_level >= 3) {
    lock.lock();
    if (snake->head_x <= 1 || snake->head_y <= 1 || snake->head_x >= grid_height - 1 || snake->head_y >= grid_width - 1) {
      std::cout << "Hit the wall!" << std::endl;
      snake->alive = false;
    }

    lock.unlock();
  }

  
}

int Game::GetScore() const { return score; }
int Game::GetSize() const { return snake->size; }