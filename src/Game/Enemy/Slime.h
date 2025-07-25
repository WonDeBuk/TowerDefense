#pragma once

#include "../Enemy.h"

class Slime: public Enemy {
// Phần private này để cho loại Enemy Slime mặc định
private:
	static constexpr float BASE_HEALTH = 75.0f;
	static constexpr float BASE_SPEED = 1.25f;

// Dùng cho các loại Slime khác có thể kế thừa
protected:
	// Kế thừa khả năng cập nhật trạng thái hoạt ảnh
	void UpdateAnimation() override;
public:
	Slime();

	void OnHeal(const float& _Heal) override;
	void Update() override;
	void Draw() const override;
	void DrawHealthBar() const override;
};