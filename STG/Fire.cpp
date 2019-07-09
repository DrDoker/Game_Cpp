#pragma once

#include "Fire.h"

Fire::Fire(Image &image, String Name, Level &lvl, float X, float Y, int W, int H, float pDx) :Entity(image, Name, lvl, X, Y, W, H) {

	dx = 0.45;
	life = true;
	playerDx = pDx;
}

Fire::~Fire() {

}

void Fire::update(float time)
{
	if (playerDx > 0) {
		dx = 0.45;
		dy = 0;
	}
	else if (playerDx < 0) {
		dx = -0.45;
		dy = 0;
	}
	else
	{
		dx = 0.45;
		dy = 0;
	}


	checkCollisionWithMap(dx, dy);//������������ ������������ �� �
	x += dx*time;//���� �������� ���� �� �
	y += dy*time;//�� �


	sprite.setPosition(x + (w / 2) + 30, y + (h / 2) + 40);

}

void Fire::checkCollisionWithMap(float Dx, float Dy)//� ��� �������� ������������ � ������
{

	for (int i = 0; i < obj.size(); i++)//���������� �� ��������
		if (getRect().intersects(obj[i].rect))//��������� ����������� ������ � ��������
		{
			if (obj[i].name == "solid")//���� ��������� �����������
			{
				life = false;// �� ���� �������
			}

		}
}