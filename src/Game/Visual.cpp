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
	VisualTemplate.FrameWidth = 1.0f * VisualTemplate.DisplayVisual->width / VisualTemplate.TotalFrameCount;
	VisualTemplate.VisualSize = _VisualSize;
	VisualTemplate.VisualUpdatePace = _VisualUpdatePace;
	return &VisualTemplate;
}

//Each frame must be a square to use this method !!!
const Visual* Visual::VisualTemplateBuildAndGet(const TextureData& _VisualData, const Vector2& _GenericPosition, const int& _VisualUpdatePace) {
	static Visual VisualTemplate;
	VisualTemplate.DisplayVisual = _VisualData.LinkedTexture;
	VisualTemplate.TotalFrameCount = _VisualData.MaxFrameCount;
	VisualTemplate.FrameWidth = 1.0f * VisualTemplate.DisplayVisual->width / VisualTemplate.TotalFrameCount;
	VisualTemplate.VisualSize = { _VisualData.ScaleFactor * VisualTemplate.FrameWidth, _VisualData.ScaleFactor * VisualTemplate.FrameWidth };
	VisualTemplate.GenericPosition = { _GenericPosition.x - VisualTemplate.VisualSize.x / 2, _GenericPosition.y - VisualTemplate.VisualSize.y / 2 };
	VisualTemplate.VisualUpdatePace = _VisualUpdatePace;
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