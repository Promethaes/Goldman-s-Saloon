#include "Player.h"
#include "Primitive.h"
#include <iostream>
#define DEADZONE 0.2f
namespace Sedna {
	Player::Player(XinputController* CONTROLLER, const char * path, cocos2d::Scene* scene, const cocos2d::Vec2 & LOCATION, float RADIUS)
		:GameObject(path, scene, LOCATION, RADIUS)
	{
		pController = CONTROLLER;
	}
	void Player::update(float dt)
	{
		checkInput();
		shoot(dt);
		checkList();
		updateGO(dt);
	}
	void Player::shoot(float dt)
	{
		pController->getTriggers(pTriggers);

		if (pTriggers.RT > 0) {
			if (gunTimer > 1.0f) {
				gunTimer = 0;
				hasShot = false;
			}
			if (gunTimer == 0) { 
				hasShot = true;
				pProjectiles.push_back(new Projectile("HelloWorld.png", scene, hitbox->getLocation(), 5));

				if (pSticks[1].x > DEADZONE || pSticks[1].x < -DEADZONE || pSticks[1].y > DEADZONE || pSticks[1].y < -DEADZONE) {
					auto direction = cocos2d::Vec2(pSticks[1].x, pSticks[1].y);
					auto force = direction / sqrt(direction.x*direction.x + direction.y*direction.y);//normalized vector
					///for (int i = 0; i < GameObject::gameObjects.size(); i++)
					///	if (pProjectiles.back()->id == GameObject::gameObjects[i]->id) {
					///		GameObject::gameObjects[i]->sprite->setRotationX(force.x);
					///		GameObject::gameObjects[i]->sprite->setRotationY(force.y);
					///
					///	}

					for (int i = 0; i < GameObject::gameObjects.size(); i++)
						if (pProjectiles.back()->id == GameObject::gameObjects[i]->id)
							GameObject::gameObjects[i]->hitbox->setForce(cocos2d::Vec2(force.x * 500, force.y * 500));

				}
				else
					for (int i = 0; i < GameObject::gameObjects.size(); i++)
						if (pProjectiles.back()->id == GameObject::gameObjects[i]->id)
							GameObject::gameObjects[i]->hitbox->setForce(cocos2d::Vec2(0, 500));
			}

		}
			if (hasShot)
				gunTimer += dt;
	}
	void Player::checkList()
	{
		if (pProjectiles.size() > 4) {

			for (int i = 0; i < GameObject::gameObjects.size(); i++) {
				if (pProjectiles.front()->id == GameObject::gameObjects[i]->id) {
					GameObject::gameObjects.erase(GameObject::gameObjects.begin() + i);
					i--;
				}
			}

			pProjectiles.front()->hitbox->getDrawNode()->removeFromParent();
			pProjectiles.front()->sprite->removeFromParent();
			pProjectiles.erase(pProjectiles.begin());
		}
	}
	void Player::checkInput()
	{
		pController->updateSticks(pSticks);
		if (pSticks[0].x > -DEADZONE && pSticks[0].x < DEADZONE && pSticks[0].y > -DEADZONE && pSticks[0].y < DEADZONE)
			hitbox->addForce(hitbox->getVelocity().x *-10.0f, hitbox->getVelocity().y*-10.0f);
		else {
			auto direction = cocos2d::Vec2(pSticks[0].x, pSticks[0].y);
			auto force = direction / sqrt(direction.x*direction.x + direction.y*direction.y);//normalized vector

			hitbox->setForce(cocos2d::Vec2((pSticks[0].x > DEADZONE || pSticks[0].x < -DEADZONE) ?
				force.x * 250 : 0.0f,
				(pSticks[0].y > DEADZONE || pSticks[0].y < -DEADZONE) ?
				force.y * 250 : 0.0f));
		}

	}
}
