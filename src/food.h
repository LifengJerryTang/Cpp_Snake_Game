#ifndef FOOD_H
#define FOOD_H

#include "gameobject.h"
#include "SDL.h"
#include "snake.h"

#include <memory>
#include <random>

class Food: public GameObject {
    public:
        Food(std::size_t grid_width, std::size_t grid_height);
        void Update() override;
        int GetX() const  {return _the_food.x;}
        void SetX(int x) {_the_food.x = x;};
        int GetY() const {return _the_food.y;}
        void SetY(int y) {_the_food.y = y;}
        void SetSnakeRef(std::shared_ptr<Snake> snake_ptr) {snake_ref = snake_ptr;}
        SDL_Point GetSDL() { return _the_food;}

        bool is_bomb{false};

    private:
        SDL_Point _the_food;
        std::shared_ptr<Snake> snake_ref;
        std::random_device dev;
        std::mt19937 engine;
        std::uniform_int_distribution<int> random_w;
        std::uniform_int_distribution<int> random_h;

        
};



#endif