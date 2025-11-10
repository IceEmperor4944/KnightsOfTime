#include "gamescene.h"
#include "controllable.h"
#include "sprite.h"

void GameScene::Initialize() {
	//musicBG = LoadMusicStream("audio/moonsetter.mp3");
	//musicBG.looping = true;
	//SetMusicVolume(musicBG, 0.5f);

	//PlayMusicStream(musicBG);


	//should call set background depending on stage select
}

void GameScene::Update(float timestep) {
	for (auto& obj : objects) {
		if (obj->tag != "Ground") {
			obj->CheckColliders(objects);
			obj->Step(timestep);

			//CheckObjectColliders(obj.get());

			for (auto& obj2 : objects) {
				if (obj2->tag != "Ground") {
					if (obj->position.x > obj2->position.x) {
						obj->spriteFlip = true;
						obj2->spriteFlip = false;
					}
					else if (obj->position.x < obj2->position.x) {
						obj->spriteFlip = false;
						obj2->spriteFlip = true;
					}
				}
			}

			//bump obj to screen, border (10 sides, 50 bottom)
			if (obj->position.x < 10)		obj->position.x = 10;
			if (obj->position.x > width - (obj->size.x * 0.5f) - 10)
				obj->position.x = width - (obj->size.x * 0.5f) - 10;
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

	UpdateMusicStream(musicBG);
}

void GameScene::FixedUpdate() {
	for (auto& obj : objects) {
		obj->FixedStep(fixedTimestep);
	}
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
		Rectangle sourceRec = { 0, 0, (float)obj->sprite.width, (float)obj->sprite.height };

		//flip over y
		sourceRec.width = (obj->spriteFlip) ? -sourceRec.width : sourceRec.width; // Make the width negative if flipped

		DrawTextureRec(obj->sprite, sourceRec, { centerX, centerY }, WHITE);

		//draw object colliders
		if (obj->drawCols) {
			for (auto& col : obj->colliders) {
				auto aabb = col->GetAABB();
				auto hurt = std::dynamic_pointer_cast<Hurtbox>(col);
				auto hit = std::dynamic_pointer_cast<Hitbox>(col);
				Color color = WHITE;
				if (hurt) {
					switch (hurt->type) {
					case BOXTYPE::Body:
						color = WHITE;
						break;
					case BOXTYPE::Block:
						color = BLUE;
						break;
					case BOXTYPE::Hurt:
						color = GREEN;
						break;
					case BOXTYPE::Invuln:
						color = YELLOW;
						break;
					default:
						color = WHITE;
						break;
					}
				}
				else if (hit) {
					color = RED;
				}

				DrawRectangleLines((int)aabb.min().x, (int)aabb.min().y, (int)col->size.x, (int)col->size.y, color);
			}
		}
	}
}

void GameScene::DrawGUI() {
	/*for (auto& obj : objects) {
		if (obj->tag.starts_with("Player")) {*/
			//get health sprite
			auto bar = std::make_unique<Sprite>("sprites/healthBar.png", 33);
			Vector2 barSize = { (float)bar->texture.width * (1 / bar->numFrames), (float)bar->texture.height };
			Rectangle sourceRec = { 0, 0, barSize.x, barSize.y };
			Vector2 position = { 100, 100 };

			/*//set position & direction of health
			if (obj->tag == "Player1") {
				//std::cout << "##KOT: Drawing P1 Health" << std::endl;
				position = { width * 0.5f, height * 0.5f };
			}
			if (obj->tag == "Player2") {
				//std::cout << "##KOT: Drawing P2 Health" << std::endl;
				sourceRec.width = -sourceRec.width; //flip bar
				position = { width - (width * 0.5f) - fabsf(sourceRec.width), height * 0.5f };
			}*/

			/*//std::cout << "----------------------------------------------------" << std::endl;
			//background of health bar
			auto barBG = bar->GetSpriteFrame(32);
			//std::cout << "##KOT: Background texture is " << (IsTextureValid(barBG) ? "" : "NOT ") << "Valid" << std::endl;
			DrawTextureRec(barBG, sourceRec, position, WHITE);

			//frame of health
			int frame = obj->health / 10;
			auto barFrame = bar->GetSpriteFrame(frame);
			std::cout << "##KOT: Frame " << frame << " texture is " << (IsTextureValid(barFrame) ? "" : "NOT ") << "Valid" << std::endl;
			std::cout << "##KOT: Width: " << barFrame.width << " | Height: " << barFrame.height << std::endl;
			std::cout << "##KOT: Width: " << barFrame.width << " | Height: " << barFrame.height << std::endl;
			DrawTextureRec(barFrame, sourceRec, position, WHITE);*/

			//border of health
			auto barBorder = bar->GetSpriteFrame(30);
			//std::cout << "##KOT: Border texture is " << (IsTextureValid(barBorder) ? "" : "NOT ") << "Valid" << std::endl;
			DrawTextureRec(barBorder, sourceRec, position, WHITE);
			//std::cout << "----------------------------------------------------" << std::endl;
		/*}
	}*/
}