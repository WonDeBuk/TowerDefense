#include "SettingState.h"
#include <iostream>
#include "../Director.h"
#include "././Utils/MathUtils.hpp"

SettingState::SettingState()
{
    CurrentStateLanguage = ResourceManager::CurrentLanguage;
    // StateDirector = &Director::GetInstance();
    ContainerDimension = {(float) SCREEN_WIDTH * RLPaddingPercent, (float) SCREEN_HEIGHT * TDPaddingPercent, (float) SCREEN_WIDTH * (1.0f - 2 * RLPaddingPercent), (float) SCREEN_HEIGHT * (1.0f - 2 * TDPaddingPercent)};
    ContentFont = &ResourceManager::GlobalFont;
    FlagIcon = new Texture2D*[NumOfLanguage];
    FlagBound = new Rectangle[NumOfLanguage];
    FlagDimension = new Rectangle[NumOfLanguage];
    for (int i = 0; i < NumOfLanguage; i++) {
        FlagIcon[i] = const_cast<Texture2D*>(&ResourceManager::GetInstance().LoadTexture("ui/" + ResourceManager::ParseLanguageToString[i] + ".png"));
    }
    TitleIcon = const_cast<Texture2D*>(&ResourceManager::GetInstance().LoadTexture("ui/SettingIcon.png"));
    SettingIndicator = const_cast<Texture2D*>(&ResourceManager::GetInstance().LoadTexture("ui/BoxIndicator.png"));
    BackButtonIcon = const_cast<Texture2D*>(&ResourceManager::GetInstance().LoadTexture("ui/HomeButton.png"));
    BackButtonBoxIndicator = SettingIndicator;
    FlagIconSize = {(float) FlagIcon[0]->width, (float) FlagIcon[0]->height};
    HoverIndex = -1;
    SettingState::Enter();
}

void SettingState::Update()
{
    Vector2 MousePosition = GetMousePosition();
    for (int i = 0; i < NumOfLanguage; i++) {
        if (CheckCollisionPointRec(MousePosition, FlagBound[i])) {
            HoverIndex = i;
            IndicatorDimension[0] = {FlagBound[i].x, FlagBound[i].y, IndicatorSize, IndicatorSize};
            IndicatorDimension[1] = {FlagBound[i].x + FlagBound[i].width - IndicatorSize, FlagBound[i].y, IndicatorSize, IndicatorSize};
            IndicatorDimension[2] = {FlagBound[i].x, FlagBound[i].y + FlagBound[i].height - IndicatorSize, IndicatorSize, IndicatorSize};
            IndicatorDimension[3] = {FlagBound[i].x + FlagBound[i].width - IndicatorSize, FlagBound[i].y + FlagBound[i].height - IndicatorSize, IndicatorSize, IndicatorSize};
            if ((i != (int) CurrentStateLanguage) && IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) {
                CurrentStateLanguage = static_cast<Language>(i);
                ResourceManager::GetInstance().ChangeLanguage(CurrentStateLanguage);
                SettingState::Enter();
            }
            break;
        } else {
            HoverIndex = -1;
        }
    }
    
    if (CheckCollisionPointRec(MousePosition, BackButtonDimension)) {
        IsBackButtonHover = true;
        if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) {
            Director::GetInstance().TransitionTo(RENDER_STATE::MAIN);
        }
    } else {
        IsBackButtonHover = false;
    }
}

