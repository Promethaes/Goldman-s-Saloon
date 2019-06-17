#include "Primitive.h"
#include "Projectile.h"
#include <stdio.h>
namespace Sedna {
	std::vector<GameObject*> GameObject::gameObjects = {};
	GameObject::GameObject(const char * path, cocos2d::Scene* scene, const cocos2d::Vec2 & LOCATION, float RADIUS, bool pushback, float ANGLE, unsigned int SEGMENTS)
	{
		hitbox = new CirclePrimitive(LOCATION, RADIUS/1.1f, ANGLE, SEGMENTS);
		sprite = cocos2d::Sprite::create(path);
		sprite->setScale(0.7f);
		scene->addChild(hitbox->getDrawNode(), 9);
		scene->addChild(sprite, 10);
		srand(time(0));
		if (pushback)
			gameObjects.push_back(this);
		this->scene = scene;
		projectiles = {};
		hitbox->getDrawNode()->setVisible(false);
	}

	void GameObject::updateGO(float dt)
	{
		hitbox->update(dt);
		sprite->setPosition(hitbox->getLocation());
	}
	void GameObject::die()
	{
	}
	void GameObject::activateBulletTime()
	{
		hitbox->dt /= 2;
		hitbox->setForce(hitbox->getVelocity());
		for (int i = 0; i < projectiles.size(); i++) {
			projectiles[i]->hitbox->dt /= 2;
			projectiles[i]->hitbox->setForce(projectiles[i]->hitbox->getVelocity());
		}
	}
	
	
	
	
	
}
