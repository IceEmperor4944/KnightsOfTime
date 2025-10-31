#pragma once
#include "hurtbox.h"
#include "hitbox.h"

struct Attack {
public:
	/// <summary>
	/// Instatiate Attack with necessary parameters.
	/// </summary>
	/// <param name="colliders">- Array of arrays of colliders. Each inner array of colliders
	/// defines those of an individual frame of attack.</param>
	/// <param name="filename">- The filename to use for animation. Should be arranged as one
	/// long line of frames, rather than a grid.</param>
	/// <param name="frameSpeed">- The rate at which frames play, i.e. FPS.</param>
	Attack(std::vector<colliders_t> colliders, std::string filename) : colliders{ colliders } {
		anim = LoadTexture(filename.c_str());
	}

	colliders_t PlayAttackFrame(Object& obj) {
		colliders_t output;

		Rectangle frameRec = { 0.0f, 0.0f, anim.width / ((float)colliders.size()), (float)anim.height }; // Example: 6 frames horizontally

		for (auto& col : colliders[obj.currentFrame-1]) {
			output.push_back(col);
		}

		frameRec.x = ((float)obj.currentFrame-1) * (float)anim.width / colliders.size();
		auto image = LoadImageFromTexture(anim);
		ImageCrop(&image, frameRec);
		obj.sprite = LoadTextureFromImage(image); //Set object texture as current frame
		//DrawTextureRec(anim, frameRec, obj.GetAABB().min(), WHITE); // Draw the current frame

		return output;
	}
public:
	std::vector<colliders_t> colliders;
	Texture2D anim;
};