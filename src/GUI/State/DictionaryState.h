#pragma once

#include "../RenderState.h"
#include "../Element/ChampionListContainer.h"

class DictionaryState : public RenderState
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
    Rectangle DictionaryIconDimension[2];
    Rectangle InformationIconDimension[2];
    Texture2D* DictionaryIconTexture[2];
    Texture2D* InformationIconTexture;

    // Content Properties
    char* DictionaryTitle;
    Vector2 DictionaryTitleSize;
    Vector2 DictionaryTitlePosition;
    char* InformationTitle;
    Vector2 InformationTitleSize;
    Vector2 InformationTitlePosition;
    Font* ContentFont;
    const float ContentFontSize = 48.0f;

    // Dictionary Container Properties
    Rectangle DictionaryContainerDimension;
    const float DictionaryContainerPercentage = 0.55f;
    ChampionListContainer* ChampionList;

    // Information Container Properties
    Rectangle InformationContainerDimension;
    const float InformationContainerPercentage = 0.425f;
    Vector2 ChampionIdleDrawPosition;
    Vector2 ChampionCastDrawPosition;
    Texture2D* ShowCaseBackgroundTexture;
    Texture2D* NoneSelectedTexture;
    Rectangle ShowCaseDimension;
    Rectangle LoreDimension;
    std::string* LoreContent;
    const float LoreContentSize = 24.0f;

    // Back Button Properties
    Rectangle BackButtonDimension;
    Rectangle ButtonIconDimension;
    Rectangle BackButtonIndicatorDimension[4];
    char* BackContent;
    Vector2 BackContentSize;
    Vector2 BackContentPosition;
    Texture2D* BackButtonIcon;
    Texture2D* BackButtonBoxIndicator;
    bool IsBackButtonHover;
    const float PaddingBotContainer = 40.0f;
    const float ButtonFontSize = 32.0f;


    // Private Method
    void DrawInformationPanel() const;
public:
    DictionaryState();

    void UpdateInformationPanel();
    void Update() override;
    void Draw() const override;
    void Enter() override;
    void Exit() override;
}; 