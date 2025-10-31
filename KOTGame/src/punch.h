#pragma once

#include "attack.h"
#include "object.h"
#include <iostream>

static void LPunch(Controllable& obj, float timestep) {
	colliders_t lPunchCols;
	std::shared_ptr<Collider> farOutCol = std::make_shared<Hitbox>(Vector2{ 100.0f, 50.0f }, Vector2{ obj.position.x + 75.0f, obj.position.y + 20.0f }, 10.0f, 0.0f);
	lPunchCols.push_back(farOutCol);
	std::vector<colliders_t> finalCols;
	finalCols.push_back(lPunchCols);
	finalCols.push_back(lPunchCols);
	finalCols.push_back(lPunchCols);
	finalCols.push_back(lPunchCols);
	auto lPunch = std::make_shared<Attack>(finalCols, "sprites/defaultPunch.png");

	//std::cout << "##KOT: Attacking" << std::endl;
	obj.frameTimer += timestep;
	//std::cout << "----------------------------------" << std::endl;
	std::cout << "##KOT: Frame Timer: " << obj.frameTimer << std::endl;
	if (obj.frameTimer >= (1.0f / obj.frameSpeed)) {
		std::cout << "##KOT: Next Frame" << std::endl;
		//std::cout << "----------------------------------" << std::endl;
		obj.currentFrame++;
		obj.frameTimer = 0.0f;
		lPunch->PlayAttackFrame(obj);
		if (obj.currentFrame >= (int)lPunch->colliders.size()) {
			//std::cout << "----------------------------------" << std::endl;
			std::cout << "##KOT: Attack Over" << std::endl;
			//std::cout << "----------------------------------" << std::endl;
			obj.state = CSTATE::Idle;
			obj.currentFrame = 0;
		}
	}
};