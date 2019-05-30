#include "Player.h"
#include "GameObject.h"
#include "Primitive.h"
#include <iostream>
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
		if (pSticks[0].x > -0.3f && pSticks[0].x < 0.3f && pSticks[0].y > -0.3f && pSticks[0].y < 0.3f)
			hitbox->addForce(hitbox->getVelocity().x *-3.0f, hitbox->getVelocity().y*-3.0f);
		else {
			auto direction = cocos2d::Vec2(pSticks[0].x, pSticks[0].y);
			auto force = direction / sqrt(direction.x*direction.x + direction.y*direction.y);//normalized vector

			hitbox->setForce(cocos2d::Vec2((pSticks[0].x > 0.3f || pSticks[0].x < -0.3f) ?
				force.x * 300 : 0.0f,
				(pSticks[0].y > 0.3f || pSticks[0].y < -0.3f) ?
				force.y * 300 : 0.0f));
		}
	}
}
