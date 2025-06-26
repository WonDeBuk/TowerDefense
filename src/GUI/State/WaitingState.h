#pragma once

#include "../RenderState.h"

class WaitingState : public RenderState
{
private:
public:
    WaitingState();

    void Update() override;

    void Draw() const override;
};