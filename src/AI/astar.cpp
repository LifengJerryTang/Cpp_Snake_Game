#include "astar.h"

AStar::AStar(int food_x, int food_y) {
    Pos initial_smart_snake_pos {1, 1};
    Pos food_pos {food_x, food_y};

    _initial_state = std::unique_ptr<GameState>(new GameState(initial_smart_snake_pos, food_pos));
    _goal_state = std::unique_ptr<GameState>(new GameState(food_pos, food_pos));
}

void AStar::Run() {
    std::priority_queue<GameState, std::vector<GameState>, decltype(CompareState)> 
                                states_queue(decltype(CompareState));
    
    states_queue.emplace(_initial_state);
}