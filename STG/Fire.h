#pragma once

#include "Entity.h"

class Fire :public Entity {
public:

	Fire(Image &image, String Name, Level &lvl, float X, float Y, int W, int H, float pDx);
	~Fire();
	void update(float time) override;
	void checkCollisionWithMap(float Dx, float Dy);
	float playerDx;

};

