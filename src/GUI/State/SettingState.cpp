#include "SettingState.h"
#include <iostream>
#include "../Director.h"
#include "././Utils/MathUtils.hpp"
#include "././Utils/SoundManager.h"
#include <algorithm>

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
    SoundIcon = const_cast<Texture2D*>(&ResourceManager::GetInstance().LoadTexture("ui/SoundIcon.png"));
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
                SoundManager::GetInstance().PlaySFX("click.ogg");
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
            SoundManager::GetInstance().PlaySFX("click.ogg");
            Director::GetInstance().TransitionTo(RENDER_STATE::MAIN);
        }
    } else {
        IsBackButtonHover = false;
    }

    // BGM Volume Slider
    Rectangle BGMHandle = { BGMVolumeSlider.x + (SoundManager::GetInstance().GetBGMVolume() * (SliderWidth - SliderHandleSize)), BGMVolumeSlider.y - (SliderHandleSize - SliderHeight) / 2, SliderHandleSize, SliderHandleSize };


    if (CheckCollisionPointRec(MousePosition, BGMVolumeSlider)) {
        if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) {
            BGMHandle = { MousePosition.x, MousePosition.y, SliderHandleSize, SliderHandleSize };
        }
    }

    if (CheckCollisionPointRec(MousePosition, BGMVolumeSlider)) {
        if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) {
            isDraggingBGM = true;
        }
    }

    if (isDraggingBGM) {
        if (IsMouseButtonDown(MOUSE_LEFT_BUTTON)) {
            float newVolume = (MousePosition.x - BGMVolumeSlider.x) / (SliderWidth - SliderHandleSize);
            newVolume = std::clamp(newVolume, 0.0f, 1.0f);
            SoundManager::GetInstance().SetBGMVolume(newVolume);
        }
        else {
            isDraggingBGM = false;
        }
    }

    // SFX Volume Slider
    Rectangle SFXHandle = { SFXVolumeSlider.x + (SoundManager::GetInstance().GetSFXVolume() * (SliderWidth - SliderHandleSize)), SFXVolumeSlider.y - (SliderHandleSize - SliderHeight) / 2, SliderHandleSize, SliderHandleSize };

    if (CheckCollisionPointRec(MousePosition, SFXVolumeSlider)) {
        if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) {
            SoundManager::GetInstance().PlaySFX("click.ogg");
            SFXHandle = { MousePosition.x, MousePosition.y, SliderHandleSize, SliderHandleSize };
        }
    }

    if (CheckCollisionPointRec(MousePosition, SFXHandle)) {
        if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) {
            isDraggingSFX = true;
        }
    }

    if (isDraggingSFX) {
        if (IsMouseButtonDown(MOUSE_LEFT_BUTTON)) {
            float newVolume = (MousePosition.x - SFXVolumeSlider.x) / (SliderWidth - SliderHandleSize);
            newVolume = std::clamp(newVolume, 0.0f, 1.0f);
            SoundManager::GetInstance().SetSFXVolume(newVolume);
        }
        else {
            isDraggingSFX = false;
        }
    }
    if (CheckCollisionPointRec(MousePosition, BGMVolumeIconDimension)) {
        if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) {
            SoundManager::GetInstance().ToggleBGMMute();
        }
    }

    if (CheckCollisionPointRec(MousePosition, SFXVolumeIconDimension)) {
        if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) {
            SoundManager::GetInstance().ToggleSFXMute();
        }
    }
}

