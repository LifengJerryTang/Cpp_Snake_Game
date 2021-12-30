#ifndef GAME_H
#define GAME_H

#include <random>
#include "SDL.h"
#include "Controller/controller.h"
#include "Renderer/renderer.h"
#include "GameObject/snake.h"
#include <thread>
#include <mutex>
#include <memory>
#include "GameObject/food.h"
#include "GameObject/gameobject.h"

class Game {
 public:
  Game(std::size_t grid_width, std::size_t grid_height);
  void ChooseLevel();
  void InitializeGameStates();
  void Run(Controller const &controller, Renderer &renderer,
           std::size_t target_frame_duration);
  int GetScore() const;
  int GetSize() const;
  

 private:
  // Snake snake;
  std::size_t grid_width;
  std::size_t grid_height;
  std::shared_ptr<Snake> snake;
  std::unique_ptr<Food> food;
  std::unique_ptr<Food> bonus_food;
  GameLevel _curr_level;
  std::mutex _mutex;
  bool running{false};

  int score{0};

  void PlaceFood();
  void Update();
  void RandomlyPlaceBonusFood();
};

#endif