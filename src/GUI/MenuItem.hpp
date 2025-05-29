#pragma once
#include "raylib.h"
#include <string>
#include <functional>

class MenuItem {
private:
    std::string text;
    Rectangle bounds;
    bool isHovered;

public:
    MenuItem(const std::string& text, Rectangle bounds)
        : text(text), bounds(bounds), isHovered(false) {}

    void draw() const {
        Color bgColor = isHovered ? SKYBLUE : WHITE;
        DrawRectangleRec(bounds, bgColor);
        DrawRectangleLinesEx(bounds, 1, BLACK);
        
        // Center text in button
        float textX = bounds.x + bounds.width/2 - MeasureText(text.c_str(), 20)/2;
        float textY = bounds.y + bounds.height/2 - 10;
        DrawText(text.c_str(), textX, textY, 20, BLACK);
    }

    bool isClicked(Vector2 mousePos) {
        isHovered = CheckCollisionPointRec(mousePos, bounds);
        return isHovered && IsMouseButtonPressed(MOUSE_LEFT_BUTTON);
    }

    const Rectangle& getBounds() const {
        return bounds;
    }

    const std::string& getText() const {
        return text;
    }
}; 