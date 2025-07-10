#pragma once

#include "./Utils/Define.h"
#include "Enemy.h"
#include "Attack.h"
// #include "Tower.h"
#include <raylib.h>

class GameManager {
private:
    // Các property thuộc về Enemy
    static char EnemyPool[MAX_ENEMY_AMOUNT][MAX_ENEMY_SIZE];
    static bool EnemyPoolTracker[MAX_ENEMY_AMOUNT];
    static int CurrentEnemyAmount;
    static Vector2 WaypointList[MAX_WAYPOINT_AMOUNT];
    static int WaypointSize;

    // Các property thuộc về Attack
    static char AttackPool[MAX_ATTACK_AMOUNT][MAX_ATTACK_SIZE];
    static bool AttackPoolTracker[MAX_ATTACK_AMOUNT];
    static int CurrentAttackAmount;

    // Các property thuộc về Tower
    static char TowerPool[MAX_TOWER_AMOUNT][MAX_TOWER_SIZE];
    static Vector2 TowerPlotList[MAX_TOWER_AMOUNT];
    static bool TowerPlotAndPoolTracker[MAX_TOWER_AMOUNT];
    static int TowerPlotSize;
    static int CurrentTowerAmount;

    // Các property khác
    static MapType CurrentMap;
    static Texture2D* MapTexture;
    static size_t Timer;

    GameManager();
public:
    // Các method liên quan đến config của game
    static GameManager& GetInstance();                                              // Dùng để lấy instance của GameManager để sử dụng các hàm non-static
    static const size_t& GetTime();                                                 // Dùng để lấy thời gian hiện tại của GameManager để đồng bộ các hoạt động
    static const int& GetWaypointSize();                                            // Dùng để lấy số lượng waypoint của map: dùng trong hàm di chuyển của Enemy khi Enemy gặp waypoint cuối thì Enemy sẽ chết
    static const Vector2& GetWaypointByIndex(int _WaypointIndex);                   // Dùng để lấy tọa độ của một waypoint cụ thể thông qua index của waypoint: dùng trong hàm di chuyển của Enemy dùng để tính toán hướng của Enemy
    static const Vector2(&GetWaypointList())[MAX_WAYPOINT_AMOUNT];                  // Dùng để lấy danh sách tọa độ các waypoint của map
    static const Vector2(&GetTowerPlotList())[MAX_TOWER_AMOUNT];                    // Dùng để lấy danh sách tọa độ của các vị trí đặt tháp: dùng trong GameState để có thể lấy các vị trí để người chơi thực hiện quá trình đặt tháp
    static const Vector2& GetTowerPlotByID(const int& _TowerID);                    // Dùng để lấy tọa độ của một chỗ đặt tháp cụ thể bằng thông qua ID: dùng để set vị trí cho các tower
    static const bool(&GetTowerPlotAndPoolTracker())[MAX_TOWER_AMOUNT];             // Dùng để lấy danh sách kiểm tra xem các vị trí đặt tháp có trụ được đặt hay chưa: dùng trong GameState để check xem vị trí đặt có được đặt tháp hay chưa
    static const int& GetTowerPlotSize();                                           // Dùng để lấy số lượng vị trí đặt tháp của map
    static const MapType& GetCurrentMap();
    void ResetConfig();                                                             // Dùng để xóa hết tất cả dữ liệu của map hiện tại
    void ChangeConfig(const MapType& _MapType);                                     // Dùng để đọc dữ liệu từ config và nạp vào nơi chứa dữ liệu config map
    void ReadConfig(const MapType& _MapType);
    void UnitTestPrintData();

    // Các method liên quan đến việc sử dụng EnemyPool
    static const char(&GetEnemyPool())[MAX_ENEMY_AMOUNT][MAX_ENEMY_SIZE];
    static const bool(&GetEnemyPoolTracker())[MAX_ENEMY_AMOUNT];
    static const int& GetCurrentEnemyAmount();
    Enemy* GetEnemyByID(const int& _EnemyID) const;
    static void AddEnemy(const EnemyType& _EnemyType, Enemy* _EnemyTemplate = nullptr);
    void KillEnemy(const int& _EnemyID);

    // Các method liên quan đến việc sử dụng AttackPool
    static const char(&GetAttackPool())[MAX_ENEMY_AMOUNT][MAX_ATTACK_SIZE];
    static const bool(&GetAttackPoolTracker())[MAX_ENEMY_AMOUNT];
    static const int& GetCurrentAttackAmount();
    void AddAttack(const AttackType& _AttackType, const Attack* _AttackTemplate);
    void KillAttack(const int& _AttackID);

    // Các method liên quan đến việc sử dụng TowerPool
    // static const char(&GetTowerPool())[MAX_TOWER_AMOUNT][MAX_TOWER_SIZE];
    // static const int& GetCurrentTowerAmount();
    // void AddTower(const TowerType& _TowerType, const int& _SlotID);
    // void KillTower(const int& _TowerID);


    void Draw() const;
    void Update();
};