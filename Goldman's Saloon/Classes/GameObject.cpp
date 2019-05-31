#include "GameObject.h"
#include "Primitive.h"
namespace Sedna {
	std::vector<GameObject*> GameObject::gameObjects = {};
	GameObject::GameObject(const char * path, cocos2d::Scene* scene, const cocos2d::Vec2 & LOCATION, float RADIUS, float ANGLE, unsigned int SEGMENTS)
	{
		hitbox = new CirclePrimitive(LOCATION, RADIUS, ANGLE, SEGMENTS);
		sprite = cocos2d::Sprite::create(path);
		scene->addChild(hitbox->getDrawNode(), 9);
		scene->addChild(sprite, 10);
		id += gameObjects.size();
		gameObjects.push_back(this);
		this->scene = scene;
	}
	
	void GameObject::updateGO(float dt)
	{
		hitbox->update(dt);
		sprite->setPosition(hitbox->getLocation());
	}
}
