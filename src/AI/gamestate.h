#ifndef GAMESTATE_H
#define GAMESTATE_H

struct Pos {
    int x;
    int y;
};

typedef struct Pos Pos;

class GameState {
    public:
        Pos snake_head_pos;
        Pos food_pos;
        GameState(Pos &snake_head_pos, Pos &food_pos);
};

#endif