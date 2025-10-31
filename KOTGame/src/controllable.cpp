#include "controllable.h"
#include "punch.h"

void Controllable::Step(float dt) {
	//Input
	if (state != CSTATE::Punch /*&& !attackCanceled*/) {

	if (tag == "Player1") {
		//walk
		if (IsKeyDown(KEY_A)) {
			velocity.x = 0.0f;
			velocity.x += -moveSpeed * dt;
			state = CSTATE::Move;
		}
		else if (IsKeyDown(KEY_D)) {
			velocity.x = 0.0f;
			velocity.x += moveSpeed * dt;
			state = CSTATE::Move;
		}
		else {
			velocity.x = 0.0f;
		}

		//jump
		if (grounded && IsKeyPressed(KEY_SPACE)) {
			std::cout << "##KOT: Jump Pressed" << std::endl;
			/*velocity.y = 0.0f;
			position.y -= 100;*/
			velocity.y += -jumpHeight;
			state = CSTATE::Air;
		}

		//punch
		if (IsKeyPressed(KEY_F)) {
			state = CSTATE::Punch;
		}

		////basic punch
		//if (IsKeyPressed(KEY_A)) {
		//	lPunch(/*std::make_shared<Controllable>(this), */);			
		//}
	}
	else if (tag == "Player2") {
		//walk
		if (IsKeyDown(KEY_J)) {
			velocity.x += -moveSpeed * dt;
			state = CSTATE::Move;
		}
		else if (IsKeyDown(KEY_L)) {
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

	if (grounded && velocity == Vector2{0, 0}) state = CSTATE::Idle;

	//check ground
	/*std::cout << "----------------------------------------------" << std::endl;
	std::cout << "##KOT: Object " << tag << " is " << (grounded ? "" : "NOT ") << "Grounded" << std::endl;
	std::cout << "##KOT: Object " << tag << " Y Velocity is " << velocity.y << std::endl;
	std::cout << "----------------------------------------------" << std::endl;*/
		
	//apply gravity
	velocity.y += 9.8f * gravScale * mass * dt;

	//make it actually move
	position += velocity;
	}
}

void Controllable::FixedStep(float timestep) {
	switch (state) {
	case Controllable::State::Idle:
		//play idle anim

		grounded = true;
		velocity.x = 0.0f;

		colliders.clear();
		colliders.push_back(std::make_shared<Hurtbox>(BOXTYPE::Body, size, position));
		break;
	case Controllable::State::Move:
		//play move anim
		//velocity.x < -0.1f ? anim.hFlip = true : false
		colliders.clear();
		colliders.push_back(std::make_shared<Hurtbox>(BOXTYPE::Body, size, position));
		break;
	case Controllable::State::Air:
		//play jump anim
		grounded = false;
		colliders.clear();
		colliders.push_back(std::make_shared<Hurtbox>(BOXTYPE::Body, size, position));
		break;
	case Controllable::State::Punch: {
		std::cout << "##KOT: Hit State Attack" << std::endl;
		LPunch(*this, timestep);
		break;
	}
	default:
		break;
	}
}

colliders_t Controllable::CheckColliders(const std::vector<std::shared_ptr<Object>>& other) {
	std::vector<std::shared_ptr<Collider>> outCols;

	for (auto& col : colliders) {
		for (auto& obj : other) {
			if (obj->tag != tag && col->Intersects(obj)) {
				/*std::cout << "----------------------------------------------" << std::endl;
				std::cout << "##KOT: Object " << tag << " Makes Collision at " << GetTime() << std::endl;*/
				outCols.push_back(col);
								
				//Hurtbox
				auto hurtCol = std::dynamic_pointer_cast<Hurtbox>(col);
				if (hurtCol) {
					/*std::cout << "##KOT: Object " << tag << " is Hurtbox" << std::endl;
					std::cout << "##KOT: Object is Type " << hurtCol->GetType() << std::endl;*/
					if (hurtCol->type == BOXTYPE::Body) {
						if (obj->tag == "Ground" && velocity.y >= 0) {
							/*std::cout << "##KOT: Object Collides with Ground" << std::endl;*/
							position.y = obj->GetAABB().min().y - (size.y * 0.5f);
							velocity.y = 0.0f;
							grounded = true;
						}
						else {
							grounded = false;
						}
					}
				}
				/*std::cout << "----------------------------------------------" << std::endl;*/
			}
		}
	}

	return outCols;
}