#include "Game.h"


int main()
{
	RenderWindow window(VideoMode(640, 480), "Doker Game");
	window.setFramerateLimit(60);
	menu(window);
	Vector2u gameSize(850, 480);
	window.setSize(gameSize);
	int numberLevel = 1;//������� 1-�� �������
	gameRunning(window, numberLevel);
	return 0;
}