#pragma once

#include "scene.h"
#include "sprite.h"

class MenuScene : public Scene {
public:
	MenuScene(int animFrameSpeed) : Scene(animFrameSpeed) {}
	~MenuScene() { Scene::~Scene(); }

	void Initialize() override;
	void Update(float timestep) override;
	void FixedUpdate() override;

	void BeginDraw() override;
	void EndDraw() override;
	void Draw() override;
	void DrawGUI() override;
public:
	std::unique_ptr<Texture2D> button;
};