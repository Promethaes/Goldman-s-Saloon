#include "Projectile.h"
namespace Sedna {

	Sedna::Projectile::Projectile(const char * path, cocos2d::Scene * scene, const cocos2d::Vec2 & LOCATION, float RADIUS)
		:GameObject(path,scene,LOCATION,RADIUS,false)
	{
	}
	
	void Projectile::update(float dt)
	{
		updateGO(dt);
	}
}
