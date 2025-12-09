#include "hitbox.h"

void Hitbox::Initialize() {
	
}

bool Hitbox::Intersects(std::shared_ptr<Collider> other) {
	return false;
}

void Hitbox::Read(const json_t& value) {
	Collider::Read(value);

	READ_DATA(value, damage);
	READ_DATA(value, kbDir);
	READ_DATA(value, kbStrength);
}