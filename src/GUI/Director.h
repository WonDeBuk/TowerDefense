#pragma once

#include "raylib.h"
#include "RenderState.h"

class RenderState;

enum RENDER_STATE {
    MAIN, PLAY, LOAD_GAME, DICTIONARY, SETTING, WAITING, GAME
};

class Director {
private:
    RenderState* CurrentState;
    RenderState** MenuBuffer;
    size_t Time;

    Director();
public:
    static Director& GetInstance();
    void Init();
    void TransitionTo(const RENDER_STATE&);
    void Update();
    void Draw() const;
    size_t GetTime() const;

    ~Director();
};
