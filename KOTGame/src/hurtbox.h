#pragma once
#include "collider.h"

#define BOXTYPE Hurtbox::Type

class Hurtbox : public Collider {
public:
	enum class Type {
		Body = 0,
		Hurt,
		Block,
		Invuln
	};
public:
	Hurtbox() = default;
	Hurtbox(BOXTYPE type, Vector2 size, Vector2 posOffset = { 0, 0 }, float restitution = 0.0f) :
		Collider{ size, posOffset, restitution },
		type{ type }
	{}

	void Initialize() override;
	std::string GetType();

	bool Intersects(std::shared_ptr<Collider> other) override;

	void Read(const json_t& value) override;
public:
	BOXTYPE type;
};