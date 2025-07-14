#include "GameState.h"
#include "././Utils/Define.h"
#include "raymath.h"
#include "././Game/GameManager.h"
#include "././Game/Attack/Projectile.h"
#include "././Game/Attack/Missile.h"
#include "././Game/WaveManager.h"
#include <iostream>

GameState::GameState() {
}

void GameState::Update() {
    GameManager::GetInstance().Update();
    WaveManager::Update();
}

void GameState::Draw() const {
    GameManager::GetInstance().Draw();
}
