#include "VisualManager.h"
#include "Utils/ResourceManager.h"
#include "Game/Visual.h"
#include "Game/Visual/TowerBindVisual.h"
#include "Game/Visual/EnemyBindVisual.h"

char VisualManager::VisualPool[MAX_VISUAL_AMOUNT][MAX_VISUAL_SIZE];
bool VisualManager::VisualPoolTracker[MAX_VISUAL_AMOUNT] = { false };

VisualManager::VisualManager() {

}

VisualManager& VisualManager::GetInstance() {
	static VisualManager Instance;
	return Instance;
}

void VisualManager::AddVisual(const VisualType& _VisualType, const Visual* _VisualTemplate) {
	if (_VisualTemplate == nullptr) return;
	int EmptySlotID = -1;
	for (int i = 0; i < MAX_VISUAL_AMOUNT; i++) {
		if (VisualPoolTracker[i] == false) {
			EmptySlotID = i;
			break;
		}
	}

	Visual* NewVisualObject = nullptr;
	if (EmptySlotID == -1) return;
	switch (_VisualType) {
	case VisualType::PLAIN:
		NewVisualObject = new (VisualPool[EmptySlotID]) Visual(*const_cast<Visual*>(_VisualTemplate));
		break;
	case VisualType::TOWER_BIND:
		NewVisualObject = new (VisualPool[EmptySlotID]) TowerBindVisual(*reinterpret_cast<TowerBindVisual*>(const_cast<Visual*>(_VisualTemplate)));
		break;
	case VisualType::ENEMY_BIND:
		NewVisualObject = new (VisualPool[EmptySlotID]) EnemyBindVisual(*reinterpret_cast<EnemyBindVisual*>(const_cast<Visual*>(_VisualTemplate)));
		break;
	}

	NewVisualObject->SetVisualID(EmptySlotID);
	VisualPoolTracker[EmptySlotID] = true;
}

void VisualManager::DeleteVisual(const int& _VisualID) {
	if (_VisualID >= 0 && _VisualID < MAX_VISUAL_AMOUNT) VisualPoolTracker[_VisualID] = false;
}

void VisualManager::Update() {
	for (int i = 0; i < MAX_VISUAL_AMOUNT; i++) {
		if (VisualPoolTracker[i]) reinterpret_cast<Visual*>(VisualPool[i])->Update();
	}
}

void VisualManager::Draw() const {
	for (int i = 0; i < MAX_VISUAL_AMOUNT; i++) {
		if (VisualPoolTracker[i]) reinterpret_cast<Visual*>(VisualPool[i])->Draw();
	}
}