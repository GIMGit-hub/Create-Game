#include"Player.h"
#include "Screen.h"
#include "Enemy.h"
#include "PlayScene.h"

Player::Player()
{
	player = LoadGraph("data/Player/Night.png");
	swordGraph = LoadGraph("data/weapon/weapon.png");
	x = 100;
	y = 100;

	GetGraphSize(swordGraph, &swordImagW, &swordImagH);

	box.left = x + 12;
	box.top = y + 8;
	box.right = x + 52;
	box.bottom = y + 60;
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

	bool isMoving = CheckHitKey(KEY_INPUT_W) || CheckHitKey(KEY_INPUT_S)
		|| CheckHitKey(KEY_INPUT_A) || CheckHitKey(KEY_INPUT_D);
	
	if (isMoving)
	{
		animTimer++;
		if (animTimer >= 8)
		{
			animTimer = 0;
			playerAnimIndex = (playerAnimIndex + 1) % 4;
		}
	}
	else
	{
		playerAnimIndex = 0;
		animTimer = 0;
	}

	//攻撃するときの処理
	if (CheckHitKey(KEY_INPUT_SPACE) && !isAttack && attackCoolTime == 0)
	{
		isAttack = true;
		attackTimer = 50;
		hitEnemy = false;
	}

	
	
	if (attackCoolTime == 0 && isAttack)
	{
		//攻撃の進行度
		float progress = 1.0f - (float)attackTimer / 50.0f;

		//振り角度
		float swingRange = 120.0f * (3.14159265f / 180.0f);
		float startAngle = -swingRange / 2.0f;
		float currentAngle = startAngle + swingRange * progress;

		//方向ごとの基準角度
		float baseAngle = 0.0f;
		float centerX = x + 63;
		float centerY = y + 63;

		if (direction == "right")      baseAngle = 0.0f;
		else if (direction == "left")  baseAngle = 3.14159265f;
		else if (direction == "up")    baseAngle = -3.14159265f / 2.0f;
		else if (direction == "down")  baseAngle = 3.14159265f / 2.0f;

		float finalAngle = baseAngle + currentAngle;

		//剣先座標を算出(Draw()でも同じ値を使う)
		swordCenterX = centerX + cosf(finalAngle) * swordDist;
		swordCenterY = centerY + sinf(finalAngle) * swordDist;
		swordAngle = finalAngle;

		//剣先を中心にattackBoxを作る
		attackBox.left = swordCenterX - attackBoxSize / 2;
		attackBox.top = swordCenterY - attackBoxSize / 2;
		attackBox.right = swordCenterX + attackBoxSize / 2;
		attackBox.bottom = swordCenterY + attackBoxSize / 2;
		
		attackTimer--;
		if (attackTimer <= 0)
		{
			isAttack = false;
			attackCoolTime = 100;
		}
	}
	if (attackCoolTime > 0)
	{
		attackCoolTime--;
	}

	//移動後の座標を当たり判定へ
	box.left = x + 12;
	box.top = y + 8;
	box.right = x + 52;
	box.bottom = y + 60;
}

void Player::Draw()
{
	
	int row = 0;
	if (direction == "down")
	{
		row = 0;
	}
	else if (direction == "left")
	{
		row = 1;
	}
	else if (direction == "right")
	{
		row = 2;
	}
	else if(direction == "up")
	{
		row = 3;
	}

	int srcX = playerAnimIndex * CELL_W;
	int srcY = row * CELL_H;

	DrawRectGraph(x, y, srcX, srcY, CELL_W, CELL_H, player,TRUE);

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

		int imgLongSide = (swordImagW > swordImagH) ? swordImagW : swordImagH;
		double extRate = (double)attackBoxSize/ (double)imgLongSide;

		DrawRotaGraph((int)swordCenterX,(int)swordCenterY, extRate, swordAngle + 3.14159265f / 4.0f, swordGraph, TRUE);

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