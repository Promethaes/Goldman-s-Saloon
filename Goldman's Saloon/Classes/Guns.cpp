#include "Guns.h"
#include "Primitive.h"
#include "Projectile.h"

Sedna::Gun::Gun(unsigned DAMAGE, unsigned PROJLIMIT, float RATEOFFIRE, unsigned AMMO)
	:damage(DAMAGE), projLimit(PROJLIMIT), gunTimerMax(RATEOFFIRE), ammo(AMMO)
{
}

Sedna::olReliable::olReliable()
	: Gun(2, 4, 0.5f, INT_MAX)
{
}
void Sedna::olReliable::shoot(float dt, Sedna::GameObject* p,bool isPlayer)
{
	if (gunTimer > gunTimerMax) {
		gunTimer = 0;
		hasShot = false;
	}
	if (gunTimer == 0) {
		hasShot = true;
		p->projectiles.push_back(new Sedna::Projectile("Bullet2.png", p->getScene(), p->hitbox->getLocation(), 5));

		///<LEAVE THIS. this is what sets the dt member variable. if you remove this, projectiles will not work properly!>
		p->projectiles.back()->update(dt);

		if (isPlayer) {

		if (static_cast<Player*>(p)->pSticks[1].x < -DEADZONE)
			p->projectiles.back()->hitbox->setForce(cocos2d::Vec2((float)(-500 * 2) / 3.0f, (float)(500 * 2) / 3.0f));
		else if (static_cast<Player*>(p)->pSticks[1].x > DEADZONE)
			p->projectiles.back()->hitbox->setForce(cocos2d::Vec2((float)(500 * 2) / 3.0f, float(500 * 2) / 3.0f));

		//if the stick is up or in all deadzones
		else if (static_cast<Player*>(p)->pSticks[1].x < DEADZONE && static_cast<Player*>(p)->pSticks[1].x > -DEADZONE && static_cast<Player*>(p)->pSticks[1].y > DEADZONE ||
			static_cast<Player*>(p)->pSticks[1].x < DEADZONE && static_cast<Player*>(p)->pSticks[1].x > -DEADZONE && static_cast<Player*>(p)->pSticks[1].y < DEADZONE && static_cast<Player*>(p)->pSticks[1].y > -DEADZONE)
			p->projectiles.back()->hitbox->setForce(cocos2d::Vec2(0, 471));
		}
		else {
			//do other shit
		}


	}
	if (hasShot)
		gunTimer += dt;
}
