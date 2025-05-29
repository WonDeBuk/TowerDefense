#pragma once
#include "MenuState.hpp"
#include "MenuDirector.hpp"
#include "../Utils/MathUtils.hpp"
#include "MenuType.hpp"

class SettingsMenuState : public MenuState {
private:
    float musicVolume;
    float effectsVolume;
    int languageIndex;
    Rectangle musicSlider;
    Rectangle effectsSlider;
    std::vector<std::string> languages;
    Rectangle languageNext;
    Rectangle languagePrev;

public:
    SettingsMenuState(MenuDirector* director, int screenWidth, int screenHeight)
        : MenuState(director),
          musicVolume(1.0f),
          effectsVolume(1.0f),
          languageIndex(0),
          languages({"English", "Español", "Français", "Deutsch", "日本語", "한국어", "中文"})
    {
        title = "Settings";
        position = Vector2{0, 0};
        size = Vector2{(float)screenWidth, (float)screenHeight};

        float sliderWidth = 300.0f;
        float sliderHeight = 20.0f;
        float startY = screenHeight/2.0f - 100.0f;

        // Initialize sliders
        musicSlider = Rectangle{
            screenWidth/2.0f - sliderWidth/2.0f,
            startY,
            sliderWidth,
            sliderHeight
        };

        effectsSlider = Rectangle{
            screenWidth/2.0f - sliderWidth/2.0f,
            startY + 80.0f,
            sliderWidth,
            sliderHeight
        };

        // Initialize language selection buttons
        float buttonWidth = 30.0f;
        float buttonHeight = 30.0f;
        languagePrev = Rectangle{
            screenWidth/2.0f - 100.0f - buttonWidth,
            startY + 160.0f,
            buttonWidth,
            buttonHeight
        };
        languageNext = Rectangle{
            screenWidth/2.0f + 100.0f,
            startY + 160.0f,
            buttonWidth,
            buttonHeight
        };
    }

    void enter() override {
        // Load current settings
        // TODO: Implement settings loading
    }

    void exit() override {
        // Save current settings
        // TODO: Implement settings saving
    }

    void update() override {
        if (isBackButtonClicked()) {
            director->transitionTo(MenuType::MAIN);
            return;
        }

        Vector2 mousePos = GetMousePosition();

        // Handle music volume slider
        if (CheckCollisionPointRec(mousePos, musicSlider) && IsMouseButtonDown(MOUSE_LEFT_BUTTON)) {
            musicVolume = (mousePos.x - musicSlider.x) / musicSlider.width;
            musicVolume = Clamp(musicVolume, 0.0f, 1.0f);
            // TODO: Update music volume
        }

        // Handle effects volume slider
        if (CheckCollisionPointRec(mousePos, effectsSlider) && IsMouseButtonDown(MOUSE_LEFT_BUTTON)) {
            effectsVolume = (mousePos.x - effectsSlider.x) / effectsSlider.width;
            effectsVolume = Clamp(effectsVolume, 0.0f, 1.0f);
            // TODO: Update effects volume
        }

        // Handle language selection
        if (CheckCollisionPointRec(mousePos, languagePrev) && IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) {
            languageIndex = (languageIndex - 1 + languages.size()) % languages.size();
            // TODO: Update language
        }
        if (CheckCollisionPointRec(mousePos, languageNext) && IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) {
            languageIndex = (languageIndex + 1) % languages.size();
            // TODO: Update language
        }
    }

    void draw() override {
        drawBase();

        // Draw music volume control
        DrawText("Music Volume", 
                size.x/2 - MeasureText("Music Volume", 20)/2,
                musicSlider.y - 30,
                20, BLACK);
        DrawRectangleRec(musicSlider, LIGHTGRAY);
        DrawRectangle(musicSlider.x, musicSlider.y,
                     musicSlider.width * musicVolume, musicSlider.height,
                     SKYBLUE);
        DrawRectangleLinesEx(musicSlider, 1, BLACK);

        // Draw effects volume control
        DrawText("Effects Volume",
                size.x/2 - MeasureText("Effects Volume", 20)/2,
                effectsSlider.y - 30,
                20, BLACK);
        DrawRectangleRec(effectsSlider, LIGHTGRAY);
        DrawRectangle(effectsSlider.x, effectsSlider.y,
                     effectsSlider.width * effectsVolume, effectsSlider.height,
                     SKYBLUE);
        DrawRectangleLinesEx(effectsSlider, 1, BLACK);

        // Draw language selection
        DrawText("Language",
                size.x/2 - MeasureText("Language", 20)/2,
                languagePrev.y - 30,
                20, BLACK);
        
        // Draw language navigation buttons
        DrawRectangleRec(languagePrev, LIGHTGRAY);
        DrawRectangleLinesEx(languagePrev, 1, BLACK);
        DrawText("<", languagePrev.x + 10, languagePrev.y + 5, 20, BLACK);

        DrawRectangleRec(languageNext, LIGHTGRAY);
        DrawRectangleLinesEx(languageNext, 1, BLACK);
        DrawText(">", languageNext.x + 10, languageNext.y + 5, 20, BLACK);

        // Draw current language
        DrawText(languages[languageIndex].c_str(),
                size.x/2 - MeasureText(languages[languageIndex].c_str(), 20)/2,
                languagePrev.y + 5,
                20, BLACK);
    }
}; 