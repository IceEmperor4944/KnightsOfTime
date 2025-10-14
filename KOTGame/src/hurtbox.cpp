#include "hurtbox.h"
#include "object.h"

void Hurtbox::Initialize() {
	//
}

std::vector<Object*> Hurtbox::GetCollisionCount() {
	/*//keep objects in border
	for (auto obj : objects)
	{
		AABB aabb = obj->GetAABB();
		AABB worldAABB = GetAABB();

		if ((aabb.min().y) < worldAABB.min().y)
		{
			float overlap = (worldAABB.min().y - aabb.min().y); // calculate how far the obj has penetrated beyond the world boundary
			obj->position.y += 1 * overlap; // move the obj back inside the world bounds
			obj->velocity.y *= -1; // multiple by -restituion to scale and flip velocity
		}
		else if ((aabb.max().y) > worldAABB.max().y)
		{
			float overlap = (worldAABB.max().y - aabb.max().y);  // calculate how far the obj has penetrated beyond the world boundary
			obj->position.y += 1 * overlap; // move the obj back inside the world bounds
			obj->velocity.y *= -1; // multiple by -restituion to scale and flip velocity
		}

		if ((aabb.min().x) < worldAABB.min().x)
		{
			float overlap = (worldAABB.min().x - aabb.min().x);
			obj->position.x += 2 * overlap;
			obj->velocity.x *= -1;
		}
		else if (aabb.max().x > worldAABB.max().x)
		{
			float overlap = (worldAABB.max().x - aabb.max().x);
			obj->position.x += 2 * overlap;
			obj->velocity.x *= -1;
		}
	}
	*/

	std::vector<Object*> objects;
	
	

	return objects;
}