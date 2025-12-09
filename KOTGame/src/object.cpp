#include "object.h"
#include "attack.h"
#include <memory>

void Object::Step(float dt) {
	auto curSprite = GetCurrentSprite();
	curSprite->AdvanceFrame(currentFrame, frameTimer, frameSpeed, dt);

	//UpdateColliderPositions();
}

void Object::Draw(Vector2 position, Color tint) {
	//UpdateColliderPositions();

	std::shared_ptr<Sprite> curSprite = GetCurrentSprite();

	if (curSprite) {
		float centerX = position.x - (size.x * 0.5f);
		float centerY = position.y - (size.y * 0.5f);

		curSprite->Draw({centerX, centerY}, spriteFlip, tint);

		if (drawCols) {
			for (auto& col : colliders) {
				auto aabb = col->GetAABB();
				//std::cout << "##KOT: Collider AABB: " << std::endl;
				//std::cout << "##KOT: CENTER | X - " << aabb.center.x << ", Y - " << aabb.center.y << std::endl;
				//std::cout << "##KOT: MIN | X - " << aabb.min().x << ", Y - " << aabb.min().y << std::endl;
				//std::cout << "##KOT: MAX | X - " << aabb.max().x << ", Y - " << aabb.max().y << std::endl;
				auto hurt = std::dynamic_pointer_cast<Hurtbox>(col);
				auto hit = std::dynamic_pointer_cast<Hitbox>(col);
				Color color = WHITE;
				if (hurt) {
					switch (hurt->type) {
					case BOXTYPE::Body:
						color = WHITE;
						break;
					case BOXTYPE::Block:
						color = BLUE;
						break;
					case BOXTYPE::Hurt:
						color = GREEN;
						break;
					case BOXTYPE::Invuln:
						color = YELLOW;
						break;
					default:
						color = WHITE;
						break;
					}
				}
				else if (hit) {
					color = RED;
				}

				DrawRectangleLines((int)aabb.min().x, (int)aabb.min().y, (int)col->size.x, (int)col->size.y, color);
			}
		}
	}
	else std::cerr << "Warning: Cannot draw. Sprite key '" << curAnim << "' not found or pointer is nullptr." << std::endl;
}

void Object::Read(const std::string& filename) {
	rapidjson::Document document;
	if (!Json::Load(filename, document)) {
		std::cerr << "Error: Could not load character data from " << filename << std::endl;
		return;
	}

	auto attack = std::make_shared<Attack>();
	std::string attackKey = tag + "IdleAttack";
	attack->Read(document, attackKey);
	if (!attack->colliders.empty()) {
		attacks[attackKey] = attack;
	}

	auto anim = std::make_shared<Sprite>();
	std::string spriteKey = tag + "IdleSprite";
	anim->Read(document, spriteKey);

	if (anim->numFrames > 0) {
		anims[spriteKey] = anim;
	}

	std::cout << "##KOT: Read " << attacks.size() << " Attacks & "
		<< anims.size() << " Sprites for Object " << tag << std::endl;
}

void Object::UpdateColliderPositions() {
	//std::cout << "##KOT: Object " << tag << " at Position (" << this->position.x << ", " << this->position.y << ")." << std::endl;

	for (auto& col : colliders) {
		float xOffset = spriteFlip ? -col->posOffset.x : col->posOffset.x;

		//std::cout << "##KOT: Collider Position Offset: (" << col->posOffset.x << ", " << col->posOffset.y << ")." << std::endl;
		col->position = { this->position.x + xOffset, this->position.y + col->posOffset.y };
		//std::cout << "##KOT: Collider New Position: (" << col->position.x << ", " << col->position.y << ")." << std::endl;
	}
}

void Object::StartAnim(const std::string& animKey) {
	if (anims.count(animKey)) {
		curAnim = animKey;
		currentFrame = 0;
		frameTimer = 0.0f;
	}
}

void Object::StartAttack(const std::string& attackKey) {
	if (attacks.count(attackKey)) {
		curAttack = attacks.at(attackKey);
	}
	else {
		curAttack = nullptr;
	}
}