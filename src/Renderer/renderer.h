#ifndef RENDERER_H
#define RENDERER_H

#include <vector>
#include "SDL.h"
#include "GameObject/snake.h"

class Renderer {
 public:
  Renderer(const std::size_t screen_width, const std::size_t screen_height,
           const std::size_t grid_width, const std::size_t grid_height);
  ~Renderer();


  void Render(GameLevel game_level, Snake const snake, Snake const computer_snake,
                      SDL_Point const &food, SDL_Point const &bonus_food);
  void UpdateWindowTitle(int score, int fps);

 private:
  SDL_Window *sdl_window;
  SDL_Renderer *sdl_renderer;

  const std::size_t screen_width;
  const std::size_t screen_height;
  const std::size_t grid_width;
  const std::size_t grid_height;

  void RenderComputerSnake(Snake const snake, SDL_Rect& block);
  void RenderSnake(Snake const snake, int color, SDL_Rect& block);
};

#endif