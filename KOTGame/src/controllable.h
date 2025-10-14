#pragma once
#include "object.h"

class Controllable : public Object {
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
public:
	float gravScale = 1.0f;
	bool grounded = true;
	float jumpHeight = 1.0f;
	float moveSpeed = 1.0f;
};