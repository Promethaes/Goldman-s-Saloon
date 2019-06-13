#include "Table.h"
#include "Primitive.h"
namespace Sedna {

	Sedna::Table::Table(cocos2d::Scene * scene, const cocos2d::Vec2 & LOCATION, float RADIUS)
		:GameObject("Table.png",scene,LOCATION,RADIUS)
	{
		id = "Table";
		hp = 4;
	}
	void Table::update(float dt)
	{
		updateGO(dt);
	}
	void Table::die()
	{
		//subject to change of course
		hitbox->getDrawNode()->removeFromParent();
		sprite->removeFromParent();
	}
}
