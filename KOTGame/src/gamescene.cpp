#include "gamescene.h"
#include "controllable.h"

void GameScene::Initialize() {
	cache = std::make_unique<RenderTexture2D>(LoadRenderTexture(width, height));
	healthBar = std::make_unique<Sprite>("sprites/defaultHealthBar.png", 31);
	healthBorder = std::make_unique<Sprite>("sprites/defaultHealthBorder.png", 1);
	player1Headshot = std::make_unique<Sprite>("sprites/defaultHeadshot.png", 1);
	player2Headshot = std::make_unique<Sprite>("sprites/default2Headshot.png", 1);

	musicBG = LoadMusicStream("audio/moonsetter.mp3");
	musicBG.looping = true;
	SetMusicVolume(musicBG, 0.5f);

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

		shouldRedraw = shouldRedraw || obj->health != obj->prevHealth; //tells gui to update health bars if either player has changed
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
		Rectangle sourceRec = { 0, 0, (float)obj->sprite->width, (float)obj->sprite->height };

		//flip over y
		sourceRec.width = (obj->spriteFlip) ? -sourceRec.width : sourceRec.width; // Make the width negative if flipped

		DrawTextureRec(*obj->sprite, sourceRec, { centerX, centerY }, WHITE);

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
	if (shouldRedraw) {
		BeginTextureMode(*cache);
		ClearBackground(BLACK);
		/*for (auto& obj : objects) {
			if (obj->tag.starts_with("Player")) {
				//get health sprite
				Vector2 barSize = { (float)healthBar->texture.width  / healthBar->numFrames, (float)healthBar->texture.height };
				Rectangle sourceRec = { 0, 0, barSize.x, barSize.y };
				Vector2 position = { 100, 100 };

				//set position & direction of health
				if (obj->tag == "Player1") {
					//std::cout << "##KOT: Drawing P1 Health" << std::endl;
					position = { width * 0.05f, height * 0.05f };
				}
				if (obj->tag == "Player2") {
					//std::cout << "##KOT: Drawing P2 Health" << std::endl;
					sourceRec.width = -sourceRec.width; //flip bar
					position = { width - (width * 0.05f) - fabsf(sourceRec.width), height * 0.05f };
				}

				//std::cout << "----------------------------------------------------" << std::endl;
				//frame of health
				int frame = obj->health / 10;
				auto barFrame = healthBar->GetSpriteFrame(frame);
				//std::cout << "##KOT: Frame " << frame << " texture is " << (IsTextureValid(barFrame) ? "" : "NOT ") << "Valid" << std::endl;
				//std::cout << "##KOT: Width: " << barFrame.width << " | Height: " << barFrame.height << std::endl;
				//std::cout << "##KOT: Width: " << barFrame.width << " | Height: " << barFrame.height << std::endl;
				DrawTextureRec(barFrame, sourceRec, position, WHITE);

				//border of health
				auto barBorder = healthBorder->GetSpriteFrame(0);
				//std::cout << "##KOT: Border texture is " << (IsTextureValid(barBorder) ? "" : "NOT ") << "Valid" << std::endl;
				DrawTextureRec(barBorder, sourceRec, position, WHITE);
				//std::cout << "----------------------------------------------------" << std::endl;

				//UnloadTexture(barFrame);
				//UnloadTexture(barBorder);
			}
		}*/

		for (auto& obj : objects) {
			if (obj->tag.starts_with("Player")) {
				// Calculate position of health bar
				Vector2 healthPos = { 100, 100 };
				Vector2 iconPos = { 100, 100 };
				bool shouldFlip = false;
				if (obj->tag == "Player1") {
					iconPos = { width * 0.05f, height * 0.05f };
					player1Headshot->UpdateFrame(0);
					player1Headshot->Draw(iconPos, shouldFlip);

					healthPos = { width * 0.15f, height * 0.05f };
				}
				else if (obj->tag == "Player2") {
					shouldFlip = true;
					iconPos = { width - (width * 0.05f) - (player2Headshot->frameRec.width), height * 0.05f };
					player2Headshot->UpdateFrame(0);
					player2Headshot->Draw(iconPos, shouldFlip);

					healthPos = { width - (width * 0.15f) - (healthBar->frameRec.width), height * 0.05f };
				}

				// Determine health frame from 0 ? numFrames-1
				int frame = obj->health / 10;
				if (frame < 0) frame = 0;
				if (frame >= healthBar->numFrames) frame = healthBar->numFrames - 1;

				// Update the sprite's source rectangle to this frame
				healthBar->UpdateFrame(frame);
				healthBar->Draw(healthPos, shouldFlip);

				// Draw border sprite (always frame 0)
				healthBorder->UpdateFrame(0);
				healthBorder->Draw(healthPos, shouldFlip);
			}
		}

		EndTextureMode();

		shouldRedraw = false;
	}

	// Just draw the "Frame Cache" to the screen.
	// This texture is the "previous set of textures" you wanted to retain.
	DrawTextureRec(cache->texture, Rectangle{ 0, 0, (float)cache->texture.width, (float)-cache->texture.height }, Vector2{ 0, 0 }, WHITE);
}