#pragma once
#include "MenuState.hpp"
#include "MenuDirector.hpp"
#include "MenuType.hpp"
#include <filesystem>
#include <chrono>
#include <ctime>

class LoadGameMenuState : public MenuState {
private:
    struct SaveGameInfo {
        std::string filename;
        std::string displayName;
        Rectangle bounds;
    };
    std::vector<SaveGameInfo> saveGames;
    const float BUTTON_WIDTH = 400.0f;
    const float BUTTON_HEIGHT = 60.0f;
    const float BUTTON_SPACING = 20.0f;

    void refreshSaveGames(int screenWidth) {
        saveGames.clear();
        float startY = 150.0f;

        // List all save files in the saves directory
        std::filesystem::path savesDir = "saves";
        if (std::filesystem::exists(savesDir) && std::filesystem::is_directory(savesDir)) {
            for (const auto& entry : std::filesystem::directory_iterator(savesDir)) {
                if (entry.path().extension() == ".save") {
                    auto filename = entry.path().filename().string();
                    auto writeTime = std::filesystem::last_write_time(entry.path());
                    auto systemTime = std::chrono::system_clock::now();
                    auto timeT = std::chrono::system_clock::to_time_t(systemTime);
                    
                    char timeStr[100];
                    std::strftime(timeStr, sizeof(timeStr), "%Y-%m-%d %H:%M:%S", std::localtime(&timeT));
                    
                    SaveGameInfo info;
                    info.filename = filename;
                    info.displayName = filename.substr(0, filename.length() - 5) + " - " + timeStr;
                    info.bounds = Rectangle{
                        screenWidth/2.0f - BUTTON_WIDTH/2.0f,
                        startY,
                        BUTTON_WIDTH,
                        BUTTON_HEIGHT
                    };
                    
                    saveGames.push_back(info);
                    startY += BUTTON_HEIGHT + BUTTON_SPACING;
                }
            }
        }
    }

public:
    LoadGameMenuState(MenuDirector* director, int screenWidth, int screenHeight)
        : MenuState(director)
    {
        title = "Load Game";
        position = Vector2{0, 0};
        size = Vector2{(float)screenWidth, (float)screenHeight};
        refreshSaveGames(screenWidth);
    }

    void enter() override {
        refreshSaveGames(size.x);
    }

    void exit() override {
        // Nothing special needed for load game menu exit
    }

    void update() override {
        if (isBackButtonClicked()) {
            director->transitionTo(MenuType::MAIN);
            return;
        }

        Vector2 mousePos = GetMousePosition();
        for (const auto& save : saveGames) {
            if (CheckCollisionPointRec(mousePos, save.bounds) && IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) {
                // Load the selected save game
                // TODO: Implement save game loading
                break;
            }
        }
    }

    void draw() override {
        drawBase();

        // Draw save game list
        if (saveGames.empty()) {
            const char* noSavesText = "No saved games found";
            DrawText(noSavesText,
                    size.x/2 - MeasureText(noSavesText, 20)/2,
                    size.y/2 - 10,
                    20, DARKGRAY);
        } else {
            for (const auto& save : saveGames) {
                DrawRectangleRec(save.bounds, WHITE);
                DrawRectangleLinesEx(save.bounds, 1, BLACK);
                DrawText(save.displayName.c_str(),
                        save.bounds.x + 20,
                        save.bounds.y + save.bounds.height/2 - 10,
                        20, BLACK);
            }
        }
    }
}; 