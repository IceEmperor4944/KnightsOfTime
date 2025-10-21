#pragma once
#include "aabb.h"
#include <vector>
#include <memory>

class Collider {
public:
	Collider(Vector2 size, Vector2 position = { 0, 0 }, float restitution = 0.0f) : size{ size }, position{ position }, restitution{ restitution } {}

	virtual void Initialize() = 0;
	AABB GetAABB() const { return AABB{ position, { size.x * 2, size.y * 2 } }; }

	virtual bool Intersects(std::shared_ptr<class Object> other) = 0;
public:
	Vector2 position{};
	Vector2 size{};

	float restitution = 1.0f;
};