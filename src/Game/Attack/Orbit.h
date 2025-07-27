#include "Game/Attack.h"
#include "Game/Tower.h"
#include "Utils/Defined.h"

class Orbit : public Tower {
private:
	static Orbit OrbitTemplate;
	float StartAngle;
	float Radius;
	int BlackListSize;
	BlackListData BlackList[5];
public:
	static const Attack* OrbitTemplateBuildAndGet(const Vector2& _AttackStartPosition, const Vector2& _AttackDestinationPosition, const float& _AttackMovementSpeed, const float& _AttackDamage, const int& _TargetEnemyID, const int& _AttackOwnTowerID, const size_t& _Lifespan);
	void Update() override;
	void Draw() override;
};