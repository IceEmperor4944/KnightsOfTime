#pragma once
#include "hurtbox.h"
#include "hitbox.h"

using colliders_t = std::vector<std::shared_ptr<Collider>>;

struct Attack {
public:
	Attack(std::vector<colliders_t> colliders/*, std::string filename, int frames*/) : colliders{ colliders }/*, frames{ frames } {
		anim = LoadTexture(filename.c_str());
	}*/ {}

	colliders_t PlayAttackFrame(int frame/*, Vector2& position*/) {
		colliders_t output;

		//Rectangle frameRec = { 0.0f, 0.0f, (float)anim.width / frames, (float)anim.height }; // Example: 6 frames horizontally

		for (auto& col : colliders[frame]) {
			output.push_back(col);
		}

		//frameRec.x = (float)frame * (float)anim.width / 6;
		//DrawTextureRec(anim, frameRec, position, WHITE); // Draw the current frame

		return output;
	}
public:
	std::vector<colliders_t> colliders;
	Texture2D anim;
	int frames = 0;
};