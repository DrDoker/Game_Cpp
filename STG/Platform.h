#pragma once

#include "Entity.h"

class Platform :public Entity {
public:

	Platform(Image &image, String Name, Level &lvl, float X, float Y, int W, int H, float dxP, float dyP);
	~Platform();
	void checkCollisionWithMap(float Dx, float Dy);
	void update(float time) override;

};

