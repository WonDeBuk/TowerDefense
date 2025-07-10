#pragma once

#include "../RenderState.h"
#include "././Utils/ResourceManager.h"

class SettingState : public RenderState
{
private:
    // Director* StateDirector;
    Language CurrentStateLanguage;

    // Container Properties
    Rectangle ContainerDimension;

    // Indicator Properties
    Texture2D* SettingIndicator;
    Rectangle IndicatorDimension[4];

    // Icon Properties
    Rectangle TitleLeftIconDimension;
    Rectangle TitleRightIconDimension;
    Texture2D* TitleIcon;

    // Content Properties
    char* SettingContent[4];
    Vector2 TextDimension[4];
    Rectangle ContentDimension[4];
    Font* ContentFont;

    // Music Properties
    Rectangle MusicContainerDimension;
    
    // Effect Properties
    Rectangle EffectContainerDimension;

    // Language Properties
    Rectangle LanguageContainerDimension;
    Vector2 FlagIconSize;
    Texture2D** FlagIcon;
    Rectangle* FlagBound;
    Rectangle* FlagDimension;
    int HoverIndex;
    const int NumOfLanguage = (int) Language::LANGUAGECOUNTING;
    Rectangle CurrentLanguageFlagDimension;

    const float TDPaddingPercent = 0.125f;
    const float RLPaddingPercent = 0.35f;
    const float ContentMargin = 20.0f;
    const float PaddingFromTitleContent = 20.0f;
    const float IndicatorSize = 12.0f;
    const float PaddingFromText = 20.0f;
    const float ContentFontSize = 48.0f;
    const float MusicContainerPercentage = 0.2f;
    const float EffectContainerPercentage = 0.2f;
    const float LanguageContainerPercentage = 0.5f;
    const float FlagScale = 3.0f;
    const float FlagMargin = 10.0f;
    const float FlagPadding = 5.0f;

    // Back Button properties
    Rectangle BackButtonDimension;
    Rectangle ButtonIconDimension;
    Rectangle BackButtonIndicatorDimension[4];
    char* BackContent;
    Vector2 BackContentSize;
    Vector2 BackContentPosition;
    Texture2D* BackButtonIcon;
    Texture2D* BackButtonBoxIndicator;
    bool IsBackButtonHover;
    const float PaddingBotContainer = 20.0f;
public:
    SettingState();

    void Update() override;
    void Draw() const override;
    void Enter() override;
    void Exit() override;
}; 