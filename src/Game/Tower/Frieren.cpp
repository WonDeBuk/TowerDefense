#include "Frieren.h"
#include "../GameManager.h"

#define nncncn 7

void Frieren::SkillLevel1() {
    GameManager::GetInstance().AddAttack(AttackType::PROJECTILE, Projectile::ProjectileTemplateBuildAndGet(MousePosition, EnemyFuturePosition1, TempAttackMovementSpeed, TempAttackDamage, Found->GetEnemyID(), 0));
    GameManager::GetInstance().AddAttack(AttackType::PROJECTILE, Projectile::ProjectileTemplateBuildAndGet(MousePosition, EnemyFuturePosition2, TempAttackMovementSpeed, TempAttackDamage, Found->GetEnemyID(), 0));
}

void Frieren::SkillLevel3() {
    GameManager::GetInstance().AddAttack(AttackType::PROJECTILE, Projectile::ProjectileTemplateBuildAndGet(MousePosition + random, EnemyFuturePosition, TempAttackMovementSpeed, TempAttackDamage, Found->GetEnemyID(), 0));
}

void FindMultipleTarget() {
    ...
    ...

}

void Frieren::UpdateLevel1()
{
    FindTarget();

    TowerAnimationState = IDLE, CAST
	if (TowerAnimationState == CAST && AnimationTimer > 0) {
		Timer--;
		if (Shots && AnimationTimer % 5 == 0) {
			if (Frieren::Skill()) {
				Shots--;
			}
		}
	}
 	else if (TowerAnimationState == CAST && AnimationTimer == 0) {
		AnimationState = IDLE;
	}
	if (TowerCurrentCooldown >= TowerCooldown) {
		if (Frieren::Skill()) {
            AnimationState = CAST;
			Shots = ShotsAmount;
			AnimationTimer = 5 * ShotsAmounts;
		}
	}

	else TowerCurrentCooldown++;

    TowerCurrentCooldown;
    TowerCooldown;

    if (GameManager::Timer % 7) {
        ++FrameState %= 10;
    }
}


void Frieren::SetTowerCurrentLevel(const int &_Level)
{
    switch (_Level)
    {
    case 1:
        TowerDamage = ...;
        TowerCooldown = ...;
        TowerRange = ...;
        BaseShots = 1;
        Skill = &Frieren::SkillLevel1();
        UpdateFrieren = &Frieren::UpdateLevel1();
        break;
    case 2:
        TowerDamage = ...;
        TowerCooldown = ...;
        TowerRange = ...;
        BaseShots = 2;
        Skill = &Frieren::SkillLevel1();
        UpdateFrieren = &Frieren::UpdateLevel2();
    Case 3:
        TowerDamage = ...;
        TowerCooldown = ...;
        TowerRange = ...;
        BaseShots = 10;
        Skill = &Frieren::SkillLevel3();
        UpdateFrieren = &Frieren::UpdateLevel3();
    default:
        break;
    }
}

void Frieren::Update()
{
    Frieren::UpdateFrieren();
}

