#include <SFML/Graphics.hpp> 
#include <SFML/Audio.hpp>
using namespace sf;


void  menu(RenderWindow & window) {
	Texture menuTexture1, menuTexture2, menuTexture3, aboutTexture, menuBackground;
	menuTexture1.loadFromFile("images/1.png");	
	menuTexture2.loadFromFile("images/2.png");
	menuTexture3.loadFromFile("images/3.png");
	aboutTexture.loadFromFile("images/about.jpg");
	menuBackground.loadFromFile("images/menuBeg2.png");
	Sprite menu1(menuTexture1), menu2(menuTexture2), menu3(menuTexture3), about(aboutTexture), menuBg(menuBackground);
	bool isMenu = 1;
	int menuNum = 0;
	menu1.setPosition(40, 160);
	menu2.setPosition(24, 368);
	menu3.setPosition(40, 411);
	menuBg.setPosition(0, 0);

	//////////////////////////////МЕНЮ///////////////////
	while (isMenu)
	{
		menu1.setColor(Color::Black);
		menu2.setColor(Color::Black);
		menu3.setColor(Color::Black);
		menuNum = 0;
	

		if (IntRect(40, 160, 217, 63).contains(Mouse::getPosition(window))) { menu1.setColor(Color(158,201,51)); menuNum = 1; }
		if (IntRect(24, 368, 105, 28).contains(Mouse::getPosition(window))) { menu2.setColor(Color(158,201,51)); menuNum = 2; }
		if (IntRect(40, 411, 65, 26).contains(Mouse::getPosition(window))) { menu3.setColor(Color(158, 201, 51)); menuNum = 3; }

		if (Mouse::isButtonPressed(Mouse::Left))
		{
			if (menuNum == 1) {
				isMenu = false; 
			}//если нажали первую кнопку, то выходим из меню 
			if (menuNum == 2) { window.draw(about); window.display(); while (!Keyboard::isKeyPressed(Keyboard::Escape)); }
			if (menuNum == 3) { window.close(); isMenu = false; }

		}

		window.draw(menuBg);
		window.draw(menu1);
		window.draw(menu2);
		window.draw(menu3);

		window.display();

		
	}
	////////////////////////////////////////////////////
}