#pragma once
#include "collider.h"

class Hitbox : public Collider {
public:
	Hitbox() = default;
	Hitbox(Vector2 size, Vector2 posOffset, int damage, Vector2 kbDir, float kbStrength) :
		Collider{ size, posOffset },
		damage{ damage },
		kbDir{ kbDir },
		kbStrength{ kbStrength }
	{}

	void Initialize() override;

	bool Intersects(std::shared_ptr<Collider> other) override;

	void Read(const json_t& value) override;
public:
	int damage = 0;
	Vector2 kbDir{};
	float kbStrength = 0.0f;
};