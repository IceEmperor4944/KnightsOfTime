#include "controllable.h"
#include <iostream>

void Controllable::Step(float dt) {
	//walk
	if (IsKeyDown(KEY_A)) position += { -moveSpeed, 0 };
	if (IsKeyDown(KEY_D)) position += {  moveSpeed, 0 };

	//apply gravity
	velocity.y += 9.8f * gravScale * mass * dt;

	//jump
	if (grounded && IsKeyPressed(KEY_W)) {
		velocity.y += -jumpHeight;
		grounded = false;
	}

	position += velocity;
}

std::vector<std::shared_ptr<Collider>> Controllable::CheckColliders(const std::vector<std::shared_ptr<Object>>& other) {
	std::vector<std::shared_ptr<Collider>> outCols;

	for (auto& col : colliders) {
		for (auto& obj : other) {
			if (!col->Intersects(obj) && obj->tag != tag) {
				outCols.push_back(col);
				std::cout << "##KOT: Object " << tag << " Collides with " << obj->tag << std::endl;
				//Hurtbox
				auto hurtCol = std::dynamic_pointer_cast<Hurtbox>(col);
				if (hurtCol != nullptr && hurtCol->type == BOXTYPE::Body) {
					if (obj->tag == "Ground") {
						position.y = obj->position.y - size.y;
						velocity.y = 0.0f;
						grounded = true;
					}
				}
			}
		}
	}

	return outCols;
}