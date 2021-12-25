#ifndef GAME_H
#define GAME_H

#include <random>
#include "SDL.h"
#include "controller.h"
#include "renderer.h"
#include "snake.h"
#include <thread>
#include <mutex>
#include <memory>
#include "food.h"
#include "gameobject.h"

class Game {
 public:
  Game(std::size_t grid_width, std::size_t grid_height);
  void ChooseLevel();
  void Run(Controller const &controller, Renderer &renderer,
           std::size_t target_frame_duration);
  int GetScore() const;
  int GetSize() const;

 private:
  // Snake snake;
  std::shared_ptr<Snake> snake;
  std::unique_ptr<Food> food;
  std::unique_ptr<Food> bonus_food;
  GameLevel _curr_level;
  std::mutex _mutex;

  int score{0};

  void PlaceFood();
  void Update();
  void RandomlyPlaceBonusFood();
};

#endif