#include "controllable.h"
#include "states.h"

void Controllable::Initialize(std::string filename) {
	Read(filename);

	curAnim = character + "IdleSprite";
	StartAnim(curAnim);
	auto curAttack = character + "IdleAttack";
	StartAttack(curAttack);

	size = Vector2{ anims[curAnim]->frameRec.width, anims[curAnim]->frameRec.height };
}

void Controllable::Step(float dt) {
	//grounded = false;

	//Input
	if (state != CSTATE::Punch && state != CSTATE::Kick /*&& !attackCanceled*/) {
		if (tag == "Player1") {
			//punch
			if (grounded && IsKeyPressed(KEY_F)) {
				if (state != CSTATE::Punch) {
					currentFrame = 0;
					state = CSTATE::Punch;
					soundPlay = LoadSound("audio/heeyah.wav");
					PlaySound(soundPlay);
				}
			}

			//kick
			else if (grounded && IsKeyPressed(KEY_V)) {
				if (state != CSTATE::Kick) {
					currentFrame = 0;
					state = CSTATE::Kick;
					soundPlay = LoadSound("audio/heeyah.wav");
					PlaySound(soundPlay);
				}
			}
			//walk
			else if (IsKeyDown(KEY_A)) {
				//animPlay = false;
				if (state != CSTATE::Move) {
					currentFrame = 0;
					state = CSTATE::Move;
				}
				velocity.x = 0.0f;
				velocity.x += -moveSpeed * dt;
			}
			else if (IsKeyDown(KEY_D)) {
				//animPlay = false;
				if (state != CSTATE::Move) {
					currentFrame = 0;
					state = CSTATE::Move;
				}
				velocity.x = 0.0f;
				velocity.x += moveSpeed * dt;
			}
			else if (grounded) {
				velocity.x = 0.0f;
				if (state != CSTATE::Idle) {
					currentFrame = 0;
					state = CSTATE::Idle;
				}
			}
			else {
				if (state != CSTATE::Air) {
					currentFrame = 0;
					state = CSTATE::Air;
				}
			}

			//jump
			if (grounded && IsKeyPressed(KEY_SPACE)) {
				//std::cout << "##KOT: Jump Pressed" << std::endl;
				/*velocity.y = 0.0f;
				position.y -= 100;*/
				//animPlay = false;
				if (state != CSTATE::Jump) {
					currentFrame = 0;
					state = CSTATE::Jump;
				}

				position.y += -2 * jumpHeight;
				velocity.y += -jumpHeight;
			}

			/*if (!grounded) state = CSTATE::Air;

			if (grounded && velocity.x == 0.0f) state = CSTATE::Idle;*/
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
				//std::cout << "##KOT: Jump Pressed" << std::endl;
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

	//set state air if in air
	//if (velocity.y != 0 || !grounded) state = CSTATE::Air;

	//apply gravity
	velocity.y += 9.8f * gravScale * mass * dt;

	//make it actually move
	position += velocity;
}

void Controllable::FixedStep(float timestep) {
	/*std::cout << "----------------------------------------------" << std::endl;
	std::cout << "##KOT: Object " << tag << " at Position (" << position.x << ", " << position.y << ")" << std::endl;*/
	switch (state) {
	case Controllable::State::Idle:
		//std::cout << "##KOT: Object " << tag << " in State: Idle" << std::endl;
		/*colliders.clear();
		if (!animPlay) {
			currentFrame = 0;
			animPlay = true;
		}*/
		PlayState(*this, timestep, "Idle");
		velocity.x = 0.0f;
		break;
	case Controllable::State::Move:
		//play move anim
		//std::cout << "##KOT: Object " << tag << " in State: Move" << std::endl;
		/*colliders.clear();
		if (!animPlay) {
			currentFrame = 0;
			animPlay = true;
		}
		colliders.push_back(std::make_shared<Hurtbox>(BOXTYPE::Body, Vector2{ size.x * 0.5f, size.y * 0.5f }, Vector2{ position.x, position.y + (size.y * 0.25f) }));*/
		PlayState(*this, timestep, "Walk");
		break;
	case Controllable::State::Air:
		//play jump anim
		//std::cout << "##KOT: Object " << tag << " in State: Air" << std::endl;
		grounded = false;
		PlayState(*this, timestep, "Air");
		break;
	case Controllable::State::Jump:
		PlayState(*this, timestep, "Jump");
		break;
	case Controllable::State::Punch: {
		//std::cout << "##KOT: Object " << tag << " in State: Punch" << std::endl;
		/*colliders.clear();
		if (!animPlay) {
			currentFrame = 0;
			animPlay = true;
			state = CSTATE::Idle;
		}*/
		PlayState(*this, timestep, "LPunch");
		break;
	}
	case Controllable::State::Kick: {
		//std::cout << "##KOT: Object " << tag << " in State: Punch" << std::endl;
		PlayState(*this, timestep, "HKick");
		break;
	}
	default:
		break;
	}
	//std::cout << "----------------------------------------------" << std::endl;

	//UpdateColliderPositions();
}

void Controllable::Read(const std::string& filename) {
	rapidjson::Document document;
	if (!Json::Load(filename, document)) {
		std::cerr << "Error: Could not load character data from " << filename << std::endl;
		return;
	}

	std::vector<std::string> attackNames = { "Idle", "Walk", "Air", "Jump", "LPunch", "MPunch", "HPunch", "LKick", "MKick", "HKick" };

	for (const auto& base : attackNames) {
		std::string attackKey = character + base + "Attack";
		std::string spriteKey = character + base + "Sprite";

		auto attack = std::make_shared<Attack>();
		attack->Read(document, attackKey);

		if (!attack->colliders.empty()) {
			attacks[attackKey] = attack;
		}

		auto anim = std::make_shared<Sprite>();
		anim->Read(document, spriteKey);

		if (anim->numFrames > 0) {
			anims[spriteKey] = anim;
		}
	}

	/*std::cout << "##KOT: Read " << attacks.size() << " Attacks & "
		<< anims.size() << " Sprites for Object " << character << std::endl;*/
}

colliders_t Controllable::CheckColliders(const std::vector<std::shared_ptr<Object>>& other) {
	std::vector<std::shared_ptr<Collider>> outCols;

	for (auto& col : colliders) {
		//std::cout << "##KOT: Collider of Object " << tag << " - " << character << " at Position (" << col->position.x << ", " << col->position.y << ")" << std::endl;

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

								if (grounded) {
									velocity.x = 0.0f;
								}
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

									//needs more tweaking in future - shifts character based on fraction of size

									obj->position.x = (leftRight < rightLeft) ? obj->GetAABB().min().x + (size.x * 0.45f) : obj->GetAABB().max().x - (size.x * 0.45f);
								}
							}
						}
						else if (hurtCol->type == BOXTYPE::Hurt) {
							for (auto& oCol : obj->colliders) {
								auto oHitCol = std::dynamic_pointer_cast<Hitbox>(oCol);
								if (oHitCol && !isHit) {
									health -= oHitCol->damage;
									velocity += oHitCol->kbDir * oHitCol->kbStrength;
								}
							}
						}
					}
					/*std::cout << "----------------------------------------------" << std::endl;*/
				}
			}
		}
	}

	Object::CheckColliders(other);

	return outCols;
}