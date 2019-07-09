#include "Game.h"


int main()
{
	RenderWindow window(VideoMode(640, 480), "Doker Game");
	window.setFramerateLimit(60);
	menu(window);
	Vector2u gameSize(850, 480);
	window.setSize(gameSize);
	int numberLevel = 1;//сначала 1-ый уровень
	gameRunning(window, numberLevel);
	return 0;
}