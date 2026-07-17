#pragma once
#include"../Library/GameObject.h"
#include"Box.h"

class  Player;

class Enemy : public GameObject
{
public:
	Enemy();
	~Enemy();
	void Update();
	void Draw();

	void ShootUpdate();
	void MeleeUpdate();
	void TeleportUpdate();

	const Box& GetBox() const;

	//enemyÇÃHPéÊìæ
	int GetEnemyHP() const;

	void SetPlayerPosition(float px, float py);
	
private:

	int enemy;
	float x, y;

	int E_HP = 10;

	//enemyë§Ç≈égÇ§playerÇÃç¿ïW
	float E_playerPositionX = 0;
	float E_playerPositionY = 0;

	enum EnemyState
	{
		Shoot,
		Melee,
		Teleport
	};
	EnemyState state;

	Player* player;

	Box box;
};

