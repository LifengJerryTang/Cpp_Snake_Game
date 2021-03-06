#include <iostream>
#include "Controller/controller.h"
#include "Game/game.h"
#include "Renderer/renderer.h"

int main() {
  constexpr std::size_t kFramesPerSecond{60};
  constexpr std::size_t kMsPerFrame{1000 / kFramesPerSecond};
  constexpr std::size_t kScreenWidth{640};
  constexpr std::size_t kScreenHeight{640};
  constexpr std::size_t kGridWidth{32};
  constexpr std::size_t kGridHeight{32};

  Game game(kGridWidth, kGridHeight);
  game.ChooseLevel();
  Renderer renderer(kScreenWidth, kScreenHeight, kGridWidth, kGridHeight);
  Controller controller;
  game.Run(controller, renderer, kMsPerFrame);
  
  std::cout << "GAME OVER! Thanks for playing!\n";
  std::cout << "Score: " << game.GetScore() << "\n";
  std::cout << "Size: " << game.GetSize() << "\n";
  return 0;
}