#pragma once

#include "controllable.h"
#include "attack.h"

/*colliders_t stageOneCols;
std::shared_ptr<Collider> innerCol = std::make_shared<Hitbox>(Vector2{ 50.0f, 70.0f }, Vector2{ obj.position.x + ((obj.spriteFlip) ? -40.0f : 40.0f), obj.position.y }, 10, 0.0f);
stageOneCols.push_back(std::make_shared<Hurtbox>(BOXTYPE::Body, Vector2{ obj.size.x * 0.5f, obj.size.y * 0.5f }, Vector2{ obj.position.x, obj.position.y + (obj.size.y * 0.25f) }));
stageOneCols.push_back(innerCol);
colliders_t stageTwoCols;
std::shared_ptr<Collider> outerCol = std::make_shared<Hitbox>(Vector2{ 70.0f, 50.0f }, Vector2{ obj.position.x + ((obj.spriteFlip) ? -30.0f : 30.0f), obj.position.y }, 10, 0.0f);
stageTwoCols.push_back(std::make_shared<Hurtbox>(BOXTYPE::Body, Vector2{ obj.size.x * 0.5f, obj.size.y * 0.5f }, Vector2{ obj.position.x, obj.position.y + (obj.size.y * 0.25f) }));
stageTwoCols.push_back(outerCol);
std::vector<colliders_t> finalCols;
for (int i = 0; i < 6; i++) finalCols.push_back(stageOneCols);
for (int i = 0; i < 6; i++) finalCols.push_back(stageTwoCols);

auto attack = std::make_shared<Attack>(finalCols);
auto anim = std::make_shared<Sprite>("sprites/defaultPunch.png", 12);*/

static void PlayState(Controllable& obj, float timestep, const std::string& stateName) {
	if (obj.currentFrame == 0 && obj.frameTimer == 0.0f) { // Check for fresh start
		auto spriteName = obj.character + stateName + "Sprite";
		auto attackName = obj.character + stateName + "Attack";

		obj.StartAttack(attackName);
		obj.StartAnim(spriteName);

		//obj.UpdateColliderPositions();
	}

	auto curAnim = obj.anims.at(obj.curAnim);
	curAnim->AdvanceFrame(obj.currentFrame, obj.frameTimer, obj.frameSpeed, timestep);

	if (obj.curAttack) {
		/*std::cout << "##KOT: Object " << obj.tag << " - " << obj.character << " Plays Attack Frame " 
			<< obj.currentFrame << " of Attack " << stateName << std::endl;*/
		obj.curAttack->PlayAttackFrame(obj);
	}

	// ... Exit logic for Punch/Kick/Jump ...
	if (stateName != "Hit" || stateName != "LPunch" || stateName != "HKick" || stateName != "Jump") {
		if (obj.currentFrame == 0/*(obj.anims.at(obj.curAnim)->numFrames - 1)*/ && obj.frameTimer == 0.0f) {
			obj.curAttack = nullptr;
			obj.state = CSTATE::Idle;
		}
	}
}

	/*rapidjson::Document document;
	Json::Load("attacks.json", document);

	auto attack = std::make_shared<Attack>();
	attack->Read(document, attackName);

	auto anim = std::make_shared<Sprite>();
	anim->Read(document, spriteName);

	anim->PlaySpriteAnim(obj, *attack.get(), timestep);*/

/*
static void HKick(Controllable& obj, float timestep) {
	if (obj.IsNewState(CSTATE::Kick)) {
		auto spriteName = obj.character + "HKickSprite";
		auto attackName = obj.character + "HKickAttack";

		obj.StartAttack(attackName);
		obj.StartAnim(spriteName);

		obj.currentFrame = 0;
		obj.frameTimer = 0.0f;

		obj.UpdateColliderPositions();
	}

	auto curAnim = obj.anims.at(obj.curAnim);
	curAnim->AdvanceFrame(obj.currentFrame, obj.frameTimer, obj.frameSpeed, timestep);

	if (obj.curAttack) {
		obj.curAttack->PlayAttackFrame(obj);
		obj.UpdateColliderPositions();
	}

	if (obj.currentFrame == 0 && obj.frameTimer == 0.0f) {
		obj.curAttack = nullptr;
		obj.state = CSTATE::Idle;
	}
};

static void Idle(Controllable& obj, float timestep) {
	if (obj.IsNewState(CSTATE::Idle)) {
		auto spriteName = obj.character + "IdleSprite";
		auto attackName = obj.character + "IdleAttack";

		obj.StartAttack(attackName);
		obj.StartAnim(spriteName);

		obj.currentFrame = 0;
		obj.frameTimer = 0.0f;

		obj.UpdateColliderPositions();
	}

	auto curAnim = obj.anims.at(obj.curAnim);
	curAnim->AdvanceFrame(obj.currentFrame, obj.frameTimer, obj.frameSpeed, timestep);

	if (obj.curAttack) {
		obj.curAttack->PlayAttackFrame(obj);
		obj.UpdateColliderPositions();
	}

	if (obj.currentFrame == 0 && obj.frameTimer == 0.0f) {
		obj.curAttack = nullptr;
		obj.state = CSTATE::Idle;
	}
};

static void Walk (Controllable& obj, float timestep) {
	if (obj.IsNewState(CSTATE::Move)) {
		auto spriteName = obj.character + "WalkSprite";
		auto attackName = obj.character + "WalkAttack";

		obj.StartAttack(attackName);
		obj.StartAnim(spriteName);

		obj.currentFrame = 0;
		obj.frameTimer = 0.0f;

		obj.UpdateColliderPositions();
	}

	auto curAnim = obj.anims.at(obj.curAnim);
	curAnim->AdvanceFrame(obj.currentFrame, obj.frameTimer, obj.frameSpeed, timestep);

	if (obj.curAttack) {
		obj.curAttack->PlayAttackFrame(obj);
		obj.UpdateColliderPositions();
	}

	if (obj.currentFrame == 0 && obj.frameTimer == 0.0f) {
		obj.curAttack = nullptr;
		obj.state = CSTATE::Idle;
	}
};*/

