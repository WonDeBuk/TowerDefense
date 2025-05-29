#include "MenuDirector.hpp"
#include "MainMenuState.hpp"
#include "DictionaryMenuState.hpp"
#include "PlayMenuState.hpp"
#include "LoadGameMenuState.hpp"
#include "SettingsMenuState.hpp"

MenuDirector::~MenuDirector() {
    if (currentState) {
        delete currentState;
        currentState = nullptr;
    }
}

void MenuDirector::transitionTo(MenuType type) {
    if (currentState) {
        currentState->exit();
        delete currentState;
        currentState = nullptr;
    }

    switch (type) {
        case MenuType::MAIN:
            currentState = new MainMenuState(this, screenWidth, screenHeight);
            break;
        case MenuType::DICTIONARY:
            currentState = new DictionaryMenuState(this, screenWidth, screenHeight);
            break;
        case MenuType::PLAY:
            currentState = new PlayMenuState(this, screenWidth, screenHeight);
            break;
        case MenuType::LOAD_GAME:
            currentState = new LoadGameMenuState(this, screenWidth, screenHeight);
            break;
        case MenuType::SETTINGS:
            currentState = new SettingsMenuState(this, screenWidth, screenHeight);
            break;
    }

    if (currentState) {
        currentState->enter();
    }
}

void MenuDirector::update() {
    if (currentState) {
        currentState->update();
    }
}

void MenuDirector::draw() {
    if (currentState) {
        currentState->draw();
    }
} 