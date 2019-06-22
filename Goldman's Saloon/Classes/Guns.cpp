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
	//so basically, these small data types are almost like objects, but since all guns have different ways of shooting, making them into data types was the best decision
	//not to mention that we don't have to specify the logic in more than one place
	Sedna::olReliable::olReliable()
		: Gun(2, 4, 0.5f, INT_MAX)
	{
	}
	//shoot is a pure virtual function, which means that all child classes of gun must create their own definition for it.
	//this is the least complicated one.
	//notice how it takes in a game object pointer. this allows us to give the same guns to enemies and players
	void Sedna::olReliable::shoot(float dt, Sedna::GameObject* p, bool isPlayer)
	{
		//evyn's patented timer code
		if (gunTimer > gunTimerMax) {
			gunTimer = 0;
			hasShot = false;
		}
		if (gunTimer == 0) {
			hasShot = true;
			ammo--;
			//make a new projectile
			p->projectiles.push_back(new Sedna::Projectile("Bullet2.png", p->getScene(), p->hitbox->getLocation(), 5));

			///<LEAVE THIS. this is what sets the dt member variable. if you remove this, projectiles will not work properly!>
			//right now, this function updates the value of dt. later in the code, it will *actually* update everything
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
			//now that a force is set, the next time we update the projectile will move.

		}
		if (hasShot)
			gunTimer += dt;
	}




	//shotgun
	Sedna::bloodyMary::bloodyMary()
		:Gun(3, 5, 0.9f, 5)
	{
	}

	void bloodyMary::shoot(float dt, Sedna::GameObject * p, bool isPlayer)
	{
		if (gunTimer > gunTimerMax) {
			gunTimer = 0;
			hasShot = false;
		}

		if (gunTimer == 0) {
			hasShot = true;
			ammo--;

			for (int i = 0; i < 5; i++) {
				p->projectiles.push_back(new Projectile("Bullet2.png", p->getScene(), p->hitbox->getLocation(), 5));
				p->projectiles.back()->update(dt);
			}

			for (auto x : p->projectiles)
				x->update(dt);

			//a bit of important redundant code
			while (p->projectiles.size() > projLimit) {

				p->projectiles.front()->hitbox->getDrawNode()->removeFromParent();
				p->projectiles.front()->sprite->removeFromParent();
				p->projectiles.erase(p->projectiles.begin());
			}

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
				for (int i = 0; i < GameObject::gameObjects.size(); i++) {
					if (GameObject::gameObjects[i]->id == "Player") {

						if (GameObject::gameObjects[i]->hitbox->getLocation().x - p->hitbox->getLocation().x < 0) {
							p->projectiles[0]->hitbox->setForce(cocos2d::Vec2(-5.06, 0) * 100);//projectile on the left
							p->projectiles[1]->hitbox->setForce(cocos2d::Vec2(-4.5, -1.75) * 100);
							p->projectiles[2]->hitbox->setForce(cocos2d::Vec2(-3.35, -3.35) * 100);//projectiles in the middle
							p->projectiles[3]->hitbox->setForce(cocos2d::Vec2(-1.75, -4.5) * 100);
							p->projectiles[4]->hitbox->setForce(cocos2d::Vec2(0, -5.06) * 100);//projectile on the right
						}
						else {
							p->projectiles[0]->hitbox->setForce(cocos2d::Vec2(0, -5.06) * 100);//projectile on the left
							p->projectiles[1]->hitbox->setForce(cocos2d::Vec2(1.75, -4.5) * 100);
							p->projectiles[2]->hitbox->setForce(cocos2d::Vec2(3.35, -3.35) * 100);//projectiles in the middle
							p->projectiles[3]->hitbox->setForce(cocos2d::Vec2(4.5, -1.75) * 100);
							p->projectiles[4]->hitbox->setForce(cocos2d::Vec2(5.06, 0) * 100);//projectile on the right
						}

					}
				}


			}
		}
		if (hasShot)
			gunTimer += dt;
	}
	rifle::rifle()
		//maybe we could do some logic that allows the player to shoot through multiple enemies with the rifle?
		:Gun(/*how much damage should this do?*/3, 1, 1.0f, 5)
	{
	}
	void rifle::shoot(float dt, Sedna::GameObject * p, bool isPlayer)
	{
		if (gunTimer > gunTimerMax) {
			gunTimer = 0;
			hasShot = false;
		}
		if (gunTimer == 0) {
			hasShot = true;
			ammo--;

			p->projectiles.push_back(new Sedna::Projectile("Bullet2.png", p->getScene(), p->hitbox->getLocation(), 5));

			p->projectiles.back()->update(dt);

			if (isPlayer) {

			}
			else {
				damage = 1;
				for (int i = 0; i < GameObject::gameObjects.size(); i++) {
					if (GameObject::gameObjects[i]->id == "Player") {
						auto direction = GameObject::gameObjects[i]->hitbox->getLocation() - p->hitbox->getLocation();
						if (direction.y > 0) {
							p->projectiles.back()->hitbox->getDrawNode()->removeFromParent();
							p->projectiles.back()->sprite->removeFromParent();
							//has to be end - 1 because end points to the position of a theoretical element that isnt actually there.
							p->projectiles.erase(p->projectiles.end() - 1);
							continue;
						}

						auto norm = direction / sqrt(direction.x*direction.x + direction.y*direction.y);


						p->projectiles.back()->hitbox->setForce(norm * 700);

					}
				}
			}
		}
		if (hasShot)
			gunTimer += dt;
	}
	dynamite::dynamite()
		:Gun(/*3 for now*/3, 8, 1.5f,/*5 for now*/5)
	{
	}
	void dynamite::shoot(float dt, Sedna::GameObject * p, bool isPlayer)
	{
		if (gunTimer > gunTimerMax) {
			gunTimer = 0;
			hasShot = false;
		}
		if (gunTimer == 0) {
			hasShot = true;
			ammo--;

			//for (int i = 0; i < 8; i++) {
			//	p->projectiles.push_back(new Projectile("Bullet2.png", p->getScene(), p->hitbox->getLocation(), 5));
			//	p->projectiles.back()->update(dt);
			//}

			if (isPlayer) {

			}
			else {
				//only let crazy pete use this...for now

				static_cast<CrazyPete*>(p)->dynStick->updateGO(dt);
				static_cast<CrazyPete*>(p)->dynStick->hitbox->setForce(cocos2d::Vec2(0, -471));
				static_cast<CrazyPete*>(p)->dynStick->sprite->setVisible(true);

			}

		}
		if (hasShot)
			gunTimer += dt;
	}
	theBiggestIron::theBiggestIron()
		:Gun(1, 10, 0.089f, 100)
	{
	}
	void theBiggestIron::shoot(float dt, Sedna::GameObject * p, bool isPlayer)
	{
		if (gunTimer > gunTimerMax) {
			gunTimer = 0;
			hasShot = false;
		}
		if (gunTimer == 0) {
			hasShot = true;
			ammo--;

			p->projectiles.push_back(new Sedna::Projectile("Bullet2.png", p->getScene(), p->hitbox->getLocation(), 5));

			p->projectiles.back()->update(dt);

			if (isPlayer) {
				auto vector = cocos2d::Vec2(static_cast<Player*>(p)->pSticks[1].x, static_cast<Player*>(p)->pSticks[1].y);
				auto direction = vector / sqrt(vector.x*vector.x + vector.y*vector.y);

				if (static_cast<Player*>(p)->pSticks[1].y >= -DEADZONE)
					p->projectiles.back()->hitbox->setForce((static_cast<Player*>(p)->pSticks[1].x > DEADZONE || static_cast<Player*>(p)->pSticks[1].x < -DEADZONE || static_cast<Player*>(p)->pSticks[1].y > DEADZONE)
						? direction * 471 : cocos2d::Vec2(0, 471));
				else {
					p->projectiles.back()->hitbox->getDrawNode()->removeFromParent();
					p->projectiles.back()->sprite->removeFromParent();
					p->projectiles.pop_back();
				}
			}
			else {

			}
		}
		if (hasShot)
			gunTimer += dt;
	}
}
