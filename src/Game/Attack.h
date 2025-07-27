#pragma once

#include <raylib.h>

class Attack {
protected:
    Vector2 AttackStartPosition;              // Vị trí bắt đầu của Attack : các dạng Projectile là vị trí bắt đầu bắn của Tower, các dạng Area là vị trí của Target hoặc tùy vào mục đích
    Vector2 AttackDestinationPosition;        // Vị trí đích đến của Attack : các dạng Projectile là vị trí của Target, các dạng Area là vị trí của Target hoặc tùy vào mục đích
    Vector2 AttackCurrentPosition;            // Vị trí hiện tại của Attack : các dạng Projectile là vị trí mà Attack đang bay hiện tại, đối với các dạng Area thì có thể thay đổi tùy vào mục đích sử dụng

    float AttackMovementSpeed;                // Tốc độ di chuyển của Attack : Các dạng Projectile thì ý nghĩa đã quá rõ, còn đối với các dạng Area có thể sử dụng tùy mục đích nhưng đa số sẽ là 0
    float AttackDamage;                       // Sát thưởng của Attack

    int AttackID;                             // Vị trí của Attack trong AttackPool
    int AttackOwnTowerID;                     // Có thể sử dụng để biến đổi trạng thái hoạt ảnh, ví dụ như Attack laser thì khi mà Laser bắn đến mục tiêu thì kết thúc hoạt ảnh casting
    int AttackTargetID;                       // Dùng để GetEnemy từ EnemyPool để kiểm tra đụng độ
    size_t Lifespan;                          // Thời gian kể từ khi xuất hiện của Attack
public:
    Attack();
    ~Attack() = default;

    virtual void Update();
    virtual void Draw() const = 0;

    void SetAttackID(const int& _AttackID);

    void AttackKill();
};