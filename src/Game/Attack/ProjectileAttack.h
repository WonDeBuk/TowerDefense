#pragma once

#include "Game/Attack.h"

class ProjectileAttack : public Attack {
public:
	ProjectileAttack(const unsigned int&, const float&);
	void Draw();
	void Update();
};