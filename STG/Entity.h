#pragma once

#include "level.h"

class Entity
{

	public:
		vector<Object> obj;//вектор объектов карты	
		Texture texture;
		Sprite sprite;
		String name;//враги могут быть разные, мы не будем делать другой класс для различающегося врага.всего лишь различим врагов по имени и дадим каждому свое действие в update в зависимости от имени

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
		float dx, dy, x, y, speed, moveTimer, CurrentFrame;//добавили переменную таймер для будущих целей
		int w, h, health;
		bool life, isMove, onGround;

};

