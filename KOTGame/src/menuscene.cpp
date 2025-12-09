#include "menuscene.h"

void MenuScene::Initialize() {
	//musicBG = LoadMusicStream("audio/moonsetter.mp3");
	//musicBG.looping = true;
	//SetMusicVolume(musicBG, 0.5f);
	//PlayMusicStream(musicBG);

	button = std::make_unique<Texture2D>(LoadTexture("sprites/playButton.png"));
	SetBackgroundTexture("github/titleAndKnightSwordHelm.jpg");
}

void MenuScene::Update(float timestep) {
	//UpdateMusicStream(musicBG);
}

void MenuScene::FixedUpdate() {
	for (auto& obj : objects) {
		obj->FixedStep(fixedTimestep);
	}
}

void MenuScene::BeginDraw() {
	Scene::BeginDraw();
}

void MenuScene::EndDraw() {
	Scene::EndDraw();
}

void MenuScene::Draw() {
	DrawTexture(*button, (int)((width * 0.5f) - (button->width * 0.5f)), (int)((height * 0.5f) - (button->height * 0.5f)), WHITE);
}

void MenuScene::DrawGUI() {
	//BeginTextureMode(*cache);
	//ClearBackground(BLACK);

	//EndTextureMode();

	//// Just draw the "Frame Cache" to the screen.
	//// This texture is the "previous set of textures" you wanted to retain.
	//DrawTextureRec(cache->texture, Rectangle{ 0, 0, (float)cache->texture.width, (float)-cache->texture.height }, Vector2{ 0, 0 }, WHITE);
}