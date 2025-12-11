#pragma once
#include "object.h"
#include "hurtbox.h"
#include "hitbox.h"

#define CSTATE Controllable::State

struct Attack;

class Controllable : public Object {
public:
	enum class State {
		Idle = 0,
		Move,
		Run,
		Crouch,
		Jump,
		Air,
		Hit,
		Punch,
		Kick
	};
public:
	Controllable() : Object() {};
	Controllable(std::string tag, float mass, int maxHealth, float gravScale, float jumpHeight, float moveSpeed, std::string character, Vector2 pos = { 0,0 }) :
		Object(tag, mass, maxHealth, pos),
		gravScale{ gravScale },
		jumpHeight{ jumpHeight },
		moveSpeed{ moveSpeed },
		character{ character }
	{
	};

	void Initialize(std::string filename) override;
	void Step(float dt) override;
	void FixedStep(float timestep) override;

	void Read(const std::string& filename) override;

	colliders_t CheckColliders(const std::vector<std::shared_ptr<Object>>& other) override;
public:
	float gravScale = 1.0f;
	bool grounded = false;
	float jumpHeight = 1.0f;
	float moveSpeed = 1.0f;

	State state{ CSTATE::Idle };
	State prevState{ CSTATE::Idle };

	Sound pSound;

	/// <summary>
	/// Sets which character to use. Most applicable when multiple characters.
	/// </summary>
	std::string character;
};