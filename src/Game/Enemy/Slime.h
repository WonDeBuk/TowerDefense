#pragma once

#include "../Enemy.h"

// Các trạng thái hoạt ảnh của các enemy có dạng Slime
enum SlimeAnimationState {
	VERTICAL,
	HORIZONTAL
};

class Slime: public Enemy {
// Phần private này để cho loại Enemy Slime mặc định
private:
	static constexpr float BASE_HEALTH = 100.0f;
	static constexpr float BASE_SPEED = 8.0f;
    Vector2 Test;
// Dùng cho các loại Slime khác có thể kế thừa
protected:
	// Kế thừa khả năng cập nhật trạng thái hoạt ảnh
	void UpdateAnimation() override;
	SlimeAnimationState CurrentAnimationState;
public:
	Slime();

	void Update() override;
	void Draw() const override;
	void DrawHealthBar() const override;
};