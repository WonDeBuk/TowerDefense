#pragma once

#include "Game/Attack.h"

class ProjectileAttack : public Attack {
public:
	ProjectileAttack(const size_t&, const size_t&);
	void Draw();
	void Update();
};