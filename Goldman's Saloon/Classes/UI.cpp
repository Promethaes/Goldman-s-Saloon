#include "UI.h"
#include "cocos2d.h"
#include "Guns.h"
#include "Player.h"
#include "CameraTracker.h"
#define SCALE 0.8f

Sedna::PlayerUI::PlayerUI(Player * P)
{
	for (int i = 0; i < 3; i++) {
		hpSprites.push_back(cocos2d::Sprite::create("fullHeart.png"));
		hpSprites[i]->setScale(SCALE);
		P->getScene()->addChild(hpSprites[i],21);
	}

	scoreLabel = cocos2d::Label::create(std::to_string(P->getScore()), "fonts/Montague.ttf", 15/*for now*/);
	ammoLabel = cocos2d::Label::create(std::to_string(P->getGun()->getAmmo()), "fonts/Montague.ttf", 15/*for now*/);

	P->getScene()->addChild(scoreLabel, 21);
	P->getScene()->addChild(ammoLabel, 21);

	
	gunSprite = P->getGun()->getSprite();
	P->getScene()->addChild(gunSprite);
	gunSprite->setScale(SCALE);

	if (P->getPlayerNumber() == 1) {
		for (int i = 0; i < hpSprites.size(); i++) 
			hpSprites[i]->setPosition(cocos2d::Vec2(15, 50 + (i * hpSprites[i]->getContentSize().height*SCALE)));
		gunSprite->setFlippedX(true);
		gunSprite->setPosition(60, 50 + hpSprites.back()->getContentSize().height*SCALE);
	}
	else if (P->getPlayerNumber() == 2) {
		for (int i = 0; i < hpSprites.size(); i++)
			hpSprites[i]->setPosition(cocos2d::Vec2(467.336f, 50 + (i * hpSprites[i]->getContentSize().height*SCALE)));
		gunSprite->setPosition(467.336f - 45, 50 + hpSprites.back()->getContentSize().height*SCALE);
	}
	p = P;
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
	gunSprite->setPosition(gunSprite->getPosition() + cocos2d::Vec2(0, CAMERASPEED));

}
