#pragma once
#include "../Library/SceneBase.h"
#include"Player.h"
#include"Enemy.h"

class PlayScene : public SceneBase
{
public:
	PlayScene();
	~PlayScene();
	void Update() override;
	void Draw() override;

	bool GameOverFlg = false;

private:
	int map;
	Player* player;
	Enemy* enemy;

	double GameOverTimer = 0;

	bool GameClearFlg = false;
	double GameClearTimer = 0;
	int m_lastTime = 0;
};
