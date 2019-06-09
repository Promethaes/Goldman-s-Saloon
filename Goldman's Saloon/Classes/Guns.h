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
	protected:
		unsigned damage, projLimit, ammo;
		//gunTimerMax should not change
		float gunTimer = 0, gunTimerMax;
		bool hasShot = false;
	};

	//make new guns here

	class olReliable : public Gun {
	public:
		olReliable();
		void shoot(float dt, Sedna::GameObject* p, bool isPlayer = true) override;

	};


}