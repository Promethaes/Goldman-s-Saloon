#include "Enemy.h"
#include "Projectile.h"
#include "Primitive.h"
namespace Sedna {

	Outlaw::Outlaw(cocos2d::Scene * scene, const cocos2d::Vec2 & LOCATION, const char * path, float RADIUS, Gun* CURRENTGUN)
		:GameObject(path, scene, LOCATION, RADIUS)
	{
		hp = 3;//subject to change of course
		id = "Outlaw";
		currentGun = CURRENTGUN;

	}
	void Outlaw::update(float dt)
	{
		currentGun->shoot(dt, this, false);
		checkList();
		for (auto x : projectiles)
			x->update(dt);

		updateGO(dt);
	}
	void Outlaw::die()
	{
		for (int i = 0; i < projectiles.size(); i++) {
			projectiles[i]->hitbox->getDrawNode()->removeFromParent();
			projectiles[i]->sprite->removeFromParent();
			projectiles.erase(projectiles.begin() + i);
			i--;
		}
		hitbox->getDrawNode()->removeFromParent();
		sprite->removeFromParent();
	}
	void Outlaw::checkProjectileCollision()
	{
		for (int i = 0; i < GameObject::gameObjects.size(); i++) {
			for (int j = 0; j < projectiles.size(); j++) {
				if (GameObject::gameObjects[i]->id != "Outlaw" &&
					projectiles[j]->hitbox->checkCollision(*GameObject::gameObjects[i]->hitbox)) {

					GameObject::gameObjects[i]->hp -= currentGun->getDamage();/*change this to gun's dmaage when you can*/

					projectiles[j]->hitbox->getDrawNode()->removeFromParent();
					projectiles[j]->sprite->removeFromParent();
					projectiles.erase(projectiles.begin() + j);
					j--;

				}

			}
		}
	}
	void Outlaw::checkList()
	{
		while (projectiles.size() > currentGun->getProjLimit()) {

			projectiles.front()->hitbox->getDrawNode()->removeFromParent();
			projectiles.front()->sprite->removeFromParent();
			projectiles.erase(projectiles.begin());
		}
	}
	ShotgunOutlaw::ShotgunOutlaw(cocos2d::Scene * scene, const cocos2d::Vec2 & LOCATION, const char * path)
		:Outlaw(scene, LOCATION, path)
	{
		currentGun = new bloodyMary();
	}
	void ShotgunOutlaw::die()
	{
		for (int i = 0; i < projectiles.size(); i++) {
			projectiles[i]->hitbox->getDrawNode()->removeFromParent();
			projectiles[i]->sprite->removeFromParent();
			projectiles.erase(projectiles.begin() + i);
			i--;
		}
		hitbox->getDrawNode()->removeFromParent();
		sprite->removeFromParent();
	}
}
