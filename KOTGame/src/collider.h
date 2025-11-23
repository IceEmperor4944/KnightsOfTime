#pragma once
#include "aabb.h"
#include "json.h"
#include <vector>
#include <memory>

class Collider {
public:
	Collider() = default;
	Collider(Vector2 size, Vector2 posOffset = { 0, 0 }, float restitution = 0.0f) : size{ size }, posOffset{ posOffset }, restitution{ restitution } {}

	virtual void Initialize() = 0;
	AABB GetAABB() const { return AABB{ posOffset, { size.x, size.y } }; }

	virtual bool Intersects(std::shared_ptr<Collider> other) = 0;

	virtual void Read(const json_t& value) {
		READ_DATA(value, size);
		READ_DATA(value, posOffset);
		READ_DATA(value, restitution);

		std::cout << "##KOT: Collider Position Offset - (" << posOffset.x << ", " << posOffset.y << ")" << std::endl;

		Initialize();
	}

public:
	Vector2 position{};
	Vector2 size{};
	Vector2 posOffset{};

	float restitution = 1.0f;
};

using colliders_t = std::vector<std::shared_ptr<Collider>>;