#pragma once
#include "scene.h"
#include "sprite.h"

class GameScene : public Scene {
public:
	GameScene(const std::string& title, int width, int height, int animFrameSpeed) : Scene(title, width, height, animFrameSpeed) {}
	~GameScene() { Scene::~Scene(); }

	void Initialize() override;
	void Update(float timestep) override;
	void FixedUpdate() override;

	void BeginDraw() override;
	void EndDraw() override;
	void Draw() override;
	void DrawGUI() override;
public:
	std::unique_ptr<Sprite> healthBar;
	std::unique_ptr<Sprite> healthBorder;
	std::unique_ptr<Sprite> player1Headshot;
	std::unique_ptr<Sprite> player2Headshot;
};