#pragma once

#include "Utils/Define.h"
#include <raylib.h>

class VisualManager {
private:
	static ImageVisualData ImageVisualContainer[MAX_VISUAL_AMOUNT];
	static bool ImageVisualTracker[MAX_VISUAL_AMOUNT];

	VisualManager();
public:
	static VisualManager& GetInstance();

	void AddImageVisual(const int& _TotalFrames, const std::string& _TexturePath, const Vector2& _Position, const Vector2& _Size);

	void Update();
	void Draw();
};