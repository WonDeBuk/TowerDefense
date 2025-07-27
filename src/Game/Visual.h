#pragma once

#include "Utils/Define.h"
#include <raylib.h>
#include <string>

class Visual {
protected:
	int VisualID;
	int TotalFrameCount;
	int VisualTimer;
	int VisualUpdatePace;
	float FrameWidth;
	Texture2D* DisplayVisual;
	Vector2 GenericPosition;
	Vector2 VisualSize;
public:
	static const Visual* VisualTemplateBuildAndGet(const std::string& _VisualPath, const int& _TotalFrameCount, const Vector2& _GenericPosition, const Vector2& _VisualSize, const int& _VisualUpdatePace = 5);
	static const Visual* VisualTemplateBuildAndGet(const TextureData& _VisualData, const Vector2& _GenericPosition, const int& _VisualUpdatePace = 5);
	Visual();

	virtual void SetVisualID(const int& _VisualID);
	virtual void Update();
	virtual void Draw() const;
};