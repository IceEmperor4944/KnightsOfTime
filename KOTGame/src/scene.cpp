#include "scene.h"
#include "solid.h"
#include "controllable.h"

Scene::Scene(const std::string& title, int width, int height) :	width{ width }, height{ height } {
	InitWindow(width, height, title.c_str());
	SetTargetFPS(120);

	SetBackgroundTexture();
}

Scene::~Scene() {
	CloseWindow();
}

void Scene::BeginDraw() {
	BeginDrawing();
	ClearBackground(BLACK);
	DrawTextures(background, { 0, 0 }, WHITE);
	if (showFPS) DrawFPS(20, 20);
}

void Scene::EndDraw() {
	EndDrawing();
}

Object* Scene::CreateObject(Object::Type type, std::string tag, const Vector2& position, float mass, std::string filename, float gravScale, float jumpHeight, float moveSpeed) {
	Object* obj;

	if (type == Object::Type::Solid) obj = new Solid(tag, mass, position);
	else obj = new Controllable(tag, mass, gravScale, jumpHeight, moveSpeed, position);

	obj->Initialize(filename);
	objects.push_back(obj);

	return obj;
}

void Scene::DrawRectangles(const Vector2& world, const Vector2& size, const Color& color) const {
	DrawRectangle((int)world.x, (int)world.y, (int)size.x, (int)size.y, color);
	DrawRectangleLines((int)world.x, (int)world.y, (int)size.x, (int)size.y, ColorTint(color, { 128, 128, 128, 255 }));
}

void Scene::DrawTextures(const Texture2D& texture, const Vector2& world, const Color& tint) const {
	DrawTexture(texture, (int)world.x, (int)world.y, WHITE);
}