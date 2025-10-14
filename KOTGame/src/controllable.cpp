#include "controllable.h"

void Controllable::Step(float dt) {
	//walk
	if (IsKeyDown(KEY_A)) position += { -moveSpeed, 0 };
	if (IsKeyDown(KEY_D)) position += {  moveSpeed, 0 };

	//apply gravity
	velocity.y += 9.8f * gravScale * mass * dt;

	//jump
	if (grounded && IsKeyPressed(KEY_W)) {
		velocity.y += -jumpHeight;
	}

	position += velocity;
	//check collision with ground, set grounded, vel.y=0
}