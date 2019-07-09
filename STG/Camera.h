#pragma once

#include <SFML/Graphics.hpp>
using namespace sf;

class Camera
{
public:
	View view;
	Camera();
	~Camera();

	void setPlayerCoordinateForView(float x, float y);
};

