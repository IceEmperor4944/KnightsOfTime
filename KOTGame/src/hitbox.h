#pragma once
#include "collider.h"

class Hitbox : public Collider {
public:
	Hitbox(Vector2 size, Vector2 position, int damage, float knockback) :
		Collider{ size, position },
		damage{ damage },
		knockback{ knockback }
	{}

	void Initialize() override;

	bool Intersects(std::shared_ptr<Collider> other) override;
public:
	int damage = 0;
	float knockback = 0.0f;
};