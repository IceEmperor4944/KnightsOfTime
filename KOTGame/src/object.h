#pragma once
#include "hurtbox.h"
#include "hitbox.h"
#include <string>
#include <iostream>

#define SOLID Object::Type::Solid
#define CONTROL Object::Type::Controllable

class Object {
public:
	enum class Type {
		Solid = 0,
		Controllable
	};
public:
	Object() {};
	Object(std::string tag, float mass, int health, Vector2 pos = { 0,0 }, float restitution = 1.0f) :
		tag{ tag },
		mass{ mass },
		health{ health },
		position{ pos },
		restitution{ restitution }
	{};

	virtual void Initialize(std::string filename) {
		sprite = std::make_shared<Texture2D>(LoadTexture(filename.c_str()));
		size = Vector2{ (float)sprite->width, (float)sprite->height };
	}

	virtual void Step(float dt) = 0;
	virtual void FixedStep(float timestep) = 0;

	AABB GetAABB() const { return AABB{ position, { size.x, size.y } }; }

	void AddCollider(std::shared_ptr<Collider> collider) { colliders.push_back(collider); }
	virtual colliders_t CheckColliders(const std::vector<std::shared_ptr<Object>>& other) {
		prevHealth = health;
		//UpdateColliderPositions();
		return colliders;
	}

	void UpdateColliderPositions() {
		std::cout << "##KOT: Object " << tag << " at Position (" << this->position.x << ", " << this->position.y << ")." << std::endl;

		for (auto& col : colliders) {
			float xOffset = spriteFlip ? -col->posOffset.x : col->posOffset.x;

			std::cout << "##KOT: Collider Position Offset: (" << col->posOffset.x << ", " << col->posOffset.y << ")." << std::endl;
			col->position = { this->position.x + xOffset, this->position.y + col->posOffset.y };
			std::cout << "##KOT: Collider New Position: (" << col->position.x << ", " << col->position.y << ")." << std::endl;
		}
	}

public:
	std::string tag = "";

	Vector2 size{};
	float mass = 0.0f;

	Vector2 position{ 0, 0 };
	Vector2 velocity{ 0, 0 };
	float restitution = 1.0f;
	
	int health = 0;
	int prevHealth = -1;

	std::shared_ptr<Texture2D> sprite;
	float frameTimer = 0.0f;
	int currentFrame = 0;
	int frameSpeed = 0;
	bool spriteFlip = false;

	bool animPlay = false;
	Sound soundPlay{ 0 };

	bool drawCols = true;

	//array of colliders for hurt/hitbox
	colliders_t colliders;
};