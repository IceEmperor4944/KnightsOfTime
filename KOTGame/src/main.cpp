#include "includes.h"
#include <iostream>

int main() {
	const int screenWidth = 1920;
	const int screenHeight = 1080;

	Scene* scene = new GameScene("Knights of Time", screenWidth, screenHeight);

	std::string filename = "resources/defaultGround.png";
	scene->CreateObject(SOLID, "Ground", { 0.0f, 720.0f }, 0.0f, filename);

	filename = "resources/default.png";
	scene->CreateObject(CONTROL, "Player1", { 0, 0 }, 1.0f, filename, 1.0f, 25.0f, 5.0f);
	/*//Check is texture invalid
	Texture2D tex = LoadTexture(filename.c_str());
	if (!IsTextureValid(tex)) {
		std::cout << "Invalid Texture: " << filename << std::endl;
		return 1;
	}*/

	for (Object* obj : scene->GetObjects()) {
		if (obj->tag == "Player1" || obj->tag == "Player2") {
			Collider* col = new Hurtbox(Hurtbox::Type::Hurt, obj->size, obj->position);
		}
		else if (obj->tag == "Ground") {
			Collider* col = new Hurtbox(Hurtbox::Type::Invuln, obj->size, obj->position);
		}
	}

	float timeAccum = 0.0f;
	while (!WindowShouldClose()) {
		scene->Update(GetFrameTime());
		timeAccum += std::min(GetFrameTime(), 0.5f);
		while (timeAccum >= Scene::fixedTimestep) {
			scene->FixedUpdate();
			timeAccum -= Scene::fixedTimestep;
		}
		scene->BeginDraw();
		scene->Draw();
		//for (auto obj : scene->objects) std::cout << "Time: " << GetTime() << " Object Pos - X: " << obj->position.x << " Y: " << obj->position.y << std::endl;
		scene->DrawGUI();
		scene->EndDraw();
	}

	CloseWindow();
	return 0;
}