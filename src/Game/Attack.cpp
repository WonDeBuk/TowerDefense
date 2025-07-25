#include "Attack.h"
#include "././Utils/MathUtils.hpp"
#include "GameManager.h"
#include <iostream>

Attack::Attack() {}

void Attack::Update() {
    Lifespan--;
}

void Attack::SetAttackID(const int &_AttackID) {
    AttackID = _AttackID;
}

void Attack::AttackKill() {
    GameManager::GetInstance().KillAttack(AttackID);
}

void Attack::SetAttackMovementSpeed(const float& _AttackMovementSpeed) {
    AttackMovementSpeed = _AttackMovementSpeed;
}

bool Attack::CheckCollisionPierceType(BlackListData _BlackList[], const int& _MaxComponent, int& _StartOfList, int& _EndOfList, int& _ListSize, int& _TotalPierce, const int& _EnemyID) {
	if (_TotalPierce <= 0) {
		Attack::AttackKill();
		return false;
	}
	Enemy* Object = GameManager::GetInstance().GetEnemyByID(_EnemyID);
	if (CheckCollisionPointRec(AttackCurrentPosition, Object->GetHitBox())) {
		int k = _StartOfList;
		bool IsInList = false;
		while (k != _EndOfList) {
			int Time = _BlackList[k].TimeAdded;
			if (Time - Lifespan >= 30) {
				_BlackList[k].EnemyID = -1;
				_StartOfList = (_StartOfList + 1) % _MaxComponent;
				_ListSize--;
			}
			else if (_BlackList[k].EnemyID == Object->GetEnemyID()) {
				IsInList = true;
				break;
			}

			k = (k + 1) % _MaxComponent;
		}
		if (!IsInList) {
			if (_ListSize == _MaxComponent) {
				_StartOfList = (_StartOfList + 1) % _MaxComponent;
				_ListSize--;
			}
			_BlackList[_EndOfList].EnemyID = Object->GetEnemyID();
			_BlackList[_EndOfList].TimeAdded = Lifespan;
			Object->OnDamage(AttackDamage);
			_EndOfList = (_EndOfList + 1) % _MaxComponent;
			_ListSize++;
			_TotalPierce--;

			if (_TotalPierce <= 0) {
				Attack::AttackKill();
				return false;
			}
		}
	}
	return true;
}