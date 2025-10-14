#pragma once
#include "object.h"

using objects_t = std::vector<Object*>;

class Scene {
public:
	Scene(const std::string& title, int width, int height);
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
	Object* CreateObject(Object::Type type, std::string tag, const Vector2& position, float mass,
		std::string filename, float gravScale = 0.0f, float jumpHeight = 0.0f, float moveSpeed = 0.0f);
	objects_t& GetObjects() { return objects; }

	friend class Object;

	//DRAW
	void DrawRectangles(const Vector2& world, const Vector2& size, const Color& color) const;
	void DrawTextures(const Texture2D& texture, const Vector2& world, const Color& tint) const;

	void SetBackgroundTexture(std::string filename = "resources/defaultBackground.png") { background = LoadTexture(filename.c_str()); }
	AABB GetAABB() { return AABB{ Vector2{width * 0.5f, height * 0.5f}, Vector2{width * 0.5f, height * 0.5f} }; }
public:
	int width = 0;
	int height = 0;

	bool showFPS = false;

	Texture2D background;

	objects_t objects;
};