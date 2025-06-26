#pragma once

#include "../RenderState.h"

class LoadGameState : public RenderState
{
private:
    Rectangle BackButton;
public:
    LoadGameState();

    void Update() override;

    void Draw() const override;
}; 