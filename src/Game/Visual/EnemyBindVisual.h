#pragma once

#include "Game/Visual.h"

class EnemyBindVisual : public Visual {
private:
	int OwnerEnemyID;
public:
	static Visual* EnemyBindVisualTemplateBuildAndGet(const std::string& _VisualPath, const int& _TotalFrameCount, const Vector2& _OffsetPosition, const Vector2& _VisualSize, const int& _OwnerEnemyID, const int& _VisualUpdatePace = 5);

	void Update() override;
	void Draw() const override;
};