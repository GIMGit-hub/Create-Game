#pragma once
#include"../Library/GameObject.h"
#include"Box.h"


class Enemy : public GameObject
{
public:
	Enemy();
	~Enemy();
	void Update();
	void Draw();

	const Box& GetBox() const;
private:

	int enemy;
	float x, y;

	Box box;
};

