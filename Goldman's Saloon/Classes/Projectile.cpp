#include "Projectile.h"
namespace Sedna {

	//WARNING: projectiles are not a part of the game object list! their physics and updating should be done internally!
	Sedna::Projectile::Projectile(const char * path, cocos2d::Scene * scene, const cocos2d::Vec2 & LOCATION, float RADIUS)
		:GameObject(path,scene,LOCATION,RADIUS,false)
	{
		sprite->setScale(1.5f);
	}
	
	void Projectile::update(float dt)
	{
		updateGO(dt);
	}
	void Projectile::die()
	{
		//do nothing, because projectile death is handled internally
	}
}
