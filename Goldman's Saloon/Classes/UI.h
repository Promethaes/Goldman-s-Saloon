#pragma once
#include <vector>
namespace cocos2d {
	class Sprite;
	class Label;
}
namespace Sedna {
	class Player;
	class PlayerUI {
	public:
		PlayerUI(Player* P);
		void update(float dt);
	private:
		Player* p;
		std::vector<cocos2d::Sprite*> hpSprites;
		cocos2d::Label* scoreLabel;
		cocos2d::Label* ammoLabel;
	};
}