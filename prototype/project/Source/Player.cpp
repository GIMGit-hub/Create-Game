#include"Player.h"


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

void Player::Update()
{

	//ˆÚ“®ˆ—
	if (CheckHitKey(KEY_INPUT_W))
	{
		y -= 5.0f;
	}

	if (CheckHitKey(KEY_INPUT_S))
	{
		y += 5.0f;
	}

	if (CheckHitKey(KEY_INPUT_A))
	{
		x -= 5.0f;
	}

	if (CheckHitKey(KEY_INPUT_D))
	{
		x += 5.0f;
	}

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
	//DrawRectGraph(x, y, 64, 0, 64, 64, player, 1);
}

const Box& Player::GetBox() const
{
	return box;
}