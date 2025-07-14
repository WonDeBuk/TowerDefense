#pragma once

#include "../RenderState.h"

class PlayState : public RenderState
{
private:
    Rectangle ForestMap;
    Rectangle FrozenMap;
    Rectangle BackButton;
public:
    PlayState();

    void Update() override;

    void Draw() const override;
}; 