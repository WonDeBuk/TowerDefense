#pragma once

#include "Game/Enemy.h"

class Revenant : public Enemy {
private:
	static constexpr float BASE_HEALTH = 18500.0f;
	static constexpr float BASE_SPEED = 0.55f;
	static constexpr int MAX_SPAWN = 6;
	int SpawnIndex;
	int WaypointAtSpawnTime;
	float WaypointUnit;
	Vector2 WaypointDirection;
protected:
	void UpdateAnimation() override;
public:
	Revenant();

	void OnHeal(const float& _Heal) override;
	void Update() override;
	void Draw() const override;
	void DrawHealthBar() const override;
};