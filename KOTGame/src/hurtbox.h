#pragma once
#include "collider.h"
#include <string>

#define BOXTYPE Hurtbox::Type

class Hurtbox : public Collider {
public:
	enum class Type {
		Body = 0,
		Block,
		Hurt,
		Invuln
	};
public:
	Hurtbox(BOXTYPE type, Vector2 size, Vector2 position = { 0, 0 }, float restitution = 0.0f) :
		Collider{ size, position, restitution },
		type{ type }
	{}

	void Initialize() override;
	std::string GetType();

	bool Intersects(std::shared_ptr<Collider> other) override;
public:
	BOXTYPE type;
};