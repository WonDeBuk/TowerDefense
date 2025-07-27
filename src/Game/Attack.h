#pragma once

#include <raylib.h>
#include "Utils/Define.h"

class Attack {
protected:
    static const TextureData NullTexture;

    Vector2 GeneralUseVector;
    Vector2 AttackCurrentPosition;              // Vị trí hiện tại của Attack : các dạng Projectile là vị trí mà Attack đang bay hiện tại, đối với các dạng Area thì có thể thay đổi tùy vào mục đích sử dụng

    float AttackMovementSpeed;                  // Tốc độ di chuyển của Attack : Các dạng Projectile thì ý nghĩa đã quá rõ, còn đối với các dạng Area có thể sử dụng tùy mục đích nhưng đa số sẽ là 0
    float AttackDamage;                         // Sát thưởng của Attack

    int AttackID;                               // Vị trí của Attack trong AttackPool
    int OwnerID;                               // Có thể sử dụng để biến đổi trạng thái hoạt ảnh, ví dụ như Attack laser thì khi mà Laser bắn đến mục tiêu thì kết thúc hoạt ảnh casting
    int Lifespan;                               // Thời gian kể từ khi xuất hiện của Attack
    
    int FrameState;
    float FrameSize;
    TextureData AttackTexture;
    TextureData DeathTexture;
public:
    Attack();
    ~Attack();

    virtual void OnDeath();

    virtual void Update();
    virtual void Draw() const = 0;
  
    const Vector2& GetAttackCurrentPosition() { return AttackCurrentPosition; }
    void SetAttackID(const int& _AttackID);

    void AttackKill();
};