void SettingState::Draw() const
{
    size_t Time = Director::GetInstance().GetTime();
    RenderState::Draw();
    DrawRectangleRec(ContainerDimension, {0, 0, 0, 100});
    for (int i = 0; i < 4; i++) {
        DrawTextEx(*ContentFont, SettingContent[i], {floorf(ContentDimension[i].x), floorf(ContentDimension[i].y)}, ContentFontSize, 1.0f, WHITE);
    }

    for (int i = 0; i < NumOfLanguage; i++)
    {
        DrawTexturePro(*FlagIcon[i], {0.0f, 0.0f, FlagIconSize.x, FlagIconSize.y}, FlagDimension[i], {0.0f, 0.0f}, 0.0f, WHITE);
    }

    DrawTexturePro(*TitleIcon, {0.0f, 0.0f, (float) TitleIcon->width, (float) TitleIcon->height}, TitleLeftIconDimension, {0.0f, 0.0f}, 0.0f, WHITE);
    DrawTexturePro(*TitleIcon, {0.0f, 0.0f, (float) TitleIcon->width, (float) TitleIcon->height}, TitleRightIconDimension, {0.0f, 0.0f}, 0.0f, WHITE);
    
    if (HoverIndex != -1) {
        for (int i = 0; i < 4; i++) {
            DrawTexturePro(*SettingIndicator, {12.0f * (i % 2), 24.0f * ((Time / 7) % 3) + 12.0f * (i / 2), 12.0f, 12.0f}, IndicatorDimension[i], {0.0f, 0.0f}, 0.0f, WHITE);
        }
    }
    DrawRectanglePro(BackButtonDimension, {0.0f, 0.0f}, 0.0f, {0, 0, 0, 100});
    DrawTexturePro(*BackButtonIcon, {0.0f, 0.0f, 64.0f, 64.0f}, ButtonIconDimension, {0.0f, 0.0f}, 0.0f, WHITE);
    DrawTextEx(*ContentFont, BackContent, BackContentPosition, ContentFontSize, 1.0f, WHITE);
    if (IsBackButtonHover) {
        for (int i = 0; i < 4; i++) {
            DrawTexturePro(*BackButtonBoxIndicator, {12.0f * (i % 2), 24.0f * ((Time / 7) % 3) + 12.0f * (i / 2), 12.0f, 12.0f}, BackButtonIndicatorDimension[i], {0.0f, 0.0f}, 0.0f, WHITE);
        }
    }
    DrawTexturePro(*FlagIcon[(int) CurrentStateLanguage], {0.0f, 0.0f, FlagIconSize.x, FlagIconSize.y}, CurrentLanguageFlagDimension, {0.0f, 0.0f}, 0.0f, WHITE);
}

