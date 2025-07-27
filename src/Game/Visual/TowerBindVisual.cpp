#include "TowerBindVisual.h"
#include "Utils/ResourceManager.h"
#include "Game/GameManager.h"
#include "Game/VisualManager.h"
#include <iostream>

Visual* TowerBindVisual::TowerBindVisualTemplateBuildAndGet(const std::string& _VisualPath, const int& _TotalFrameCount, const Vector2& _OffsetPosition, const Vector2& _VisualSize, const int& _OwnerTowerID, const int& _VisualUpdatePace) {
	static TowerBindVisual TowerBindVisualTemplate;
	TowerBindVisualTemplate.DisplayVisual = const_cast<Texture*>(&ResourceManager::GetInstance().LoadTexture(_VisualPath));
	TowerBindVisualTemplate.TotalFrameCount = _TotalFrameCount;
	TowerBindVisualTemplate.GenericPosition = _OffsetPosition;
	TowerBindVisualTemplate.VisualSize = _VisualSize;
	TowerBindVisualTemplate.VisualUpdatePace = _VisualUpdatePace;
	TowerBindVisualTemplate.FrameWidth = 1.0f * TowerBindVisualTemplate.DisplayVisual->width / TowerBindVisualTemplate.TotalFrameCount;
	TowerBindVisualTemplate.OwnerTowerID = _OwnerTowerID;
	return reinterpret_cast<Visual*>(&TowerBindVisualTemplate);
}

void TowerBindVisual::Update() {
	VisualTimer++;
	if (VisualTimer >= TotalFrameCount * VisualUpdatePace - 1 || GameManager::GetInstance().GetTowerPlotAndPoolTracker()[OwnerTowerID] == false) {
		VisualManager::GetInstance().DeleteVisual(VisualID);
		return;
	}
}

void TowerBindVisual::Draw() const {
	int CurrentFrameState = VisualTimer / VisualUpdatePace;
	Tower* BindTower = GameManager::GetInstance().GetTowerByID(OwnerTowerID);
	if (BindTower == nullptr) return;
	Vector2 TowerPosition = BindTower->GetTowerPosition();
	DrawTexturePro(*DisplayVisual, { FrameWidth * CurrentFrameState, 0.0f, FrameWidth, 1.0f * DisplayVisual->height }, { TowerPosition.x - GenericPosition.x, TowerPosition.y - GenericPosition.y, VisualSize.x, VisualSize.y }, { 0.0f, 0.0f }, 0.0f, WHITE);
}