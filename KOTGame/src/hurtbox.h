#pragma once
#include "collider.h"

#define BOXTYPE Hurtbox::Type

class Hurtbox : public Collider {
public:
	enum class Type {
		Block = 0,
		Hurt,
		Invuln
	};
public:
	Hurtbox(BOXTYPE type, Vector2 size, Vector2 position = { 0, 0 }) :
		Collider{ size, position },
		type{ type }
	{}

	void Initialize() override;

	std::vector<class Object*> GetCollisionCount() override;
public:
	BOXTYPE type;
};