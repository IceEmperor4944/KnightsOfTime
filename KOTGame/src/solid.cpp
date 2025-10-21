#include "solid.h"

void Solid::Step(float dt) {
	//
}

std::vector<std::shared_ptr<Collider>> Solid::CheckColliders(const std::vector<std::shared_ptr<Object>>& other)
{
	return std::vector<std::shared_ptr<Collider>>();
}
