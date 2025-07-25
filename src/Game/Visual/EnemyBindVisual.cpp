#include "EnemyBindVisual.h"
#include "Utils/ResourceManager.h"
#include "Game/GameManager.h"
#include "Game/VisualManager.h"
#include <iostream>

Visual* EnemyBindVisual::EnemyBindVisualTemplateBuildAndGet(const std::string& _VisualPath, const int& _TotalFrameCount, const Vector2& _OffsetPosition, const Vector2& _VisualSize, const int& _OwnerEnemyID, const int& _VisualUpdatePace) {
	static EnemyBindVisual EnemyBindVisualTemplate;
	EnemyBindVisualTemplate.DisplayVisual = const_cast<Texture*>(&ResourceManager::GetInstance().LoadTexture(_VisualPath));
	EnemyBindVisualTemplate.TotalFrameCount = _TotalFrameCount;
	EnemyBindVisualTemplate.GenericPosition = _OffsetPosition;
	EnemyBindVisualTemplate.VisualSize = _VisualSize;
	EnemyBindVisualTemplate.VisualUpdatePace = _VisualUpdatePace;
	EnemyBindVisualTemplate.FrameWidth = 1.0f * EnemyBindVisualTemplate.DisplayVisual->width / EnemyBindVisualTemplate.TotalFrameCount;
	EnemyBindVisualTemplate.OwnerEnemyID = _OwnerEnemyID;
	return reinterpret_cast<Visual*>(&EnemyBindVisualTemplate);
}

void EnemyBindVisual::Update() {
	VisualTimer++;
	if (VisualTimer >= TotalFrameCount * VisualUpdatePace || GameManager::GetInstance().GetEnemyPoolTracker()[OwnerEnemyID] == false) {
		VisualManager::GetInstance().DeleteVisual(VisualID);
		return;
	}
}

void EnemyBindVisual::Draw() const {
	int CurrentFrameState = VisualTimer / VisualUpdatePace;
	Enemy* BindEnemy = GameManager::GetInstance().GetEnemyByID(OwnerEnemyID);
	if (BindEnemy == nullptr) return;
	Vector2 EnemyPosition = BindEnemy->GetEnemyCurrentPosition();
	DrawTexturePro(*DisplayVisual, { FrameWidth * CurrentFrameState, 0.0f, FrameWidth, 1.0f * DisplayVisual->height }, { EnemyPosition.x - GenericPosition.x, EnemyPosition.y - GenericPosition.y, VisualSize.x, VisualSize.y }, { 0.0f, 0.0f }, 0.0f, WHITE);
}