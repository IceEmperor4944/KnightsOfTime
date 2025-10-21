#include "hurtbox.h"
#include "object.h"

void Hurtbox::Initialize() {
	//
}

std::string Hurtbox::GetType() {
	switch (type) {
	case Hurtbox::Type::Body:
		return "BODY";
		break;
	case Hurtbox::Type::Block:
		return "BLOCK";
		break;
	case Hurtbox::Type::Hurt:
		return "HURT";
		break;
	case Hurtbox::Type::Invuln:
		return "INVULN";
		break;
	default:
		return "";
		break;
	}
}

bool Hurtbox::Intersects(std::shared_ptr<Object> other) {
	/*//float distance = Vector2Distance(objA->position, objB->position);
	//float radiusX = objA->size.x + objB->size.x;
	//float radiusY = objA->size.y + objB->size.y;

	//AABB colA = objA->GetAABB();
	//AABB colB = objB->GetAABB();

	//if ((colA.min().y) < colB.min().y) 	{
	//		float overlap = (colB.min().y - colA.min().y); // calculate how far the objects have penetrated each other
	//	if (objA->tag.find("Player")) {
	//		objA->position.y += 1 * overlap; // move the first object away
	//		objA->velocity.y *= -objA->restitution; // multiple by -restituion to scale and flip velocity
	//	}
	//	if (objB->tag.find("Player")) {
	//		objB->position.y += 1 * overlap; // move the second object away
	//		objB->velocity.y *= -objB->restitution; // multiple by -restituion to scale and flip velocity
	//	}
	//}
	//else if ((colA.max().y) < colB.max().y) {
	//	float overlap = (colB.min().y - colA.min().y); // calculate how far the objects have penetrated each other
	//	if (objA->tag.find("Player")) {
	//		objA->position.y += 1 * overlap; // move the first object away
	//		objA->velocity.y *= -objA->restitution; // multiple by -restituion to scale and flip velocity
	//	}
	//	if (objB->tag.find("Player")) {
	//		objB->position.y += 1 * overlap; // move the second object away
	//		objB->velocity.y *= -objB->restitution; // multiple by -restituion to scale and flip velocity
	//	}
	//}

	//if ((colA.min().x) < colB.min().x) {
	//	float overlap = (colB.min().x - colA.min().x);
	//	if (objA->tag.find("Player")) {
	//		objA->position.x += 1 * overlap;
	//		objA->velocity.x *= -objA->restitution;
	//	}
	//	if (objB->tag.find("Player")) {
	//		objB->position.x += 1 * overlap;
	//		objB->velocity.x *= -objB->restitution;
	//	}
	//}
	//else if ((colA.max().x) < colB.max().x) {
	//	float overlap = (colB.min().x - colA.min().x);
	//	if (objA->tag.find("Player")) {
	//		objA->position.x += 1 * overlap;
	//		objA->velocity.x *= -objA->restitution;
	//	}
	//	if (objB->tag.find("Player")) {
	//		objB->position.x += 1 * overlap;
	//		objB->velocity.x *= -objB->restitution;
	//	}
	//}

	//return (distance <= radius);*/
	AABB colA = GetAABB();
	AABB colB = other->GetAABB(); //AABB{ {0, 0}, {0, 0} };

	/*for (auto& oc : other->colliders) {
		auto hc = std::dynamic_pointer_cast<Hurtbox>(oc);
		if (hc != nullptr && hc->type == BOXTYPE::Body) colB = oc->GetAABB();
	}

	if (type == BOXTYPE::Body) {*/
	return colA.min().x < colB.max().x &&
		colA.max().x > colB.min().x &&
		colA.min().y < colB.max().y &&
		colA.max().y > colB.min().y;

	/*if (other->tag == "Ground") {
		float pushA = colA.min().y;
		float pushB = colB.max().y;

		float adjustUp = fabsf(pushA - pushB);
		float adjustDown = fabsf(pushB - pushA);

		float adjust = 0.0f;
		if (adjustUp <= adjustDown) adjust = adjustUp;
		else if (adjustDown <= adjustUp) adjust = -adjustDown;

		position.y += adjust * 0.5f;
		return adjust > 0.0f;
	}
	else {
		float pushLeftA = colA.min().x;
		float pushRightA = colA.max().x;

		float pushLeftB = colB.min().x;
		float pushRightB = colB.max().x;

		float rightGap = fabsf(pushRightA - pushLeftB);
		float leftGap = fabsf(pushRightB - pushLeftA);

		float adjust = 0.0f;

		//add wall check, switch for adjust
		if (rightGap <= leftGap) adjust = rightGap;
		else if (leftGap <= rightGap) adjust = -leftGap;

		other->position.x += adjust * 0.5f;
		return adjust > 0.0f;
	}*/
	/*}

	return false;*/
}