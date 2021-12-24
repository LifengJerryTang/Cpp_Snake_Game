#ifndef GAMEOBJECT_H
#define GAMEOBJECT_H

enum class GameLevel {kONE, kTWO, kTHREE};

class GameObject {
    public:
        virtual void Update() = 0;
        void SetGameLevel(GameLevel level);
        GameLevel GetGameLevel() const;

    private:
        GameLevel _curr_level;

    
};

#endif