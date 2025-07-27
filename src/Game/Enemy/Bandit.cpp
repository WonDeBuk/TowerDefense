#include "Bandit.h"
#include "Utils/ResourceManager.h"
#include "Game/GameManager.h"

Bandit::Bandit() {
	EnemyHealth = BASE_HEALTH;
	EnemySpeed = BASE_SPEED;

	EnemyTexture = const_cast<Texture2D*>(&ResourceManager::GetInstance().LoadTexture("ui/Bandit.png"));
	EnemyTextureSize = { 128.0f, 128.0f };

	EnemyFrameStateAmount = 8;
	Bandit::UpdateAnimation();

	CashStolen = 0;
	AbilityCooldown = 0;

	EnemyDrawbox = { EnemyCurrentPosition.x - EnemyTextureSize.x * 0.5f, EnemyCurrentPosition.y - EnemyTextureSize.y * 0.55f, EnemyTextureSize.x, EnemyTextureSize.y };

}

void Bandit::UpdateAnimation() {
	// Cập nhật trạng thái frame
	if (EnemyLifespan % 6 == 0) {
		EnemyFrameState++;
		EnemyFrameState %= EnemyFrameStateAmount;
	}
}

void Bandit::OnHeal(const float& _Heal) {
	EnemyHealth += _Heal;
	if (EnemyHealth > BASE_HEALTH) EnemyHealth = BASE_HEALTH;
}

void Bandit::Update() {
	// Cập nhật lớp cha
	Enemy::UpdatePosition();

	if (EnemyLifespan - PreviousAbilityFrame >= AbilityCooldown && CashStolen < MAX_CASH_CAPACITY) {
		PreviousAbilityFrame = EnemyLifespan;
		int PotentialSteal = MAX_CASH_CAPACITY - CashStolen;
		int PortionOfPlayer = 0.35f * GameManager::GetInstance().GetPlayerCash();
		if (PotentialSteal < PortionOfPlayer) {
			CashStolen += PotentialSteal;
			GameManager::GetInstance().ModifyCash(-PotentialSteal);
		}
		else {
			CashStolen += PortionOfPlayer;
			GameManager::GetInstance().ModifyCash(-PortionOfPlayer);
		}
		EnemySpeed = (1.0f - 0.8f * (CashStolen / MAX_CASH_CAPACITY)) * BASE_SPEED;
		AbilityCooldown = GetRandomValue(300, 600);
	}

	// Cập nhật trạng thái hoạt ảnh
	Bandit::UpdateAnimation();

	// Cập nhật vị trí Hitbox và Drawbox
	EnemyDrawbox.x = EnemyCurrentPosition.x - EnemyTextureSize.x * 0.5f;
	EnemyDrawbox.y = EnemyCurrentPosition.y - EnemyTextureSize.y * 0.55f;
}

void Bandit::Draw() const {
	DrawTexturePro(*EnemyTexture, { 144.0f * EnemyFrameState, 0.0f, 144.0f * CurrentDirectionType, 144.0f }, EnemyDrawbox, { 0.0f, 0.0f }, 0.0f, WHITE);
	Bandit::DrawHealthBar();
}

void Bandit::DrawHealthBar() const {
	if (EnemyHealth == BASE_HEALTH) return;
	DrawRectangle(EnemyCurrentPosition.x - 50.0f, EnemyCurrentPosition.y - EnemyDrawbox.height * 0.55f, 100.0f, 5.0f, BLACK);
	DrawRectangle(EnemyCurrentPosition.x - 50.0f, EnemyCurrentPosition.y - EnemyDrawbox.height * 0.55f, 100.0f * EnemyHealth / BASE_HEALTH, 5.0f, RED);
}