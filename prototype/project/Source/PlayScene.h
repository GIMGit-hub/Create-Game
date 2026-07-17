#pragma once
#include "../Library/SceneBase.h"
#include"Player.h"
#include"Enemy.h"


/// <summary>
/// ゲームプレイのシーンを制御する
/// </summary>
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

	int GameOverTimer = 0;
};
