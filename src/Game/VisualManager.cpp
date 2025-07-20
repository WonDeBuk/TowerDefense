#include "VisualManager.h"
#include "Utils/ResourceManager.h"

ImageVisualData VisualManager::ImageVisualContainer[MAX_VISUAL_AMOUNT] = { 0 };
bool VisualManager::ImageVisualTracker[MAX_VISUAL_AMOUNT] = { false };

VisualManager::VisualManager() {

}

VisualManager& VisualManager::GetInstance() {
	static VisualManager Instance;
	return Instance;
}

void VisualManager::AddImageVisual(const int& _TotalFrames, const std::string& _TexturePath, const Vector2& _Position, const Vector2& _Size) {
	Texture2D* ValidTexture = const_cast<Texture2D*>(&ResourceManager::GetInstance().LoadTexture(_TexturePath));
	if (ValidTexture == nullptr) return;
	for (int i = 0; i < MAX_VISUAL_AMOUNT; i++) {
		if (ImageVisualTracker[i] == false) {
			ImageVisualTracker[i] = true;
			ImageVisualContainer[i].TotalFrame = _TotalFrames;
			ImageVisualContainer[i].Display = ValidTexture;
			ImageVisualContainer[i].Position.x = _Position.x;
			ImageVisualContainer[i].Position.y = _Position.y;
			ImageVisualContainer[i].Size.x = _Size.x;
			ImageVisualContainer[i].Size.y = _Size.y;
			ImageVisualContainer[i].Timer = 0;
			break;
		}
	}
}

void VisualManager::Update() {
	for (int i = 0; i < MAX_VISUAL_AMOUNT; i++) {
		if (ImageVisualTracker[i]) {
			ImageVisualContainer[i].Timer++;
			if (ImageVisualContainer[i].Timer >= ImageVisualContainer[i].TotalFrame * VISUAL_UPDATE_PACE) ImageVisualTracker[i] = false;
		}
	}
}

void VisualManager::Draw() {
	for (int i = 0; i < MAX_VISUAL_AMOUNT; i++) {
		if (ImageVisualTracker[i]) {
			ImageVisualData Current = ImageVisualContainer[i];
			float CellWidth = Current.Display->width / Current.TotalFrame;
			DrawTexturePro(*Current.Display,
			{ CellWidth * (Current.Timer / VISUAL_UPDATE_PACE), 0.0f, CellWidth, 1.0f * Current.Display->height }, {Current.Position.x, Current.Position.y, Current.Size.x, Current.Size.y},
			{ 0.0f, 0.0f }, 0.0f, WHITE);
		}
	}
}