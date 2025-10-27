#include "hurtbox.h"
#include "object.h"
#include <iostream>

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
	AABB colA = GetAABB();
	AABB colB = other->GetAABB(); //AABB{ {0, 0}, {0, 0} };

	bool output1 = (colA.min().x <= colB.max().x); //obj A left side overlaps obj B right side
	bool output2 = (colA.max().x >= colB.min().x); //obj A right side overlaps obj B left side
	bool output3 = (colA.min().y <= colB.max().y); //obj A bottom overlaps obj B top
	bool output4 = (colA.max().y >= colB.min().y); //obj A top overlaps obj B bottom

	if (output1 && output2 && output3 && output4) {
		std::cout << "##KOT: Object at Position " << position.x << ", " << position.y << " of Size " << size.x
			<< ", " << size.y << " Intersects Object at Position " << other->position.x << ", " << other->position.y
			<< " of Size " << other->size.x << ", " << other->size.y << std::endl;
	}

	return output1 && output2 && output3 && output4;
}