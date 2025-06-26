#pragma once

#include "raylib.h"
#include "RenderState.h"

class RenderState;

enum class RENDER_STATE {
    MAIN,
    DICTIONARY,
    PLAY,
    LOAD_GAME,
    SETTING,
    GAME,
    WAITING
};

class Director {
private:
    RenderState* CurrentState;

    Director() : CurrentState(nullptr) {}
public:
    static Director& GetInstance();
    void TransitionTo(const RENDER_STATE&);
    void Update();
    void Draw();

    ~Director();
};
