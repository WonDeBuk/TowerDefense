#include "Director.h"
#include "State/DictionaryState.h"
#include "State/LoadGameState.h"
#include "State/MainState.h"
#include "State/PlayState.h"
#include "State/SettingState.h"
#include "State/WaitingState.h"
#include "State/GameState.h"

Director& Director::GetInstance()
{
    static Director Instance;
    return Instance;
}

void Director::TransitionTo(const RENDER_STATE &__State)
{

    if (CurrentState) {
        delete CurrentState;
        CurrentState = nullptr;
    }

    switch (__State) {
        case RENDER_STATE::MAIN:
            CurrentState = new MainState;
            break;
        case RENDER_STATE::DICTIONARY:
            CurrentState = new DictionaryState;
            break;
        case RENDER_STATE::PLAY:
            CurrentState = new PlayState;
            break;
        case RENDER_STATE::LOAD_GAME:
            CurrentState = new LoadGameState;
            break;
        case RENDER_STATE::SETTING:
            CurrentState = new SettingState;
            break;
        case RENDER_STATE::GAME:
            CurrentState = new GameState;
            break;
        case RENDER_STATE::WAITING:
            CurrentState = new WaitingState;
            break;
        default:
            break;
    }
}

void Director::Update() {
    if (CurrentState) {
        CurrentState->Update();
    }
}

void Director::Draw() {
    if (CurrentState) {
        CurrentState->Draw();
    }
}

Director::~Director()
{
    if (CurrentState) {
        delete CurrentState;
        CurrentState = nullptr;
    }
}
