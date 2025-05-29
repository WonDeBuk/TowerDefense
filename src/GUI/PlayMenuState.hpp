#pragma once
#include "MenuState.hpp"
#include "MenuDirector.hpp"
#include "MenuType.hpp"

class PlayMenuState : public MenuState {
private:
    struct MapInfo {
        std::string name;
        Rectangle bounds;
        Texture2D preview;
    };
    std::vector<MapInfo> maps;

public:
    PlayMenuState(MenuDirector* director, int screenWidth, int screenHeight)
        : MenuState(director)
    {
        title = "Select Map";
        position = Vector2{0, 0};
        size = Vector2{(float)screenWidth, (float)screenHeight};

        float buttonWidth = 200.0f;
        float buttonHeight = 150.0f;
        float startX = screenWidth/2.0f - buttonWidth - 20.0f;
        float startY = screenHeight/2.0f - buttonHeight - 20.0f;

        // Initialize map buttons in a 2x2 grid
        maps = {
            {"Forest", Rectangle{startX, startY, buttonWidth, buttonHeight}, 
             AssetManager::getInstance().loadTexture("maps/forest_preview.png")},
            {"Desert", Rectangle{startX + buttonWidth + 40.0f, startY, buttonWidth, buttonHeight},
             AssetManager::getInstance().loadTexture("maps/desert_preview.png")},
            {"Snow", Rectangle{startX, startY + buttonHeight + 40.0f, buttonWidth, buttonHeight},
             AssetManager::getInstance().loadTexture("maps/snow_preview.png")},
            {"Volcano", Rectangle{startX + buttonWidth + 40.0f, startY + buttonHeight + 40.0f, buttonWidth, buttonHeight},
             AssetManager::getInstance().loadTexture("maps/volcano_preview.png")}
        };
    }

    ~PlayMenuState() {
        // Unload textures
        for (const auto& map : maps) {
            AssetManager::getInstance().unloadTexture(map.preview);
        }
    }

    void enter() override {
        // Nothing special needed for play menu enter
    }

    void exit() override {
        // Nothing special needed for play menu exit
    }

    void update() override {
        if (isBackButtonClicked()) {
            director->transitionTo(MenuType::MAIN);
            return;
        }

        Vector2 mousePos = GetMousePosition();
        for (const auto& map : maps) {
            if (CheckCollisionPointRec(mousePos, map.bounds) && IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) {
                // Start game with selected map
                // TODO: Implement game start with selected map
                break;
            }
        }
    }

    void draw() override {
        drawBase();

        // Draw map previews
        for (const auto& map : maps) {
            DrawRectangleRec(map.bounds, WHITE);
            DrawRectangleLinesEx(map.bounds, 1, BLACK);
            DrawTexturePro(map.preview, 
                          Rectangle{0, 0, (float)map.preview.width, (float)map.preview.height},
                          map.bounds,
                          Vector2{0, 0}, 0, WHITE);
            
            // Draw map name
            DrawText(map.name.c_str(),
                    map.bounds.x + map.bounds.width/2 - MeasureText(map.name.c_str(), 20)/2,
                    map.bounds.y + map.bounds.height + 10,
                    20, BLACK);
        }
    }
}; 