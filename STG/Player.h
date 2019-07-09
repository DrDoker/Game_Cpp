#pragma once

#include "Entity.h"
#include "Camera.h"


class Player :public Entity { // класс Игрока

public:
	enum { left, right, up, down, jump, stay } state;//добавляем тип перечисления - состояние объекта
	

	Player(Image &image, String Name, Level &lvl, float X, float Y, int W, int H);
	~Player();
	void control(float time);
	void update(float time) override;
	void updatePlayer(float time, Camera &camera); //функция "оживления" объекта класса. update - обновление. принимает в себя время SFML , вследствие чего работает бесконечно, давая персонажу движение.
	void checkCollisionWithMap(float Dx, float Dy);//ф-ция взаимодействия с картой

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