void SettingState::Enter()
{
    BackContent = &const_cast<std::string&>(ResourceManager::GetInstance().LoadPlaceholder("BackButton"))[0];

    BackContentSize = MeasureTextEx(*ContentFont, BackContent, ContentFontSize, 1.0f);
    BackButtonDimension = {ContainerDimension.x, ContainerDimension.y - BackContentSize.y - PaddingBotContainer, 32.0f + BackContentSize.x + PaddingFromText * 2.0f, BackContentSize.y};
    BackContentPosition = {BackButtonDimension.x + 32.0f + PaddingFromText, BackButtonDimension.y};
    ButtonIconDimension = {BackButtonDimension.x, BackButtonDimension.y, 48.0f, 48.0f};
    BackButtonIndicatorDimension[0] = {BackButtonDimension.x - 12.0f, BackButtonDimension.y - 12.0f, 12.0f, 12.0f};
    BackButtonIndicatorDimension[1] = {BackButtonDimension.x + BackButtonDimension.width, BackButtonDimension.y - 12.0f, 12.0f, 12.0f};
    BackButtonIndicatorDimension[2] = {BackButtonDimension.x - 12.0f, BackButtonDimension.y + BackButtonDimension.height, 12.0f, 12.0f};
    BackButtonIndicatorDimension[3] = {BackButtonDimension.x + BackButtonDimension.width, BackButtonDimension.y + BackButtonDimension.height, 12.0f, 12.0f};

    for (int i = 0; i < 4; i++) {
        SettingContent[i] = &const_cast<std::string&>(ResourceManager::GetInstance().LoadPlaceholder("Setting" + std::to_string(i + 1)))[0];
        TextDimension[i] = MeasureTextEx(*ContentFont, SettingContent[i], ContentFontSize, 1.0f);
    }

    ContentDimension[0] = {ContainerDimension.x + (ContainerDimension.width - TextDimension[0].x) / 2, ContainerDimension.y + ContentMargin, TextDimension[0].x, TextDimension[0].y};
    TitleLeftIconDimension = {ContentDimension[0].x - ContentDimension[0].height - PaddingFromText, ContentDimension[0].y, ContentDimension[0].height, ContentDimension[0].height};
    TitleRightIconDimension = {ContentDimension[0].x + ContentDimension[0].width + PaddingFromText, ContentDimension[0].y, ContentDimension[0].height, ContentDimension[0].height};
    float ContentHeight = ContainerDimension.height - 2 * ContentMargin - ContentDimension[0].height - PaddingFromTitleContent;
    float PaddingTop = ContentHeight * (1.0f - MusicContainerPercentage - EffectContainerPercentage - LanguageContainerPercentage) / 3;
    MusicContainerDimension = {ContainerDimension.x + ContentMargin, ContentDimension[0].y + ContentDimension[0].height + PaddingTop + PaddingFromTitleContent, ContainerDimension.width - 2 * ContentMargin, ContentHeight * MusicContainerPercentage};
    ContentDimension[1] = {MusicContainerDimension.x, MusicContainerDimension.y, TextDimension[1].x, TextDimension[1].y};
    EffectContainerDimension = {MusicContainerDimension.x, MusicContainerDimension.y + MusicContainerDimension.height + PaddingTop + PaddingFromTitleContent, MusicContainerDimension.width, ContentHeight * EffectContainerPercentage};
    ContentDimension[2] = {EffectContainerDimension.x, EffectContainerDimension.y, TextDimension[2].x, TextDimension[2].y};
    LanguageContainerDimension = {MusicContainerDimension.x, EffectContainerDimension.y + EffectContainerDimension.height + PaddingTop + PaddingFromTitleContent, MusicContainerDimension.width, ContentHeight * LanguageContainerPercentage};
    ContentDimension[3] = {LanguageContainerDimension.x, LanguageContainerDimension.y, TextDimension[3].x, TextDimension[3].y};

    Vector2 ItemSize = {FlagIconSize.x * FlagScale + FlagMargin * 2.0f + FlagPadding * 2.0f, FlagIconSize.y * FlagScale + FlagMargin * 2.0f + FlagPadding * 2.0f};
    int ItemPerLine = 1;
    while (LanguageContainerDimension.width / (ItemPerLine * ItemSize.x) >= 1.0f) {
        ItemPerLine++;
        if (ItemPerLine > NumOfLanguage) {
            break;
        }
    }
    --ItemPerLine;
    float RLPadding = (LanguageContainerDimension.width - ItemPerLine * ItemSize.x) / 2;
    for (int i = 0; i < NumOfLanguage; i++) {
        FlagDimension[i] = {LanguageContainerDimension.x + RLPadding + ItemSize.x * (i % ItemPerLine) + FlagMargin + FlagPadding, ContentDimension[3].y + ContentDimension[3].height + ItemSize.y * (i / ItemPerLine) + FlagMargin + FlagPadding, FlagIconSize.x * FlagScale, FlagIconSize.y * FlagScale};
        FlagBound[i] = {FlagDimension[i].x - FlagMargin, FlagDimension[i].y - FlagMargin, FlagDimension[i].width + 2.0f * FlagMargin, FlagDimension[i].height + 2.0f * FlagMargin};
    }

    CurrentLanguageFlagDimension = {ContainerDimension.x + ContainerDimension.width - FlagDimension[0].width - ContentMargin, ContentDimension[3].y + (ContentDimension[3].height - FlagDimension[0].height) / 2,FlagDimension[0].width, FlagDimension[0].height};
}

void SettingState::Exit()
{
}
