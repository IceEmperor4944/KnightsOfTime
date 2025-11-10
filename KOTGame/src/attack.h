#pragma once

#include "collider.h"
#include "sprite.h"

struct Attack {
public:
	/// <summary>
	/// Instatiate Attack with necessary parameters.
	/// </summary>
	/// <param name="colliders">- Array of arrays of colliders. Each inner array of colliders
	/// defines those of an individual frame of attack.</param>
	/// <param name="filename">- The filename to use for animation. Should be arranged as one
	/// long line of frames, rather than a grid.</param>
	Attack(std::vector<colliders_t> colliders) : colliders{ colliders } {}

	void PlayAttackFrame(Object& obj) {
		for (auto& col : colliders[obj.currentFrame]) obj.colliders.push_back(col);
	}
public:
	std::vector<colliders_t> colliders;
};