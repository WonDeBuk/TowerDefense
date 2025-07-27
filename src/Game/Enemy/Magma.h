#pragma once

#include "../Enemy.h"

class Magma : public Enemy {
	// Phần private này để cho loại Enemy Magma mặc định
private:
	static constexpr float BASE_HEALTH = 100.0f;
	static constexpr float BASE_SPEED = 1.15f;

	// Dùng cho các loại Magma khác có thể kế thừa
protected:
	// Kế thừa khả năng cập nhật trạng thái hoạt ảnh
	void UpdateAnimation() override;
public:
	Magma();

	void OnHeal(const float& _Heal) override;
	void Update() override;
	void Draw() const override;
	void DrawHealthBar() const override;
};