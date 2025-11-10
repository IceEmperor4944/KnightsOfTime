#pragma once

#include "attack.h"
#include "object.h"
#include "checks.h"
#include <string>
#include <iostream>

struct Sprite {
public:
	Sprite(std::string filename, int numFrames) : filename{ filename }, numFrames { numFrames } {
		texture = LoadTexture(filename.c_str());
	}

	Texture2D GetSpriteFrame(int frame) const {
		int frameSize = texture.width / numFrames;
		Rectangle frameRec = { 0.0f, 0.0f, (float)frameSize, (float)texture.height }; // Example: 6 frames horizontally

		frameRec.x = (float)((frame)*frameSize);
		auto image = LoadImageFromTexture(texture);
		ImageCrop(&image, frameRec);
		return LoadTextureFromImage(image);
	}

	Texture2D PlaySpriteAnim(Controllable& obj, Attack atk, float timestep) const {
		obj.frameTimer += timestep;
		if (obj.frameTimer >= (1.0f / obj.frameSpeed)) {
			std::cout << "##KOT: Sprite " << texture.id << " Current Frame: " << obj.currentFrame << std::endl;
			
			atk.PlayAttackFrame(obj);
			obj.sprite = GetSpriteFrame(obj.currentFrame); //Set object texture as current frame

			obj.currentFrame++;
			obj.frameTimer = 0.0f;
			if (obj.currentFrame >= numFrames) {
				obj.currentFrame = 0;
				obj.animPlay = false;
				obj.state = CSTATE::Idle;
			}
		}

		return obj.sprite;
	}
public:
	int numFrames;
	Texture2D texture;

	std::string filename;
};