#include "Visual.h"
#include "Utils/ResourceManager.h"
#include "Game/VisualManager.h"
#include <iostream>

Visual::Visual() {
	VisualTimer = 0;
}

const Visual* Visual::VisualTemplateBuildAndGet(const std::string& _VisualPath, const int& _TotalFrameCount, const Vector2& _GenericPosition, const Vector2& _VisualSize, const int& _VisualUpdatePace) {
	static Visual VisualTemplate;
	VisualTemplate.DisplayVisual = const_cast<Texture*>(&ResourceManager::GetInstance().LoadTexture(_VisualPath));
	VisualTemplate.TotalFrameCount = _TotalFrameCount;
	VisualTemplate.GenericPosition = _GenericPosition;
	VisualTemplate.VisualSize = _VisualSize;
	VisualTemplate.VisualUpdatePace = _VisualUpdatePace;
	VisualTemplate.FrameWidth = 1.0f * VisualTemplate.DisplayVisual->width / VisualTemplate.TotalFrameCount;;
	return &VisualTemplate;
}

void Visual::SetVisualID(const int& _VisualID) {
	VisualID = _VisualID;
}

void Visual::Update() {
	VisualTimer++;
	if (VisualTimer >= VisualUpdatePace * TotalFrameCount) {
		VisualManager::GetInstance().DeleteVisual(VisualID);
		return;
	}
}

void Visual::Draw() const {
	int CurrentFrameState = VisualTimer / VisualUpdatePace;
	DrawTexturePro(*DisplayVisual, { FrameWidth * CurrentFrameState, 0.0f, FrameWidth, 1.0f * DisplayVisual->height }, { GenericPosition.x, GenericPosition.y, VisualSize.x, VisualSize.y }, {0.0f, 0.0f}, 0.0f, WHITE);
}