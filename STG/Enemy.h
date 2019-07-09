#pragma once

#include "Entity.h"

class Enemy :public Entity {
public:

	Enemy(Image &image, String Name, Level &lvl, float X, float Y, int W, int H);
	~Enemy();
	void checkCollisionWithMap(float Dx, float Dy);
	void update(float time) override;

};

