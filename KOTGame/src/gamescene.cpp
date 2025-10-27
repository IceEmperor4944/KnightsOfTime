#include "gamescene.h"
#include "controllable.h"
#include <iostream>

void GameScene::Initialize() {
	//
}

void GameScene::Update(float timestep) {
	for (auto& obj : objects) {
		if (obj->tag != "Ground") {
			obj->Step(timestep);

			obj->CheckColliders(objects);
			
			//bump obj to screen, border (10 sides, 50 bottom)
			if (obj->position.x < 10)		obj->position.x = 10;
			if (obj->position.x > width -	(obj->size.x * 0.5f) - 10)
				obj->position.x = width -	(obj->size.x * 0.5f) - 10;
			/*if (obj->position.y > height -	(obj->size.y * 0.5f) - 360) {
				obj->position.y = height -	(obj->size.y * 0.5f) - 360;
				auto cont = std::dynamic_pointer_cast<Controllable>(obj);
				if (cont) {
					cont->grounded = true;
					(fabsf(cont->velocity.x) > 0.01f) ? cont->state = CSTATE::Move : CSTATE::Idle;
					obj = cont;
				}
			}*/
		}
	}
}

void GameScene::FixedUpdate() {
	for (auto& obj : objects) obj->FixedStep(fixedTimestep);
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

		if (obj->drawCols) {
			for (auto& col : obj->colliders) {
				auto aabb = col->GetAABB();
				DrawRectangleLines((int)aabb.min().x, (int)aabb.min().y, (int)col->size.x, (int)col->size.y, WHITE);
			}
		}
	}
}

void GameScene::DrawGUI() {
	//
}