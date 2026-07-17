#include"Enemy.h"
#include"Screen.h"
#include"Player.h"

Enemy::Enemy()
{
	enemy = LoadGraph("data/Enemy/slime_block_walk_a.png");
	x = 800;
	y = 500;

	box.left = x;
	box.top = y;
	box.right = x + 64;
	box.bottom = y + 64;
}

Enemy::~Enemy()
{

}

void Enemy::Update()
{
	float dx = E_playerPositionX - x;
	float dy = E_playerPositionY - y;
	float distance = sqrtf(dx * dx + dy * dy);

	if (distance > 300)
	{
		state = Shoot;
	}
	else
	{
		state = Melee;
	}
	if (rand() % 5000 == 0)
	{
		state = Teleport;
	}

	switch (state)
	{
	case Enemy::Shoot:
		ShootUpdate();
		break;
	case Enemy::Melee:
		MeleeUpdate();
		break;
	case Enemy::Teleport:
		TeleportUpdate();
		break;
	default:
		break;
	}

	


	//移動制限
	if (y < -30)
	{
		y = -30;
	}
	if (y > Screen::HEIGHT - 125)
	{
		y = Screen::HEIGHT - 125;
	}
	if (x < -30)
	{
		x = -30;
	}
	if (x > Screen::WIDTH - 115)
	{
		x = Screen::WIDTH - 115;
	}

	//当たり判定
	box.left = x;
	box.top = y;
	box.right = x + 64;
	box.bottom = y + 64;
}

void Enemy::ShootUpdate()
{

}

void Enemy::MeleeUpdate()
{

}

void Enemy::TeleportUpdate()
{
	//テレポート時の処理
	int offsetX = rand() % 201 - 100;
	int offsetY = rand() % 201 - 100;

	x = E_playerPositionX + offsetX;
	y = E_playerPositionY + offsetY;
}

void Enemy::Draw()
{
	DrawGraph(x, y, enemy, TRUE);

	//当たり判定の可視化
	DrawBox((int)box.left, (int)box.top, (int)box.right, (int)box.bottom, GetColor(255, 0, 0), FALSE);
}

const Box& Enemy::GetBox() const
{
	return box;
}

int Enemy::GetEnemyHP() const
{
	return E_HP;
}

void Enemy::SetPlayerPosition(float px, float py)
{
	E_playerPositionX = px;
	E_playerPositionY = py;
}
