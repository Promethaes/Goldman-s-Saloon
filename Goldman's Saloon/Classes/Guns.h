#pragma once
#include <vector>
#define DEADZONE 0.2f
#include "Player.h"
namespace Sedna {

	class Player;
	class Gun {
	public:
		Gun(unsigned DAMAGE, unsigned PROJLIMIT, float RATEOFFIRE, unsigned AMMO);

		virtual void shoot(float dt, Sedna::GameObject* p, bool isPlayer = true) = 0;
		unsigned getDamage() const { return damage; }
		unsigned getProjLimit() const { return projLimit; }
		unsigned getAmmo() const { return ammo; }
		cocos2d::Sprite* getSprite() const { return gunSprite; }
	protected:
		cocos2d::Sprite* gunSprite;
		unsigned damage, projLimit, ammo;
		//gunTimerMax should not change
		float gunTimer = 0, gunTimerMax;
		bool hasShot = false;
	};

	//make new guns here

	//base gun
	class olReliable : public Gun {
	public:
		olReliable();
		void shoot(float dt, Sedna::GameObject* p, bool isPlayer = true) override;
	};

	//shotgun
	class bloodyMary : public Gun {
	public:
		bloodyMary();
		void shoot(float dt, Sedna::GameObject*p, bool isPlayer = true) override;
	};

	class theBiggestIron : public Gun {
	public:
		theBiggestIron();
		void shoot(float dt, Sedna::GameObject*p, bool isPlayer = true) override;
	};

	class rifle : public Gun {
	public:
		rifle();
		void shoot(float dt, Sedna::GameObject*p, bool isPlayer = true) override;
	};

	//crazy pete's "gun"
	class dynamite : public Gun {
	public:
		dynamite();
		void shoot(float dt, Sedna::GameObject*p, bool isPlayer = true) override;
	};

}