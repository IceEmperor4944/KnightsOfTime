#include "controllable.h"
#include "states.h"

void Controllable::Step(float dt) {
	//Input
	if (state != CSTATE::Punch /*&& !attackCanceled*/) {
		if (tag == "Player1") {
			//walk
			if (IsKeyDown(KEY_A)) {
				velocity.x = 0.0f;
				velocity.x += -moveSpeed * dt;
				//animPlay = false;
				currentFrame = 0;
				state = CSTATE::Move;
			}
			else if (IsKeyDown(KEY_D)) {
				velocity.x = 0.0f;
				velocity.x += moveSpeed * dt;
				//animPlay = false;
				currentFrame = 0;
				state = CSTATE::Move;
			}
			else {
				velocity.x = 0.0f;
				currentFrame = 0;
				state = CSTATE::Idle;
			}

			//jump
			if (grounded && IsKeyPressed(KEY_SPACE)) {
				std::cout << "##KOT: Jump Pressed" << std::endl;
				/*velocity.y = 0.0f;
				position.y -= 100;*/
				position.y += -2 * jumpHeight;
				velocity.y += -jumpHeight;
				//animPlay = false;
				currentFrame = 0;
				state = CSTATE::Air;
			}

			//punch
			if (IsKeyPressed(KEY_F)) {
				state = CSTATE::Punch;
				currentFrame = 0;
				PlaySound(LoadSound("audio/heeyah.mp3"));
			}
		}
		else if (tag == "Player2") {
			//walk
			if (IsKeyDown(KEY_J)) {
				velocity.x = 0.0f;
				velocity.x += -moveSpeed * dt;
				//animPlay = false;
				currentFrame = 0;
				state = CSTATE::Move;
			}
			else if (IsKeyDown(KEY_L)) {
				velocity.x = 0.0f;
				velocity.x += moveSpeed * dt;
				//animPlay = false;
				currentFrame = 0;
				state = CSTATE::Move;
			}
			else {
				velocity.x = 0.0f;
				currentFrame = 0;
				state = CSTATE::Idle;
			}

			//jump
			if (grounded && IsKeyPressed(KEY_I)) {
				std::cout << "##KOT: Jump Pressed" << std::endl;
				/*velocity.y = 0.0f;
				position.y -= 100;*/
				position.y += -2 * jumpHeight;
				velocity.y += -jumpHeight;
				//animPlay = false;
				currentFrame = 0;
				state = CSTATE::Air;
			}

			//punch
			if (IsKeyPressed(KEY_H)) {
				state = CSTATE::Punch;
				currentFrame = 0;
				PlaySound(LoadSound("audio/heeyah.mp3"));
			}
		}
	}

	//if (grounded && velocity == Vector2{ 0, 0 }) state = CSTATE::Idle;
	if (velocity.y != 0 || !grounded) state = CSTATE::Air;

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


void Controllable::FixedStep(float timestep) {
	std::cout << "----------------------------------------------" << std::endl;
	std::cout << "##KOT: Object " << tag << " at Position (" << position.x << ", " << position.y << ")" << std::endl;
	switch (state) {
	case Controllable::State::Idle:
		std::cout << "##KOT: Object " << tag << " in State: Idle" << std::endl;
		//if (!animPlay) {
		colliders.clear();
		//currentFrame = 0;
		//animPlay = true;
		Idle(*this, timestep);
		//}
		velocity.x = 0.0f;
		break;
	case Controllable::State::Move:
		//play move anim
		std::cout << "##KOT: Object " << tag << " in State: Move" << std::endl;
		//velocity.x < -0.1f ? anim.hFlip = true : false
		colliders.clear();
		colliders.push_back(std::make_shared<Hurtbox>(BOXTYPE::Body, Vector2{ size.x, size.y * 0.5f }, Vector2{ position.x, position.y + (size.y * 0.25f) }));
		break;
	case Controllable::State::Air:
		//play jump anim
		std::cout << "##KOT: Object " << tag << " in State: Air" << std::endl;
		grounded = false;
		colliders.clear();
		colliders.push_back(std::make_shared<Hurtbox>(BOXTYPE::Body, Vector2{ size.x, size.y * 0.5f }, Vector2{ position.x, position.y + (size.y * 0.25f) }));
		break;
	case Controllable::State::Punch: {
		std::cout << "##KOT: Object " << tag << " in State: Punch" << std::endl;
		//if (!animPlay) {
		colliders.clear();
		//currentFrame = 0;
		//animPlay = true;
		LPunch(*this, timestep);
		//}
		break;
	}
	default:
		break;
	}
	std::cout << "----------------------------------------------" << std::endl;
}

colliders_t Controllable::CheckColliders(const std::vector<std::shared_ptr<Object>>& other) {
	std::vector<std::shared_ptr<Collider>> outCols;

	for (auto& col : colliders) {
		for (auto& obj : other) {
			for (auto& oCol : obj->colliders) {
				if (obj->tag != tag && col->Intersects(oCol)) {
					/*std::cout << "----------------------------------------------" << std::endl;
					std::cout << "##KOT: Object " << tag << " Makes Collision at " << GetTime() << std::endl;*/
					outCols.push_back(col);

					//Hurtbox
					auto hurtCol = std::dynamic_pointer_cast<Hurtbox>(col);
					if (hurtCol) {
						/*std::cout << "##KOT: Object " << tag << " is Hurtbox" << std::endl;
						std::cout << "##KOT: Object Other is Type " << hurtCol->GetType() << std::endl;*/
						if (hurtCol->type == BOXTYPE::Body) {
							if (obj->tag == "Ground" && velocity.y >= 0) {
								/*std::cout << "##KOT: Object " << tag << " Collides with Ground" << std::endl;*/
								position.y = obj->GetAABB().min().y - (size.y * 0.5f);
								velocity.y = 0.0f;
								grounded = true;
							}
							else {
								grounded = false;
							}

							if (obj->tag.starts_with("Player")) {
								auto oHurtCol = std::dynamic_pointer_cast<Hurtbox>(oCol);
								if (oHurtCol && oHurtCol->type == BOXTYPE::Body) {
									velocity.x = 0.0f;
									auto leftRight = fabsf(GetAABB().min().x - obj->GetAABB().max().x);
									auto rightLeft = fabsf(GetAABB().max().x - obj->GetAABB().min().x);
									obj->position.x = (leftRight < rightLeft) ? obj->GetAABB().min().x : obj->GetAABB().max().x;
								}
							}
						}
						else if (hurtCol->type == BOXTYPE::Hurt) {
							for (auto& oCol : obj->colliders) {
								auto oHitCol = std::dynamic_pointer_cast<Hitbox>(oCol);
								if (oHitCol) health -= oHitCol->damage;
							}
						}
					}
					/*std::cout << "----------------------------------------------" << std::endl;*/
				}
			}
		}
	}

	return outCols;
}