#include "Guns.h"
#include "Primitive.h"
#include "Projectile.h"
#include "Enemy.h"

namespace Sedna {

	Sedna::Gun::Gun(unsigned DAMAGE, unsigned PROJLIMIT, float RATEOFFIRE, unsigned AMMO)
		:damage(DAMAGE), projLimit(PROJLIMIT), gunTimerMax(RATEOFFIRE), ammo(AMMO)
	{
	}


	//base gun
	Sedna::olReliable::olReliable()
		: Gun(2, 4, 0.5f, INT_MAX)
	{
	}
	void Sedna::olReliable::shoot(float dt, Sedna::GameObject* p, bool isPlayer)
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
				//make sure that only players do more damage...for now
				damage = 1;
				p->projectiles.back()->hitbox->setForce(cocos2d::Vec2(0, -471));
			}


		}
		if (hasShot)
			gunTimer += dt;
	}




	//shotgun
	Sedna::bloodyMary::bloodyMary()
		:Gun(3, 5, 0.9f, 10)
	{
	}

	void bloodyMary::shoot(float dt, Sedna::GameObject * p, bool isPlayer)
	{
		for (int i = 0; i < 5; i++) 
			p->projectiles.push_back(new Projectile("Bullet2.png", p->getScene(), p->hitbox->getLocation(), 5));

		for (auto x : p->projectiles)
			x->update(dt);

		if (isPlayer) {
			if (static_cast<Player*>(p)->pSticks[1].x < -DEADZONE) {
				p->projectiles[0]->hitbox->setForce(cocos2d::Vec2(-5.06, 0));//projectile on the left
				p->projectiles[1]->hitbox->setForce(cocos2d::Vec2(-4.5, 1.75));
				p->projectiles[2]->hitbox->setForce(cocos2d::Vec2(-3.35, 3.35));//projectiles in the middle
				p->projectiles[3]->hitbox->setForce(cocos2d::Vec2(-1.75, 4.5));
				p->projectiles[4]->hitbox->setForce(cocos2d::Vec2(0, 5.06));//projectile on the right

			}

			else if (static_cast<Player*>(p)->pSticks[1].x > DEADZONE) {
				p->projectiles[0]->hitbox->setForce(cocos2d::Vec2(0, 5.06));//projectile on the left
				p->projectiles[1]->hitbox->setForce(cocos2d::Vec2(1.75, 4.5));
				p->projectiles[2]->hitbox->setForce(cocos2d::Vec2(3.35, 3.35));//projectiles in the middle
				p->projectiles[3]->hitbox->setForce(cocos2d::Vec2(4.5, 1.75));
				p->projectiles[4]->hitbox->setForce(cocos2d::Vec2(5.06, 0));//projectile on the right
			}

			//if the stick is up or in all deadzones
			else if (static_cast<Player*>(p)->pSticks[1].x < DEADZONE && static_cast<Player*>(p)->pSticks[1].x > -DEADZONE && static_cast<Player*>(p)->pSticks[1].y > DEADZONE ||
				static_cast<Player*>(p)->pSticks[1].x < DEADZONE && static_cast<Player*>(p)->pSticks[1].x > -DEADZONE && static_cast<Player*>(p)->pSticks[1].y < DEADZONE && static_cast<Player*>(p)->pSticks[1].y > -DEADZONE) {

				p->projectiles[0]->hitbox->setForce(cocos2d::Vec2(-3.25, 3.25));//projectile on the left
				p->projectiles[1]->hitbox->setForce(cocos2d::Vec2(-1.75, 4.5));
				p->projectiles[2]->hitbox->setForce(cocos2d::Vec2(0, 5.06));//projectiles in the middle
				p->projectiles[3]->hitbox->setForce(cocos2d::Vec2(1.75, 4.5));
				p->projectiles[4]->hitbox->setForce(cocos2d::Vec2(3.25, 3.25));//projectile on the right
			}
		}
		else {
			damage = 1;
			//might have to handle this internally
			//for (int i = 0; i < GameObject::gameObjects.size(); i++) {
			//	if (GameObject::gameObjects[i]->id == "Player") {
			//
			//		if (GameObject::gameObjects[i]->hitbox->getLocation().x - p->hitbox->getLocation().x < 0) {
			//			//static_cast<ShotgunOutlaw*>(p)->onLeft = true;
			//			p->projectiles[0]->hitbox->setForce(cocos2d::Vec2(-5.06, 0));//projectile on the left
			//			p->projectiles[1]->hitbox->setForce(cocos2d::Vec2(-4.5, -1.75));
			//			p->projectiles[2]->hitbox->setForce(cocos2d::Vec2(-3.35, -3.35));//projectiles in the middle
			//			p->projectiles[3]->hitbox->setForce(cocos2d::Vec2(-1.75, -4.5));
			//			p->projectiles[4]->hitbox->setForce(cocos2d::Vec2(0, -5.06));//projectile on the right
			//		}
			//		else {
			//			p->projectiles[0]->hitbox->setForce(cocos2d::Vec2(0, -5.06));//projectile on the left
			//			p->projectiles[1]->hitbox->setForce(cocos2d::Vec2(1.75, -4.5));
			//			p->projectiles[2]->hitbox->setForce(cocos2d::Vec2(3.35, -3.35));//projectiles in the middle
			//			p->projectiles[3]->hitbox->setForce(cocos2d::Vec2(4.5, -1.75));
			//			p->projectiles[4]->hitbox->setForce(cocos2d::Vec2(5.06, 0));//projectile on the right
			//		}
			//		//static_cast<ShotgunOutlaw*>(p)->onLeft = false;
			//
			//	}
			//}
			p->projectiles[0]->hitbox->setForce(cocos2d::Vec2(-5.06, 0));//projectile on the left
			p->projectiles[1]->hitbox->setForce(cocos2d::Vec2(-4.5, -1.75));
			p->projectiles[2]->hitbox->setForce(cocos2d::Vec2(-3.35, -3.35));//projectiles in the middle
			p->projectiles[3]->hitbox->setForce(cocos2d::Vec2(-1.75, -4.5));
			p->projectiles[4]->hitbox->setForce(cocos2d::Vec2(0, -5.06));//projectile on the right

		}

	}
}
