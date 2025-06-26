#pragma once

#include "../RenderState.h"

class SettingState : public RenderState
{
private:
    Rectangle BackButton;
public:
    SettingState();

    void Update() override;

    void Draw() const override;
}; 