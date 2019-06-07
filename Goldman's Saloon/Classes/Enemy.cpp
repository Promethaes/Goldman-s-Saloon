#include "Enemy.h"
#include "Projectile.h"
#include "Primitive.h"
namespace Sedna {

	Outlaw::Outlaw(cocos2d::Scene * scene, const cocos2d::Vec2 & LOCATION, const char * path, float RADIUS)
		:GameObject(path,scene,LOCATION,RADIUS)
	{
		hp = 3;//subject to change of course
		id = "Outlaw";
	}
	void Outlaw::update(float dt)
	{
		shoot(dt);
		checkList();
		for (auto x : eProjectiles)
			x->update(dt);
				
		updateGO(dt);
	}
	void Outlaw::die()
	{
		///<doesn't work right now>
		for (int i = 0; i < eProjectiles.size(); i++) {
			eProjectiles[i]->hitbox->getDrawNode()->removeFromParent();
			eProjectiles[i]->sprite->removeFromParent();
			eProjectiles.erase(eProjectiles.begin() + i);
			i--;
		}
	}
	void Outlaw::shoot(float dt)
	{
		if (gunTimer > 0.5f) {
			gunTimer = 0;
			hasShot = false;
		}
		if (gunTimer == 0) {
			hasShot = true;
			eProjectiles.push_back(new Projectile(/*change this string later*/"Bullet2.png", scene, hitbox->getLocation(), 5));
			eProjectiles.back()->update(dt);

			eProjectiles.back()->hitbox->setForce(cocos2d::Vec2(0, -500));

		}
		if (hasShot)
			gunTimer += dt;
	}
	void Outlaw::checkList()
	{
		if (eProjectiles.size() > 4) {
			
			eProjectiles.front()->hitbox->getDrawNode()->removeFromParent();
			eProjectiles.front()->sprite->removeFromParent();
			eProjectiles.erase(eProjectiles.begin());
		}
	}
}
