#pragma once

#include "collider.h"
#include "sprite.h"
#include <string>
#include <map>
#include <iostream>

#define SOLID Object::Type::Solid
#define CONTROL Object::Type::Controllable

struct Attack;

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
	{
	};

	virtual void Initialize(std::string filename) = 0;

	virtual void Step(float dt);
	virtual void FixedStep(float timestep) = 0;

	void Draw(Vector2 position, Color tint = WHITE);

	virtual void Read(const std::string& filename);

	////////////////////////

	std::shared_ptr<Sprite> GetCurrentSprite() {
		auto iter = anims.find(curAnim);
		if (iter != anims.end()) {
			return iter->second;
		}

		return nullptr;
	}

	AABB GetAABB() const { return AABB{ position, { size.x, size.y } }; }

	void AddCollider(std::shared_ptr<Collider> collider) { colliders.push_back(collider); }
	virtual colliders_t CheckColliders(const std::vector<std::shared_ptr<Object>>& other) {
		prevHealth = health;
		UpdateColliderPositions();
		return colliders;
	}

	void UpdateColliderPositions();

	void StartAnim(const std::string& animKey);
	void StartAttack(const std::string& attackKey);

public:
	std::string tag = "";

	Vector2 size{};
	float mass = 0.0f;

	Vector2 position{ 0, 0 };
	Vector2 velocity{ 0, 0 };
	float restitution = 1.0f;

	int health = 1;
	int prevHealth = -1;

	std::map<std::string, std::shared_ptr<Sprite>> anims;
	std::map<std::string, std::shared_ptr<Attack>> attacks;
	std::string curAnim = "Idle";
	std::shared_ptr<Attack> curAttack{ nullptr };
	int currentFrame = 0;
	float frameTimer = 0.0f;
	int frameSpeed = 0;
	bool spriteFlip = false;

	bool animPlay = false;

	bool drawCols = false;

	colliders_t colliders;
};