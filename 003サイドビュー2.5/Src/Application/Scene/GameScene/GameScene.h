#pragma once
#include"../BaseScene/BaseScene.h"
class Player;
class Enemy;
class GameScene : public BaseScene
{
public :

	GameScene() { Init(); }
	~GameScene() {}

private:

	void Event() override;
	void Init() override;
	//ウィークポインター
	std::weak_ptr<Player> m_player;
};
