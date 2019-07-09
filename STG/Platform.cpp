#pragma once

#include "Platform.h"

Platform::Platform(Image &image, String Name, Level &lvl, float X, float Y, int W, int H, float dxP, float dyP) :Entity(image, Name, lvl, X, Y, W, H) {

	sprite.setTextureRect(IntRect(0, 0, w, h));
	dx = dxP;
	dy = dyP;
}

Platform::~Platform() {

}

void Platform::checkCollisionWithMap(float Dx, float Dy)//ф ци€ проверки столкновений с картой
{

	for (int i = 0; i < obj.size(); i++)//проходимс€ по объектам
		if (getRect().intersects(obj[i].rect))//провер€ем пересечение игрока с объектом
		{
			if (obj[i].name == "solidP")//если встретили преп€тствие
			{
				if (Dx>0) { x = obj[i].rect.left - w;  dx = -0.1; }
				if (Dx<0) { x = obj[i].rect.left + obj[i].rect.width; dx = 0.1; }
				if (Dy>0) { y = obj[i].rect.top - h;  dy = -0.1; }
				if (Dy<0) { y = obj[i].rect.top + obj[i].rect.height;  dy = 0.1; }
			}

		}
}


void Platform::update(float time)
{

	checkCollisionWithMap(dx, dy);//обрабатываем столкновение по ’ y
	x += dx*time;
	y += dy*time;
	sprite.setPosition(x + w / 2, y + h / 2); //задаем позицию спрайта в место его центра

}