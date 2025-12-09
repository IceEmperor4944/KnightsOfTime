#pragma once
#include "object.h"

using objects_t = std::vector<std::shared_ptr<Object>>;

class Scene {
public:
	Scene(int animFrameSpeed);
	virtual ~Scene();

	virtual void Initialize() = 0;
	virtual void Update(float timestep) = 0;
	virtual void FixedUpdate() = 0;

	virtual void BeginDraw();
	virtual void EndDraw();
	virtual void Draw() = 0;
	virtual void DrawGUI() = 0;

	bool IsQuit() { return WindowShouldClose(); }

	static constexpr float fixedTimestep = 1.0f / 24.0f;

	//OBJECT
	std::shared_ptr<Object> CreateObject(Object::Type type, std::string tag, const Vector2& position, float mass,
		std::string filename, int health, float gravScale, float jumpHeight, float moveSpeed, std::string character);
	std::shared_ptr<Object> CreateObject(Object::Type type, std::string tag, const Vector2& position, float mass,
		std::string filename, int health);

	friend class Object;

	//DRAW
	void DrawRectangles(const Vector2& world, const Vector2& size, const Color& color) const;
	void DrawTextures(const Texture2D& texture, const float posX, const float posY, const Color& tint) const;

	void SetBackgroundTexture(std::string filename = "sprites/defaultBackground.png") { background = std::make_shared<Texture2D>(LoadTexture(filename.c_str())); }
	AABB GetAABB() { return AABB{ Vector2{width * 0.5f, height * 0.5f}, Vector2{width * 0.5f, height * 0.5f} }; }
public:
	int width = 0;
	int height = 0;

	bool showFPS = false;
	int animFrameSpeed = 0;

	std::shared_ptr<Texture2D> background;
	RenderTexture2D cache;
	bool shouldRedraw = true;

	Music musicBG;

	objects_t objects;
};