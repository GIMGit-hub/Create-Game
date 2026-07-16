#include"Enemy.h"

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
	box.left = x;
	box.top = y;
	box.right = x + 64;
	box.bottom = y + 64;
}

void Enemy::Draw()
{
	DrawGraph(x, y, enemy, TRUE);

	//“–‚½‚è”»’è‚Ì‰ÂŽ‹‰»
	DrawBox((int)box.left, (int)box.top, (int)box.right, (int)box.bottom, GetColor(255, 0, 0), FALSE);
}

const Box& Enemy::GetBox() const
{
	return box;
}