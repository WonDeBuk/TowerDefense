#include "MainState.h"
#include "../Director.h"
#include "././Utils/ResourceManager.h"
#include "././Utils/SoundManager.h"
#include <iostream>
#include <string>

extern Font GlobalFont;

MainState::MainState()
{
    HoverIndex = -1;
    StateDirector = &Director::GetInstance();
    ContentFont = &ResourceManager::GlobalFont;
    BackgroundImage = const_cast<Texture2D*>(&ResourceManager::GetInstance().LoadTexture("ui/MainMenu.png"));
    Indicator = const_cast<Texture2D*>(&ResourceManager::GetInstance().LoadTexture("ui/LineIndicator.png"));
    BackgroundImageDimension = {0.0f, ((float) GetScreenHeight() - ((float) GetScreenWidth() / (float) BackgroundImage->width) * (float) BackgroundImage->height) / 2, (float) GetScreenWidth(), ((float) GetScreenWidth() / (float) BackgroundImage->width) * (float) BackgroundImage->height};
    MainState::Enter();
}

void MainState::Update()
{
    Vector2 MousePosition = GetMousePosition();

    for (int i = 0; i < 4; i++)
    {
        if (CheckCollisionPointRec(MousePosition, ButtonBound[i])) {
            if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) {
                SoundManager::GetInstance().PlaySFX("click.ogg");
                switch (i)
                {
                case 0:
                    StateDirector->TransitionTo(RENDER_STATE::PLAY);
                    break;
                case 1:
                    StateDirector->TransitionTo(RENDER_STATE::LOAD_GAME);
                    break;
                case 2:
                    StateDirector->TransitionTo(RENDER_STATE::DICTIONARY);
                    break;
                case 3:
                    StateDirector->TransitionTo(RENDER_STATE::SETTING);
                    break;
                default:
                    break;
                }
            }
            HoverIndex = i;
            RightIndicator = {ButtonBound[i].x + ButtonBound->width, ButtonBound[i].y, (ButtonBound[i].height / (float) 32.0f) * 16.0f, ButtonBound[i].height};
            LeftIndicator = {ButtonBound[i].x - RightIndicator.width, ButtonBound[i].y, RightIndicator.width, ButtonBound[i].height};
            break;
        }
        else {
            HoverIndex = -1;
        }
    }
}

void MainState::Draw() const
{
    size_t Time = StateDirector->GetTime();
    RenderState::Draw();
    DrawTexturePro(*BackgroundImage, {0.0f, 0.0f, (float) BackgroundImage->width, (float) BackgroundImage->height}, BackgroundImageDimension, {0.0f, 0.0f}, 0.0f, WHITE);

    for (int i = 0; i < 4; i++)
    {
        DrawTextEx(*ContentFont, ButtonContent[i], {ContentDimension[i].x, ContentDimension[i].y}, ButtonFontSize, 1.0f, WHITE);
    }

    if (HoverIndex != -1) {
        DrawTexturePro(*Indicator, {0.0f, 32.0f * ((Time / 7) % 3), 16.0f, 32.0f}, LeftIndicator, {0.0f, 0.0f}, 0.0f, WHITE);
        DrawTexturePro(*Indicator, {16.0f, 32.0f * ((Time / 7) % 3), 16.0f, 32.0f}, RightIndicator, {0.0f, 0.0f}, 0.0f, WHITE);
    }
}

void MainState::Enter()
{
    float HeightPadding = (BackgroundImageDimension.height / 4 - MeasureTextEx(*ContentFont, "0", ButtonFontSize , 1.0f).y) / 2;
    int MaxWidthContentIndex = 0;
    float MaxWidthContentWidth = -1.0f;
    for (int i = 0; i < 4; i++)
    {
        ButtonContent[i] = &const_cast<std::string&>(ResourceManager::GetInstance().LoadPlaceholder("MainButton" + std::to_string(i + 1)))[0];
        Vector2 TextDimension = MeasureTextEx(*ContentFont, ButtonContent[i], ButtonFontSize, 1.0f);
        ContentDimension[i] = {((float) GetScreenWidth() - TextDimension.x) / 2, BackgroundImageDimension.y + (BackgroundImageDimension.height / 4) * i + HeightPadding, TextDimension.x, TextDimension.y};
        if (TextDimension.x > MaxWidthContentWidth) {
            MaxWidthContentWidth = TextDimension.x;
            MaxWidthContentIndex = i;
        }
    }

    ButtonBound[MaxWidthContentIndex] = {ContentDimension[MaxWidthContentIndex].x - ButtonLRMargin, ContentDimension[MaxWidthContentIndex].y - ButtonTDMargin, MaxWidthContentWidth + ButtonLRMargin * 2, ContentDimension[MaxWidthContentIndex].height + ButtonTDMargin * 2};
    for (int i = 0; i < 4; i++)
    {
        ButtonBound[i] = ButtonBound[MaxWidthContentIndex];
        ButtonBound[i].y = ContentDimension[i].y - ButtonTDMargin;
    }
}

void MainState::Exit()
{
}
