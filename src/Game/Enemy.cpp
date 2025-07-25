#include "Enemy.h"
#include "GameManager.h"
#include "Game/VisualManager.h"
#include <cmath>
#include <assert.h>
#include <iostream>
#include <raymath.h>

Enemy::Enemy() {
    // Khởi tạo thời gian sống
    EnemyLifespan = 0;

    // Khởi tạo giá trị index của điểm Waypoint hướng tới ban đầu
    HeadingWaypointIndex = 0;

    // Khởi tạo vị trí ban đầu của Enemy ở vị trí của Waypoint đầu tiên
    EnemyCurrentPosition = GameManager::GetWaypointByIndex(0);

    // Khởi tạo hướng ban đầu của Enemy
    EnemyDirection = Vector2Normalize(Vector2Subtract(GameManager::GetWaypointByIndex(HeadingWaypointIndex), GameManager::GetWaypointByIndex(HeadingWaypointIndex - 1)));

    // Khởi tạo trạng thái hoạt ảnh ban đầu
    EnemyFrameState = 0;

    PreviousAbilityFrame = 0;
    CurrentSprite = 0;
    IsAbility = false;
}

Enemy::~Enemy() {}

void Enemy::SetEnemyID(const int& _ID) {
    EnemyID = _ID;
}

Vector2 Enemy::GetEnemyFuturePosition(const int &_DeltaTime) const {
    Vector2 EnemyFuturePosition = EnemyCurrentPosition;
    int TempHeadingWaypointIndex = HeadingWaypointIndex;
    Vector2 TempHeadingWaypointPosition = GameManager::GetWaypointByIndex(HeadingWaypointIndex);
    Vector2 TempEnemyDirection = EnemyDirection;
    for (int i = 0; i < _DeltaTime;) {
        // Nếu khoảng cách từ Enemy đến vị trí của Waypoint lớn hơn khoảng cách mà Enemy có thể đi
        // trong khoảng thời gian _DeltaTime còn lại thì thuật toán kế thúc, đã tìm được vị trí
        // trong tương lai sau _DeltaTime
        if (Vector2Distance(EnemyFuturePosition, TempHeadingWaypointPosition) >= (EnemySpeed * (_DeltaTime - i))) {
            EnemyFuturePosition.x += (_DeltaTime - i) * EnemySpeed * TempEnemyDirection.x;
            EnemyFuturePosition.y += (_DeltaTime - i) * EnemySpeed * TempEnemyDirection.y;
            i = _DeltaTime;
        } else {
            i += (int) ceilf(Vector2Distance(EnemyFuturePosition, TempHeadingWaypointPosition) / EnemySpeed);
            EnemyFuturePosition = TempHeadingWaypointPosition;
            if (TempHeadingWaypointIndex != GameManager::GetWaypointSize() - 1) {
                TempHeadingWaypointIndex++;
                TempHeadingWaypointPosition = GameManager::GetWaypointByIndex(TempHeadingWaypointIndex);
                TempEnemyDirection = Vector2Normalize(Vector2Subtract(GameManager::GetWaypointByIndex(TempHeadingWaypointIndex), GameManager::GetWaypointByIndex(TempHeadingWaypointIndex - 1)));
            } else {
                break;
            }
        }
    }

    return EnemyFuturePosition;
}

void Enemy::UpdatePosition() {
    EnemyLifespan++;

    // Kiểm tra nếu vị trí hiện tại bằng với vị trí của Waypoint mà Enemy đang hướng đến thì ta cập nhật các properties
    if (EnemyCurrentPosition == GameManager::GetWaypointByIndex(HeadingWaypointIndex)) {
        // Tăng index của Waypoint mà Enemy đang hướng đến sang Waypoint kế tiếp trong danh sách Waypoint
        HeadingWaypointIndex++;
        // Kiểm tra nếu đã đi đến Waypoint cuối cùng thì sẽ Kill Enemy
        if (HeadingWaypointIndex == GameManager::GetWaypointSize()) {
            Enemy::EnemyKill();
        }
        // Cập nhật hướng Enemy đang đi
        EnemyDirection = Vector2Normalize(Vector2Subtract(GameManager::GetWaypointByIndex(HeadingWaypointIndex), GameManager::GetWaypointByIndex(HeadingWaypointIndex - 1)));
        // Di chuyển vị trí của Enemy
        EnemyCurrentPosition.x += EnemySpeed * EnemyDirection.x;
        EnemyCurrentPosition.y += EnemySpeed * EnemyDirection.y;

        UpdateDirection();
    }
    // Kiểm tra nếu khoảng cách giữa vị trí hiện tại và điểm Waypoint đang hướng tới nếu nhỏ hơn hoặc
    // bằng khoảng cách có thể đi trong một đơn vị thời gian thì ta đặt vị trí của Enemy ở vị trí của
    // điểm Waypoint đang hướng tớ, nếu không thì Enemy sẽ đi qua khỏi điểm Waypoint
    else if (Vector2DistanceSqr(EnemyCurrentPosition, GameManager::GetWaypointByIndex(HeadingWaypointIndex)) <= EnemySpeed * EnemySpeed) {
        // Cập nhật vị trí của Enemy tại điểm Waypoint
        EnemyCurrentPosition = GameManager::GetWaypointByIndex(HeadingWaypointIndex);
    }
    // Nếu không thuộc một trong hai trường hợp trên thì Enemy di chuyển bình thường
    else {
        // Di chuyển vị trí của Enemy
        EnemyCurrentPosition.x += EnemySpeed * EnemyDirection.x;
        EnemyCurrentPosition.y += EnemySpeed * EnemyDirection.y;
    }
}

void Enemy::UpdateDirection() {
    if (EnemyDirection.x == 1.0f || EnemyDirection.y == -1.0f) CurrentDirectionType = EnemyDirectionType::FORWARD;
    else CurrentDirectionType = EnemyDirectionType::BACKWARD;
}

void Enemy::OnDamage(const float& _Damage) {
    if (EnemyHealth <= _Damage) {
        VisualManager::GetInstance().AddVisual(VisualType::PLAIN, Visual::VisualTemplateBuildAndGet("ui/CoinFlip.png", 7, { EnemyCurrentPosition.x - 64.0f, EnemyCurrentPosition.y - 128.0f }, { 128.0f, 128.0f }, 3));
        OnDeath();
        EnemyKill();
        return;
    }
    EnemyHealth -= _Damage;
}

void Enemy::OnDeath() {
     
}

void Enemy::EnemyKill() const{
    GameManager::GetInstance().KillEnemy(EnemyID);
}

void Enemy::DrawHitboxAndPivot() const {
    DrawRectangleLines(EnemyHitbox.x, EnemyHitbox.y, EnemyHitbox.width, EnemyHitbox.height, RED);
    DrawCircle(EnemyCurrentPosition.x, EnemyCurrentPosition.y, 3, RED);
}