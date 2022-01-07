#ifndef ASTAR_H
#define ASTAR_H

#include "gamestate.h"
#include <queue>
#include <vector>
#include <functional>
#include <memory>


class AStar {

    public:
        AStar(int food_x, int food_y);
        void Run();
        bool CompareState(GameState &state_1, GameState &state_2);
        double EuclidDistToFood(GameState &state) const;

    private:
        std::unique_ptr<GameState> _initial_state;
        std::unique_ptr<GameState> _goal_state;
        
};

#endif