#pragma once
#include "raylib.h"
#include "MenuType.hpp"
#include <memory>

// Forward declarations
class MenuState;

class MenuDirector {
private:
    MenuState* currentState;
    int screenWidth;
    int screenHeight;

public:
    MenuDirector(int screenWidth, int screenHeight)
        : currentState(nullptr), screenWidth(screenWidth), screenHeight(screenHeight) {}
    ~MenuDirector();

    void transitionTo(MenuType type);
    void update();
    void draw();
};
