#include "Table.h"
namespace Sedna {

	Sedna::Table::Table(cocos2d::Scene * scene, const cocos2d::Vec2 & LOCATION, float RADIUS)
		:GameObject("Table.png",scene,LOCATION,RADIUS)
	{
		id = "Table";
		hp = 5;
	}
	void Table::update(float dt)
	{
		updateGO(dt);
	}
}
