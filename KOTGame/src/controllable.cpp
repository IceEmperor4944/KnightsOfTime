#include "controllable.h"
#include "punch.h"
#include <iostream>

void Controllable::Step(float dt) {
	//apply gravity
	velocity.y += 9.8f * gravScale * mass * dt;

	//Input
	if (tag == "Player1") {
		//walk
		if (IsKeyDown(KEY_LEFT)) {
			velocity.x += -moveSpeed * dt;
			state = CSTATE::Move;
		}
		else if (IsKeyDown(KEY_RIGHT)) {
			velocity.x += moveSpeed * dt;
			state = CSTATE::Move;
		}
		else {
			velocity.x = 0.0f;
		}


		//jump
		if (grounded && IsKeyPressed(KEY_UP)) {
			velocity.y += -jumpHeight * dt;
			state = CSTATE::Air;
		}

		//punch
		if (IsKeyPressed(KEY_Z)) {
			state = CSTATE::Punch;
		}

		////basic punch
		//if (IsKeyPressed(KEY_A)) {
		//	lPunch(/*std::make_shared<Controllable>(this), */);			
		//}
	}
	else if (tag == "Player2") {
		//walk
		if (IsKeyDown(KEY_KP_4)) {
			velocity.x += -moveSpeed * dt;
			state = CSTATE::Move;
		}
		else if (IsKeyDown(KEY_KP_6)) {
			velocity.x += moveSpeed * dt;
			state = CSTATE::Move;
		}
		else {
			velocity.x = 0.0f;
		}

		//jump
		if (grounded && IsKeyPressed(KEY_KP_8)) {
			velocity.y += -jumpHeight * dt;
			state = CSTATE::Air;
		}
	}

	//make it actually move
	position += velocity;
}

void Controllable::FixedStep(float timestep) {
	switch (state) {
	case Controllable::State::Idle:
		//play idle anim

		velocity.x = 0.0f;

		colliders.clear();
		colliders.push_back(std::make_shared<Hurtbox>(BOXTYPE::Body, size, position + (size * 0.5f)));
		break;
	case Controllable::State::Move:
		//play move anim
		//velocity.x < -0.1f ? anim.hFlip = true : false
		colliders.clear();
		colliders.push_back(std::make_shared<Hurtbox>(BOXTYPE::Body, size, position + (size * 0.5f)));
		break;
	case Controllable::State::Air:
		//play jump anim
		grounded = false;
		colliders.clear();
		colliders.push_back(std::make_shared<Hurtbox>(BOXTYPE::Body, size, position + (size * 0.5f)));
		break;
	case Controllable::State::Punch: {
		float curFrame = 0.0f;

		colliders_t lPunchCols;
		std::shared_ptr<Collider> farOutCol = std::make_shared<Hitbox>(Vector2{ 100.0f, 50.0f }, Vector2{ position.x + 75.0f, position.y + 20.0f }, 10.0f, 0.0f);
		lPunchCols.push_back(farOutCol);
		lPunchCols.push_back(std::make_shared<Hurtbox>(BOXTYPE::Body, size, position + (size * 0.5f)));
		std::vector<colliders_t> finalCols;
		finalCols.push_back(lPunchCols);
		finalCols.push_back(lPunchCols);
		finalCols.push_back(lPunchCols);
		finalCols.push_back(lPunchCols);
		auto lPunch = std::make_shared<Attack>(finalCols/*, "defaultPunch.png", finalCols.size()*/);

		for (auto& col : lPunch->PlayAttackFrame((int)curFrame)) {
			colliders.clear();
			colliders.push_back(col);
		}

		curFrame += timestep;
		break;
	}
	default:
		break;
	}
}

std::vector<std::shared_ptr<Collider>> Controllable::CheckColliders(const std::vector<std::shared_ptr<Object>>& other) {
	std::vector<std::shared_ptr<Collider>> outCols;

	for (auto& col : colliders) {
		for (auto& obj : other) {
			if (obj->tag != tag && col->Intersects(obj)) {
				outCols.push_back(col);
				std::cout << "##KOT: Object " << tag << " Collides with " << obj->tag << std::endl;
				//Hurtbox
				auto hurtCol = std::dynamic_pointer_cast<Hurtbox>(col);
				if (hurtCol != nullptr && hurtCol->type == BOXTYPE::Body) {
					if (obj->tag == "Ground") {
						position.y = obj->position.y - (obj->size.y * 0.5f) - (size.y * 0.5f);
						velocity.y = 0.0f;
						grounded = true;
					}
				}
			}
		}
	}

	return outCols;
}