#pragma once

#include "../Enemy.h"

class Frost : public Enemy {
	// Phần private này để cho loại Enemy Frost mặc định
private:
	static constexpr float BASE_HEALTH = 100.0f;
	static constexpr float BASE_SPEED = 1.15f;

	// Dùng cho các loại Frost khác có thể kế thừa
protected:
	// Kế thừa khả năng cập nhật trạng thái hoạt ảnh
	void UpdateAnimation() override;
public:
	Frost();

	void OnHeal(const float& _Heal) override;
	void Update() override;
	void Draw() const override;
	void DrawHealthBar() const override;
};