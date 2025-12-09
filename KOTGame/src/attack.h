#pragma once

#include "object.h"
#include "hurtbox.h"
#include "hitbox.h"

struct Attack {
public:
	/// <summary>
	/// Create Attack without filling values. For use with JSON.
	/// </summary>
	Attack() = default;
	/// <summary>
	/// Instatiate Attack with necessary parameters.
	/// </summary>
	/// <param name="colliders">Array of arrays of colliders. Each inner array of colliders
	/// defines those of an individual frame of attack.</param>
	/// <param name="filename">The filename to use for animation. Should be arranged as one
	/// long line of frames, rather than a grid.</param>
	Attack(std::vector<colliders_t> colliders) : colliders{ colliders } {}

	/// <summary>
	/// Set colliders for object based on individual frame of attack.
	/// </summary>
	/// <param name="obj">The object whose colliders should change.</param>
	void PlayAttackFrame(Object& obj) {
		obj.colliders.clear();
		for (const auto& col : colliders[obj.currentFrame]) obj.colliders.push_back(col);

		//obj.UpdateColliderPositions();
	}

	/// <summary>
	/// Read in JSON value and parse to new Attack.
	/// </summary>
	/// <param name="value">The JSON value to read and parse.</param>
	/// <param name="name">The name of the attack in the JSON file.</param>
	void Read(const json_t& value, std::string name) {
		if (!value.HasMember(name.c_str()) || !value[name.c_str()].IsArray()) {
			std::cerr << "Could not read Json value: " << name << std::endl;
			return;
		}

		// get json array object
		const auto& array = value[name.c_str()];
		// get array values
		for (auto outItr = array.Begin(); outItr != array.End(); ++outItr) {
			const json_t& inner = *outItr;

			if (!inner.IsArray()) {
				std::cerr << "Could not read Json value: " << name << std::endl;
				continue;
			}

			colliders_t inVec;

			for (auto inItr = inner.Begin(); inItr != inner.End(); ++inItr) {
				const json_t & final = *inItr;

				if (!final.IsObject() || !final.HasMember("type") || !final["type"].IsString()) {
					std::cerr << "Error: Object missing a 'type' discriminator." << std::endl;
					continue;
				}

					std::string type = final["type"].GetString();

					if (type == "hit") {
						auto col = std::make_unique<Hitbox>();

						col->Read(final);
						inVec.push_back(std::move(col));
					}
					else if (type == "hurt") {
						auto col = std::make_unique<Hurtbox>();

						col->Read(final);
						inVec.push_back(std::move(col));
					}
					else {
						std::cerr << "Warning: Unknown collider type '" << type << "'" << std::endl;
					}
			}

			colliders.push_back(std::move(inVec));
		}
	}

public:
	std::vector<colliders_t> colliders;
};