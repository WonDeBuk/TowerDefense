#pragma once

#include "../RenderState.h"
#include "././Game/GameManager.h"

class GameState : public RenderState
{
private:
    Rectangle BackButton;
public:
    GameState();

    void Update() override;

    void Draw() const override;
}; 