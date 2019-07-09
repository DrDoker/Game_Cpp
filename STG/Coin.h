#pragma once

#include "Entity.h"

class Coin :public Entity {
public:

	Coin(Image &image, String Name, Level &lvl, float X, float Y, int W, int H);
	~Coin();
	void update(float time) override;

};

