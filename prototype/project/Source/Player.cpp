#include"Player.h"
#include "Screen.h"
#include "Enemy.h"
#include "PlayScene.h"

Player::Player()
{
	player = LoadGraph("data/Player/character_green_hit.png");
	swordGraph = LoadGraph("data/weapon/weapon.png");
	x = 100;
	y = 100;

	box.left = x + 18;
	box.top = y + 32;
	box.right = x + 108;
	box.bottom = y + 128;
}

Player::~Player()
{

}

void Player::SetGameOver(bool value)
{
	P_GameOverFlg = value;
}

void Player::Update()
{
	if (P_GameOverFlg)
	{
		return;
	}
	//移動処理
	if (CheckHitKey(KEY_INPUT_W))
	{
		y -= P_move;
		if (y < -30)
		{
			y = -30;
		}
		direction = "up";
	}

	if (CheckHitKey(KEY_INPUT_S))
	{
		y += P_move;
		if (y > Screen::HEIGHT-125)
		{
			y = Screen::HEIGHT-125;
		}
		direction = "down";
	}

	if (CheckHitKey(KEY_INPUT_A))
	{
		x -= P_move;
		if (x < -30)
		{
			x = -30;
		}
		direction = "left";
	}

	if (CheckHitKey(KEY_INPUT_D))
	{
		x += P_move;
		if (x > Screen::WIDTH-115)
		{
			x = Screen::WIDTH-115;
		}
		direction = "right";
	}


	//攻撃するときの処理
	if (CheckHitKey(KEY_INPUT_SPACE) && !isAttack && attackCoolTime == 0)
	{
		isAttack = true;
		attackTimer = 50;
		hitEnemy = false;
	}

	if (attackCoolTime == 0)
	{
		if (isAttack && direction == "right")
		{
			attackBox.left = x + 96;
			attackBox.top = y + 32;
			attackBox.right = x + 160;
			attackBox.bottom = y + 96;

			attackTimer--;

			if (attackTimer <= 0)
			{
				isAttack = false;
				attackCoolTime = 100;
			}
		}
		else if(isAttack && direction == "left")
		{
			attackBox.left = x - 84;
			attackBox.top = y + 32;
			attackBox.right = x - 20;
			attackBox.bottom = y + 96;

			attackTimer--;

			if (attackTimer <= 0)
			{
				isAttack = false;
				attackCoolTime = 100;
			}
		}
		else if (isAttack && direction == "up")
		{
			attackBox.left = x + 32;
			attackBox.top = y - 2;
			attackBox.right = x + 96;
			attackBox.bottom = y - 46;

			attackTimer--;

			if (attackTimer <= 0)
			{
				isAttack = false;
				attackCoolTime = 100;
			}
		}
		else if(isAttack && direction == "down")
		{
			attackBox.left = x + 32;
			attackBox.top = y + 96;
			attackBox.right = x + 96;
			attackBox.bottom = y + 160;

			attackTimer--;

			if (attackTimer <= 0)
			{
				isAttack = false;
				attackCoolTime = 100;
			}
		}
		
	}
	
	if (attackCoolTime > 0)
	{
		attackCoolTime--;
	}

	//移動後の座標を当たり判定へ
	box.left = x + 18;
	box.top = y + 32;
	box.right = x + 108;
	box.bottom = y + 128;
}

void Player::Draw()
{
	DrawGraph(x, y, player, TRUE);

	//当たり判定の可視化
	DrawBox((int)box.left,(int)box.top,(int)box.right,(int)box.bottom,GetColor(255, 0, 0),FALSE);

	//攻撃時
	if (isAttack)
	{
		DrawBox(
			attackBox.left,
			attackBox.top,
			attackBox.right,
			attackBox.bottom,
			GetColor(255, 255, 0),
			FALSE);

		//攻撃の進行度
		float progress = 1.0f - (float)attackTimer / 50.0f;

		//振り角度
		float swingRange = 120.0f * (3.14159265f / 180.0f);
		float startAngle = -swingRange / 2.0f;
		float currentAngle = startAngle + swingRange * progress;

		//剣の初期向き + プレイヤー中心からの描画距離
		float baseAngle = 0.0f;
		float centerX = 0, centerY = 0;
		int swordDist = 60; //プレイヤー中心から剣までの距離

		if (direction == "right")
		{
			baseAngle = 0.0f;
			centerX = x + 63;
			centerY = y + 63;
		}
		else if (direction == "left")
		{
			baseAngle = 3.14159265f; // 180度
			centerX = x + 63;
			centerY = y + 63;
		}
		else if (direction == "up")
		{
			baseAngle = -3.14159265f / 2.0f; // -90度
			centerX = x + 63;
			centerY = y + 63;
		}
		else if (direction == "down")
		{
			baseAngle = 3.14159265f / 2.0f; // 90度
			centerX = x + 63;
			centerY = y + 63;
		}

		float finalAngle = baseAngle + currentAngle;

		int swordX = centerX + (int)(cosf(finalAngle) * swordDist);
		int swordY = centerY + (int)(sinf(finalAngle) * swordDist);

		DrawRotaGraph(swordX, swordY, 1.0, finalAngle + 3.14159265f / 4.0f, swordGraph, TRUE);

	}
	//DrawRectGraph(x, y, 64, 0, 64, 64, player, 1);
}

const Box& Player::GetBox() const
{
	return box;
}

const Box& Player::GetAttackBox() const
{
	return attackBox;
}

bool Player::IsAttack() const
{
	return isAttack;
}

int Player::GetHP() const
{
	return P_HP;
}

void Player::Damage(int value)
{
	P_HP -= value;
	if (P_HP < 0)
	{
		P_HP = 0;
	}
}

float Player::GetPlayerPositionX() const
{
	return x;
}

float Player::GetPlayerPositionY() const
{
	return y;
}

bool Player::HitEnemy() const
{
	return hitEnemy;
}

void Player::SetHitEnemy(bool value)
{
	hitEnemy = value;
}