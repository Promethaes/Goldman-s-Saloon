#pragma once
#include "cocos2d.h"
#include <vector>
namespace Sedna {
	class CirclePrimitive;
	class Projectile;
	class GameObject {
	public:
		GameObject(const char* path, cocos2d::Scene* scene, const cocos2d::Vec2 &LOCATION, float RADIUS, bool pushback = true, float ANGLE = 5, unsigned int SEGMENTS = 50);
		void updateGO(float dt);
		///<every single game object should have its own update that calls updateGO>
		virtual void update(float dt) = 0;
		virtual void die();
		cocos2d::Scene* getScene() const { return scene; }

		static std::vector<GameObject*> gameObjects;
		CirclePrimitive* hitbox;
		cocos2d::Sprite* sprite;

		//optional id. Thinking about using this for collision checks.
		std::string id = "";
		int hp;
		std::vector<Projectile*> projectiles;

	protected:
		cocos2d::Scene* scene;
	};
}