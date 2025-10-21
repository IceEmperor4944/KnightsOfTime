#pragma once
#include "collider.h"

class Hitbox : public Collider {
public:
	Hitbox(Vector2 size, Vector2 position, float damage, float knockback) :
		Collider{ size, position },
		damage{ damage },
		knockback{ knockback }
	{}

	void Initialize() override;

	bool Intersects(std::shared_ptr<class Object> other) override;
public:
	float damage = 0.0f;
	float knockback = 0.0f;
};