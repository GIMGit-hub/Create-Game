#pragma once
#include "Box.h"

class Bullet
{
public:
	Bullet(float startX, float startY, float angle, float speed,int graphHandle);
	void Update();
	void Draw();
	bool IsDead() const;
	const Box& GetBox() const;

private:
	float x, y;
	float vx, vy;
	int graphHandle;
	Box box;
	bool isDead = false;

	int width = 50;
	int height = 50;

	
};


