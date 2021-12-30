#include "food.h"


Food::Food(std::size_t grid_width, std::size_t grid_height): 
              random_w(0, static_cast<int>(grid_width - 1)),
              random_h(0, static_cast<int>(grid_height - 1)),
              engine(dev()) {

}

void Food::Update() {
  int x, y;
  while (true) {
    x = random_w(engine);
    y = random_h(engine);
    // Check that the location is not occupied by a snake item before placing
    // food.
    while(snake_ref->SnakeCell(x, y)) {
      x = random_w(engine);
      y = random_h(engine);
    }
    this->SetX(x);
    this->SetY(y);
    return;
  }
}