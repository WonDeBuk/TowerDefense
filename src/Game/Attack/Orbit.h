#include "Game/Attack/Multi.h"
#include "Utils/Define.h"

class Orbit : public Multi {
private:
	int TargetID;
	float PathProgress;
	float CurrentRadius;
	float MaxRadius;
	float Angle;
public:
	Orbit();

	static const Attack* OrbitTemplateBuildAndGet(const TextureData& _AttackTexture, const Vector2& _AttackStartPosition, const Vector2& _AttackDestinationPosition, const float& _AttackMovementSpeed, const float& _AttackDamage, const int& _TargetEnemyID, const int& _OwnerID, const float& _StartingAngle, const float& _MaxRadius, const int& _Lifespan, const int& _TotalHit, const HitType& _HitType, const TextureData& _DeathTexture = Attack::NullTexture);
	void Update() override;
	void Draw() const override;
};