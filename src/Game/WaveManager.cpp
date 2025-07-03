#include "WaveManager.h"

WaveManager& WaveManager::GetInstance() {
	static WaveManager Instance;
	return Instance;
}

std::string TypeToString(EnemyType _type) {
	switch (_type) {
	case ENEMY_SLIME:
		return "ENEMY_SLIME";
	}
}

void WaveManager::SwitchTo(const WaveLayoutType& _type) {
	CurrentLayout = &WaveLayout::GetInstance(_type);
}

bool WaveManager::Invoke() {
	CurrentWave++;
	if (CurrentWave >= CurrentLayout->GetMaxWave()) return false;
	CurrentEnemy = 0;
	WaveTime = 0;
	IntermissionTime = 15 * GetFPS();
	return true;
}

void WaveManager::Update() {
	if (IntermissionTime > 0) {
		IntermissionTime--;
		if (CheckCollisionPointRec(GetMousePosition(), SkipButton) && IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) {
			IntermissionTime = 0;
		}
		return;
	} 
	else if (CurrentEnemy == CurrentLayout->GetMaxEnemyInWave(CurrentWave) && GameManager::GetInstance().GetTotalEnemy() == 0) {
		Invoke();
		return;
	}

	if (CurrentWave >= CurrentLayout->GetMaxWave()) return;
	std::cout << WaveTime << ' ';
	if (CurrentLayout->GetIndexLayout(CurrentWave)[CurrentEnemy].Time == WaveTime) {
		GameManager::GetInstance().AddEnemy(CurrentLayout->GetIndexLayout(CurrentWave)[CurrentEnemy].Type);
		CurrentEnemy++;
	}
	WaveTime++;
}

void WaveManager::Draw() {
	if (IntermissionTime) {
		DrawText(("Intermission: " + std::to_string(IntermissionTime)).c_str(), 15, 150, 20, WHITE);
		DrawRectangleRec(SkipButton, GRAY);
		DrawText("Skip?", 15, 300, 30, WHITE);
	}
	if (CurrentWave >= CurrentLayout->GetMaxWave()) DrawText("END WAVE.", 15, 100, 30, WHITE);
	else DrawText(("Wave " + std::to_string(CurrentWave + 1 - (IntermissionTime > 0))).c_str(), 15, 100, 30, WHITE);

}