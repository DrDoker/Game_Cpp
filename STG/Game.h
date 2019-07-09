#pragma once

#include "Player.h"
#include "Enemy.h"
#include "Coin.h"
#include "Life.h"
#include "Platform.h"
#include "Fire.h"
#include "Camera.h"

#include <sstream>
#include <list>

#include "menu.h"

void changeLevel(Level &lvl, int &numberLevel) {
	if (numberLevel == 1) { lvl.LoadFromFile("Level1_full.tmx"); } //загрузили в него карту, внутри класса с помощью методов он ее обработает.
	if (numberLevel == 2) { lvl.LoadFromFile("Level2_full.tmx"); }
	if (numberLevel == 3) { lvl.LoadFromFile("Level1_full.tmx"); }
}

bool startGame(RenderWindow &window, int &numberLevel)
{
	Camera camera;
	camera.view.reset(FloatRect(0, 0, 850, 480));//размер "вида" камеры при создании объекта вида камеры. (потом можем менять как хотим) Что то типа инициализации.

	SoundBuffer fireBuffer;//создаём буфер для звука
	fireBuffer.loadFromFile("sound/shoot.wav");//загружаем в него звук
	Sound fireSound(fireBuffer);//создаем звук и загружаем в него звук из буфера

	SoundBuffer coinsBuffer;//создаём буфер для звука
	coinsBuffer.loadFromFile("sound/coins.wav");//загружаем в него звук
	Sound coinsSound(coinsBuffer);//создаем звук и загружаем в него звук из буфера

	SoundBuffer lifeBuffer;//создаём буфер для звука
	lifeBuffer.loadFromFile("sound/life.wav");//загружаем в него звук
	Sound lifeSound(lifeBuffer);//создаем звук и загружаем в него звук из буфера

	Level lvl;//создали экземпляр класса уровень
	changeLevel(lvl, numberLevel);
	double sleep = 0;

	Image bullImage;//изображение для пули
	bullImage.loadFromFile("images/bull.png");//загрузили картинку в объект изображения
	list<Entity*>  bullList;//создаю список, сюда буду кидать объекты.
	list<Entity*>::iterator itB;//итератор чтобы проходить по эл-там списка


	Image heroImage; 
	heroImage.loadFromFile("images/hero1.png");
	Object player = lvl.GetObject("player");//объект игрока на нашей карте.задаем координаты игроку в начале при помощи него
	Player p(heroImage, "Player1", lvl, player.rect.left, player.rect.top, 70, 90);//передаем координаты прямоугольника player из карты в координаты нашего игрока
	

	vector<Object> allObjMap = lvl.GetAllObjects();//все объекты врага на tmx карте хранятся в этом векторе

	Image Enemy1Image;
	Enemy1Image.loadFromFile("images/enem.png");
	Image Enemy2Image;
	Enemy2Image.loadFromFile("images/enem2.png");
	list<Entity*>  enemyList;//создаю список, сюда буду кидать объекты.например врагов.
	list<Entity*>::iterator it;//итератор чтобы проходить по эл-там списка
	

	for (int i = 0; i < allObjMap.size(); i++)//проходимся по элементам этого вектора(а именно по врагам)
	{
		if (allObjMap[i].name == "Enemy1") {
			enemyList.push_back(new Enemy(Enemy1Image, "myEnemy1", lvl, allObjMap[i].rect.left, allObjMap[i].rect.top, 90, 80));//и закидываем в список всех наших врагов с карты
		}
		else if (allObjMap[i].name == "Enemy2") {
			enemyList.push_back(new Enemy(Enemy2Image, "myEnemy2", lvl, allObjMap[i].rect.left, allObjMap[i].rect.top, 100, 90));//и закидываем в список всех наших врагов с карты
		}	
	}
	

	Image coinImage;
	coinImage.loadFromFile("images/coin.png");
	list<Entity*>  coinList;//создаю список, сюда буду кидать объекты
	list<Entity*>::iterator itC;//итератор чтобы проходить по эл-там списка
	vector<Object> coinVect = lvl.GetObjects("coin");//все объекты врага на tmx карте хранятся в этом векторе

	for (int i = 0; i < allObjMap.size(); i++)//проходимся по элементам этого вектора(а именно монеты )
		if (allObjMap[i].name == "coin") {
			coinList.push_back(new Coin(coinImage, "Coin", lvl, allObjMap[i].rect.left, allObjMap[i].rect.top, 32, 32));//и закидываем в список 
		}

	Image lifeImage;
	lifeImage.loadFromFile("images/life.png");
	list<Entity*>  lifeList;//создаю список, сюда буду кидать объекты
	list<Entity*>::iterator itL;//итератор чтобы проходить по эл-там списка

	for (int i = 0; i < allObjMap.size(); i++)//проходимся по элементам этого вектора
		if (allObjMap[i].name == "life") {
			lifeList.push_back(new Life(lifeImage, "Life", lvl, allObjMap[i].rect.left, allObjMap[i].rect.top, 34, 45));//и закидываем в список всех наших врагов с карты
		}

	Image platformImage;
	platformImage.loadFromFile("images/p.png");
	list<Entity*>  platformList;//создаю список, сюда буду кидать объекты
	list<Entity*>::iterator itP;//итератор чтобы проходить по эл-там списка


	for (int i = 0; i < allObjMap.size(); i++)//проходимся по элементам этого вектора
	{
		if (allObjMap[i].name == "platform") {
			platformList.push_back(new Platform(platformImage, "myPlatform", lvl, allObjMap[i].rect.left, allObjMap[i].rect.top, 224, 54, 0.1, 0));//и закидываем в список всех наших врагов с карты
		}
		else if (allObjMap[i].name == "platformV") {
			platformList.push_back(new Platform(platformImage, "myPlatformV", lvl, allObjMap[i].rect.left, allObjMap[i].rect.top, 224, 54, 0, 0.1));//и закидываем в список всех
		}
	}

	Font font;//шрифт 
	font.loadFromFile("font/colo.ttf");//передаем нашему шрифту файл шрифта
	Text text("", font, 25);//создаем объект текст. закидываем в объект текст строку, шрифт, размер шрифта(в пикселях);//сам объект текст (не строка)	
	text.setFillColor(Color::Black);

	Font font2;//шрифт 
	font2.loadFromFile("font/col.ttf");//передаем нашему шрифту файл шрифта
	Text gameOver("", font2, 100);//создаем объект текст. закидываем в объект текст строку, шрифт, размер шрифта(в пикселях);//сам объект текст (не строка)
	gameOver.setFillColor(Color::Black);

	Clock clock;

	while (window.isOpen())
	{
	

		
		float time = clock.getElapsedTime().asMicroseconds();

		clock.restart();
		time = time / 800;

		Event event;
		while (window.pollEvent(event)) {
			if (event.type == sf::Event::Closed) {
				window.close();
			}
				

			if (p.GetFire() == true)
			{
				p.SetFire(false);
				bullList.push_back(new Fire(bullImage, "bullFire", lvl, p.GetX(), p.GetY(), 32, 32, p.GetDx()));
				fireSound.play();
			}

			if (Keyboard::isKeyPressed(Keyboard::Tab)) { return true; }// перезагружаем игру

			if ((p.GetNextLvl() == true) || Keyboard::isKeyPressed(Keyboard::N)) //Переход на след уровень
			{
				if (p.GetPlayerScore() == coinVect.size()) {
					numberLevel++;
					return true;
				}
			}
		}



		if (Keyboard::isKeyPressed(Keyboard::S)) //Переход на след уровень
		{
			numberLevel++;
			return true;
		}


		////////Оживляет Врага
		for (it = enemyList.begin(); it != enemyList.end();)//говорим что проходимся от начала до конца
		{
			Entity *b = *it;//для удобства, чтобы не писать (*it)->
			b->update(time);//вызываем ф-цию update для всех объектов (по сути для тех, кто жив)
			if (b->GetLife() == false) { it = enemyList.erase(it); delete b; b = nullptr;}// если этот объект мертв, то удаляем его
			else it++;//и идем курсором (итератором) к след объекту. так делаем со всеми объектами списка
		}

		//////////Оживляет Монету
		for (itC = coinList.begin(); itC != coinList.end();)//говорим что проходимся от начала до конца
		{
			Entity *c = *itC;//для удобства, чтобы не писать (*it)->
			c->update(time);//вызываем ф-цию update для всех объектов (по сути для тех, кто жив)
			if (c->GetLife() == false) { itC = coinList.erase(itC); delete c; c = nullptr;}// если этот объект мертв, то удаляем его
			else itC++;//и идем курсором (итератором) к след объекту. так делаем со всеми объектами списка
		}

		//////////Оживляет Life
		for (itL = lifeList.begin(); itL != lifeList.end();)//говорим что проходимся от начала до конца
		{
			Entity *l = *itL;//для удобства, чтобы не писать (*it)->
			l->update(time);//вызываем ф-цию update для всех объектов (по сути для тех, кто жив)
			if (l->GetLife() == false) { itL = lifeList.erase(itL); delete l; l = nullptr;}// если этот объект мертв, то удаляем его
			else itL++;//и идем курсором (итератором) к след объекту. так делаем со всеми объектами списка
		}

		//////////Оживляет Platform
		for (itP = platformList.begin(); itP != platformList.end();)//говорим что проходимся от начала до конца
		{
			Entity *pla = *itP;//для удобства, чтобы не писать (*it)->
			pla ->update(time);//вызываем ф-цию update для всех объектов (по сути для тех, кто жив)
			itP++;//и идем курсором (итератором) к след объекту. так делаем со всеми объектами списка
		}

		//////////Оживляет Fire
		for (itB = bullList.begin(); itB != bullList.end();)//говорим что проходимся от начала до конца
		{

			Entity *f = *itB;//для удобства, чтобы не писать (*it)->
			f->update(time);//вызываем ф-цию update для всех объектов (по сути для тех, кто жив)
			if (f->GetLife() == false) { itB = bullList.erase(itB); delete f; f = nullptr;}// если этот объект мертв, то удаляем его
			else itB++;//и идем курсором (итератором) к след объекту. так делаем со всеми объектами списка
			
		}

		p.updatePlayer(time, camera);//оживляем объект p класса Player с помощью времени sfml, передавая время в качестве параметра функции update. благодаря этому персонаж может двигаться

		//////////////////////////// СТОЛКНОВЕНИЕ ПЕРСОНАЖА С ВРАГОМ
		for (it = enemyList.begin(); it != enemyList.end(); it++)//проходимся по эл-там списка
		{
			for (int i = 0; i < allObjMap.size(); i++){
			
				if ((*it)->getRect().intersects(p.getRect()) && !(*it)->getRect().intersects(allObjMap[i].rect)) {
					if ((*it)->name == "myEnemy1") {

						if ((p.GetDy() > 0) && (p.GetOnGround() == false)) { (*it)->SetDx(0); p.SetDy(-0.2); (*it)->SetHealth(0); }//если прыгнули на врага,то даем врагу скорость 0,отпрыгиваем от него чуть вверх,даем ему здоровье 0




						if ((*it)->GetDx() > 0)//если враг идет вправо
						{


							if (p.GetLife() == true) {
								p.SetHealth(p.GetHealth() - 20);
								if (p.GetDx() < 0) { p.SetX((*it)->GetX() + (*it)->GetW() + 80); }//если столкнулись с врагом и игрок идет влево то выталкиваем игрока
								if (p.GetDx() > 0) { p.SetX((*it)->GetX() - p.GetW() - 80); }//если столкнулись с врагом и игрок идет вправо то выталкиваем игрока
								if (p.GetDx() == 0) { p.SetX((*it)->GetX() + (*it)->GetW() + 60); }//если столкнулись с врагом и игрок идет вправо то выталкиваем игрока
							}


						}
						if ((*it)->GetDx() < 0)//если враг идет влево
						{

							if (p.GetLife() == true) {
								p.SetHealth(p.GetHealth() - 20);

								if (p.GetDx() < 0) { p.SetX((*it)->GetX() + (*it)->GetW() + 80); }//если столкнулись с врагом и игрок идет влево то выталкиваем игрока
								if (p.GetDx() > 0) { p.SetX((*it)->GetX() - p.GetW() - 80); }//если столкнулись с врагом и игрок идет вправо то выталкиваем игрока
								if (p.GetDx() == 0) { p.SetX((*it)->GetX() - p.GetW() - 60); }
							}
						}
					}

					if ((*it)->name == "myEnemy2") {

													//if ((p.dy>0) && (p.onGround == false)) { (*it)->dx = 0; p.dy = -0.2; (*it)->health = 0; }//если прыгнули на врага,то даем врагу скорость 0,отпрыгиваем от него чуть вверх,даем ему здоровье 0


						if ((*it)->GetDx() > 0)//если враг идет вправо
						{

							if (p.GetLife() == true) {
								p.SetHealth(p.GetHealth() - 40);
								if (p.GetDx() < 0) { p.SetX((*it)->GetX() + (*it)->GetW() + 80); }//если столкнулись с врагом и игрок идет влево то выталкиваем игрока
								if (p.GetDx() > 0) { p.SetX((*it)->GetX() - p.GetW() - 80); }//если столкнулись с врагом и игрок идет вправо то выталкиваем игрока
								if (p.GetDx() == 0) { p.SetX((*it)->GetX() + (*it)->GetW() + 60); }
							}


						}
						if ((*it)->GetDx() < 0)//если враг идет влево
						{

							if (p.GetLife() == true) {
								p.SetHealth(p.GetHealth() - 40);

								if (p.GetDx() < 0) { p.SetX((*it)->GetX() + (*it)->GetW() + 80); }//если столкнулись с врагом и игрок идет влево то выталкиваем игрока
								if (p.GetDx() > 0) { p.SetX((*it)->GetX() - p.GetW() - 80); }//если столкнулись с врагом и игрок идет вправо то выталкиваем игрока
								if (p.GetDx() == 0) { p.SetX((*it)->GetX() - p.GetW() - 60); }
							}


						}
					}

				}
			}
			
		}

	
		////////////////////////////////////////////////// СТОЛКНОВЕНИЕ ПЕРСОНАЖА С МОНЕТОЙ
		for (itC = coinList.begin(); itC != coinList.end(); itC++)//проходимся по эл-там списка
		{
			if ((*itC)->getRect().intersects(p.getRect()))//если прямоугольник спрайта объекта пересекается с игроком
			{
					p.SetPlayerScore(p.GetPlayerScore() + 1);
					(*itC)->SetLife(false); 
					coinsSound.play();
			}
		}

		////////////////////////////////////////////////// СТОЛКНОВЕНИЕ ПЕРСОНАЖА С ЖИЗНЯМИ
		for (itL = lifeList.begin(); itL != lifeList.end(); itL++)//проходимся по эл-там списка
		{
			if ((*itL)->getRect().intersects(p.getRect()))//если прямоугольник спрайта объекта пересекается с игроком
			{
				p.SetHealth(p.GetHealth() + 40);
				(*itL)->SetLife(false);
				lifeSound.play();
			}
		}


		////////////////////////////////////////////////// СТОЛКНОВЕНИЕ ПЕРСОНАЖА С PLATFORM
		for (itP = platformList.begin(); itP != platformList.end(); itP++)//проходимся по эл-там списка
		{
			if ((*itP)->getRect().intersects(p.getRect()))//если прямоугольник спрайта объекта пересекается с игроком
			{
				if ((p.GetDy() > 0) && (p.GetY() < (*itP)->GetY())) {
					p.SetX(p.GetX() + ((*itP)->GetDx()*time));
					p.SetY((*itP)->GetY() - p.GetH() + 1);
					p.SetDy(0);
					p.SetOnGround(true);
				}

			}
		}

		////////////////////////////////////////////////// СТОЛКНОВЕНИЕ ПУЛИ С ВРАГОМ
		for (itB = bullList.begin(); itB != bullList.end(); itB++)//проходимся по эл-там списка
		{
			for (it = enemyList.begin(); it != enemyList.end(); it++)//проходимся по эл-там списка
			{
				if ((*itB)->getRect().intersects((*it)->getRect()))//если прямоугольник спрайта объекта пересекается с игроком
				{
					(*itB)->SetLife(false);

					if ((*it)->name == "myEnemy1") {
						(*it)->SetHealth((*it)->GetHealth() - 8);
					}
					else if ((*it)->name == "myEnemy2") {
						(*it)->SetHealth((*it)->GetHealth() - 20);
					}
				}
			}
		}

		///////Действия при смерте игрока
		if (p.GetLife() == false) {

			gameOver.setString("Game over");//задает строку тексту
			gameOver.setPosition(camera.view.getCenter().x - 225, camera.view.getCenter().y - 130);//задаем позицию текста, центр камеры

			sleep += time;
			if (3000 < sleep) {
				return true;
			}
		}
				

		window.setView(camera.view);//"оживляем" камеру в окне sfml
		window.clear();

		lvl.Draw(window);//рисуем новую карту


		ostringstream playerScoreString, playerScoreHealth, playerScoreAll;    // объявили переменную
		playerScoreString << p.GetPlayerScore();		//занесли в нее число очков, то есть формируем строку
		playerScoreHealth << p.GetHealth();
		playerScoreAll << coinVect.size();
		text.setString("Health: " + playerScoreHealth.str() + "    Coins: " + playerScoreString.str() + " | " + playerScoreAll.str());//задает строку тексту
		text.setPosition(camera.view.getCenter().x - 400, camera.view.getCenter().y - 230);//задаем позицию текста, центр камеры
		
		window.draw(p.sprite);//рисуем спрайт объекта p класса player

		for (it = enemyList.begin(); it != enemyList.end(); it++) {
			window.draw((*it)->sprite); //рисуем entities объекты (сейчас это только враги)
		}

		for (itC = coinList.begin(); itC != coinList.end(); itC++) {
			window.draw((*itC)->sprite); //рисуем coin объекты 
		}

		for (itL = lifeList.begin(); itL != lifeList.end(); itL++) {
			window.draw((*itL)->sprite); //рисуем life объекты 
		}

		for (itP = platformList.begin(); itP != platformList.end(); itP++) {
			window.draw((*itP)->sprite); //рисуем Platform объекты 
		}

		for (itB = bullList.begin(); itB != bullList.end(); itB++) {
			window.draw((*itB)->sprite); //рисуем bull объекты 
		}

		window.draw(gameOver);//рисую этот текст
		window.draw(text);//рисую этот текст

		window.display();

	}



	for (it = enemyList.begin(); it != enemyList.end(); it++) {
		delete (*it);
		(*it) = nullptr;
	}

	for (itC = coinList.begin(); itC != coinList.end(); itC++) {
		delete (*itC);
		(*itC) = nullptr;
	}

	for (itL = lifeList.begin(); itL != lifeList.end(); itL++) {
		delete (*itL);
		(*itL) = nullptr;
	}

	for (itP = platformList.begin(); itP != platformList.end(); itP++) {
		delete (*itP);
		(*itP) = nullptr;
	}

	for (itB = bullList.begin(); itB != bullList.end(); itB++) {
		delete (*itB);	
		(*itB) = nullptr;
	}


}


void gameRunning(RenderWindow & window, int & numberLevel) {//ф-ция перезагружает игру , если это необходимо
	if (startGame(window, numberLevel)) { 
		gameRunning(window, numberLevel); 
	}//принимает с какого уровня начать игру
}