void SettingState::Draw() const
{
    size_t Time = Director::GetInstance().GetTime();
    RenderState::Draw();
    DrawRectangleRounded(ContainerDimension, 0.2f, 0, {0, 0, 0, 100});
    DrawRectangleRoundedLinesEx(ContainerDimension, 0.2f, 0, 2.0f, WHITE);

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

    // Back Button Draw
    DrawRectangleRounded(BackButtonDimension, 0.4f, 0, {0, 0, 0, 100});
    DrawRectangleRoundedLinesEx(BackButtonDimension, 0.4f, 0, 2.0f, WHITE);
    DrawTexturePro(*BackButtonIcon, {0.0f, 0.0f, 64.0f, 64.0f}, ButtonIconDimension, {0.0f, 0.0f}, 0.0f, WHITE);
    DrawTextEx(*ContentFont, BackContent, BackContentPosition, ButtonFontSize, 1.0f, WHITE);
    if (IsBackButtonHover) {
        for (int i = 0; i < 4; i++) {
            DrawTexturePro(*BackButtonBoxIndicator, {12.0f * (i % 2), 24.0f * ((Time / 7) % 3) + 12.0f * (i / 2), 12.0f, 12.0f}, BackButtonIndicatorDimension[i], {0.0f, 0.0f}, 0.0f, WHITE);
        }
    }
    DrawTexturePro(*FlagIcon[(int) CurrentStateLanguage], {0.0f, 0.0f, FlagIconSize.x, FlagIconSize.y}, CurrentLanguageFlagDimension, {0.0f, 0.0f}, 0.0f, WHITE);

    // Draw volume sliders
    DrawRectangleRec(BGMVolumeBar, { 100, 100, 100, 255 });
    DrawRectangleRec(SFXVolumeBar, { 100, 100, 100, 255 });

    // Draw BGM slider handle
    Rectangle BGMHandle = { BGMVolumeSlider.x + (SoundManager::GetInstance().GetBGMVolume() * (SliderWidth - SliderHandleSize)), BGMVolumeSlider.y - (SliderHandleSize - SliderHeight) / 2, SliderHandleSize, SliderHandleSize };
    DrawRectangleRec(BGMHandle, WHITE);

    // Draw SFX slider handle
    Rectangle SFXHandle = { SFXVolumeSlider.x + (SoundManager::GetInstance().GetSFXVolume() * (SliderWidth - SliderHandleSize)), SFXVolumeSlider.y - (SliderHandleSize - SliderHeight) / 2, SliderHandleSize, SliderHandleSize };
    DrawRectangleRec(SFXHandle, WHITE);

    // Draw sound icons
    DrawTexturePro(*SoundIcon, { 0.0f, 0.0f, (float)SoundIcon->width, (float)SoundIcon->height }, BGMVolumeIconDimension, { 0.0f, 0.0f }, 0.0f, WHITE);
    DrawTexturePro(*SoundIcon, { 0.0f, 0.0f, (float)SoundIcon->width, (float)SoundIcon->height }, SFXVolumeIconDimension, { 0.0f, 0.0f }, 0.0f, WHITE);
}

void SettingState::Enter()
{
    BackContent = &const_cast<std::string&>(ResourceManager::GetInstance().LoadPlaceholder("BackButton"))[0];

    BackContentSize = MeasureTextEx(*ContentFont, BackContent, ButtonFontSize, 1.0f);

    const float BackButtonContentMargin = 5.0f;
    const float PaddingFromLeft = 48.0f;
    BackButtonDimension = {ContainerDimension.x + PaddingFromLeft, ContainerDimension.y - BackContentSize.y - BackButtonContentMargin * 2.0f - PaddingBotContainer, ButtonFontSize + BackContentSize.x + BackButtonContentMargin * 3.0f, ButtonFontSize + BackButtonContentMargin * 2.0f};
    ButtonIconDimension = {BackButtonDimension.x + BackButtonContentMargin, BackButtonDimension.y + BackButtonContentMargin, ButtonFontSize, ButtonFontSize};
    BackContentPosition = {BackButtonDimension.x + ButtonIconDimension.width + BackButtonContentMargin * 2, BackButtonDimension.y + BackButtonContentMargin};
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

    BGMVolumeSlider = { MusicContainerDimension.x + ContentMargin * 4, MusicContainerDimension.y + ContentMargin * 4, SliderWidth, SliderHeight };
    SFXVolumeSlider = { EffectContainerDimension.x + ContentMargin * 4, EffectContainerDimension.y + ContentMargin * 4, SliderWidth, SliderHeight };
    BGMVolumeBar = { BGMVolumeSlider.x, BGMVolumeSlider.y, SliderWidth, SliderHeight };
    SFXVolumeBar = { SFXVolumeSlider.x, SFXVolumeSlider.y, SliderWidth, SliderHeight };
    BGMVolumeIconDimension = { BGMVolumeSlider.x - IconSize - IconMargin, BGMVolumeSlider.y + (SliderHeight - IconSize) / 2, IconSize, IconSize };
    SFXVolumeIconDimension = { SFXVolumeSlider.x - IconSize - IconMargin, SFXVolumeSlider.y + (SliderHeight - IconSize) / 2, IconSize, IconSize };

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
