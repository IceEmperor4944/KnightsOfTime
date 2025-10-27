#pragma once

#include "attack.h"
#include "object.h"

//static void lPunch(const Object& obj) {
//	colliders_t lPunchCols;
//	std::shared_ptr<Collider> farOutCol = std::make_shared<Hitbox>(Vector2{ 100.0f, 50.0f }, Vector2{ obj.position.x + 75.0f, obj.position.y + 20.0f }, 10.0f, 0.0f);
//	lPunchCols.push_back(farOutCol);
//	std::vector<colliders_t> finalCols;
//	finalCols.push_back(lPunchCols);
//	finalCols.push_back(lPunchCols);
//	finalCols.push_back(lPunchCols);
//	finalCols.push_back(lPunchCols);
//	auto lPunch = std::make_shared<Attack>(finalCols/*, "defaultPunch.png", finalCols.size()*/);
//
//	for (auto& col : lPunch->PlayAttackFrame(lPunch->currentFrame)) {
//		obj.colliders.push_back(col);
//	}
//};