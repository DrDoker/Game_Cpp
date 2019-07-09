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
	if (numberLevel == 1) { lvl.LoadFromFile("Level1_full.tmx"); } //��������� � ���� �����, ������ ������ � ������� ������� �� �� ����������.
	if (numberLevel == 2) { lvl.LoadFromFile("Level2_full.tmx"); }
	if (numberLevel == 3) { lvl.LoadFromFile("Level1_full.tmx"); }
}

bool startGame(RenderWindow &window, int &numberLevel)
{
	Camera camera;
	camera.view.reset(FloatRect(0, 0, 850, 480));//������ "����" ������ ��� �������� ������� ���� ������. (����� ����� ������ ��� �����) ��� �� ���� �������������.

	SoundBuffer fireBuffer;//������ ����� ��� �����
	fireBuffer.loadFromFile("sound/shoot.wav");//��������� � ���� ����
	Sound fireSound(fireBuffer);//������� ���� � ��������� � ���� ���� �� ������

	SoundBuffer coinsBuffer;//������ ����� ��� �����
	coinsBuffer.loadFromFile("sound/coins.wav");//��������� � ���� ����
	Sound coinsSound(coinsBuffer);//������� ���� � ��������� � ���� ���� �� ������

	SoundBuffer lifeBuffer;//������ ����� ��� �����
	lifeBuffer.loadFromFile("sound/life.wav");//��������� � ���� ����
	Sound lifeSound(lifeBuffer);//������� ���� � ��������� � ���� ���� �� ������

	Level lvl;//������� ��������� ������ �������
	changeLevel(lvl, numberLevel);
	double sleep = 0;

	Image bullImage;//����������� ��� ����
	bullImage.loadFromFile("images/bull.png");//��������� �������� � ������ �����������
	list<Entity*>  bullList;//������ ������, ���� ���� ������ �������.
	list<Entity*>::iterator itB;//�������� ����� ��������� �� ��-��� ������


	Image heroImage; 
	heroImage.loadFromFile("images/hero1.png");
	Object player = lvl.GetObject("player");//������ ������ �� ����� �����.������ ���������� ������ � ������ ��� ������ ����
	Player p(heroImage, "Player1", lvl, player.rect.left, player.rect.top, 70, 90);//�������� ���������� �������������� player �� ����� � ���������� ������ ������
	

	vector<Object> allObjMap = lvl.GetAllObjects();//��� ������� ����� �� tmx ����� �������� � ���� �������

	Image Enemy1Image;
	Enemy1Image.loadFromFile("images/enem.png");
	Image Enemy2Image;
	Enemy2Image.loadFromFile("images/enem2.png");
	list<Entity*>  enemyList;//������ ������, ���� ���� ������ �������.�������� ������.
	list<Entity*>::iterator it;//�������� ����� ��������� �� ��-��� ������
	

	for (int i = 0; i < allObjMap.size(); i++)//���������� �� ��������� ����� �������(� ������ �� ������)
	{
		if (allObjMap[i].name == "Enemy1") {
			enemyList.push_back(new Enemy(Enemy1Image, "myEnemy1", lvl, allObjMap[i].rect.left, allObjMap[i].rect.top, 90, 80));//� ���������� � ������ ���� ����� ������ � �����
		}
		else if (allObjMap[i].name == "Enemy2") {
			enemyList.push_back(new Enemy(Enemy2Image, "myEnemy2", lvl, allObjMap[i].rect.left, allObjMap[i].rect.top, 100, 90));//� ���������� � ������ ���� ����� ������ � �����
		}	
	}
	

	Image coinImage;
	coinImage.loadFromFile("images/coin.png");
	list<Entity*>  coinList;//������ ������, ���� ���� ������ �������
	list<Entity*>::iterator itC;//�������� ����� ��������� �� ��-��� ������
	vector<Object> coinVect = lvl.GetObjects("coin");//��� ������� ����� �� tmx ����� �������� � ���� �������

	for (int i = 0; i < allObjMap.size(); i++)//���������� �� ��������� ����� �������(� ������ ������ )
		if (allObjMap[i].name == "coin") {
			coinList.push_back(new Coin(coinImage, "Coin", lvl, allObjMap[i].rect.left, allObjMap[i].rect.top, 32, 32));//� ���������� � ������ 
		}

	Image lifeImage;
	lifeImage.loadFromFile("images/life.png");
	list<Entity*>  lifeList;//������ ������, ���� ���� ������ �������
	list<Entity*>::iterator itL;//�������� ����� ��������� �� ��-��� ������

	for (int i = 0; i < allObjMap.size(); i++)//���������� �� ��������� ����� �������
		if (allObjMap[i].name == "life") {
			lifeList.push_back(new Life(lifeImage, "Life", lvl, allObjMap[i].rect.left, allObjMap[i].rect.top, 34, 45));//� ���������� � ������ ���� ����� ������ � �����
		}

	Image platformImage;
	platformImage.loadFromFile("images/p.png");
	list<Entity*>  platformList;//������ ������, ���� ���� ������ �������
	list<Entity*>::iterator itP;//�������� ����� ��������� �� ��-��� ������


	for (int i = 0; i < allObjMap.size(); i++)//���������� �� ��������� ����� �������
	{
		if (allObjMap[i].name == "platform") {
			platformList.push_back(new Platform(platformImage, "myPlatform", lvl, allObjMap[i].rect.left, allObjMap[i].rect.top, 224, 54, 0.1, 0));//� ���������� � ������ ���� ����� ������ � �����
		}
		else if (allObjMap[i].name == "platformV") {
			platformList.push_back(new Platform(platformImage, "myPlatformV", lvl, allObjMap[i].rect.left, allObjMap[i].rect.top, 224, 54, 0, 0.1));//� ���������� � ������ ����
		}
	}

	Font font;//����� 
	font.loadFromFile("font/colo.ttf");//�������� ������ ������ ���� ������
	Text text("", font, 25);//������� ������ �����. ���������� � ������ ����� ������, �����, ������ ������(� ��������);//��� ������ ����� (�� ������)	
	text.setFillColor(Color::Black);

	Font font2;//����� 
	font2.loadFromFile("font/col.ttf");//�������� ������ ������ ���� ������
	Text gameOver("", font2, 100);//������� ������ �����. ���������� � ������ ����� ������, �����, ������ ������(� ��������);//��� ������ ����� (�� ������)
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

			if (Keyboard::isKeyPressed(Keyboard::Tab)) { return true; }// ������������� ����

			if ((p.GetNextLvl() == true) || Keyboard::isKeyPressed(Keyboard::N)) //������� �� ���� �������
			{
				if (p.GetPlayerScore() == coinVect.size()) {
					numberLevel++;
					return true;
				}
			}
		}



		if (Keyboard::isKeyPressed(Keyboard::S)) //������� �� ���� �������
		{
			numberLevel++;
			return true;
		}


		////////�������� �����
		for (it = enemyList.begin(); it != enemyList.end();)//������� ��� ���������� �� ������ �� �����
		{
			Entity *b = *it;//��� ��������, ����� �� ������ (*it)->
			b->update(time);//�������� �-��� update ��� ���� �������� (�� ���� ��� ���, ��� ���)
			if (b->GetLife() == false) { it = enemyList.erase(it); delete b; b = nullptr;}// ���� ���� ������ �����, �� ������� ���
			else it++;//� ���� �������� (����������) � ���� �������. ��� ������ �� ����� ��������� ������
		}

		//////////�������� ������
		for (itC = coinList.begin(); itC != coinList.end();)//������� ��� ���������� �� ������ �� �����
		{
			Entity *c = *itC;//��� ��������, ����� �� ������ (*it)->
			c->update(time);//�������� �-��� update ��� ���� �������� (�� ���� ��� ���, ��� ���)
			if (c->GetLife() == false) { itC = coinList.erase(itC); delete c; c = nullptr;}// ���� ���� ������ �����, �� ������� ���
			else itC++;//� ���� �������� (����������) � ���� �������. ��� ������ �� ����� ��������� ������
		}

		//////////�������� Life
		for (itL = lifeList.begin(); itL != lifeList.end();)//������� ��� ���������� �� ������ �� �����
		{
			Entity *l = *itL;//��� ��������, ����� �� ������ (*it)->
			l->update(time);//�������� �-��� update ��� ���� �������� (�� ���� ��� ���, ��� ���)
			if (l->GetLife() == false) { itL = lifeList.erase(itL); delete l; l = nullptr;}// ���� ���� ������ �����, �� ������� ���
			else itL++;//� ���� �������� (����������) � ���� �������. ��� ������ �� ����� ��������� ������
		}

		//////////�������� Platform
		for (itP = platformList.begin(); itP != platformList.end();)//������� ��� ���������� �� ������ �� �����
		{
			Entity *pla = *itP;//��� ��������, ����� �� ������ (*it)->
			pla ->update(time);//�������� �-��� update ��� ���� �������� (�� ���� ��� ���, ��� ���)
			itP++;//� ���� �������� (����������) � ���� �������. ��� ������ �� ����� ��������� ������
		}

		//////////�������� Fire
		for (itB = bullList.begin(); itB != bullList.end();)//������� ��� ���������� �� ������ �� �����
		{

			Entity *f = *itB;//��� ��������, ����� �� ������ (*it)->
			f->update(time);//�������� �-��� update ��� ���� �������� (�� ���� ��� ���, ��� ���)
			if (f->GetLife() == false) { itB = bullList.erase(itB); delete f; f = nullptr;}// ���� ���� ������ �����, �� ������� ���
			else itB++;//� ���� �������� (����������) � ���� �������. ��� ������ �� ����� ��������� ������
			
		}

		p.updatePlayer(time, camera);//�������� ������ p ������ Player � ������� ������� sfml, ��������� ����� � �������� ��������� ������� update. ��������� ����� �������� ����� ���������

		//////////////////////////// ������������ ��������� � ������
		for (it = enemyList.begin(); it != enemyList.end(); it++)//���������� �� ��-��� ������
		{
			for (int i = 0; i < allObjMap.size(); i++){
			
				if ((*it)->getRect().intersects(p.getRect()) && !(*it)->getRect().intersects(allObjMap[i].rect)) {
					if ((*it)->name == "myEnemy1") {

						if ((p.GetDy() > 0) && (p.GetOnGround() == false)) { (*it)->SetDx(0); p.SetDy(-0.2); (*it)->SetHealth(0); }//���� �������� �� �����,�� ���� ����� �������� 0,����������� �� ���� ���� �����,���� ��� �������� 0




						if ((*it)->GetDx() > 0)//���� ���� ���� ������
						{


							if (p.GetLife() == true) {
								p.SetHealth(p.GetHealth() - 20);
								if (p.GetDx() < 0) { p.SetX((*it)->GetX() + (*it)->GetW() + 80); }//���� ����������� � ������ � ����� ���� ����� �� ����������� ������
								if (p.GetDx() > 0) { p.SetX((*it)->GetX() - p.GetW() - 80); }//���� ����������� � ������ � ����� ���� ������ �� ����������� ������
								if (p.GetDx() == 0) { p.SetX((*it)->GetX() + (*it)->GetW() + 60); }//���� ����������� � ������ � ����� ���� ������ �� ����������� ������
							}


						}
						if ((*it)->GetDx() < 0)//���� ���� ���� �����
						{

							if (p.GetLife() == true) {
								p.SetHealth(p.GetHealth() - 20);

								if (p.GetDx() < 0) { p.SetX((*it)->GetX() + (*it)->GetW() + 80); }//���� ����������� � ������ � ����� ���� ����� �� ����������� ������
								if (p.GetDx() > 0) { p.SetX((*it)->GetX() - p.GetW() - 80); }//���� ����������� � ������ � ����� ���� ������ �� ����������� ������
								if (p.GetDx() == 0) { p.SetX((*it)->GetX() - p.GetW() - 60); }
							}
						}
					}

					if ((*it)->name == "myEnemy2") {

													//if ((p.dy>0) && (p.onGround == false)) { (*it)->dx = 0; p.dy = -0.2; (*it)->health = 0; }//���� �������� �� �����,�� ���� ����� �������� 0,����������� �� ���� ���� �����,���� ��� �������� 0


						if ((*it)->GetDx() > 0)//���� ���� ���� ������
						{

							if (p.GetLife() == true) {
								p.SetHealth(p.GetHealth() - 40);
								if (p.GetDx() < 0) { p.SetX((*it)->GetX() + (*it)->GetW() + 80); }//���� ����������� � ������ � ����� ���� ����� �� ����������� ������
								if (p.GetDx() > 0) { p.SetX((*it)->GetX() - p.GetW() - 80); }//���� ����������� � ������ � ����� ���� ������ �� ����������� ������
								if (p.GetDx() == 0) { p.SetX((*it)->GetX() + (*it)->GetW() + 60); }
							}


						}
						if ((*it)->GetDx() < 0)//���� ���� ���� �����
						{

							if (p.GetLife() == true) {
								p.SetHealth(p.GetHealth() - 40);

								if (p.GetDx() < 0) { p.SetX((*it)->GetX() + (*it)->GetW() + 80); }//���� ����������� � ������ � ����� ���� ����� �� ����������� ������
								if (p.GetDx() > 0) { p.SetX((*it)->GetX() - p.GetW() - 80); }//���� ����������� � ������ � ����� ���� ������ �� ����������� ������
								if (p.GetDx() == 0) { p.SetX((*it)->GetX() - p.GetW() - 60); }
							}


						}
					}

				}
			}
			
		}

	
		////////////////////////////////////////////////// ������������ ��������� � �������
		for (itC = coinList.begin(); itC != coinList.end(); itC++)//���������� �� ��-��� ������
		{
			if ((*itC)->getRect().intersects(p.getRect()))//���� ������������� ������� ������� ������������ � �������
			{
					p.SetPlayerScore(p.GetPlayerScore() + 1);
					(*itC)->SetLife(false); 
					coinsSound.play();
			}
		}

		////////////////////////////////////////////////// ������������ ��������� � �������
		for (itL = lifeList.begin(); itL != lifeList.end(); itL++)//���������� �� ��-��� ������
		{
			if ((*itL)->getRect().intersects(p.getRect()))//���� ������������� ������� ������� ������������ � �������
			{
				p.SetHealth(p.GetHealth() + 40);
				(*itL)->SetLife(false);
				lifeSound.play();
			}
		}


		////////////////////////////////////////////////// ������������ ��������� � PLATFORM
		for (itP = platformList.begin(); itP != platformList.end(); itP++)//���������� �� ��-��� ������
		{
			if ((*itP)->getRect().intersects(p.getRect()))//���� ������������� ������� ������� ������������ � �������
			{
				if ((p.GetDy() > 0) && (p.GetY() < (*itP)->GetY())) {
					p.SetX(p.GetX() + ((*itP)->GetDx()*time));
					p.SetY((*itP)->GetY() - p.GetH() + 1);
					p.SetDy(0);
					p.SetOnGround(true);
				}

			}
		}

		////////////////////////////////////////////////// ������������ ���� � ������
		for (itB = bullList.begin(); itB != bullList.end(); itB++)//���������� �� ��-��� ������
		{
			for (it = enemyList.begin(); it != enemyList.end(); it++)//���������� �� ��-��� ������
			{
				if ((*itB)->getRect().intersects((*it)->getRect()))//���� ������������� ������� ������� ������������ � �������
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

		///////�������� ��� ������ ������
		if (p.GetLife() == false) {

			gameOver.setString("Game over");//������ ������ ������
			gameOver.setPosition(camera.view.getCenter().x - 225, camera.view.getCenter().y - 130);//������ ������� ������, ����� ������

			sleep += time;
			if (3000 < sleep) {
				return true;
			}
		}
				

		window.setView(camera.view);//"��������" ������ � ���� sfml
		window.clear();

		lvl.Draw(window);//������ ����� �����


		ostringstream playerScoreString, playerScoreHealth, playerScoreAll;    // �������� ����������
		playerScoreString << p.GetPlayerScore();		//������� � ��� ����� �����, �� ���� ��������� ������
		playerScoreHealth << p.GetHealth();
		playerScoreAll << coinVect.size();
		text.setString("Health: " + playerScoreHealth.str() + "    Coins: " + playerScoreString.str() + " | " + playerScoreAll.str());//������ ������ ������
		text.setPosition(camera.view.getCenter().x - 400, camera.view.getCenter().y - 230);//������ ������� ������, ����� ������
		
		window.draw(p.sprite);//������ ������ ������� p ������ player

		for (it = enemyList.begin(); it != enemyList.end(); it++) {
			window.draw((*it)->sprite); //������ entities ������� (������ ��� ������ �����)
		}

		for (itC = coinList.begin(); itC != coinList.end(); itC++) {
			window.draw((*itC)->sprite); //������ coin ������� 
		}

		for (itL = lifeList.begin(); itL != lifeList.end(); itL++) {
			window.draw((*itL)->sprite); //������ life ������� 
		}

		for (itP = platformList.begin(); itP != platformList.end(); itP++) {
			window.draw((*itP)->sprite); //������ Platform ������� 
		}

		for (itB = bullList.begin(); itB != bullList.end(); itB++) {
			window.draw((*itB)->sprite); //������ bull ������� 
		}

		window.draw(gameOver);//����� ���� �����
		window.draw(text);//����� ���� �����

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


void gameRunning(RenderWindow & window, int & numberLevel) {//�-��� ������������� ���� , ���� ��� ����������
	if (startGame(window, numberLevel)) { 
		gameRunning(window, numberLevel); 
	}//��������� � ������ ������ ������ ����
}