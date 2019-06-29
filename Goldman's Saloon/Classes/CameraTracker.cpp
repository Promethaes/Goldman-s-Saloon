#include "CameraTracker.h"
#include "Primitive.h"

namespace Sedna {

	Background::Background(const char* path, cocos2d::Scene* scene)
	{
		//ALL BACKGROUNDS SHOULD BE 1920 by 1080
		sprite = cocos2d::Sprite::create(path);
		sprite->setAnchorPoint(cocos2d::Vec2(0.0f, 0.0f));
		sprite->setScaleX(0.85f);
		sprite->setScaleY(0.92f);
		scene->addChild(sprite, -1000);
	}

	CameraTracker::CameraTracker(cocos2d::Scene* scene, const cocos2d::Vec2& LOCATION)
		:GameObject("crosshairs.png", scene, LOCATION, 1)
	{
		id = "CAMERA";
		hp = INT_MAX;
		bg1 = new Background("bg1.png", scene);
		bg2 = new Background("bg2.png", scene);
		bg2->sprite->setPosition(bg2->sprite->getPosition().x, bg2->sprite->getContentSize().height - 30);
	}

	void CameraTracker::update(float dt)
	{
		if (!stop) {
			scene->getDefaultCamera()->setPosition(scene->getDefaultCamera()->getPosition() + cocos2d::Vec2(0, CAMERASPEED));
			hitbox->setLocation(hitbox->getLocation() + cocos2d::Vec2(0, CAMERASPEED));
			backgroundSwitch();
		}
		updateGO(dt);
	}

	void CameraTracker::die()
	{
	}

	void CameraTracker::backgroundSwitch()
	{
		if (this->hitbox->getLocation().y - bg1->sprite->getPosition().y >= 290 * 2) {
			bg1->sprite->setTexture("bg2.png");
			bg1->sprite->setPosition(bg1->sprite->getPosition() + cocos2d::Vec2(0, 290 * 2));
		}


		if (this->hitbox->getLocation().y - bg2->sprite->getPosition().y >= 290 * 2)
			bg2->sprite->setPosition(bg2->sprite->getPosition() + cocos2d::Vec2(0, 290 * 2));

	}
}