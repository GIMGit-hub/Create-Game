#include "Bullet.h"
#include "Screen.h"
#include "DxLib.h"
#include <cmath>

Bullet::Bullet(float startX, float startY, float angle, float speed,int handle)
{
	x = startX;
	y = startY;
	vx = cosf(angle) * speed;
	vy = sinf(angle) * speed;
	graphHandle = handle;
	box.left = x;
	box.top = y;
	box.right = x + 16;
	box.bottom = y + 16;

	
}

void Bullet::Update()
{
	x += vx;
	y += vy;

	box.left = x;
	box.top = y;
	box.right = x + 16;
	box.bottom = y + 16;

	if (x < -50 || x > Screen::WIDTH + 50 || y < -50 || y > Screen::HEIGHT + 50)
	{
		isDead = true;
	}
}

void Bullet::Draw()
{
	DrawExtendGraph((int)x - width / 2, (int)y - height / 2, (int)x + width / 2, y + height / 2, graphHandle, true);
	DrawBox((int)box.left, (int)box.top, (int)box.right, (int)box.bottom, GetColor(255, 0, 0), FALSE);
}

bool Bullet::IsDead() const
{
	return isDead;
}

const Box& Bullet::GetBox() const
{
	return box;
}
