#include "manager.h"

void GameManager::Initialize() {
	scene->Initialize();

	scene->width = (int)screenSize.x;
	scene->height = (int)screenSize.y;
}

void GameManager::Update(float timestep) {
	auto menu = std::dynamic_pointer_cast<MenuScene>(scene);
	auto game = std::dynamic_pointer_cast<GameScene>(scene);

	scene->Update(timestep);
	if (menu) {
		//std::cout << "##KOT: Scene: MENU" << std::endl;

		scene->showFPS = false;

		Rectangle rec = { ((scene->width * 0.5f) - (menu->button->width * 0.5f)), ((scene->height * 0.5f) - (menu->button->height * 0.5f)),
			(float)menu->button->width, (float)menu->button->height };
		if (CheckCollisionPointRec(GetMousePosition(), rec) && IsMouseButtonReleased(MOUSE_BUTTON_LEFT)) {
			StartGame();
		}
	}
	else if (game) {
		scene->showFPS = true;

		if (game->gameOver) {
			game->gameOver = false;

			ClearBackground(BLACK);
			EndGame();
		}
	}

	scene->BeginDraw();
	scene->Draw();
	scene->DrawGUI();
	scene->EndDraw();
}

void GameManager::FixedUpdate() {
	scene->FixedUpdate();
}

void GameManager::StartGame() {
	scene = std::make_shared<GameScene>(scene->animFrameSpeed);
	scene->width = (int)screenSize.x;
	scene->height = (int)screenSize.y;
	scene->Initialize();

	std::string filename = "ground.json";
	scene->CreateObject(SOLID, "Ground", Vector2{ scene->width * 0.5f, (float)(scene->height - (scene->height * 0.125f))/*960.0f, 900.0f*/ }, 0.0f, filename, 10000); //Create Ground Object
	//CheckTexture(filename); //Check for Valid Texture

	filename = "attacks.json";
	scene->CreateObject(CONTROL, "Player1", Vector2{ 640.0f, 560.0f }, 1.0f, filename, 300, 1.0f, 12.0f, 500.0f, "Default"); //Create Player 1
	//CheckTexture(filename);

	scene->CreateObject(CONTROL, "Player2", Vector2{ 1280.0f, 560.0f }, 1.0f, filename, 300, 1.0f, 12.0f, 500.0f, "Default");//Create Player 2
	/*
	//CheckTexture(filename);

	//Check for Objects in Scene
	//CheckSceneObjects(scene->objects);

	////Set Colliders for Objects
	//for (auto& obj : scene->objects) {
	//	std::shared_ptr<Collider> col;

	//	//If player object
	//	if (obj->tag == "Player1") {
	//		//CheckTag(obj.get(), "Player1");

	//		//Body of player
	//		col = std::make_shared<Hurtbox>(BOXTYPE::Body, Vector2{ obj->size.x, obj->size.y * 0.5f }, Vector2{ obj->position.x, obj->position.y + (obj->size.y * 0.25f) });
	//	}
	//	else if (obj->tag == "Player2") {
	//		//CheckTag(obj.get(), "Player2");

	//		//Body of player
	//		col = std::make_shared<Hurtbox>(BOXTYPE::Body, Vector2{ obj->size.x, obj->size.y * 0.5f }, Vector2{ obj->position.x, obj->position.y + (obj->size.y * 0.25f) });
	//	}
	//	//If Ground object
	//	else if (obj->tag == "Ground") {
	//		//CheckTag(obj.get(), "Ground");

	//		//Body of Ground
	//		col = std::make_shared<Hurtbox>(BOXTYPE::Body, obj->size, obj->position);
	//	}
	//	obj->colliders.push_back(col);
	//}
	*/
}

void GameManager::EndGame() {
	scene = std::make_shared<MenuScene>(scene->animFrameSpeed);
	scene->width = (int)screenSize.x;
	scene->height = (int)screenSize.y;
	scene->Initialize();
}