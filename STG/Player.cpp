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
			sprite.setTextureRect(IntRect(70 * (1 + int(CurrentFrame)) + 70, 90, -70, 90)); //����� ������ p ������ player ������ ������, ����� �������� (��������� �������� �����)

		}

		if (Keyboard::isKeyPressed(Keyboard::Right)) {
			state = right;
			speed = 0.135;//����������� ������, �� ����
			CurrentFrame += 0.0055*time;
			if (CurrentFrame > 6)
				CurrentFrame -= 6;
			sprite.setTextureRect(IntRect(70 * (1 + int(CurrentFrame)), 90, 70, 90));  //����� ������ p ������ player ������ ������, ����� �������� (��������� �������� �����)

		}


		if (Keyboard::isKeyPressed(Keyboard::Space) && (onGround)) {
			state = jump;
			dy = -0.65;
			onGround = false;
			CurrentFrame += 0.005*time;
			if (CurrentFrame > 6)
				CurrentFrame -= 6;
			sprite.setTextureRect(IntRect(70 * (1 + int(CurrentFrame)), 90, 70, 90));  //����� ������ p ������ player ������ ������, ����� �������� (��������� �������� �����)
		}

		if (Keyboard::isKeyPressed(Keyboard::Up) && (onLadder == true)) {
			state = up;
			CurrentFrame += 0.005*time; //������ ��� ����������� �� "������". ���������� ������� �� ���� �������� ������������ ������� � ��������. ������� 0.005 ����� �������� �������� ��������
			if (CurrentFrame > 8)
				CurrentFrame -= 8; //���������� �� ������ � ������� �� ������ ������������. ���� ������ � �������� ����� - ������������ �����.
			sprite.setTextureRect(IntRect(70 * int(CurrentFrame) + 70, 0, -70, 90)); //���������� �� ����������� �. ���������� 96,96*2,96*3 � ����� 96
		}

		if (Keyboard::isKeyPressed(Keyboard::Down) && (onLadder == true)) {
			state = down;
			CurrentFrame += 0.005*time; //������ ��� ����������� �� "������". ���������� ������� �� ���� �������� ������������ ������� � ��������. ������� 0.005 ����� �������� �������� ��������
			if (CurrentFrame > 8)
				CurrentFrame -= 8; //���������� �� ������ � ������� �� ������ ������������. ���� ������ � �������� ����� - ������������ �����.
			sprite.setTextureRect(IntRect(70 * int(CurrentFrame) + 70, 0, -70, 90)); //���������� �� ����������� �. ���������� 96,96*2,96*3 � ����� 96
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

void Player::updatePlayer(float time, Camera &camera) //������� "���������" ������� ������. update - ����������. ��������� � ���� ����� SFML , ���������� ���� �������� ����������, ����� ��������� ��������.
{

	control(time);
	camera.setPlayerCoordinateForView(x, y);

	

	switch (state)//��������� ��������� � ����������� �� �����������. (������ ����� ������������� �����������)
	{
	case right: dx = speed; break;//�� ���� ������ ������������� ��������, �� ������ ��������. ��������, ��� �������� ���� ������ ������
	case left: dx = -speed; break;//�� ���� ������ ������������� ��������, �� ������ ��������. ����������, ��� �������� ���� ������ �����
	case up:  dy = 0; break;//�� ���� ������ ������� ��������, �� ������ �������������. ����������, ��� �������� ���� ������ ����
	case down: dy = 0; break;//�� ���� ������ ������� ��������, �� ������ �������������. ����������, ��� �������� ���� ������ �����
	case jump: break;
	case stay: break;

	}

	x += dx*time;//�� �������� �� �������� �����. ���� ��������� �� ����� �������� �������� ��������� � ��� ��������� ��������
	checkCollisionWithMap(dx, 0);
	y += dy*time;//���������� �� ������
	checkCollisionWithMap(0, dy);


	dy += 0.0015*time;


	speed = 0;
	sprite.setPosition(x + w / 2, y + h / 2); //������� ������ � ������� x y , ����������. ���������� ������� � ���� �������, ����� �� ��� ������ ����� �� �����.	

	if (health <= 0) {
		life = false;
		sprite.setTextureRect(IntRect(490, 90, 70, 90));
		health = 0;
	}

	if (health > 100) {
		health = 100;
	}
}


void Player::checkCollisionWithMap(float Dx, float Dy)//�-��� �������������� � ������
{

	for (int i = 0; i < obj.size(); i++)//���������� �� ��������
		if (getRect().intersects(obj[i].rect))//��������� ����������� ������ � ��������
		{
			if (obj[i].name == "solid")//���� ��������� �����������
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
						onLadder = false; //����� �������� ����� � ��� ������ �� ������� 
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

