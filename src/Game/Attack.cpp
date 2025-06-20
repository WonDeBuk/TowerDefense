#include <Attack.h>

const AttackType& Attack::GetAttackType() const
{
    return Attack_Type;
}

void Attack::SetAttackType(const AttackType& __Type)
{
    Attack_Type = __Type;
}

void Attack::SetTargetEnemy(const size_t& __Enemy)
{
    TargetEnemy = __Enemy;
}

void Attack::SetAttackPosition(const Vector2& __Position)
{
    AttackStartPosition = __Position;
}

void Attack::Update()
{
    float DifferenceX = AttackStartPosition.x - AttackArrivePosition.x;
    float DifferenceY = AttackStartPosition.y - AttackArrivePosition.y;
    Position.x += DifferenceX * Macro[Attack_Type].Speed;
    Position.y += DifferenceY * Macro[Attack_Type].Speed;
    AngleState = static_cast<size_t>(atan2f(DifferenceY, DifferenceX)) / 5 * 5;
}