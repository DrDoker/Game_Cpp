#pragma once

#include "Entity.h"

class Life :public Entity {
public:

	Life(Image &image, String Name, Level &lvl, float X, float Y, int W, int H);
	~Life();
	void update(float time) override;

};

