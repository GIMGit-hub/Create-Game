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

	//player‚Æenemy‚ª“–‚½‚Á‚½Žž‚Ìˆ—
	if (CheckHit(player->GetBox(), enemy->GetBox()))
	{
		//“–‚½‚Á‚½Žž‚Ìˆ—
		DrawString(10, 10, "Hit!", GetColor(0, 0, 0));
	}
	//player‚ªUŒ‚‚ðs‚¢enemy‚Öhit‚µ‚½Žž‚Ìˆ—
	if (player->IsAttack())
	{
		if (CheckHit(player->GetAttackBox(), enemy->GetBox()))
		{
			DrawString(10, 10, "Hit", GetColor(0, 255, 0));
		}
	}


	if (CheckHitKey(KEY_INPUT_ESCAPE)) {
		SceneManager::ChangeScene("TITLE");
	}
}

void PlayScene::Draw()
{
	DrawGraph(0, 0, map,TRUE);
	player->Draw();
	enemy->Draw();
	DrawString(0, 0, "PLAY SCENE", GetColor(255, 255, 255));
	//DrawString(100, 400, "Push [T]Key To Title", GetColor(255, 255, 255));
}
