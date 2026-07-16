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

private:
	int player;
	float x, y;

	Box box;
};

