#pragma once

#include "gamescene.h"
#include "menuscene.h"

class GameManager {
public:
	GameManager() = default;
	GameManager(const std::string& title, Vector2 screenSize, int animFrameSpeed) : screenSize{ screenSize } {
		InitWindow((int)screenSize.x, (int)screenSize.y, title.c_str());
		SetTargetFPS(60);
		scene = std::make_shared<MenuScene>(animFrameSpeed);
		InitAudioDevice();
	};

	~GameManager() {
		CloseAudioDevice();
		CloseWindow();
	}

	void Initialize();
	void Update(float timestep);
	void FixedUpdate();

	void StartGame();
	void EndGame();

	void ShowObjectColliders(bool shouldShow) { for (auto& obj : scene->objects) { obj->drawCols = shouldShow; } }
public:
	std::shared_ptr<Scene> scene{ nullptr };

	Vector2 screenSize;

	bool showCols = false;
};