#pragma once
#include"../Library/GameObject.h"
#include"Box.h"
#include <vector>
#include "Bullet.h"

enum ShootPattern
{
	Aimed,//自機狙い単発
	Circular,//全方位円形
	Spiral,//螺旋
};


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

	//enemyのHP取得
	int GetEnemyHP() const;

	void SetPlayerPosition(float px, float py);

	const std::vector<Bullet>& GetBullets() const;

	void TakeDamage(int damage);
	bool IsEnemyDead() const;
	
private:

	int enemy;
	float x, y;

	int E_HP = 10;

	bool isEnemyDead = false;

	//enemy側で使うplayerの座標
	float E_playerPositionX = 0;
	float E_playerPositionY = 0;

	enum EnemyState
	{
		Shoot,
		Melee,
		Teleport
	};

	int bulletGraphHandle;

	std::vector<Bullet> bullets;
	int shootTimer = 0;
	ShootPattern currrentPattern = Aimed;
	float spiralAngle = 0.0f;
	int patternTimer = 0;
	const int SHOOT_INTERVAL = 40;//弾の打つ間隔
	const int PATTERN_CHANGE_INTERVAL = 500;//パターン切り替え

	EnemyState state;

	Player* player;

	Box box;

	const float TELEPORT_MIN_DIST = 150.0f;
	const float TELEPORT_MAX_DIST = 250.0f;
};

