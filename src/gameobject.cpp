#include "gameobject.h"


void GameObject::SetGameLevel(GameLevel level) {
    _curr_level = level;
}

GameLevel GameObject::GetGameLevel() const {
    return _curr_level;
}