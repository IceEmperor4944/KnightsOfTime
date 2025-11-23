#pragma once

#include "attack.h"
#include "controllable.h"

class Sprite {
public:
	Sprite() = default;
	Sprite(std::string filename, int numFrames) : filename{ filename }, numFrames{ numFrames } {
		Initialize();
	}

	~Sprite() {
		if (IsTextureValid(texture)) {
			UnloadTexture(texture);
		}
	}

	void Initialize() {
		texture = LoadTexture(filename.c_str());

		if (numFrames <= 0) {
			numFrames = 1;
		}

		//printf("Loading %s | Width: %i, Height: %i, NumFrames: %i\n", filename.c_str(), texture.width, texture.height, numFrames);		
		frameWidth = texture.width / numFrames;
		frameRec = { 0, 0, (float)frameWidth, (float)texture.height };
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

	void PlaySpriteAnim(Controllable& obj, Attack& atk, float timestep) {
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

	void Read(const json_t& value, std::string name) {
		if (!value.HasMember(name.c_str()) || !value[name.c_str()].IsObject()) {
			std::cerr << "Could not read Json value: " << name << std::endl;
			return;
		}

		// get the data
		READ_DATA(value[name.c_str()], filename);
		READ_DATA(value[name.c_str()], numFrames);

		if (numFrames <= 0) {
			std::cerr << "Error: Number of Frames must be at least 1. Defaulting to 1 to prevent crash." << std::endl;
			numFrames = 1;
		}

		Initialize();
	}

public:
	Texture2D texture{};
	Rectangle frameRec{};
	int frameWidth = 0;
	int numFrames = 0;

	std::string filename{};
};