#include "Player.h"
#include "GameObject.h"
#include "Primitive.h"
#include <iostream>
#define DEADZONE 0.2f
namespace Sedna {
	Player::Player(XinputController* CONTROLLER, const char * path,cocos2d::Scene* scene, const cocos2d::Vec2 & LOCATION, float RADIUS)
		:GameObject(path,scene,LOCATION,RADIUS)
	{
		pController = CONTROLLER;
	}
	void Player::update(float dt)
	{
		checkInput();
		updateGO(dt);
		///std::cout << hitbox->getLocation().x << " " << hitbox->getLocation().y << "\n";
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
