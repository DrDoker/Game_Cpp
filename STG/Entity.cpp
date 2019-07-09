#pragma once

#include "Entity.h"

float Entity::GetX() { return x; }
float Entity::GetY() { return y; }
float Entity::GetDx() { return dx; }
float Entity::GetDy() { return dy; }
int Entity::GetW() { return w; }
int Entity::GetH() { return h; }
int Entity::GetHealth() { return health; }
bool Entity::GetLife() { return life; };
bool Entity::GetOnGround() { return onGround; };

void Entity::SetX(float setX) { x = setX; }
void Entity::SetY(float setY) { y = setY; }
void Entity::SetDx(float setDx) { dx = setDx; }
void Entity::SetDy(float setDy) { dy = setDy; }
void Entity::SetW(int setW) { w = setW; }
void Entity::SetH(int setH) { h = setH; }
void Entity::SetHealth(int setHealth) { health = setHealth; }
void Entity::SetLife(bool setLife) { life = setLife; }
void Entity::SetOnGround(bool setOnGround) { onGround = setOnGround; }

Entity::Entity(Image &image, String Name, Level &lvl, float X, float Y, int W, int H) {
	x = X;
	y = Y;
	w = W;
	h = H;
	name = Name;
	moveTimer = 0;
	speed = 0;
	health = 100;
	dx = 0;
	dy = 0;
	life = true;
	onGround = false;
	isMove = false;
	texture.loadFromImage(image);
	sprite.setTexture(texture);
	sprite.setOrigin(w / 2, h / 2);

	obj = lvl.GetAllObjects();//инициализируем.получаем все объекты для взаимодействия персонажа с картой
}


Entity::~Entity() {

}

FloatRect Entity::getRect() {//ф-ция получения прямоугольника. его коорд,размеры (шир,высот).
	return FloatRect(x, y, w, h);//эта ф-ция нужна для проверки столкновений 
}