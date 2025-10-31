#pragma once
#include "object.h"

using objects_t = std::vector<std::shared_ptr<Object>>;

class Scene {
public:
	Scene(const std::string& title, int width, int height, int animFrameSpeed);
	virtual ~Scene();

	virtual void Initialize() = 0;
	virtual void Update(float timestep) = 0;
	virtual void FixedUpdate() = 0;

	virtual void BeginDraw();
	virtual void EndDraw();
	virtual void Draw() = 0;
	virtual void DrawGUI() = 0;

	bool IsQuit() { return WindowShouldClose(); }

	static constexpr float fixedTimestep = 1.0f / 60.0f;

	//OBJECT
	std::shared_ptr<Object> CreateObject(Object::Type type, std::string tag, const Vector2& position, float mass,
		std::string filename, float gravScale, float jumpHeight, float moveSpeed);
	std::shared_ptr<Object> CreateObject(Object::Type type, std::string tag, const Vector2& position, float mass,
		std::string filename, float health);

	friend class Object;

	//DRAW
	void DrawRectangles(const Vector2& world, const Vector2& size, const Color& color) const;
	void DrawTextures(const Texture2D& texture, const float posX, const float posY, const Color& tint) const;

	void SetBackgroundTexture(std::string filename = "defaultBackground.png") { background = LoadTexture(filename.c_str()); }
	AABB GetAABB() { return AABB{ Vector2{width * 0.5f, height * 0.5f}, Vector2{width * 0.5f, height * 0.5f} }; }
public:
	int width = 0;
	int height = 0;

	bool showFPS = true;
	int animFrameSpeed = 0;

	Texture2D background;

	objects_t objects;
};