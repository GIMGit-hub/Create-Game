#pragma once
#include "../Library/GameObject.h"
#include "Box.h"
#include "PlayScene.h"

class Enemy;

class Player : public GameObject
{
public:
	Player();
	~Player();
	void Update()override;
	void Draw()override;

	const Box& GetBox() const;
	const Box& GetAttackBox() const;
	bool IsAttack() const;

	int GetHP() const;
	void Damage(int value);

	float GetPlayerPositionX() const;
	float GetPlayerPositionY() const;

	void SetGameOver(bool gameover);
	
	bool HitEnemy() const;
	void SetHitEnemy(bool value);

private:
	int player;
	float x, y;

	int P_HP = 1;
	float P_move = 2.0f;

	std::string direction;

	Enemy* enemy;

	Box box;
	Box attackBox;

	bool hitEnemy = false;

	//攻撃しているかを判定
	bool isAttack = false;
	//攻撃の持続時間
	int attackTimer = 0;
	//攻撃のクールタイム
	int attackCoolTime = 0;

	bool P_GameOverFlg = false;

	int swordGraph;
	int swordImagW, swordImagH;

	float swordCenterX = 0, swordCenterY = 0; //剣先座標
	float swordAngle = 0;//剣の回転角度
	int swordDist = 70;//プレイヤー中心から剣先までの距離
	int attackBoxSize = 60;//剣先を中心とした判定枠の一辺

	int playerAnimIndex = 0;
	int animTimer = 0;
	const int CELL_W = 64;
	const int CELL_H = 64;
};

