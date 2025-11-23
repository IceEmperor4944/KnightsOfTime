#pragma once
#include "collider.h"

class Hitbox : public Collider {
public:
	Hitbox() = default;
	Hitbox(Vector2 size, Vector2 posOffset, int damage, float knockback) :
		Collider{ size, posOffset },
		damage{ damage },
		knockback{ knockback }
	{}

	void Initialize() override;

	bool Intersects(std::shared_ptr<Collider> other) override;

	void Read(const json_t& value) override;
public:
	int damage = 0;
	float knockback = 0.0f;
};