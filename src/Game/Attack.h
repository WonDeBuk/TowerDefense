#pragma once

#include <raylib.h>
#include <math.h>
#include <string>

enum AttackType
{
    Projectile_ARROW,
    Projectile_BULLET,
    NONE
};

typedef struct AttackMacro
{
    Texture2D* AttackMacroTexture;
    float Speed;

    AttackMacro(std::string TextureString, float SpeedValue)
    {
        AttackMacroTexture = &LoadTexture(TextureString.c_str());
        Speed = SpeedValue;
    }
};

const AttackMacro Macro[2] =
{
    AttackMacro(ASSETS_PATH + "textures/ui/Arrow.png", 2.0f),
    AttackMacro(ASSETS_PATH + "textures/ui/Bullet.png", 2.0f)
};

class Attack
{
    private:
        Vector2 AttackStartPosition;
        Vector2 AttackArrivePosition;
        Vector2 Position;
        size_t TargetEnemy;
        AttackType Attack_Type;
        size_t AngleState;
    public:
        void Draw() const;

        void SetAttackType(const AttackType&);
        void SetTargetEnemy(const size_t&);
        void SetAttackPosition(const Vector2&);

        void Update();

        const AttackType& GetAttackType() const;
};