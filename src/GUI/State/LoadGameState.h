#pragma once

#include "../RenderState.h"

class LoadGameState : public RenderState
{
private:
    // Container Properties
    Rectangle ContainerDimension;
    const float TDPaddingPercent = 0.125f;
    const float RLPaddingPercent = 0.125f;
    const float ContentMargin = 20.0f;
    const float PaddingFromTitleContent = 20.0f;

    // Icon Properties
    const float PaddingFromText = 20.0f;
    Rectangle ContinueIconDimension[2];
    Rectangle InformationIconDimension[2];
    Texture2D* ContinueIconTexture[2];
    Texture2D* InformationIconTexture[2];

    // Content Properties
    char* ContinueTitle;
    Vector2 ContinueTitleSize;
    Vector2 ContinueTitlePosition;
    char* InformationTitle;
    Vector2 InformationTitleSize;
    Vector2 InformationTitlePosition;
    Font* ContentFont;
    const float ContentFontSize = 48.0f;

    // Continue Container Properties
    Rectangle ContinueContainerDimension;
    const float ContinueContainerPercentage = 0.55f;

    // Information Container Properties
    Rectangle InformationContainerDimension;
    const float InformationContainerPercentage = 0.4f;

    // Back Button Properties
    Rectangle BackButtonDimension;
    Rectangle ButtonIconDimension;
    Rectangle BackButtonIndicatorDimension[4];
    Vector2 BackContentSize;
    Vector2 BackContentPosition;
    Texture2D* BackButtonIcon;
    Texture2D* BackButtonBoxIndicator;
    char* BackContent;
    bool IsBackButtonHover;
    const float PaddingBotContainer = 20.0f;
public:
    LoadGameState();

    void Update() override;
    void Draw() const override;
    void Enter() override;
    void Exit() override;
}; 