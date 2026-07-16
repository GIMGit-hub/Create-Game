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

private:
	int player;
	float x, y;

	Box box;

	Box attackBox;

	bool isAttack = false;
	int attackTimer = 0;
};

