#include "gamescene.h"
#include "controllable.h"

void GameScene::Initialize() {
	cache = LoadRenderTexture(width, height);
	healthBar = std::make_unique<Sprite>("sprites/defaultHealthBar.png", 31);
	healthBorder = std::make_unique<Sprite>("sprites/defaultHealthBorder.png", 1);
	player1Headshot = std::make_unique<Sprite>("sprites/defaultHeadshot.png", 1);
	player2Headshot = std::make_unique<Sprite>("sprites/default2Headshot.png", 1);

	//musicBG = LoadMusicStream("audio/moonsetter.mp3");
	//musicBG.looping = true;
	//SetMusicVolume(musicBG, 0.5f);
	//PlayMusicStream(musicBG);

	//should call set background depending on stage select
	SetBackgroundTexture();
}

void GameScene::Update(float timestep) {
	for (auto& obj : objects) {
		obj->CheckColliders(objects);
		obj->Step(timestep);
		//std::cout << "##KOT: Object " << obj->tag << " at Position (" << obj->position.x << ", " << obj->position.y << ")" << std::endl;

		if (obj->tag != "Ground") {
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


			shouldRedraw = shouldRedraw || obj->health != obj->prevHealth; //tells gui to update health bars if either player has changed
		}
	}

	//UpdateMusicStream(musicBG);
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
	ClearBackground(BLACK);
	for (auto& obj : objects) {
		obj->Draw(obj->position);
	}
}

void GameScene::DrawGUI() {
	//if (shouldRedraw) {
	BeginTextureMode(cache);
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

	//shouldRedraw = false;
//}

	DrawTextureRec(cache.texture, Rectangle{ 0, 0, (float)cache.texture.width, (float)-cache.texture.height }, Vector2{ 0, 0 }, WHITE);
}