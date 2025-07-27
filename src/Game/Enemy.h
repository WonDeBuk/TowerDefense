#pragma once

#include <raylib.h>

class GameManager;

enum EnemyDirectionType {
    BACKWARD = -1,
    FORWARD = 1

};

class Enemy {
protected:
    bool IsAbility;
    int CurrentSprite;
    int AbilityCooldown;

    // Các property cơ bản cần thiết
    int EnemyID;			// Dùng để chứa ID của Enemy trong EnemyPool
    int HeadingWaypointIndex;		// Dùng để chứa index của waypoint mà Enemy đang hướng đến
    int EnemyLifespan;			// Dùng để chứa thời gian từ khi xuất hiện của Enemy
    int PreviousAbilityFrame;
    float EnemyHealth;			// Dùng để chứa máu của Enemy
    float EnemySpeed;			// Dùng để chứa tốc độ di chuyển của Enemy

    // Các property về toán
    Vector2 EnemyCurrentPosition;	// Dùng để chứa vị trí hiện tại của Enemy
    Vector2 EnemyDirection;		// Dùng để chứa hướng di chuyển của Enemy
    Rectangle EnemyHitbox;		// Dùng để kiểm tra với các hàm kiểm tra đụng độ
    
    // Các property về animation
    int EnemyFrameState;		// Dùng để chuyển động giữa các frame trong một animation
    int EnemyFrameStateAmount;		// Dùng để chứa số lượng frame của một animation
    EnemyDirectionType CurrentDirectionType;
    // Các property về texture
    Vector2 EnemyTextureSize;		// Dùng để chứa kích thước của một frame của Enemy
    Texture2D* EnemyTexture;		// Dùng để chứa texture của Enemy
    Rectangle EnemyDrawbox;		// Dùng để xác định nơi vẽ texture

    virtual void DrawHitboxAndPivot() const;
public:
    Enemy();
    ~Enemy();

    virtual void UpdatePosition();
    virtual void UpdateDirection();
    virtual void Update() = 0;
    virtual void Draw() const = 0;

    virtual void OnHeal(const float& _Heal) = 0;
    virtual void OnDamage(const float& _Damage);
    virtual void OnDeath();
    
    virtual void UpdateAnimation() = 0;
    virtual void DrawHealthBar() const = 0;
    
    // Dùng để lấy được vị trí trong tương lai của Enemy sau _DeltaTime tick: sử dụng trong hàm dự đoán và hàm cập nhật
    Vector2 GetEnemyFuturePosition(const int& _DeltaTime) const;

    int& GetEnemyID() {return EnemyID;}
    int& GetHeaddingWaypointIndex() {return HeadingWaypointIndex;}
    float& GetEnemyHealth() {return EnemyHealth;}
    float& GetEnemySpeed() {return EnemySpeed;}

    Vector2& GetEnemyCurrentPosition() {return EnemyCurrentPosition;}
    Vector2& GetEnemyDirection() {return EnemyDirection;}
    Rectangle& GetHitBox() {return EnemyHitbox;}

    void SetEnemyID(const int& _ID);

    void EnemyKill() const;
};