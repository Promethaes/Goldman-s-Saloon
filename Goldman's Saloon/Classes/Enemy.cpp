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
		checkProjectileCollision();
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

	Rifleman::Rifleman(cocos2d::Scene* scene, const cocos2d::Vec2& LOCATION, const char* path)
		:Outlaw(scene,LOCATION,path)
	{
		currentGun = new rifle();
	}

	void Rifleman::die()
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
	CrazyPete::CrazyPete(cocos2d::Scene * scene, const cocos2d::Vec2 & LOCATION, const char * path)
		:Outlaw(scene,LOCATION,path)
	{
		currentGun = new dynamite();

		dynStick = new Projectile("a.png", scene, LOCATION, 8);

	}
	void CrazyPete::update(float dt)
	{
		currentGun->shoot(dt, this, false);
		checkDynamite(dt);
		checkProjectileCollision();
		for (auto x : projectiles)
			x->update(dt);

		updateGO(dt);
	}
	void CrazyPete::die()
	{
		for (int i = 0; i < projectiles.size(); i++) {
			projectiles[i]->hitbox->getDrawNode()->removeFromParent();
			projectiles[i]->sprite->removeFromParent();
			projectiles.erase(projectiles.begin() + i);
			i--;
		}
		hitbox->getDrawNode()->removeFromParent();
		sprite->removeFromParent();
		dynStick->hitbox->getDrawNode()->removeFromParent();
		dynStick->sprite->removeFromParent();
	}
	void CrazyPete::checkDynamite(float dt)
	{

		dynStick->sprite->setRotation(dynStick->sprite->getRotation() + 25.0f);
		dynStick->update(dt);
		if (this->hitbox->getLocation().y - dynStick->hitbox->getLocation().y > 200) {

			for (int i = 0; i < 8; i++) {
				projectiles.push_back(new Projectile("Bullet2.png", getScene(), dynStick->hitbox->getLocation(), 5));
				projectiles.back()->update(dt);
			}
			checkList();


			auto speed = 500;

			//set the force of all new bullets

			projectiles[0]->hitbox->setForce(cocos2d::Vec2(-1, 0)*speed);
			projectiles[1]->hitbox->setForce(cocos2d::Vec2(1, 0) *speed);
			projectiles[2]->hitbox->setForce(cocos2d::Vec2(0, 1) *speed);
			projectiles[3]->hitbox->setForce(cocos2d::Vec2(0, -1)*speed);
			projectiles[4]->hitbox->setForce(cocos2d::Vec2(-0.5f, -0.5f)*speed);
			projectiles[5]->hitbox->setForce(cocos2d::Vec2(-0.5f, 0.5f) *speed);
			projectiles[6]->hitbox->setForce(cocos2d::Vec2(0.5f, -0.5f) *speed);
			projectiles[7]->hitbox->setForce(cocos2d::Vec2(0.5f, 0.5f)  *speed);


			dynStick->hitbox->setLocation(hitbox->getLocation());
			dynStick->hitbox->setForce(cocos2d::Vec2(0, 0));
			dynStick->sprite->setVisible(false);
		}
	}
}
