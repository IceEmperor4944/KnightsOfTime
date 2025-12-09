#include "solid.h"
#include "attack.h"

void Solid::Initialize(std::string filename) {
	Read(filename);

	curAnim = tag + "IdleSprite";
	StartAnim(curAnim);
	auto curAttack = tag + "IdleAttack";
	StartAttack(curAttack);

	size = Vector2{ anims[curAnim]->frameRec.width, anims[curAnim]->frameRec.height };
}

void Solid::Step(float dt) {
	if (health <= 0.0f) delete this;
}

void Solid::FixedStep(float timestep) {
	auto spriteName = tag + "IdleSprite";
	auto attackName = tag + "IdleAttack";
	
	StartAnim(spriteName);
	StartAttack(attackName);

	curAttack->PlayAttackFrame(*this);
}

std::vector<std::shared_ptr<Collider>> Solid::CheckColliders(const std::vector<std::shared_ptr<Object>>& other) {
	return Object::CheckColliders(other);
}