#pragma once

#include "object.h"

static void CheckTexture(std::string filename) {
	Texture2D tex = LoadTexture(filename.c_str());
	if (!IsTextureValid(tex)) {
		std::cout << "##KOT: Invalid Texture: " << filename << std::endl;
	}
	else {
		std::cout << "##KOT: Texture " << filename << " exists with " << "Texture Width: " << tex.width << " and Texture Height: " << tex.height << std::endl;
	}
}

static void CheckTag(Object* obj, std::string tag) {
	std::cout << "##KOT: Object " << obj->tag << " DOES " << (obj->tag != tag ? "NOT " : "") << "match Tag " << tag << std::endl;
}

static void CheckSceneObjects(std::vector<std::shared_ptr<Object>> objects) {
	for (auto& obj : objects) {
		std::cout << "##KOT: Scene contains Object " << obj->tag << " at Position " << obj->position.x << ", " << obj->position.y << std::endl;
	}
}

static void CheckObjectColliders(Object* obj) {
	if (!obj->colliders.empty()) {
		std::cout << "##KOT: Object " << obj->tag << " contains:" << std::endl;
		for (auto& col : obj->colliders) {
			auto hurtCol = std::dynamic_pointer_cast<Hurtbox>(col);
			if (hurtCol) {
				std::cout << "- Hurtbox of Type " << hurtCol->GetType() << ", Size (" << col->size.x << ", "
					<< col->size.y << ") at Position (" << col->position.x << ", " << col->position.y << ")" << std::endl;
			}
			else {
				std::cout << "- Hitbox of Size (" << col->size.x << ", "
					<< col->size.y << ") at Position (" << col->position.x << ", " << col->position.y << ")" << std::endl;
			}
		}
	}
	else {
		std::cout << "##KOT: Object " << obj->tag << " is EMPTY" << std::endl;
	}
}