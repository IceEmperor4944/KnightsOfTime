#include "gamescene.h"
#include <iostream>

void GameScene::Initialize() {
	//
}

void GameScene::Update(float timestep) {
	for (auto& obj : objects) {
		if (obj->tag != "Ground") {
			obj->Step(timestep);

			obj->CheckColliders(objects);
			/*auto cols = obj->CheckColliders(objects);
			for (auto col : cols) {
				std::cout << "##KOT: Collider of Size (" << col->size.x << ", " << col->size.y << ") has Collision" << std::endl;
			}*/

			//bump obj to screen, border (10 sides, 50 bottom)
			if (obj->position.x < 10)		obj->position.x = 10;
			if (obj->position.x > width	-	obj->size.x - 10)
				obj->position.x = width -	obj->size.x - 10;
			//if (obj->position.y > height -	obj->size.y - 360)
			//	obj->position.y = height -	obj->size.y - 360;
		}
	}
}

void GameScene::FixedUpdate() {
	//
}

void GameScene::BeginDraw() {
	Scene::BeginDraw();
}

void GameScene::EndDraw() {
	Scene::EndDraw();
}

void GameScene::Draw() {
	for (auto& obj : objects) {
		float centerX = obj->position.x - (obj->size.x * 0.5f);
		float centerY = obj->position.y - (obj->size.y * 0.5f);
		DrawTextures(obj->sprite, centerX, centerY, WHITE);
	}
}

void GameScene::DrawGUI() {
	//
}