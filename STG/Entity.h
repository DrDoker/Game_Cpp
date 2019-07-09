#pragma once

#include "level.h"

class Entity
{

	public:
		vector<Object> obj;//������ �������� �����	
		Texture texture;
		Sprite sprite;
		String name;//����� ����� ���� ������, �� �� ����� ������ ������ ����� ��� �������������� �����.����� ���� �������� ������ �� ����� � ����� ������� ���� �������� � update � ����������� �� �����

		Entity(Image &image, String Name, Level &lvl, float X, float Y, int W, int H);
		~Entity();
		FloatRect getRect();

		virtual void update(float time) = 0;

		float GetX();
		void SetX(float setX);
		float GetY();
		void SetY(float setY);

		float GetDx();
		void SetDx(float setDx);
		float GetDy();
		void SetDy(float setDy);

		int GetW();
		void SetW(int setW);

		int GetH();
		void SetH(int setH);

		int GetHealth();
		void SetHealth(int setHealth);

		bool GetLife();
		void SetLife(bool setLife);

		bool GetOnGround();
		void SetOnGround(bool setOnGround);

	protected:
		float dx, dy, x, y, speed, moveTimer, CurrentFrame;//�������� ���������� ������ ��� ������� �����
		int w, h, health;
		bool life, isMove, onGround;

};

