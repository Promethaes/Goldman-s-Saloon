#pragma once
#include "GameObject.h"
namespace Powerups {
	enum Powerup_Type {
		none = 0,
		healthPot,
		invincePot,
		revivePot
	};
}
namespace Sedna {
	class Table : public GameObject {
	public:
		Table(cocos2d::Scene* scene, const cocos2d::Vec2 &LOCATION, Powerups::Powerup_Type POTIONTYPE = Powerups::none,float RADIUS = 30);
		void update(float dt) override;
		void die() override;
		Powerups::Powerup_Type getPotionType() const { return potionType; }
		void resetPotionType() { potionType = Powerups::none; sprite->setTexture("TableKnocked.png"); }
	private:
		//handling this stuff inside player
		Powerups::Powerup_Type potionType;
	};
}