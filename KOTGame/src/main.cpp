#include "manager.h"
#include <iostream>

int main(int argc, char** argv) {
	SetTraceLogLevel(LOG_NONE);

	const int screenWidth = 1920;
	const int screenHeight = 1080;

	auto game = std::make_unique<GameManager>("Knights of Time", Vector2{ screenWidth, screenHeight }, 24);
	game->Initialize();

	RenderTexture2D staticCanvas = LoadRenderTexture(screenWidth, screenHeight);
	//auto groundTex = LoadTexture("sprites/defaultGround.png");

	// --- Draw the static world ONCE ---
	BeginTextureMode(staticCanvas);
	ClearBackground(BLACK);
	DrawTexture(*game->scene->background, 0, 0, WHITE);
	//DrawTexture(groundTex, 960, 900, WHITE);
	//DrawRectangle(100, 100, 50, 50, BLUE); // A static platform
	//DrawRectangle(200, 150, 50, 50, BLUE); // Another static platform
	EndTextureMode();

	float timeAccum = 0.0f;

	while (!WindowShouldClose()) {
	//DrawTexture(staticCanvas.texture, 0, 0, WHITE);
		game->Update(GetFrameTime());
		timeAccum += std::min(GetFrameTime(), 0.5f);
		while (timeAccum >= Scene::fixedTimestep) {
			game->FixedUpdate();
			timeAccum -= Scene::fixedTimestep;
		}
	}

	return 0;
}