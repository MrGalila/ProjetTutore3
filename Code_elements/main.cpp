#include <SFML/Graphics.hpp>
#include <iostream>
#include <ctime>
#include <string>
#include <cstdlib>
#include <sstream>
#include <iomanip>
#include <locale>
#include "Personnage.cpp"
#include <SFML/Audio.hpp>
#include <thread>
#include <chrono>
#include "Abdel.cpp"

#include <fstream>
#include <vector>

#include <functional>


using namespace std;

void TestWait() {
	printf("sleep lanc�");
	sf::sleep(sf::milliseconds(10000));
	printf("sleep stop�");
}

void action(Personnage* player, char move) {
	int i = 0;
	switch (move)
	{
	case 'r':
		if (player->getOrientation())
			player->Reculer();
		else
			player->Avancer();
		break;
	case'q':
		if (player->getOrientation())
			player->Avancer();
		else
			player->Reculer();
		break;
	}

}


int main()
{

	Abdel p1(false);
	Abdel p2(true);

	p1.init();
	p2.init();

	sf::Clock clock;
	int countdown = 5;

	sf::RenderWindow windowI(sf::VideoMode(560, 438), "M0RT4L T34CH-R");
	//d�finition de l'intro du jeu vid�o
	sf::Texture introTexture;
	sf::Sprite intro;
	introTexture.loadFromFile("C:/Users/pc 1/source/repos/PT3/intro.png");
	intro.setTexture(introTexture);
	//560x438 pour chaque frame de l'intro.

	intro.setTextureRect(sf::IntRect(0, 0, 560, 438));
	int introTimer = 1;
	int introMax = 23;

	windowI.setActive(false);
	//lancement de l'introduction
	while (windowI.isOpen())
	{
		if (introTimer <= introMax) {
			windowI.clear();
			windowI.draw(intro);
			windowI.display();

			intro.setTextureRect(sf::IntRect(560 * (introTimer - 1), 0, 560 * introTimer, 438));
			introTimer++;
			std::this_thread::sleep_for(std::chrono::milliseconds(250));
		}
		else {
			windowI.close();
		}
	}

	sf::RenderWindow window(sf::VideoMode(945, 647), "M0RT4L T34CH-R");
	sf::Sprite map;

	

	sf::Event event;

	sf::Texture texture;
	texture.loadFromFile("C:/Users/pc 1/source/repos/PT3/map1.png");
	map.setTexture(texture);

	window.setActive(false);

	sf::Thread aaa(&TestWait);
	aaa.launch();

	//d�finition et lancement de la musique d�s l'ex�cution du jeu
	sf::Music music;
	music.openFromFile("5Keer.ogg");
	music.setVolume(10);
	music.play();

	// d�finition d'un bruitage 'outch'
	sf::SoundBuffer buffer;
	buffer.loadFromFile("outch.ogg");
	sf::Sound sound;
	sound.setBuffer(buffer);

	//window.setVerticalSyncEnabled(true);

	while (window.isOpen())
	{

		//int timer = clock.getElapsedTime().asSeconds();
		//std::cout << timer << std::endl;
		/*
		if (timer > 0) {
			if (!countdown == 0) {
				countdown--;
				convert << countdown;
				countdownString = convert.str();
				timerText.setString(countdownString);
				clock.restart();
			}
			else
				timerText.setString("0");

		}
		*/
		

		while (window.pollEvent(event))
		{


			if (sf::Event::Closed) {
				window.close();
			}

			if ((sf::Keyboard::isKeyPressed(sf::Keyboard::Right))) {
				sf::Thread thread(std::bind(&action, &p1, 'r'));
				thread.launch();
			}

			if ((sf::Keyboard::isKeyPressed(sf::Keyboard::Q))) {
				sf::Thread thread(std::bind(&action, &p2, 'q'));
				thread.launch();
			}

			if ((sf::Keyboard::isKeyPressed(sf::Keyboard::A))) {
				sf::Thread thread(&TestWait);
				thread.launch();
			}


			if ((sf::Keyboard::isKeyPressed(sf::Keyboard::Left))) {
				if (p1.getOrientation())
					p1.Avancer();
				else
					p1.Reculer();
			}

			if ((sf::Keyboard::isKeyPressed(sf::Keyboard::D))) {
				if (p2.getOrientation())
					p2.Reculer();
				else
					p2.Avancer();
			}

			if ((sf::Keyboard::isKeyPressed(sf::Keyboard::Up))) {

			}

			if ((sf::Keyboard::isKeyPressed(sf::Keyboard::Down)))
			{

			}

			if(p1.getX() < p2.getX() && p1.getX() + 80 > p2.getX() or p1.getX() < p2.getX()+80 && p1.getX() + 80 > p2.getX()+80) {
				p1.setHP(10);
				sound.play();
				
			}

			if (p1.getHP() == 0 or p2.getHP() == 0) {
				sf::Sprite spriteKo;
				sf::Texture texture;
				texture.loadFromFile("C:/Users/pc 1/source/repos/PT3/Ko.png");
				spriteKo.setTexture(texture);
				spriteKo.setPosition(sf::Vector2f(370, 10));
				window.draw(spriteKo);
				window.display();
				std::this_thread::sleep_for(std::chrono::milliseconds(6000));
				window.close();
			}
			

			p1.SurPlace(p2);
			p2.SurPlace(p1);

			window.clear();
			window.draw(map);
			window.draw(p1.getSprite());
			window.draw(p2.getSprite());
			window.draw(p1.hp(50,50)); // on dessine la barre de vie et on donne sa position
			window.draw(p2.hp(590, 50)); // comme au dessus wesh fait pas genre t'a pas compris
		
			window.display();
			std::this_thread::sleep_for(std::chrono::milliseconds(50));
		}
	}


	return 0;
}