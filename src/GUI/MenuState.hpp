#pragma once
#include "raylib.h"
#include "MenuItem.hpp"
#include "MenuType.hpp"
#include <string>
#include <vector>
#include <memory>

// Forward declaration
class MenuDirector;

class MenuState {
protected:
    MenuDirector* director;
    std::string title;
    Vector2 position;
    Vector2 size;
    std::vector<MenuItem> items;

public:
    MenuState(MenuDirector* director) : director(director) {}
    virtual ~MenuState() = default;

    virtual void enter() = 0;
    virtual void exit() = 0;
    virtual void update() = 0;
    virtual void draw() = 0;

    // Common functionality for all menus
    void drawBase() {
        // Draw title
        DrawText(title.c_str(), 
                position.x + size.x/2 - MeasureText(title.c_str(), 40)/2,
                50,
                40,
                BLACK);

        // Draw back button
        Rectangle backButton = {20, 20, 100, 30};
        DrawRectangleRec(backButton, LIGHTGRAY);
        DrawRectangleLinesEx(backButton, 1, BLACK);
        DrawText("Back", 45, 25, 20, BLACK);

        // Draw menu items
        for (const auto& item : items) {
            item.draw();
        }
    }

    bool isBackButtonClicked() {
        Rectangle backButton = {20, 20, 100, 30};
        return CheckCollisionPointRec(GetMousePosition(), backButton) && IsMouseButtonPressed(MOUSE_LEFT_BUTTON);
    }
}; 