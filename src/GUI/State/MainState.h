#pragma once

#include "raylib.h"
#include "../RenderState.h"

class MainState : public RenderState {
private:
    Rectangle Button1, Button2, Button3, Button4;
public:
    MainState();

    void Update() override;

    void Draw() const override;
}; 