#pragma once
#include "../Library/GameObject.h"
#include "Box.h"


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

private:
	int player;
	float x, y;

	int P_HP = 1;
	float P_move = 2.0f;

	Box box;

	Box attackBox;

	//UŒ‚‚µ‚Ä‚¢‚é‚©‚ğ”»’è
	bool isAttack = false;
	//UŒ‚‚Ì‘±ŠÔ
	int attackTimer = 0;
	//UŒ‚‚ÌƒN[ƒ‹ƒ^ƒCƒ€
	int attackCoolTime = 0;

};

