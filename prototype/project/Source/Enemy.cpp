#include"Enemy.h"
#include"Screen.h"
#include"Player.h"
#include<algorithm>

Enemy::Enemy()
{
	enemy = LoadGraph("data/Enemy/Enemy.png");
	bulletGraphHandle = LoadGraph("data/Enemy/Bullet.png");
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

	if (distance > 1)
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

	//‘S’e‚ğ1ƒtƒŒ[ƒ€“®‚©‚µ‚Ä‚¢‚é
	for (auto& b : bullets)
	{
		b.Update();
	}

	//€‚ñ‚¾’e‚ğvecter‚ÌŒã‚ë‚É‚¸‚ç‚µŒã‚ë‚Ì•ª‚ğØ‚èÌ‚Ä‚é
	bullets.erase(
		std::remove_if(bullets.begin(),bullets.end(),
			[](const Bullet& b) {return b.IsDead(); }),
		bullets.end());


	//ˆÚ“®§ŒÀ
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

	//“–‚½‚è”»’è
	box.left = x;
	box.top = y;
	box.right = x + 64;
	box.bottom = y + 64;
}

void Enemy::ShootUpdate()
{
	patternTimer++;
	if (patternTimer >= PATTERN_CHANGE_INTERVAL)
	{
		patternTimer = 0;
		currrentPattern = static_cast<ShootPattern>(rand() % 3);
	}

	shootTimer++;
	if (shootTimer < SHOOT_INTERVAL) return;
	shootTimer = 0;

	float dx = E_playerPositionX - x;
	float dy = E_playerPositionY - y;
	float aimAngle = atan2f(dy, dx);

	switch (currrentPattern)
	{
	case Aimed:
	{
		bullets.push_back(Bullet(x + 32, y + 32, aimAngle, 5.0f,bulletGraphHandle));
		break;
	}
	case Circular:
	{
		const int bulletCount = 16;
		for (int i = 0; i < bulletCount; i++)
		{
			float angle = (2.0f * 3.14159265f * i) / bulletCount;
			bullets.push_back(Bullet(x + 32, y + 32, angle, 3.5f,bulletGraphHandle));
		}
		break;
	}	
	case Spiral:
	{
		bullets.push_back(Bullet(x + 32, y + 32, spiralAngle, 4.0f,bulletGraphHandle));
		spiralAngle += 0.3f;
		break;
	}
	}
}

void Enemy::MeleeUpdate()
{
	//À‘•—\’è‚¾‚Á‚½‹ß‹——£UŒ‚
}

void Enemy::TeleportUpdate()
{
	float angle = (rand() % 360) * (3.14159265f / 180.0f);

	float dist = TELEPORT_MIN_DIST * (float)(rand() % (int)(TELEPORT_MAX_DIST - TELEPORT_MIN_DIST));

	/*x = E_playerPositionX + cosf(angle) * dist;
	y = E_playerPositionY + sinf(angle) * dist;*/

	x = E_playerPositionX + E_playerPositionX;
	y = E_playerPositionY + E_playerPositionY;
}

void Enemy::Draw()
{
	DrawGraph(x, y, enemy, TRUE);

	//“–‚½‚è”»’è‚Ì‰Â‹‰»
	DrawBox((int)box.left, (int)box.top, (int)box.right, (int)box.bottom, GetColor(255, 0, 0), FALSE);

	for (auto& b : bullets)
	{
		b.Draw();
	}
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

const std::vector<Bullet>& Enemy::GetBullets() const
{
	return bullets;
}

void Enemy::TakeDamage(int damage)
{
	E_HP -= damage;
	if (E_HP <= 0)
	{
		E_HP = 0;
		isEnemyDead = true;
	}
}

bool Enemy::IsEnemyDead() const
{
	return isEnemyDead;
}
