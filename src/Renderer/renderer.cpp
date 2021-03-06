#include "renderer.h"
#include <iostream>
#include <string>
#include "GameObject/gameobject.h"

Renderer::Renderer(const std::size_t screen_width,
                   const std::size_t screen_height,
                   const std::size_t grid_width, const std::size_t grid_height)
    : screen_width(screen_width),
      screen_height(screen_height),
      grid_width(grid_width),
      grid_height(grid_height) {
  // Initialize SDL
  if (SDL_Init(SDL_INIT_VIDEO) < 0) {
    std::cerr << "SDL could not initialize.\n";
    std::cerr << "SDL_Error: " << SDL_GetError() << "\n";
  }

  // Create Window
  sdl_window = SDL_CreateWindow("Snake Game", SDL_WINDOWPOS_CENTERED,
                                SDL_WINDOWPOS_CENTERED, screen_width,
                                screen_height, SDL_WINDOW_SHOWN);

  if (nullptr == sdl_window) {
    std::cerr << "Window could not be created.\n";
    std::cerr << " SDL_Error: " << SDL_GetError() << "\n";
  }

  // Create renderer
  sdl_renderer = SDL_CreateRenderer(sdl_window, -1, SDL_RENDERER_ACCELERATED);
  if (nullptr == sdl_renderer) {
    std::cerr << "Renderer could not be created.\n";
    std::cerr << "SDL_Error: " << SDL_GetError() << "\n";
  }
}

Renderer::~Renderer() {
//  std::cout << "Renderer destructor called "<< std::endl;
  SDL_DestroyWindow(sdl_window);
  SDL_Quit();
}


void Renderer::Render(GameLevel game_level, Snake const snake, Snake const computer_snake,
                      SDL_Point const &food, SDL_Point const &bonus_food) {
  SDL_Rect block;
  SDL_Rect block2;
  block.w = screen_width / grid_width;
  block.h = screen_height / grid_height;

  // Clear screen
  SDL_SetRenderDrawColor(sdl_renderer, 0x1E, 0x1E, 0x1E, 0xFF);
  SDL_RenderClear(sdl_renderer);

  // Render food
  SDL_SetRenderDrawColor(sdl_renderer, 0xFF, 0xFF, 0x00, 0xFF);
  block.x = food.x * block.w;
  block.y = food.y * block.h;
  SDL_RenderFillRect(sdl_renderer, &block);

  if (game_level > GameLevel::kTWO) {
      block2.w = screen_width / grid_width;
      block2.h = screen_height / grid_height;
      SDL_SetRenderDrawColor(sdl_renderer, 0xFF, 0x8C, 0x00, 0xFF);
      block2.x = bonus_food.x * block2.w;
      block2.y = bonus_food.y * block2.h;
      SDL_RenderFillRect(sdl_renderer, &block2);
  }

  RenderSnake(snake, 0XFF, block);

  if ((int)game_level >= 3) {
    RenderComputerSnake(computer_snake, block);
  }

  // Update Screen
  SDL_RenderPresent(sdl_renderer);
}

void Renderer::RenderSnake(Snake const snake, int color, SDL_Rect& block) {
  
  // Render snake's body
  SDL_SetRenderDrawColor(sdl_renderer, color, color, color, color);
  for (SDL_Point const &point : snake.body) {
    block.x = point.x * block.w;
    block.y = point.y * block.h;
    SDL_RenderFillRect(sdl_renderer, &block);
  }

  // Render snake's head
  block.x = static_cast<int>(snake.head_x) * block.w;
  block.y = static_cast<int>(snake.head_y) * block.h;
  if (snake.alive) {
    SDL_SetRenderDrawColor(sdl_renderer, 0x00, 0x7A, 0xCC, 0xFF);
  } else {
    SDL_SetRenderDrawColor(sdl_renderer, 0xFF, 0x00, 0x00, 0xFF);

  }
  SDL_RenderFillRect(sdl_renderer, &block);

}

void Renderer::RenderComputerSnake(Snake const snake, SDL_Rect& block) {
  RenderSnake(snake, 0XF9, block);
}



void Renderer::UpdateWindowTitle(int score, int fps) {
  std::string title{"Snake Score: " + std::to_string(score) + " FPS: " + std::to_string(fps)};
  SDL_SetWindowTitle(sdl_window, title.c_str());
}
