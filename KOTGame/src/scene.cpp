#include "scene.h"
#include "solid.h"
#include "controllable.h"

Scene::Scene(int animFrameSpeed) : animFrameSpeed{ animFrameSpeed } {
	cache = LoadRenderTexture(width, height);
	musicBG = LoadMusicStream("audio/moonsetter.mp3");

	//SetBackgroundTexture();
}

Scene::~Scene() {
	for (auto& obj : objects) {
		obj->colliders.clear();
	}
	objects.clear();

	//if (musicBG.stream.buffer) {
	//	StopMusicStream(musicBG);
	//	UnloadMusicStream(musicBG);
	//}

	UnloadRenderTexture(cache);
}

void Scene::BeginDraw() {
	BeginDrawing();
	//ClearBackground(BLACK);
	if (showFPS) DrawFPS(20, 20);
}

void Scene::EndDraw() {
	EndDrawing();
}

std::shared_ptr<Object> Scene::CreateObject(Object::Type type, std::string tag, const Vector2& position, float mass, std::string filename, int health, float gravScale, float jumpHeight, float moveSpeed, std::string character) {
	std::shared_ptr<Object> obj;

	if (type == Object::Type::Controllable) obj = std::make_shared<Controllable>(tag, mass, health, gravScale, jumpHeight, moveSpeed, character, position);

	obj->Initialize(filename);
	obj->frameSpeed = animFrameSpeed;
	objects.push_back(obj);

	return obj;
}

std::shared_ptr<Object> Scene::CreateObject(Object::Type type, std::string tag, const Vector2& position, float mass, std::string filename, int health) {
	std::shared_ptr<Object> obj;

	if (type == Object::Type::Solid) obj = std::make_shared<Solid>(tag, mass, health, position);

	obj->Initialize(filename);
	obj->frameSpeed = animFrameSpeed;
	objects.push_back(obj);

	return obj;
}

void Scene::DrawRectangles(const Vector2& world, const Vector2& size, const Color& color) const {
	DrawRectangle((int)world.x, (int)world.y, (int)size.x, (int)size.y, color);
	DrawRectangleLines((int)world.x, (int)world.y, (int)size.x, (int)size.y, ColorTint(color, { 128, 128, 128, 255 }));
}

void Scene::DrawTextures(const Texture2D& texture, const float posX, const float posY, const Color& tint) const {
	DrawTexture(texture, (int)posX, (int)posY, WHITE);
}