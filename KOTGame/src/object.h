#pragma once
#include "hurtbox.h"
#include "hitbox.h"
#include <string>

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
	Object(std::string tag, float mass, int maxHealth, Vector2 pos = { 0,0 }, float restitution = 1.0f) :
		tag{ tag },
		mass{ mass },
		maxHealth{ maxHealth },
		position{ pos },
		restitution{ restitution }
	{};

	virtual void Initialize(std::string filename) {
		sprite = LoadTexture(filename.c_str());
		size = { (float)sprite.width, (float)sprite.height };
		health = maxHealth;
	}

	virtual void Step(float dt) = 0;
	virtual void FixedStep(float timestep) = 0;

	AABB GetAABB() const { return AABB{ position, { size.x, size.y } }; }

	void AddCollider(std::shared_ptr<Collider> collider) { colliders.push_back(collider); }
	virtual colliders_t CheckColliders(const std::vector<std::shared_ptr<Object>>& other) = 0;
public:
	std::string tag = "";

	Vector2 size{};
	float mass = 0.0f;

	Vector2 position{ 0, 0 };
	Vector2 velocity{ 0, 0 };
	float restitution = 1.0f;
	
	int maxHealth = 0;
	int health = 0;

	Texture2D sprite{};
	float frameTimer = 0.0f;
	int currentFrame = 0;
	int frameSpeed = 0;
	bool spriteFlip = false;

	bool animPlay = false;
	Sound soundPlay{ 0 };

	bool drawCols = true;

	//array of colliders for hurt/hitbox
	std::vector<std::shared_ptr<Collider>> colliders;
};