/*static void HKick(Controllable& obj, float timestep) {
	colliders_t stageOneCols;
	std::shared_ptr<Collider> innerCol = std::make_shared<Hitbox>(Vector2{ 50.0f, 80.0f }, Vector2{ obj.position.x + ((obj.spriteFlip) ? -100.0f : 100.0f), obj.position.y + 70.0f }, 10, Vector2{ 0.259f, 0.965f }, 10.0f);
	stageOneCols.push_back(std::make_shared<Hurtbox>(BOXTYPE::Body, Vector2{ obj.size.x * 0.5f, obj.size.y * 0.5f }, Vector2{ obj.position.x + ((obj.spriteFlip) ? -50.0f : 50.0f), obj.position.y + (obj.size.y * 0.25f) }));
	stageOneCols.push_back(innerCol);
	colliders_t stageTwoCols;
	std::shared_ptr<Collider> outerCol = std::make_shared<Hitbox>(Vector2{ 100.0f, 50.0f }, Vector2{ obj.position.x + ((obj.spriteFlip) ? -140.0f : 140.0f), obj.position.y + 40.0f }, 10, Vector2{ 0.259f, 0.965f }, 10.0f);
	stageTwoCols.push_back(std::make_shared<Hurtbox>(BOXTYPE::Body, Vector2{ obj.size.x * 0.5f, obj.size.y * 0.5f }, Vector2{ obj.position.x + ((obj.spriteFlip) ? -50.0f : 50.0f), obj.position.y + (obj.size.y * 0.25f) }));
	stageTwoCols.push_back(outerCol);
	std::vector<colliders_t> finalCols;
	for (int i = 0; i < 6; i++) finalCols.push_back(stageOneCols);
	for (int i = 0; i < 6; i++) finalCols.push_back(stageTwoCols);

	auto hKick = std::make_shared<Attack>(finalCols);

	auto anim = std::make_shared<Sprite>("sprites/defaultKick.png", 12);
	anim->PlaySpriteAnim(obj, *hKick.get(), timestep);
	//obj.sprite = anim->texture;
};

static void Idle(Controllable& obj, float timestep) {
	colliders_t idleCols;
	std::shared_ptr<Collider> hitCol1 = std::make_shared<Hurtbox>(BOXTYPE::Hurt, Vector2{ 50.0f, 70.0f }, Vector2{ obj.position.x, obj.position.y - 70.0f });
	std::shared_ptr<Collider> hitCol2 = std::make_shared<Hurtbox>(BOXTYPE::Hurt, Vector2{ 100.0f, 160.0f }, Vector2{ obj.position.x, obj.position.y + 40.0f });
	idleCols.push_back(std::make_shared<Hurtbox>(BOXTYPE::Body, Vector2{ obj.size.x * 0.5f, obj.size.y * 0.5f }, Vector2{ obj.position.x, obj.position.y + (obj.size.y * 0.25f) }));
	idleCols.push_back(hitCol1);
	idleCols.push_back(hitCol2);
	std::vector<colliders_t> finalCols;
	for (int i = 0; i < 10; i++) finalCols.push_back(idleCols);

	auto idle = std::make_shared<Attack>(finalCols);

	auto anim = std::make_shared<Sprite>("sprites/defaultIdle.png", 10);
	//std::cout << "##KOT: Animation " << anim->filename << " is " << (IsTextureValid(anim->texture) ? "" : "NOT ") << "Valid" << std::endl;
	anim->PlaySpriteAnim(obj, *idle.get(), timestep);
	//std::cout << "##KOT: Current Frame is " << (IsTextureValid(curAnim) ? "" : "NOT ") << "Valid" << std::endl;

	//obj.sprite = anim->texture;
}*/