#pragma once
#include "MenuState.hpp"
#include "MenuDirector.hpp"
#include "MenuType.hpp"

class MainMenuState : public MenuState {
public:
    MainMenuState(MenuDirector* director, int screenWidth, int screenHeight) 
        : MenuState(director) {
        title = "Tower Defense";
        position = Vector2{0, 0};
        size = Vector2{(float)screenWidth, (float)screenHeight};

        float buttonWidth = 200.0f;
        float buttonHeight = 40.0f;
        float startY = screenHeight/2.0f - 100.0f;

        // Add menu items
        items.emplace_back("Dictionary", 
            Rectangle{screenWidth/2.0f - buttonWidth/2.0f, startY, buttonWidth, buttonHeight});
        items.emplace_back("Play Game",
            Rectangle{screenWidth/2.0f - buttonWidth/2.0f, startY + 60.0f, buttonWidth, buttonHeight});
        items.emplace_back("Load Game",
            Rectangle{screenWidth/2.0f - buttonWidth/2.0f, startY + 120.0f, buttonWidth, buttonHeight});
        items.emplace_back("Settings",
            Rectangle{screenWidth/2.0f - buttonWidth/2.0f, startY + 180.0f, buttonWidth, buttonHeight});
    }

    void enter() override {
        // Nothing special needed for main menu enter
    }

    void exit() override {
        // Nothing special needed for main menu exit
    }

    void update() override {
        Vector2 mousePos = GetMousePosition();
        
        for (size_t i = 0; i < items.size(); i++) {
            if (items[i].isClicked(mousePos)) {
                switch (i) {
                    case 0: director->transitionTo(MenuType::DICTIONARY); break;
                    case 1: director->transitionTo(MenuType::PLAY); break;
                    case 2: director->transitionTo(MenuType::LOAD_GAME); break;
                    case 3: director->transitionTo(MenuType::SETTINGS); break;
                }
            }
        }
    }

    void draw() override {
        drawBase();
    }
}; 