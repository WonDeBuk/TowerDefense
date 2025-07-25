#include "Game/Attack.h"
#include "Utils/Define.h"

class Orbit : public Attack {
private:
	static constexpr int LIST_SIZE = 8;
	static Orbit OrbitTemplate;
	float PathProgress;
	float MaxRadius;
	int StartOfList;
	int EndOfList;
	int ListSize;
	int TotalPierce;
	BlackListData BlackList[LIST_SIZE];
public:
	static const Attack* OrbitTemplateBuildAndGet(const Vector2& _AttackStartPosition, const Vector2& _AttackDestinationPosition, const float& _AttackMovementSpeed, const float& _AttackDamage, const int& _AttackEnemyID, const int& _AttackOwnTowerID, const float& _StartingAngle, const float& _MaxRadius, const int& _Lifespan, const int& _TotalPierce);
	void Update() override;
	void Draw() const override;
};