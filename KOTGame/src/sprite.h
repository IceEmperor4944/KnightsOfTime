#pragma once

#include "attack.h"
#include "controllable.h"
#include "checks.h"

class Sprite {
public:
	Sprite(std::string filename, int numFrames) : filename{ filename }, numFrames{ numFrames } {
		texture = LoadTexture(filename.c_str());

		//printf("Loading %s | Width: %i, Height: %i, NumFrames: %i\n", filename.c_str(), texture.width, texture.height, numFrames);

		frameWidth = texture.width / numFrames;
		frameRec = { 0, 0, (float)frameWidth, (float)texture.height };
	}

	~Sprite() {
		if (IsTextureValid(texture)) {
			UnloadTexture(texture);
		}
	}

	Texture2D GetSpriteFrame() const {
		/*int frameSize = (int)((float)texture.width / numFrames);
		Rectangle frameRec = { 0.0f, 0.0f, (float)frameSize, (float)texture.height }; // Example: 6 frames horizontally

		frameRec.x = (float)((frame)*frameSize);*/
		auto image = std::make_unique<Image>(LoadImageFromTexture(texture));
		ImageCrop(image.get(), frameRec);
		return LoadTextureFromImage(*image);
	}

	void UpdateFrame(int frame) {
		frameRec.x = (float)frame * frameWidth;
	}

	void Draw(Vector2 position, bool hFlip, Color tint = WHITE) const {
		Rectangle rect = frameRec;
		rect.width = (hFlip ? -frameRec.width : frameRec.width);
		
		DrawTextureRec(texture, rect, position, tint);
	}

	/*Texture2D PlaySpriteAnim(Controllable& obj, Attack atk, float timestep) const {
		obj.frameTimer += timestep;
		if (obj.frameTimer >= (1.0f / obj.frameSpeed)) {
			//std::cout << "##KOT: Sprite " << texture.id << " Current Frame: " << obj.currentFrame << std::endl;

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
	}*/

	void PlaySpriteAnim(Controllable& obj, Attack atk, float timestep) {
		obj.frameTimer += timestep;

		if (obj.frameTimer >= (1.0f / obj.frameSpeed)) {

			atk.PlayAttackFrame(obj);
			UpdateFrame(obj.currentFrame);
			obj.sprite = std::make_shared<Texture2D>(GetSpriteFrame());

			obj.currentFrame++;
			obj.frameTimer = 0.f;

			if (obj.currentFrame >= numFrames) {
				obj.currentFrame = 0;
				obj.animPlay = false;
				obj.state = CSTATE::Idle;
			}
		}
	}

public:
	Texture2D texture;
	Rectangle frameRec;
	int frameWidth;
	int numFrames;

	std::string filename;
};