#include "PlayScene.h"
#include "Player.h"
#include "Enemy.h"
#include "Collision.h"

PlayScene::PlayScene()
{
	map = LoadGraph("data/map/ground-dot1.jpg");

	player = new Player();
	enemy = new Enemy();
}

PlayScene::~PlayScene()
{
	player->Update();
	enemy->Update();
}

void PlayScene::Update()
{
	player->Update();
	enemy->Update();

	if (CheckHit(player->GetBox(), enemy->GetBox()))
	{
		//“–‚½‚Á‚½Žž‚Ìˆ—
		DrawString(10, 10, "Hit!", GetColor(0, 0, 0));
	}


	if (CheckHitKey(KEY_INPUT_T)) {
		SceneManager::ChangeScene("TITLE");
	}
}

void PlayScene::Draw()
{
	DrawGraph(0, 0, map,TRUE);
	player->Draw();
	enemy->Draw();
	DrawString(0, 0, "PLAY SCENE", GetColor(255, 255, 255));
	DrawString(100, 400, "Push [T]Key To Title", GetColor(255, 255, 255));
}
