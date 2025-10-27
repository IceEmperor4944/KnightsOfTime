#pragma once
#include "object.h"

#define CSTATE Controllable::State

class Controllable : public Object {
public:
	enum class State {
		Idle = 0,
		Move,
		Air,
		Punch
	};
public:
	Controllable() : Object() {};
	Controllable(std::string tag, float mass, float gravScale, float jumpHeight, float moveSpeed, Vector2 pos = { 0,0 }) :
		Object(tag, mass, pos),
		gravScale{ gravScale },
		jumpHeight{ jumpHeight },
		moveSpeed{ moveSpeed }
	{};

	void Initialize(std::string filename) override { Object::Initialize(filename); }
	void Step(float dt) override;
	void FixedStep(float timestep) override;

	std::vector<std::shared_ptr<Collider>> CheckColliders(const std::vector<std::shared_ptr<Object>>& other) override;
public:
	float gravScale = 1.0f;
	bool grounded = true;
	float jumpHeight = 1.0f;
	float moveSpeed = 1.0f;

	State state{ CSTATE::Idle };

	////////////////////////////////////////////////////////
	//for future use:
	std::string character;	//set this in constructor
	//append string to each filename to get specific sprites
};