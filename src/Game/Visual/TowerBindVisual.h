#pragma once

#include "Game/Visual.h"

class TowerBindVisual : public Visual {
private:
	int OwnerTowerID;
public:
	static Visual* TowerBindVisualTemplateBuildAndGet(const std::string& _VisualPath, const int& _TotalFrameCount, const Vector2& _OffsetPosition, const Vector2& _VisualSize, const int& _OwnerTowerID, const int& _VisualUpdatePace = 5);

	void Update() override;
	void Draw() const override;
};