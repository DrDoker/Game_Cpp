#pragma once

#include "Life.h"

Life::Life(Image &image, String Name, Level &lvl, float X, float Y, int W, int H) :Entity(image, Name, lvl, X, Y, W, H) {

	if (name == "Life") {
		sprite.setTextureRect(IntRect(0, 0, w, h));
	}
}

Life::~Life() {

}

void Life::update(float time)
{
	if (name == "Life") {//для персонажа с таким именем логика будет такой

		sprite.setPosition(x + w / 2, y + h / 2); //задаем позицию спрайта в место его центра

		if (health <= 0) {
			life = false;
		}
	}

}