//#define _WINSOCK_DEPRECATED_NO_WARNINGS
//#define ENET_IMPLEMENTATION
//#include "enet.h"

#include "includes.h"
#include <iostream>

int main() {
	const int screenWidth = 1920;
	const int screenHeight = 1080;

	std::unique_ptr<Scene> scene = std::make_unique<GameScene>("Knights of Time", screenWidth, screenHeight, 8);

	std::string filename = "sprites/defaultGround.png";
	scene->CreateObject(SOLID, "Ground", Vector2{ 960.0f, 900.0f }, 0.0f, filename, 100.0f); //Create Ground Object
	CheckTexture(filename); //Check for Valid Texture

	filename = "sprites/default.png";
	scene->CreateObject(CONTROL, "Player1", { 640.0f, 0 }, 1.0f, filename, 1.0f, 5.0f, 500.0f); //Create Player 1
	CheckTexture(filename);

	filename = "sprites/default2.png";
	scene->CreateObject(CONTROL, "Player2", { 1280.0f, 0 }, 1.0f, filename, 1.0f, 10.0f, 5.0f);   //Create Player 2
	CheckTexture(filename);

	//Check for Objects in Scene
	CheckSceneObjects(scene->objects);

	//Set Colliders for Objects
	for (auto& obj : scene->objects) {
		std::shared_ptr<Collider> col;

		//If player object
		if (obj->tag == "Player1") {
			CheckTag(obj.get(), "Player1");

			//Body of player
			col = std::make_shared<Hurtbox>(BOXTYPE::Body, obj->size, obj->position);
		}
		else if (obj->tag == "Player2") {
			CheckTag(obj.get(), "Player2");

			//Body of player
			col = std::make_shared<Hurtbox>(BOXTYPE::Body, obj->size, obj->position);
		}
		//If Ground object
		else if (obj->tag == "Ground") {
			CheckTag(obj.get(), "Ground");

			//Body of Ground
			col = std::make_shared<Hurtbox>(BOXTYPE::Body, obj->size, obj->position);
		}
		obj->colliders.push_back(col);
	}

	//Check for Colliders per Object
	for (auto& obj : scene->objects) {
		CheckObjectColliders(obj.get());
	}

	float timeAccum = 0.0f;

	while (!WindowShouldClose()) {
		timeAccum += std::min(GetFrameTime(), 0.5f);
		while (timeAccum >= Scene::fixedTimestep) {
			scene->FixedUpdate();
			timeAccum -= Scene::fixedTimestep;
		}
		scene->Update(GetFrameTime());
		scene->BeginDraw();
		scene->Draw();
		/*for (auto obj : scene->objects) std::cout << "Time: " << GetTime() << " Object Pos - X: "
			<< obj->position.x << " Y: " << obj->position.y << std::endl;*/
		scene->DrawGUI();
		scene->EndDraw();
	}

	return 0;
}