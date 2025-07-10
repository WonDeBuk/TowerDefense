#include "DictionaryState.h"
#include "../Director.h"
#include "././Utils/MathUtils.hpp"
#include "././Utils/ResourceManager.h"
#include <iostream>
#include <assert.h>

DictionaryState::DictionaryState() : IsBackButtonHover(false){
    // Calculate Container Dimension
    ContainerDimension = {(float) SCREEN_WIDTH * RLPaddingPercent, (float) SCREEN_HEIGHT * TDPaddingPercent, (float) SCREEN_WIDTH * (1.0f - 2 * RLPaddingPercent), (float) SCREEN_HEIGHT * (1.0f - 2 * TDPaddingPercent)};
    DictionaryContainerDimension = {ContainerDimension.x, ContainerDimension.y, ContainerDimension.width * DictionaryContainerPercentage, ContainerDimension.height};
    float PaddingWidth = ContainerDimension.width * (1.0f - InformationContainerPercentage - DictionaryContainerPercentage);
    InformationContainerDimension = {ContainerDimension.x + DictionaryContainerDimension.width + PaddingWidth, ContainerDimension.y, ContainerDimension.width * InformationContainerPercentage, ContainerDimension.height};
    
    // Load Font and Texture
    ContentFont = &ResourceManager::GlobalFont;
    DictionaryIconTexture[0] = const_cast<Texture2D*>(&ResourceManager::GetInstance().LoadTexture("ui/DictionaryIconLeft.png"));
    DictionaryIconTexture[1] = const_cast<Texture2D*>(&ResourceManager::GetInstance().LoadTexture("ui/DictionaryIconRight.png"));
    InformationIconTexture = const_cast<Texture2D*>(&ResourceManager::GetInstance().LoadTexture("ui/InformationIcon.png"));
    BackButtonIcon = const_cast<Texture2D*>(&ResourceManager::GetInstance().LoadTexture("ui/HomeButton.png"));
    BackButtonBoxIndicator = const_cast<Texture2D*>(&ResourceManager::GetInstance().LoadTexture("ui/BoxIndicator.png"));

    // Calculate Responsive Component
    DictionaryState::Enter();

    // Initialize The PagedContainer
    ChampionList = new ChampionListContainer({DictionaryContainerDimension.x + ContentMargin, DictionaryContainerDimension.y + DictionaryTitleSize.y + PaddingFromTitleContent + ContentMargin, DictionaryContainerDimension.width - 2.0f * ContentMargin, DictionaryContainerDimension.height - DictionaryTitleSize.y - PaddingFromTitleContent - 2.0f * ContentMargin}, 3, 3, const_cast<ChampionData*>(ResourceManager::ChampionDataList), 12);
}

void DictionaryState::Update()
{
    Vector2 MousePosition = GetMousePosition();
    if (CheckCollisionPointRec(MousePosition, BackButtonDimension)) {
        IsBackButtonHover = true;
        if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) {
            Director::GetInstance().TransitionTo(RENDER_STATE::MAIN);
        }
    } else {
        IsBackButtonHover = false;
    }
    ChampionList->Update();
}

void DictionaryState::Draw() const {
    size_t Time = Director::GetInstance().GetTime();

    // Parallax Background Draw
    RenderState::Draw();

    // Container Background Draw
    DrawRectangleRec(DictionaryContainerDimension, {0, 0, 0, 100});
    DrawRectangleRec(InformationContainerDimension, {0, 0, 0, 100});

    // Title Draw
    DrawTextEx(*ContentFont, DictionaryTitle, DictionaryTitlePosition, ContentFontSize, 1.0f, WHITE);
    DrawTextEx(*ContentFont, InformationTitle, InformationTitlePosition, ContentFontSize, 1.0f, WHITE);
    
    // Icon Draw
    for (int i = 0; i < 2; i++) {
        DrawTexturePro(*DictionaryIconTexture[i], {0.0f, 0.0f, (float) DictionaryIconTexture[i]->width, (float) DictionaryIconTexture[i]->height}, DictionaryIconDimension[i], {0.0f, 0.0f}, 0.0f, WHITE);
        DrawTexturePro(*InformationIconTexture, {0.0f, 0.0f, (float) InformationIconTexture->width, (float) InformationIconTexture->height}, InformationIconDimension[i], {0.0f, 0.0f}, 0.0f, WHITE);
    }

    // Back Button Draw
    DrawRectanglePro(BackButtonDimension, {0.0f, 0.0f}, 0.0f, {0, 0, 0, 100});
    DrawTexturePro(*BackButtonIcon, {0.0f, 0.0f, 64.0f, 64.0f}, ButtonIconDimension, {0.0f, 0.0f}, 0.0f, WHITE);
    DrawTextEx(*ContentFont, BackContent, BackContentPosition, ContentFontSize, 1.0f, WHITE);
    if (IsBackButtonHover) {
        for (int i = 0; i < 4; i++) {
            DrawTexturePro(*BackButtonBoxIndicator, {12.0f * (i % 2), 24.0f * ((Time / 7) % 3) + 12.0f * (i / 2), 12.0f, 12.0f}, BackButtonIndicatorDimension[i], {0.0f, 0.0f}, 0.0f, WHITE);
        }
    }

    // Paged Container Draw
    ChampionList->Draw();
}

