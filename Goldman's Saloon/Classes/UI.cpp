#include "UI.h"
#include "cocos2d.h"
#include "Guns.h"
#include "Player.h"
#include "CameraTracker.h"
//#define CAMERASPEED 1.0f


Sedna::PlayerUI::PlayerUI(Player * P)
{
	for (int i = 0; i < 3; i++) {
		hpSprites[i] = cocos2d::Sprite::create("fullHeart.png");
		P->getScene()->addChild(hpSprites[i],21);
	}

	scoreLabel = cocos2d::Label::create(std::to_string(P->getScore()), "fonts/Montague.ttf", 15/*for now*/);
	ammoLabel = cocos2d::Label::create(std::to_string(P->getGun()->getAmmo()), "fonts/Montague.ttf", 15/*for now*/);

	P->getScene()->addChild(scoreLabel, 21);
	P->getScene()->addChild(ammoLabel, 21);
}

void Sedna::PlayerUI::update(float dt)
{
	for (auto x : hpSprites) {
		x->setPosition(x->getPosition() + cocos2d::Vec2(0, CAMERASPEED));
		if (x->getZOrder() == 21)
			x->setTexture("fullHeart.png");
		else if (x->getZOrder() == 20)
			x->setTexture("brokenHeart.png");
	}

	scoreLabel->setPosition(scoreLabel->getPosition() + cocos2d::Vec2(0, CAMERASPEED));
	ammoLabel->setPosition(ammoLabel->getPosition() + cocos2d::Vec2(0, CAMERASPEED));

}
