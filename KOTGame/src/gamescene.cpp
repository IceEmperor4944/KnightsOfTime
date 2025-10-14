#include "gamescene.h"

void GameScene::Initialize() {
	//
}

void GameScene::Update(float timestep) {
	for (auto obj : objects) {
		obj->Step(timestep);

		//bump obj to screen, border (10 sides, 50 bottom)
		if (obj->position.x < 10)		obj->position.x = 10;
		if (obj->position.x > width -	obj->size.x - 10)
			obj->position.x = width -	obj->size.x - 10;
		if (obj->position.y > height -	obj->size.y - 360)
			obj->position.y = height -	obj->size.y - 360;
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
	for (auto obj : objects) {
		DrawTextures(obj->sprite, { obj->position.x, obj->position.y }, WHITE);
	}
}

void GameScene::DrawGUI() {
	//
}