#pragma once

#include "../RenderState.h"

class MainState : public RenderState {
private:
    Director* StateDirector;
    char* ButtonContent[5];
    const float ButtonFontSize = 64.0f;
    const float ButtonTDMargin = 5.0f;
    const float ButtonLRMargin = 20.0f;
    Rectangle ContentDimension[5];
    Rectangle ButtonBound[5];
    Rectangle BackgroundImageDimension;
    Rectangle RightIndicator, LeftIndicator;
    Texture2D* BackgroundImage;
    Texture2D* Indicator;
    Font* ContentFont;
    int HoverIndex;
public:
    MainState();

    void Update() override;
    void Draw() const override;
    void Enter() override;
    void Exit() override;
}; 