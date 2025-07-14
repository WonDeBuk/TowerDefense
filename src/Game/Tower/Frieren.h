#pragma once

#include "./Tower.h"

class Frieren: public Tower {
private:
    int ShotsCounting;
    int BaseShots;
    size_t AnimationTimer;
    int 

    int TargetEnemiesID[3];
    int TargetEnemyID;

    void (*Skill)();
    void (*UpdateFrieren)();

    void SkillLevel1();
    void SkillLevel3();
    void UpdateLevel1();
public:
    void SetTowerCurrentLevel(const int& _Level) override;
    void Update() override;
};