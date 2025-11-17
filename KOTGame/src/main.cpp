//#define _WINSOCK_DEPRECATED_NO_WARNINGS
//#define ENET_IMPLEMENTATION
//#include "enet.h"

#include "includes.h"
#include <iostream>

int main(int argc, char** argv) {
	SetTraceLogLevel(LOG_NONE);

	const int screenWidth = 1920;
	const int screenHeight = 1080;

	std::unique_ptr<Scene> scene = std::make_unique<GameScene>("Knights of Time", screenWidth, screenHeight, 24);
	scene->Initialize();

	RenderTexture2D staticCanvas = LoadRenderTexture(screenWidth, screenHeight);
	auto groundTex = LoadTexture("sprites/defaultGround.png");

	// --- Draw the static world ONCE ---
	BeginTextureMode(staticCanvas);
	ClearBackground(BLACK);
	DrawTexture(*scene->background, 0, 0, WHITE);
	//DrawTexture(groundTex, 960, 900, WHITE);
	//DrawRectangle(100, 100, 50, 50, BLUE); // A static platform
	//DrawRectangle(200, 150, 50, 50, BLUE); // Another static platform
	EndTextureMode();

	std::string filename = "sprites/defaultGround.png";
	scene->CreateObject(SOLID, "Ground", Vector2{ 960.0f, 900.0f }, 0.0f, filename, 10000); //Create Ground Object
	//CheckTexture(filename); //Check for Valid Texture

	filename = "sprites/default.png";
	scene->CreateObject(CONTROL, "Player1", { 640.0f, 560.0f }, 1.0f, filename, 300, 1.0f, 12.0f, 500.0f); //Create Player 1
	//CheckTexture(filename);

	filename = "sprites/default2.png";
	scene->CreateObject(CONTROL, "Player2", { 1280.0f, 560.0f }, 1.0f, filename, 300, 1.0f, 12.0f, 500.0f);//Create Player 2
	//CheckTexture(filename);

	//Check for Objects in Scene
	//CheckSceneObjects(scene->objects);

	//Set Colliders for Objects
	for (auto& obj : scene->objects) {
		std::shared_ptr<Collider> col;

		//If player object
		if (obj->tag == "Player1") {
			//CheckTag(obj.get(), "Player1");

			//Body of player
			col = std::make_shared<Hurtbox>(BOXTYPE::Body, Vector2{ obj->size.x, obj->size.y * 0.5f }, Vector2{ obj->position.x, obj->position.y + (obj->size.y * 0.25f) });
		}
		else if (obj->tag == "Player2") {
			//CheckTag(obj.get(), "Player2");

			//Body of player
			col = std::make_shared<Hurtbox>(BOXTYPE::Body, Vector2{ obj->size.x, obj->size.y * 0.5f }, Vector2{ obj->position.x, obj->position.y + (obj->size.y * 0.25f) });
		}
		//If Ground object
		else if (obj->tag == "Ground") {
			//CheckTag(obj.get(), "Ground");

			//Body of Ground
			col = std::make_shared<Hurtbox>(BOXTYPE::Body, obj->size, obj->position);
		}
		obj->colliders.push_back(col);
	}

	////Check for Colliders per Object
	//for (auto& obj : scene->objects) {
	//	CheckObjectColliders(obj.get());
	//}

	float timeAccum = 0.0f;

	while (!WindowShouldClose()) {
		timeAccum += std::min(GetFrameTime(), 0.5f);
		while (timeAccum >= Scene::fixedTimestep) {
			scene->FixedUpdate();
			timeAccum -= Scene::fixedTimestep;
		}
		scene->Update(GetFrameTime());
		scene->BeginDraw();
		scene->DrawGUI();
		scene->Draw();
		scene->EndDraw();
	}

	return 0;
}