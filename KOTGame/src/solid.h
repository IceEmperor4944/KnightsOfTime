#pragma once
#include "object.h"

class Solid : public Object {
public:
	Solid() : Object() {};
	Solid(std::string tag, float mass, int health, Vector2 pos = { 0,0 }) : Object(tag, mass, health, pos) {};

	void Initialize(std::string filename) override;
	void Step(float dt) override;
	void FixedStep(float timestep) override;
	
	std::vector<std::shared_ptr<Collider>> CheckColliders(const std::vector<std::shared_ptr<Object>>& other) override;
public:
};