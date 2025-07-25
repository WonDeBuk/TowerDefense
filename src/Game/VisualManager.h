#pragma once

#include "Utils/Define.h"
#include <raylib.h>
#include "Game/Visual.h"

class VisualManager {
private:
	static char VisualPool[MAX_VISUAL_AMOUNT][MAX_VISUAL_SIZE];
	static bool VisualPoolTracker[MAX_VISUAL_AMOUNT];

	VisualManager();
public:
	static VisualManager& GetInstance();

	void AddVisual(const VisualType& _VisualType, const Visual* _VisualTemplate);
	void DeleteVisual(const int& _VisualID);

	void Update();
	void Draw() const;
};