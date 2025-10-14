#pragma once
#include "aabb.h"
#include <vector>

class Collider {
public:
	Collider(Vector2 size, Vector2 position = { 0, 0 }) : size { size }, position{ position } {}

	virtual void Initialize() = 0;
	AABB GetAABB() const { return AABB{ position, { size.x * 2, size.y * 2 } }; }

	virtual std::vector<class Object*> GetCollisionCount() = 0;
public:
	Vector2 position{};
	Vector2 size{};
};