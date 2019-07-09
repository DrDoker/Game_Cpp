#pragma once

#include "Player.h"

int Player::GetPlayerScore() { return playerScore; }
bool Player::GetOnLadder() { return onLadder; }
bool Player::GetNextLvl() { return nextLvl; }
bool Player::GetFire() { return fire; }

void Player::SetPlayerScore(int setPlayerScore) { playerScore = setPlayerScore; }
void Player::SetOnLadder(bool setOnLadder) { onLadder = setOnLadder; }
void Player::SetNextLvl(bool setNextLvl) { nextLvl = setNextLvl; }
void Player::SetFire(bool setFire) { fire = setFire; }

Player::Player(Image &image, String Name, Level &lvl, float X, float Y, int W, int H) :Entity(image, Name, lvl, X, Y, W, H) {
	
	playerScore = 0;
	CurrentFrame = 0;
	state = stay;


	onLadder = false;
	nextLvl = false;
	fire = false;

	if (name == "Player1") {
		sprite.setTextureRect(IntRect(0, 90, w, h));
	}
}

Player::~Player() {

}


void Player::control(float time) {

	sprite.setTextureRect(IntRect(0, 90, 70, 90));

	if (life == true) {
		if (Keyboard::isKeyPressed(Keyboard::Left)) {
			state = left;
			speed = 0.135;
			CurrentFrame += 0.0055*time;
			if (CurrentFrame > 6)
				CurrentFrame -= 6;
			sprite.setTextureRect(IntRect(70 * (1 + int(CurrentFrame)) + 70, 90, -70, 90)); //через объект p класса player меняем спрайт, делая анимацию (используя оператор точку)

		}

		if (Keyboard::isKeyPressed(Keyboard::Right)) {
			state = right;
			speed = 0.135;//направление вправо, см выше
			CurrentFrame += 0.0055*time;
			if (CurrentFrame > 6)
				CurrentFrame -= 6;
			sprite.setTextureRect(IntRect(70 * (1 + int(CurrentFrame)), 90, 70, 90));  //через объект p класса player меняем спрайт, делая анимацию (используя оператор точку)

		}


		if (Keyboard::isKeyPressed(Keyboard::Space) && (onGround)) {
			state = jump;
			dy = -0.65;
			onGround = false;
			CurrentFrame += 0.005*time;
			if (CurrentFrame > 6)
				CurrentFrame -= 6;
			sprite.setTextureRect(IntRect(70 * (1 + int(CurrentFrame)), 90, 70, 90));  //через объект p класса player меняем спрайт, делая анимацию (используя оператор точку)
		}

		if (Keyboard::isKeyPressed(Keyboard::Up) && (onLadder == true)) {
			state = up;
			CurrentFrame += 0.005*time; //служит для прохождения по "кадрам". переменная доходит до трех суммируя произведение времени и скорости. изменив 0.005 можно изменить скорость анимации
			if (CurrentFrame > 8)
				CurrentFrame -= 8; //проходимся по кадрам с первого по третий включительно. если пришли к третьему кадру - откидываемся назад.
			sprite.setTextureRect(IntRect(70 * int(CurrentFrame) + 70, 0, -70, 90)); //проходимся по координатам Х. получается 96,96*2,96*3 и опять 96
		}

		if (Keyboard::isKeyPressed(Keyboard::Down) && (onLadder == true)) {
			state = down;
			CurrentFrame += 0.005*time; //служит для прохождения по "кадрам". переменная доходит до трех суммируя произведение времени и скорости. изменив 0.005 можно изменить скорость анимации
			if (CurrentFrame > 8)
				CurrentFrame -= 8; //проходимся по кадрам с первого по третий включительно. если пришли к третьему кадру - откидываемся назад.
			sprite.setTextureRect(IntRect(70 * int(CurrentFrame) + 70, 0, -70, 90)); //проходимся по координатам Х. получается 96,96*2,96*3 и опять 96
		}

		if (Keyboard::isKeyPressed(Keyboard::Z)) {
			fire = true;
			if (dx == 0) {
				sprite.setTextureRect(IntRect(70, 90, 70, 90));
			}

		}
	}

}

void Player::update(float time) {}

void Player::updatePlayer(float time, Camera &camera) //функция "оживления" объекта класса. update - обновление. принимает в себя время SFML , вследствие чего работает бесконечно, давая персонажу движение.
{

	control(time);
	camera.setPlayerCoordinateForView(x, y);

	

	switch (state)//реализуем поведение в зависимости от направления. (каждая цифра соответствует направлению)
	{
	case right: dx = speed; break;//по иксу задаем положительную скорость, по игреку зануляем. получаем, что персонаж идет только вправо
	case left: dx = -speed; break;//по иксу задаем отрицательную скорость, по игреку зануляем. получается, что персонаж идет только влево
	case up:  dy = 0; break;//по иксу задаем нулевое значение, по игреку положительное. получается, что персонаж идет только вниз
	case down: dy = 0; break;//по иксу задаем нулевое значение, по игреку отрицательное. получается, что персонаж идет только вверх
	case jump: break;
	case stay: break;

	}

	x += dx*time;//то движение из прошлого урока. наше ускорение на время получаем смещение координат и как следствие движение
	checkCollisionWithMap(dx, 0);
	y += dy*time;//аналогично по игреку
	checkCollisionWithMap(0, dy);


	dy += 0.0015*time;


	speed = 0;
	sprite.setPosition(x + w / 2, y + h / 2); //выводим спрайт в позицию x y , посередине. бесконечно выводим в этой функции, иначе бы наш спрайт стоял на месте.	

	if (health <= 0) {
		life = false;
		sprite.setTextureRect(IntRect(490, 90, 70, 90));
		health = 0;
	}

	if (health > 100) {
		health = 100;
	}
}


void Player::checkCollisionWithMap(float Dx, float Dy)//ф-ция взаимодействия с картой
{

	for (int i = 0; i < obj.size(); i++)//проходимся по объектам
		if (getRect().intersects(obj[i].rect))//проверяем пересечение игрока с объектом
		{
			if (obj[i].name == "solid")//если встретили препятствие
			{
				if (Dy>0) { y = obj[i].rect.top - h;  dy = 0; onGround = true; }
				if (Dy<0) { y = obj[i].rect.top + obj[i].rect.height;   dy = 0; }
				if (Dx>0) { x = obj[i].rect.left - w; }
				if (Dx<0) { x = obj[i].rect.left + obj[i].rect.width; }
			}


			if (obj[i].name == "lesn")
			{
				if (((obj[i].rect.left) < (x + w / 2)) && ((x + w / 2) < (obj[i].rect.left + obj[i].rect.width))) {


					if ((Keyboard::isKeyPressed(Keyboard::Up)))
					{
						dx = 0;
						dy = -0.2; onLadder = true;
					}
					else if ((Keyboard::isKeyPressed(Keyboard::Down)))
					{
						dy = 0;
						dy = 0.2; onLadder = true;
					}
					else {
						onLadder = false; //можно нажимать вверх и низ только на леснице 
					}

				}
			}

			if (obj[i].name == "nextLvl")
			{
				nextLvl = true;
			}

			if (obj[i].name == "fire")
			{
				life = false;
				health = 0;
			}
		}


}

