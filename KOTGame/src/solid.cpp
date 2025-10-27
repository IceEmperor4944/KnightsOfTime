#include "solid.h"

void Solid::Step(float dt) {
	if (health <= 0.0f) delete this;
}

void Solid::FixedStep(float timestep) {
	//
}

std::vector<std::shared_ptr<Collider>> Solid::CheckColliders(const std::vector<std::shared_ptr<Object>>& other) {
	return colliders;
}