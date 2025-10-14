#pragma once
#include "collider.h"
#include <string>

#define SOLID Object::Type::Solid
#define CONTROL Object::Type::Controllable

class Object {
public:
	enum class Type {
		Solid = 0,
		Controllable = 1
	};
public:
	Object() {};
	Object(std::string tag, float mass, Vector2 pos = { 0,0 }) : mass{ mass }, position{ pos } {};

	virtual void Initialize(std::string filename) {
		sprite = LoadTexture(filename.c_str());
		size = { (float)sprite.width, (float)sprite.height };
	}

	virtual void Step(float dt) = 0;

	AABB GetAABB() const { return AABB{ position, { size.x * 2, size.y * 2 } }; }

	Collider* AddCollider(Collider* collider) { colliders.push_back(collider); }
public:
	std::string tag = "";

	Vector2 size{};
	float mass = 0.0f;

	Vector2 position{ 0, 0 };
	Vector2 velocity{ 0, 0 };
	
	Texture2D sprite{};

	//array of colliders for hurt/hitbox
	std::vector<Collider*> colliders;

};