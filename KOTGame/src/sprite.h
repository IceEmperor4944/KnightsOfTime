#pragma once

#include "raylib.h"

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

	void UpdateFrame(int frame) {
		frameRec.x = (float)frame * frameWidth;
	}

	void Draw(Vector2 position, bool hFlip, Color tint = WHITE) const {
		Rectangle rect = frameRec;
		rect.width = (hFlip ? -frameRec.width : frameRec.width);

		//DrawRectangleV(position, { frameRec.width, frameRec.height }, RED);
		DrawTextureRec(texture, rect, position, tint);
	}

	void AdvanceFrame(int& currentFrame, float& frameTimer, int animSpeed, float timestep) {
		frameTimer += timestep;
		//std::cout << "##KOT: CurrentFrame: " << currentFrame << std::endl;

		if (frameTimer >= (1.0f / animSpeed)) {

			//atk.PlayAttackFrame(obj);
			//UpdateFrame(obj.currentFrame);
			//obj.sprite = std::make_shared<Texture2D>(GetSpriteFrame());

			currentFrame++;
			frameTimer = 0.0f;

			if (currentFrame >= numFrames) {
				currentFrame = /*numFrames - 1*/0;
				frameTimer = 0.0f;
				/*obj.animPlay = false;
				obj.state = CSTATE::Idle;*/
			}
		}

		UpdateFrame(currentFrame);
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