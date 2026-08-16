#include"Player.h"
#include "Screen.h"
#include "Enemy.h"
#include "PlayScene.h"

Player::Player()
{
	player = LoadGraph("data/Player/character_green_hit.png");
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
	//ˆÚ“®ˆ—
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


	//UŒ‚‚·‚é‚Æ‚«‚Ìˆ—
	if (CheckHitKey(KEY_INPUT_SPACE) && !isAttack && attackCoolTime == 0)
	{
		isAttack = true;
		attackTimer = 50;
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
			attackBox.left = x + 20;
			attackBox.top = y + 32;
			attackBox.right = x - 46;
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

	//ˆÚ“®Œã‚ÌÀ•W‚ğ“–‚½‚è”»’è‚Ö
	box.left = x + 18;
	box.top = y + 32;
	box.right = x + 108;
	box.bottom = y + 128;
}

void Player::Draw()
{
	DrawGraph(x, y, player, TRUE);

	//“–‚½‚è”»’è‚Ì‰Â‹‰»
	DrawBox((int)box.left,(int)box.top,(int)box.right,(int)box.bottom,GetColor(255, 0, 0),FALSE);

	//UŒ‚
	if (isAttack)
	{
		DrawBox(
			attackBox.left,
			attackBox.top,
			attackBox.right,
			attackBox.bottom,
			GetColor(255, 255, 0),
			FALSE);
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

