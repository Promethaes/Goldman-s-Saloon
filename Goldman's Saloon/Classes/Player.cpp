#include "Guns.h"
#include "Primitive.h"
#include "Projectile.h"
#include "Input.h"
#include "Events.h"
#include "Table.h"
#define DEADZONE 0.2f

namespace Sedna {
	Player::Player(XinputController* CONTROLLER, const char * path, cocos2d::Scene* scene, unsigned playerNumber, const cocos2d::Vec2 & LOCATION, float RADIUS)
		:GameObject(path, scene, LOCATION, RADIUS)
	{
		this->playerNumber = playerNumber;
		pController = CONTROLLER;
		id = "Player";
		hitbox->getDrawNode()->setZOrder(10);
		sprite->setZOrder(11);
#ifdef _DEBUG
		hp = INT_MAX;
#else
		hp = 3;
#endif
		currentGun = new theBiggestIron();// for now

		pUi = new PlayerUI(this);
	}


	void Player::update(float dt)
	{
		if (invincible) {
			invincibilityTimer -= dt;
		
			if (invincibilityTimer <= 0) {
				invincible = false;
				invincibilityTimer = 5.0f;
			}
		
		}
#ifdef _DEBUG
		if (pController->isButtonPressed(X)) {
			//removes the data currentGun points to
			delete currentGun;
			currentGun = nullptr;
			currentGun = new theBiggestIron();
		}
#endif
		if (currentGun->getAmmo() == 0) {
			//removes the data currentGun points to
			delete currentGun;
			currentGun = nullptr;
			currentGun = new olReliable();
		}
		

		checkCollision(dt);
		checkInput();
		shoot(dt);
		checkList();
		checkProjectileCollision();

		for (auto x : projectiles)
			x->update(dt);

		updateGO(dt);
		pUi->update(dt);
	}

	//might wanna make this not a pure virtual function in game object header
	void Player::die()
	{
		for (int i = 0; i < projectiles.size(); i++) {
			projectiles[i]->hitbox->getDrawNode()->removeFromParent();
			projectiles[i]->sprite->removeFromParent();
			delete projectiles[i];
			projectiles[i] = nullptr;
			projectiles.erase(projectiles.begin() + i);
			i--;
		}
		hitbox->getDrawNode()->removeFromParent();
		sprite->removeFromParent();
		delete currentGun;
		currentGun = nullptr;
	}



	void Player::checkCollision(float dt)
	{
		for (int i = 0; i < GameObject::gameObjects.size(); i++)
			if (GameObject::gameObjects[i]->id != "Player" && hitbox->checkCollision(*GameObject::gameObjects[i]->hitbox) && !kickTables())
				hitbox->setLocation(hitbox->getLocation() - hitbox->getVelocity());

	}



	bool Player::kickTables()
	{
		for (int i = 0; i < GameObject::gameObjects.size(); i++)
			if (GameObject::gameObjects[i]->id == "Table" && hitbox->checkCollision(*GameObject::gameObjects[i]->hitbox) && pController->isButtonPressed(A)) {
				auto force = hitbox->getLocation() - GameObject::gameObjects[i]->hitbox->getLocation();
				GameObject::gameObjects[i]->hitbox->addForce(-force * 10);

				// == 1 FOR READABILITY. lol
				//hp
				if (static_cast<Table*>(GameObject::gameObjects[i])->getPotionType() == 1)
					hp < 3 ? hp++ : hp = 3;
				//invincibility
				else if (static_cast<Table*>(GameObject::gameObjects[i])->getPotionType() == 2)
					invincible = true;
					
				//dunno how revive logic is gonna work yet

				/*----->*/static_cast<Table*>(GameObject::gameObjects[i])->resetPotionType();
				

				return true;
			}
		return false;
	}



	void Player::shoot(float dt)
	{
		pController->getTriggers(pTriggers);


		if (pTriggers.RT > 0.0f)
			currentGun->shoot(dt, this);
	}



	void Player::checkList()
	{
		if (projectiles.size() > currentGun->getProjLimit()) {

			projectiles.front()->hitbox->getDrawNode()->removeFromParent();
			projectiles.front()->sprite->removeFromParent();
			delete projectiles.front();
			projectiles.front() = nullptr;
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

		//////<keyboard input,comment this out when you wanna actually test stuff.>
		///if (isEvent(Events::W))
		///	hitbox->setForce(cocos2d::Vec2(0, 300.0f));
		///else if (isEvent(Events::S))
		///	hitbox->setForce(cocos2d::Vec2(0, -300.0f));
		///else if (isEvent(Events::A))
		///	hitbox->setForce(cocos2d::Vec2(-300.0f, 0));
		///else if (isEvent(Events::D))
		///	hitbox->setForce(cocos2d::Vec2(300.0f, 0));
		///else
		///	hitbox->addForce(hitbox->getVelocity().x *-10.0f, hitbox->getVelocity().y*-10.0f);


	}
	void Player::checkProjectileCollision()
	{
		for (int i = 0; i < GameObject::gameObjects.size(); i++) {
			for (int j = 0; j < projectiles.size(); j++) {
				if (GameObject::gameObjects[i]->id != "Player" && GameObject::gameObjects[i]->id != "Table"&&
					projectiles[j]->hitbox->checkCollision(*GameObject::gameObjects[i]->hitbox)) {

					GameObject::gameObjects[i]->hp -= currentGun->getDamage();

					projectiles[j]->hitbox->getDrawNode()->removeFromParent();
					projectiles[j]->sprite->removeFromParent();
					delete projectiles[j];
					projectiles[j] = nullptr;
					projectiles.erase(projectiles.begin() + j);
					j--;

				}

			}
		}
	}
}
