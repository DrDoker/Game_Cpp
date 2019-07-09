#include "Camera.h"



Camera::Camera()
{
}


Camera::~Camera()
{
}

void Camera::setPlayerCoordinateForView(float x, float y) {
	float tempX = x; float tempY = y;

	if (x < 430) tempX = 430;
	if (y < 240) tempY = 240;//верхнюю сторону
	if (y > 550) tempY = 550;//нижнюю стороню.для новой карты
	if (x > 2775) tempX = 2775;

	view.setCenter(tempX, tempY);
}