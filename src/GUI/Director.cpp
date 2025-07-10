#include "Director.h"
#include <iostream>
#include "State/MainState.h"
#include "State/PlayState.h"
#include "State/GameState.h"
#include "State/WaitingState.h"
#include "State/DictionaryState.h"
#include "State/LoadGameState.h"
#include "State/SettingState.h"

Director::Director() : Time(0) {
    
}

void Director::Init() {
    MenuBuffer = new RenderState*[7];
    MenuBuffer[0] = new MainState;
    MenuBuffer[1] = new PlayState;
    MenuBuffer[2] = new LoadGameState;
    MenuBuffer[3] = new DictionaryState;
    MenuBuffer[4] = new SettingState;
    MenuBuffer[5] = new WaitingState;
    MenuBuffer[6] = new GameState;
    CurrentState = MenuBuffer[0];
}

Director& Director::GetInstance() {
    static Director Instance;
    return Instance;
}

void Director::TransitionTo(const RENDER_STATE &__State) {
    CurrentState->Exit();

    switch (__State) {
        case RENDER_STATE::MAIN:
            CurrentState = MenuBuffer[0];
            break;
        case RENDER_STATE::PLAY:
            CurrentState = MenuBuffer[1];
            break;
        case RENDER_STATE::LOAD_GAME:
            CurrentState = MenuBuffer[2];
            break;
        case RENDER_STATE::DICTIONARY:
            CurrentState = MenuBuffer[3];
            break;
        case RENDER_STATE::SETTING:
            CurrentState = MenuBuffer[4];
            break;
        case RENDER_STATE::WAITING:
            CurrentState = MenuBuffer[5];
            break;
        case RENDER_STATE::GAME:
            CurrentState = MenuBuffer[6];
            break;
        default:
            break;
    }

    CurrentState->Enter();
}

void Director::Update() {
    Time++;
    if (CurrentState) {
        CurrentState->Update();
    }
}

void Director::Draw() const {
    if (CurrentState) {
        CurrentState->Draw();
    }
}

size_t Director::GetTime() const {
    return Time;
}

Director::~Director() {
    Director::TransitionTo(RENDER_STATE::WAITING);
    for (int i = 0; i < 5; i++)
    {
        delete MenuBuffer[i];
    }
    delete[] MenuBuffer;
}
