#include "hurtbox.h"

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

bool Hurtbox::Intersects(std::shared_ptr<Collider> other) {
	AABB colA = GetAABB();
	AABB colB = other->GetAABB(); //AABB{ {0, 0}, {0, 0} };

	bool output1 = (colA.min().x <= colB.max().x); //obj A left side overlaps obj B right side
	bool output2 = (colA.max().x >= colB.min().x); //obj A right side overlaps obj B left side
	bool output3 = (colA.min().y <= colB.max().y); //obj A top overlaps obj B bottom
	bool output4 = (colA.max().y >= colB.min().y); //obj A bottom overlaps obj B top

	//Check for collision bounds
	/*std::cout << "##KOT: Col A over Range (" << colA.min().x << ", " << colA.min().y
		<< ") - (" << colA.max().x << ", " << colA.max().y << ")" << std::endl;
	std::cout << "##KOT: Col B of Object '" << other->tag <<  "' over Range ("
		<< colB.min().x << ", " << colB.min().y << ") - (" << colB.max().x << ", " << colB.max().y << ")" << std::endl;
	std::cout << "------------------------------------------------------------" << std::endl;*/

	return output1 && output2 && output3 && output4;
}

void Hurtbox::Read(const json_t& value) {
	Collider::Read(value);

	std::string btype;
	READ_DATA(value, btype);

	if (btype == "Body") type = BOXTYPE::Body;
	else if (btype == "Hurt") type = BOXTYPE::Hurt;
	else if (btype == "Block") type = BOXTYPE::Block;
	else if (btype == "Invuln") type = BOXTYPE::Invuln;
}