void DictionaryState::Enter() {
    // Load Content
    DictionaryTitle = &const_cast<std::string&>(ResourceManager::GetInstance().LoadPlaceholder("DictionaryTitle"))[0];
    InformationTitle = &const_cast<std::string&>(ResourceManager::GetInstance().LoadPlaceholder("InformationTitle"))[0];
    BackContent = &const_cast<std::string&>(ResourceManager::GetInstance().LoadPlaceholder("BackButton"))[0];
    
    // Calculate Content Size
    DictionaryTitleSize = MeasureTextEx(*ContentFont, DictionaryTitle, ContentFontSize, 1.0f);
    InformationTitleSize = MeasureTextEx(*ContentFont, InformationTitle, ContentFontSize, 1.0f);
    BackContentSize = MeasureTextEx(*ContentFont, BackContent, ContentFontSize, 1.0f);
    
    // Back Button Properties Calculate
    BackButtonDimension = {ContainerDimension.x, ContainerDimension.y - BackContentSize.y - PaddingBotContainer, 32.0f + BackContentSize.x + PaddingFromText * 2.0f, BackContentSize.y};
    BackContentPosition = {BackButtonDimension.x + 32.0f + PaddingFromText, BackButtonDimension.y};
    ButtonIconDimension = {BackButtonDimension.x, BackButtonDimension.y, 48.0f, 48.0f};
    BackButtonIndicatorDimension[0] = {BackButtonDimension.x - 12.0f, BackButtonDimension.y - 12.0f, 12.0f, 12.0f};
    BackButtonIndicatorDimension[1] = {BackButtonDimension.x + BackButtonDimension.width, BackButtonDimension.y - 12.0f, 12.0f, 12.0f};
    BackButtonIndicatorDimension[2] = {BackButtonDimension.x - 12.0f, BackButtonDimension.y + BackButtonDimension.height, 12.0f, 12.0f};
    BackButtonIndicatorDimension[3] = {BackButtonDimension.x + BackButtonDimension.width, BackButtonDimension.y + BackButtonDimension.height, 12.0f, 12.0f};
    
    // Title and Icon Calculate
    DictionaryTitlePosition = {DictionaryContainerDimension.x + (DictionaryContainerDimension.width - DictionaryTitleSize.x) / 2, ContainerDimension.y + ContentMargin};
    InformationTitlePosition = {InformationContainerDimension.x + (InformationContainerDimension.width - InformationTitleSize.x) / 2, InformationContainerDimension.y + ContentMargin};
    DictionaryIconDimension[0] = {DictionaryTitlePosition.x - DictionaryTitleSize.y - PaddingFromText, DictionaryTitlePosition.y, DictionaryTitleSize.y, DictionaryTitleSize.y};
    DictionaryIconDimension[1] = {DictionaryTitlePosition.x + DictionaryTitleSize.x + PaddingFromText, DictionaryTitlePosition.y, DictionaryTitleSize.y, DictionaryTitleSize.y};
    InformationIconDimension[0] = {InformationTitlePosition.x - InformationTitleSize.y - PaddingFromText, InformationTitlePosition.y, InformationTitleSize.y, InformationTitleSize.y};
    InformationIconDimension[1] = {InformationTitlePosition.x + InformationTitleSize.x + PaddingFromText, InformationTitlePosition.y, InformationTitleSize.y, InformationTitleSize.y};
}

void DictionaryState::Exit()
{
}
