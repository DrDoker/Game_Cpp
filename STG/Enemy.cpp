#pragma once

#include "Enemy.h"

Enemy::Enemy(Image &image, String Name, Level &lvl, float X, float Y, int W, int H) :Entity(image, Name, lvl, X, Y, W, H) {

	if (name == "myEnemy1") {
		health = 100;
		sprite.setTextureRect(IntRect(0, 0, w, h));
		dx = 0.1;//���� ��������.���� ������ ������ ���������
	}
	else if (name == "myEnemy2") {
		health = 150;
		sprite.setTextureRect(IntRect(0, 0, w, h));
		dx = -0.09;//���� ��������.���� ������ ������ ���������
	}
}

Enemy::~Enemy() {

}

void Enemy::checkCollisionWithMap(float Dx, float Dy)//� ��� �������� ������������ � ������
{

	for (int i = 0; i < obj.size(); i++)//���������� �� ��������
		if (getRect().intersects(obj[i].rect))//��������� ����������� ������ � ��������
		{
			if (obj[i].name == "solidEnem")//���� ��������� �����������
			{
				if (Dy>0) { y = obj[i].rect.top - h;  dy = 0; onGround = true; }
				if (Dy<0) { y = obj[i].rect.top + obj[i].rect.height;   dy = 0; }
				if (Dx>0) { x = obj[i].rect.left - w;  dx = -0.1; sprite.scale(-1, 1); }
				if (Dx<0) { x = obj[i].rect.left + obj[i].rect.width; dx = 0.1; sprite.scale(-1, 1); }
			}

		}
}


void Enemy::update(float time)
{
	if (name == "myEnemy1") {//��� ��������� � ����� ������ ������ ����� �����

		moveTimer += time; if (moveTimer>10000) { dx *= -1; sprite.scale(-1, 1); moveTimer = 0; }//������ ����������� �������� ������ 10 ���
		checkCollisionWithMap(dx, 0);//������������ ������������ �� �
		x += dx*time;
		sprite.setPosition(x + w / 2, y + h / 2); //������ ������� ������� � ����� ��� ������

		CurrentFrame += 0.005*time;
		if (CurrentFrame > 5)
			CurrentFrame -= 5;
		sprite.setTextureRect(IntRect(90 * int(CurrentFrame), 0, 90, 80));

		if (health <= 0) {
			life = false;
		}
	}

	if (name == "myEnemy2") {//��� ��������� � ����� ������ ������ ����� �����

		moveTimer += time; if (moveTimer>10000) { dx *= -1; sprite.scale(-1, 1); moveTimer = 0; }//������ ����������� �������� ������ 10 ���
		checkCollisionWithMap(dx, 0);//������������ ������������ �� �
		x += dx*time;
		sprite.setPosition(x + w / 2, y + h / 2); //������ ������� ������� � ����� ��� ������


		CurrentFrame += 0.0045*time;
		if (CurrentFrame > 6)
			CurrentFrame -= 6;
		sprite.setTextureRect(IntRect(100 * int(CurrentFrame), 0, 100, 90));

		if (health <= 0) {
			life = false;
		}
	}
}