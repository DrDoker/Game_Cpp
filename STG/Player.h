#pragma once

#include "Entity.h"
#include "Camera.h"


class Player :public Entity { // ����� ������

public:
	enum { left, right, up, down, jump, stay } state;//��������� ��� ������������ - ��������� �������
	

	Player(Image &image, String Name, Level &lvl, float X, float Y, int W, int H);
	~Player();
	void control(float time);
	void update(float time) override;
	void updatePlayer(float time, Camera &camera); //������� "���������" ������� ������. update - ����������. ��������� � ���� ����� SFML , ���������� ���� �������� ����������, ����� ��������� ��������.
	void checkCollisionWithMap(float Dx, float Dy);//�-��� �������������� � ������

	int GetPlayerScore();
	bool GetOnLadder();
	bool GetNextLvl();
	bool GetFire();

	void SetPlayerScore(int setPlayerScore);
	void SetOnLadder(bool setOnLadder);
	void SetNextLvl(bool setNextLvl);
	void SetFire(bool setFire);

protected:
	int playerScore;
	bool onLadder, nextLvl, fire;
};


