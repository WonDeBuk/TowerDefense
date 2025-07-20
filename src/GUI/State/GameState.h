#pragma once

#include "../RenderState.h"

class GameState : public RenderState {
private:
    int SelectedTower;

public:
    GameState();

    void Update() override;

    void Draw() const override;
}; 