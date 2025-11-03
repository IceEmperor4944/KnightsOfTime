#pragma once

#include "attack.h"
#include "object.h"
#include <iostream>

static void LPunch(Controllable& obj, float timestep) {
	colliders_t lPunchCols;
	std::shared_ptr<Collider> farOutCol = std::make_shared<Hitbox>(Vector2{ 100.0f, 50.0f }, Vector2{ obj.position.x + 75.0f, obj.position.y + 20.0f }, 10, 0.0f);
	lPunchCols.push_back(std::make_shared<Hurtbox>(BOXTYPE::Body, Vector2{ obj.size.x, obj.size.y * 0.5f }, Vector2{ obj.position.x, obj.position.y + (obj.size.y * 0.25f) }));
	lPunchCols.push_back(farOutCol);
	std::vector<colliders_t> finalCols;
	for (int i = 0; i < 4; i++) finalCols.push_back(lPunchCols);
	auto lPunch = std::make_shared<Attack>(finalCols, "sprites/defaultPunch.png");

	obj.frameTimer += timestep;
	std::cout << "----------------------------------" << std::endl;
	std::cout << "##KOT: Attacking" << std::endl;
	std::cout << "##KOT: Frame Timer: " << obj.frameTimer << std::endl;
	if (obj.frameTimer >= (1.0f / obj.frameSpeed)) {
		std::cout << "##KOT: Next Frame" << std::endl;
		std::cout << "----------------------------------" << std::endl;
		obj.frameTimer = 0.0f;
		obj.currentFrame++;
		for (auto& col : lPunch->PlayAttackFrame(obj)) obj.colliders.push_back(col);
		if (obj.currentFrame >= (int)lPunch->colliders.size()) {
			std::cout << "----------------------------------" << std::endl;
			std::cout << "##KOT: Attack Over" << std::endl;
			std::cout << "----------------------------------" << std::endl;
			obj.state = CSTATE::Idle;
			obj.currentFrame = 0;
			obj.animPlay = false;
		}
	}
};

static void Idle(Controllable& obj, float timestep) {
	colliders_t idleCols;
	std::shared_ptr<Collider> hitCol1 = std::make_shared<Hurtbox>(BOXTYPE::Hurt, Vector2{ 50.0f, 70.0f }, Vector2{ obj.position.x, obj.position.y - 70.0f });
	std::shared_ptr<Collider> hitCol2 = std::make_shared<Hurtbox>(BOXTYPE::Hurt, Vector2{ 100.0f, 160.0f }, Vector2{ obj.position.x, obj.position.y + 40.0f });
	idleCols.push_back(std::make_shared<Hurtbox>(BOXTYPE::Body, Vector2{ obj.size.x, obj.size.y * 0.5f }, Vector2{ obj.position.x, obj.position.y + (obj.size.y * 0.25f) }));
	idleCols.push_back(hitCol1);
	idleCols.push_back(hitCol2);
	std::vector<colliders_t> finalCols;
	for (int i = 0; i < 10; i++) finalCols.push_back(idleCols);
	auto idle = std::make_shared<Attack>(finalCols, "sprites/defaultIdle.png");
	obj.frameTimer += timestep;
	if (obj.frameTimer >= (1.0f / obj.frameSpeed)) {
		obj.currentFrame++;
		obj.frameTimer = 0.0f;
		for (auto& col : idle->PlayAttackFrame(obj)) obj.colliders.push_back(col);
		if (obj.currentFrame >= (int)idle->colliders.size()) {
			obj.currentFrame = 0;
			obj.animPlay = false;
		}
	}
}