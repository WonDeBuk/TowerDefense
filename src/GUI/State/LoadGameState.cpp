#include "LoadGameState.h"
#include "../Director.h"
#include "././Utils/ResourceManager.h"

LoadGameState::LoadGameState() : IsBackButtonHover(false) {
    // Calculate Container Dimension
    ContainerDimension = {(float) SCREEN_WIDTH * RLPaddingPercent, (float) SCREEN_HEIGHT * TDPaddingPercent, (float) SCREEN_WIDTH * (1.0f - 2 * RLPaddingPercent), (float) SCREEN_HEIGHT * (1.0f - 2 * TDPaddingPercent)};
    ContinueContainerDimension = {ContainerDimension.x, ContainerDimension.y, ContainerDimension.width * ContinueContainerPercentage, ContainerDimension.height};
    float PaddingWidth = ContainerDimension.width * (1.0f - InformationContainerPercentage - ContinueContainerPercentage);
    InformationContainerDimension = {ContainerDimension.x + ContinueContainerDimension.width + PaddingWidth, ContainerDimension.y, ContainerDimension.width * InformationContainerPercentage, ContainerDimension.height};

    // Load Font and Texture
    ContentFont = &ResourceManager::GlobalFont;
    ContinueIconTexture[0] = const_cast<Texture2D*>(&ResourceManager::GetInstance().LoadTexture("ui/ContinueIconLeft.png"));
    ContinueIconTexture[1] = const_cast<Texture2D*>(&ResourceManager::GetInstance().LoadTexture("ui/ContinueIconRight.png"));
    InformationIconTexture[0] = const_cast<Texture2D*>(&ResourceManager::GetInstance().LoadTexture("ui/InformationIconLeft.png"));
    InformationIconTexture[1] = const_cast<Texture2D*>(&ResourceManager::GetInstance().LoadTexture("ui/InformationIconRight.png"));
    BackButtonIcon = const_cast<Texture2D*>(&ResourceManager::GetInstance().LoadTexture("ui/HomeButton.png"));
    BackButtonBoxIndicator = const_cast<Texture2D*>(&ResourceManager::GetInstance().LoadTexture("ui/BoxIndicator.png"));

    // Calculate Responsive Component
    LoadGameState::Enter();
}

void LoadGameState::Update() {
    Vector2 MousePosition = GetMousePosition();
    if (CheckCollisionPointRec(MousePosition, BackButtonDimension)) {
        IsBackButtonHover = true;
        if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) {
            Director::GetInstance().TransitionTo(RENDER_STATE::MAIN);
        }
    } else {
        IsBackButtonHover = false;
    }
}

void LoadGameState::Draw() const {
    size_t Time = Director::GetInstance().GetTime();

    // Parallax Background Draw
    RenderState::Draw();

    // Container Background Draw
    DrawRectangleRec(ContinueContainerDimension, {0, 0, 0, 100});
    DrawRectangleRec(InformationContainerDimension, {0, 0, 0, 100});

    // Title Draw
    DrawTextEx(*ContentFont, ContinueTitle, ContinueTitlePosition, ContentFontSize, 1.0f, WHITE);
    DrawTextEx(*ContentFont, InformationTitle, InformationTitlePosition, ContentFontSize, 1.0f, WHITE);

    // Icon Draw
    for (int i = 0; i < 2; i++) {
        DrawTexturePro(*ContinueIconTexture[i], {0.0f, 0.0f, (float) ContinueIconTexture[i]->width, (float) ContinueIconTexture[i]->height}, ContinueIconDimension[i], {0.0f, 0.0f}, 0.0f, WHITE);
        DrawTexturePro(*InformationIconTexture[i], {0.0f, 0.0f, (float) InformationIconTexture[i]->width, (float) InformationIconTexture[i]->height}, InformationIconDimension[i], {0.0f, 0.0f}, 0.0f, WHITE);
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
}

void LoadGameState::Enter() {
    // Load Content
    ContinueTitle = &const_cast<std::string&>(ResourceManager::GetInstance().LoadPlaceholder("ContinueTitle"))[0];
    InformationTitle = &const_cast<std::string&>(ResourceManager::GetInstance().LoadPlaceholder("InformationTitle"))[0];
    BackContent = &const_cast<std::string&>(ResourceManager::GetInstance().LoadPlaceholder("BackButton"))[0];

    // Calculate Content Size
    ContinueTitleSize = MeasureTextEx(*ContentFont, ContinueTitle, ContentFontSize, 1.0f);
    InformationTitleSize = MeasureTextEx(*ContentFont, InformationTitle, ContentFontSize, 1.0f);
    BackContentSize = MeasureTextEx(*ContentFont, BackContent, ContentFontSize, 1.0f);

    // Back Button Properties Calculate
    BackButtonDimension = {ContainerDimension.x, ContainerDimension.y - BackContentSize.y - PaddingBotContainer, 32.0f + BackContentSize.x + PaddingFromText * 2.0f, BackContentSize.y};
    ButtonIconDimension = {BackButtonDimension.x, BackButtonDimension.y, 48.0f, 48.0f};
    BackContentPosition = {BackButtonDimension.x + 32.0f + PaddingFromText, BackButtonDimension.y};
    BackButtonIndicatorDimension[0] = {BackButtonDimension.x - 12.0f, BackButtonDimension.y - 12.0f, 12.0f, 12.0f};
    BackButtonIndicatorDimension[1] = {BackButtonDimension.x + BackButtonDimension.width, BackButtonDimension.y - 12.0f, 12.0f, 12.0f};
    BackButtonIndicatorDimension[2] = {BackButtonDimension.x - 12.0f, BackButtonDimension.y + BackButtonDimension.height, 12.0f, 12.0f};
    BackButtonIndicatorDimension[3] = {BackButtonDimension.x + BackButtonDimension.width, BackButtonDimension.y + BackButtonDimension.height, 12.0f, 12.0f};

    // Title and Icon Calculate
    ContinueTitlePosition = {ContinueContainerDimension.x + (ContinueContainerDimension.width - ContinueTitleSize.x) / 2, ContainerDimension.y + ContentMargin};
    InformationTitlePosition = {InformationContainerDimension.x + (InformationContainerDimension.width - InformationTitleSize.x) / 2, InformationContainerDimension.y + ContentMargin};
    ContinueIconDimension[0] = {ContinueTitlePosition.x - ContinueTitleSize.y - PaddingFromText, ContinueTitlePosition.y, ContinueTitleSize.y, ContinueTitleSize.y};
    ContinueIconDimension[1] = {ContinueTitlePosition.x + ContinueTitleSize.x + PaddingFromText, ContinueTitlePosition.y, ContinueTitleSize.y, ContinueTitleSize.y};
    InformationIconDimension[0] = {InformationTitlePosition.x - InformationTitleSize.y - PaddingFromText, InformationTitlePosition.y, InformationTitleSize.y, InformationTitleSize.y};
    InformationIconDimension[1] = {InformationTitlePosition.x + InformationTitleSize.x + PaddingFromText, InformationTitlePosition.y, InformationTitleSize.y, InformationTitleSize.y};
}

void LoadGameState::Exit() {
    
}
