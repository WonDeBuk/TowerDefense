#include "BulletAttack.h"
#include "Game/GameManager.h"

BulletAttack::BulletAttack() {
	Type = ATTACK_BULLET;
	Damage = BASE_DAMAGE;
	Speed = BASE_SPEED;
}

BulletAttack::~BulletAttack() {
	Attack::~Attack();
}

void BulletAttack::SetOrigin(const Vector2& _og) {
	Attack::SetOrigin(_og);
}

void BulletAttack::SetDestination(const Vector2& _dest) {
	Attack::SetDestination(_dest);
}

void BulletAttack::Update() {
	//if (Lifespan >= BASE_LIFESPAN) Die();
	//Lifespan += GetFrameTime();

	//GameManager& GameM = GameManager::GetInstance();
	//
	//const char(&EnemeyList)[MAX_ENEMY][sizeof(Enemy)] = GameM.GetEnemyList();
	//const bool(&EnemyUsed)[MAX_ENEMY] = GameM.GetEnemyUsed();
	//for (size_t i = 0; i < MAX_ENEMY; i++) {
	//	if (EnemyUsed[i] == true) {

	//	}
	//}
}

void BulletAttack::Draw() {
	
}

void BulletAttack::OnExpired() {

}

void BulletAttack::Die() {
	Attack::Die();
}