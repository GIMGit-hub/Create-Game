#include "PlayScene.h"
#include "Player.h"
#include "Enemy.h"
#include "Collision.h"
#include "Bullet.h"

PlayScene::PlayScene()
{
	map = LoadGraph("data/map/map3.jpg");

	player = new Player();
	enemy = new Enemy();
	
}

PlayScene::~PlayScene()
{
	//delete player;
	//delete enemy;
}

void PlayScene::Update()
{
	if (!GameOverFlg && !GameClearFlg)
	{
		player->Update();

		enemy->SetPlayerPosition(player->GetPlayerPositionX(), player->GetPlayerPositionY());

		enemy->Update();

		//player‚Æenemy‚ª“–‚½‚Á‚½Žž‚Ìˆ—
		if (CheckHit(player->GetBox(), enemy->GetBox()))
		{
			//“–‚½‚Á‚½Žž‚Ìˆ—
			//DrawString(10, 10, "Hit!", GetColor(0, 0, 0));
			player->Damage(1);
			GameOverFlg = true;
			player->SetGameOver(GameOverFlg);
			GameOverTimer = 600;
		}
		//enemy‚Ì’e‚ªplayer‚É“–‚½‚Á‚½‚Æ‚«‚Ìˆ—
		for (const auto& bullet : enemy->GetBullets())
		{
			if (CheckHit(player->GetBox(), bullet.GetBox()))
			{
				player->Damage(1);
				GameOverFlg = true;
				player->SetGameOver(GameOverFlg);
				GameOverTimer = 200;
				break;
			}
		}
		//player‚ªUŒ‚‚ðs‚¢enemy‚Öhit‚µ‚½Žž‚Ìˆ—
		if (player->IsAttack() && !player->HitEnemy())
		{
			if (CheckHit(player->GetAttackBox(), enemy->GetBox()))
			{
				enemy->TakeDamage(1);
				player->SetHitEnemy(true);

				if (enemy->IsEnemyDead())
				{
					GameClearFlg = true;
					player->SetGameOver(true);
					GameClearTimer = 200;
				}

				DrawString(10, 10, "Hit", GetColor(0, 255, 0));
			}
		}
		
		

	}
	else if(GameOverFlg)
	{
		GameOverTimer--;

		if (GameOverTimer <= 0)
		{
			SceneManager::ChangeScene("TITLE");
		}
	}
	else if(GameClearFlg)
	{
		GameOverTimer--;

		if (GameOverTimer <= 0)
		{
			SceneManager::ChangeScene("TITLE");
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
	//DrawString(0, 0, "PLAY SCENE", GetColor(255, 255, 255));
	//DrawString(100, 400, "Push [T]Key To Title", GetColor(255, 255, 255));
	
	//DrawFormatString(10, 30, GetColor(255, 255, 255), "X:%.1f Y:%.1f", player->GetPlayerPositionX(), player->GetPlayerPositionY());

	if (GameOverFlg)
	{
		DrawString(100, 400, "GAMEOVER", GetColor(0, 0, 0));
	}
}
