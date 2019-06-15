/****************************************************************************
 Copyright (c) 2017-2018 Xiamen Yaji Software Co., Ltd.

 http://www.cocos2d-x.org

 Permission is hereby granted, free of charge, to any person obtaining a copy
 of this software and associated documentation files (the "Software"), to deal
 in the Software without restriction, including without limitation the rights
 to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 copies of the Software, and to permit persons to whom the Software is
 furnished to do so, subject to the following conditions:

 The above copyright notice and this permission notice shall be included in
 all copies or substantial portions of the Software.

 THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
 THE SOFTWARE.
 ****************************************************************************/

#include "HelloWorldScene.h"
#include "SimpleAudioEngine.h"


Sedna::XinputManager HelloWorld::manager = Sedna::XinputManager();
Sedna::XinputController* HelloWorld::p1Controller = manager.getController(0);
Sedna::Stick HelloWorld::p1Sticks[] = {};
Sedna::Triggers HelloWorld::p1Triggers;
Sedna::XinputController* HelloWorld::p2Controller = manager.getController(1);

// Print useful error message instead of segfaulting when files are not there.
static void problemLoading(const char* filename)
{
	printf("Error while loading: %s\n", filename);
	printf("Depending on how you compiled you might have to add 'Resources/' in front of filenames in HelloWorldScene.cpp\n");
}

// on "init" you need to initialize your instance
bool HelloWorld::init()
{
	//////////////////////////////
	// 1. super init first
	if (!Scene::init())
	{
		return false;
	}

	auto visibleSize = cocos2d::Director::getInstance()->getVisibleSize();
	cocos2d::Vec2 origin = cocos2d::Director::getInstance()->getVisibleOrigin();

	p1Controller = manager.getController(0);
	p2Controller = manager.getController(1);

	///<include the following lines in the update function of the child scene if you want triggers and sticks to work for player 1. repeat for player 2>
//p1Controller->updateSticks(p1Sticks);
//p1Controller->getTriggers(p1Triggers);

	manager.update();



	return true;
}

Background::Background(const char* path, cocos2d::Scene* scene)
{
	//ALL BACKGROUNDS SHOULD BE 1920 by 1080
	sprite = cocos2d::Sprite::create(path);
	sprite->setAnchorPoint(cocos2d::Vec2(0.0f, 0.0f));
	sprite->setScaleX(0.85f);
	sprite->setScaleY(0.92f);
	scene->addChild(sprite, -1000);
}
