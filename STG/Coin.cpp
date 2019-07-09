#pragma once

#include "Coin.h"

Coin::Coin(Image &image, String Name, Level &lvl, float X, float Y, int W, int H) :Entity(image, Name, lvl, X, Y, W, H) {

	if (name == "Coin") {
		sprite.setTextureRect(IntRect(0, 0, w, h));
	}
}

Coin::~Coin() {

}

void Coin::update(float time)
{
	if (name == "Coin") {//для персонажа с таким именем логика будет такой

		sprite.setPosition(x + w / 2, y + h / 2); //задаем позицию спрайта в место его центра

		CurrentFrame += 0.0045*time;
		if (CurrentFrame > 6)
			CurrentFrame -= 6;
		sprite.setTextureRect(IntRect(32 * int(CurrentFrame), 0, 32, 32));


		if (health <= 0) {
			life = false;
		}
	}

}