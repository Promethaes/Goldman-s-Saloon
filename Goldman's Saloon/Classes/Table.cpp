#include "Table.h"
#include "Primitive.h"
namespace Sedna {

	Sedna::Table::Table(cocos2d::Scene * scene, const cocos2d::Vec2 & LOCATION, Powerups::Powerup_Type POTIONTYPE, float RADIUS)
		:GameObject("Table.png", scene, LOCATION, RADIUS)
	{
		id = "Table";
		hp = 4;
		potionType = POTIONTYPE;
	}
	void Table::update(float dt)
	{
		if (hitbox->getVelocity() != cocos2d::Vec2(0, 0))
			hitbox->addForce(hitbox->getVelocity().x *-10.0f, hitbox->getVelocity().y*-10.0f);

		updateGO(dt);
	}
	void Table::die()
	{
		//subject to change of course
		hitbox->getDrawNode()->removeFromParent();
		sprite->removeFromParent();
	}
}
