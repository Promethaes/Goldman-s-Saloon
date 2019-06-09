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
		for (auto x : projectiles)
			x->update(dt);
				
		updateGO(dt);
	}
	void Outlaw::die()
	{
		///<doesn't work right now>
		for (int i = 0; i < projectiles.size(); i++) {
			projectiles[i]->hitbox->getDrawNode()->removeFromParent();
			projectiles[i]->sprite->removeFromParent();
			projectiles.erase(projectiles.begin() + i);
			i--;
		}
		hitbox->getDrawNode()->removeFromParent();
		sprite->removeFromParent();
	}
	void Outlaw::shoot(float dt)
	{
		if (gunTimer > 0.5f) {
			gunTimer = 0;
			hasShot = false;
		}
		if (gunTimer == 0) {
			hasShot = true;
			projectiles.push_back(new Projectile(/*change this string later*/"Bullet2.png", scene, hitbox->getLocation(), 5));
			projectiles.back()->update(dt);

			projectiles.back()->hitbox->setForce(cocos2d::Vec2(0, -500));

		}
		if (hasShot)
			gunTimer += dt;
	}
	void Outlaw::checkList()
	{
		if (projectiles.size() > 4) {
			
			projectiles.front()->hitbox->getDrawNode()->removeFromParent();
			projectiles.front()->sprite->removeFromParent();
			projectiles.erase(projectiles.begin());
		}
	}
}
