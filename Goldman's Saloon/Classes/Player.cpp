#include "Guns.h"
#include "Primitive.h"
#include "Projectile.h"
#include <iostream>
#define DEADZONE 0.2f

namespace Sedna {
	Player::Player(XinputController* CONTROLLER, const char * path, cocos2d::Scene* scene, const cocos2d::Vec2 & LOCATION, float RADIUS)
		:GameObject(path, scene, LOCATION, RADIUS)
	{
		pController = CONTROLLER;
		id = "Player";
		hitbox->getDrawNode()->setZOrder(10);
		sprite->setZOrder(11);
		hp = 3;
		currentGun = new olReliable();// for now
	}
	void Player::update(float dt)
	{
		checkInput();
		shoot(dt);
		checkList();
		checkProjectileCollision();

		for (auto x : projectiles)
			x->update(dt);

		updateGO(dt);
	}
	void Player::shoot(float dt)
	{
		pController->getTriggers(pTriggers);


		if (pTriggers.RT > 0.0f)
			currentGun->shoot(dt, this);
	}
	void Player::checkList()
	{
		if (projectiles.size() > 4) {

			projectiles.front()->hitbox->getDrawNode()->removeFromParent();
			projectiles.front()->sprite->removeFromParent();
			projectiles.erase(projectiles.begin());
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
				force.x * 300 : 0.0f,
				(pSticks[0].y > DEADZONE || pSticks[0].y < -DEADZONE) ?
				force.y * 300 : 0.0f));
		}

	}
	void Player::checkProjectileCollision()
	{
		for (int i = 0; i < GameObject::gameObjects.size(); i++) {
			for (int j = 0; j < projectiles.size(); j++) {
				if (GameObject::gameObjects[i]->id != "Player" && GameObject::gameObjects[i]->id != "Table"&&
					projectiles[j]->hitbox->checkCollision(*GameObject::gameObjects[i]->hitbox)) {

					GameObject::gameObjects[i]->hp -= currentGun->getDamage();/*change this to gun's dmaage when you can*/

					projectiles[j]->hitbox->getDrawNode()->removeFromParent();
					projectiles[j]->sprite->removeFromParent();
					projectiles.erase(projectiles.begin() + j);
					j--;

				}

			}
		}
	}
}
