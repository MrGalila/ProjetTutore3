#include <SFML/Graphics.hpp>
//#include "Moteur.cpp"
#include <string>
#include <thread>
#include <cstdlib>
#include <iostream>


#pragma once

class Personnage : public sf::Sprite {
public:
	Personnage() : pv(300), enSaut(false), accroupi(false), poids(0), rectSourceSprite(0, 80, 80, 80), sprite(texture, rectSourceSprite), x(0), y(0), pos(x, y) // Constructeur
	{

	}

	void init() {

		sprite.setOrigin(40, 0);

		if (orientation == false) {
			x = 200;
			y = 370;
			sprite.setScale(2, 2);

		}
		else if (orientation == true) {
			x = 770;
			y = 370;
			sprite.setScale(-2, 2);
		}
		pos.x = x;
		pos.y = y;
	}

	// definition de la barre de vie 
	sf::RectangleShape hp(int x,int y) {

		sf::RectangleShape hp;
		hp.setSize(sf::Vector2f(pv, 40)); // Taille 
		hp.setPosition(x, y); //Position sur l'écran
		hp.setFillColor(sf::Color(100, 250, 50));
	
		hp.setOutlineColor(sf::Color(0, 0, 0)); //Couleur du Contour
		hp.setOutlineThickness(4); //Taille du contour

		return hp;
	}

	// utiliser pour modifier les pv lorsqu'un personnage prend des dégâts
	void setHP(int degat) {
		pv = pv-degat;
	}



	int getHP() {
		return pv;
	}

	void Avancer() { //Avance toujours vers l'adversaire
		if (orientation == false)
			pos.x += 10;
		else
			pos.x -= 10;

		if (rectSourceSprite.left == 160)
			rectSourceSprite.left = 0;
		else {
			rectSourceSprite.left += 80;
		}
		sprite.setTextureRect(rectSourceSprite);
		sprite.setPosition(pos.x, pos.y);
	}

	void SurPlace(Personnage p2) {

		if (orientation == false) {
			if ((this->pos.x) - 75 > p2.pos.x) {
				this->orientation = true;
				sprite.setScale(-2, 2);
			}
		}
		else {
			if ((this->pos.x) + 75 < p2.pos.x) {
				this->orientation = false;
				sprite.setScale(2, 2);
			}
		}
		sprite.setPosition(pos.x, pos.y);
	}

	void Reculer() {
		if (orientation == false)
			pos.x -= 5;
		else
			pos.x += 5;
		if (rectSourceSprite.left == 0)
			rectSourceSprite.left = 160;
		else {
			rectSourceSprite.left -= 80;
		}
		sprite.setTextureRect(rectSourceSprite);
		sprite.setPosition(pos.x, pos.y);
	}

	void Sauter();
	void Accroupir();
	void Bloquer();

	sf::Sprite CoupDePoing() {


		if (rectSourceSprite.left == 1000)
			rectSourceSprite.left = 0;
		else {
			rectSourceSprite.left += 500;
		}
		sprite.setTextureRect(rectSourceSprite);
		return sprite;
	}

	sf::Sprite CoupDePied();


	bool getOrientation() {
		return this->orientation;
	}

	double getX() {
		return pos.x;
	}

	sf::Sprite getSprite() {
		sprite.setTextureRect(rectSourceSprite);
		sprite.setPosition(pos.x, pos.y);
		return sprite;
	}

	void TestWait() {
		sf::sleep(sf::milliseconds(10000));
	}

	void TestThread() {
		printf("yo");
	}

protected:
	std::string nom; //Nom du personnage
	sf::Texture texture; //Toute la table de texture, qui sera ensuite transformée en différents sprites
	bool accroupi; //false = Debout / true = Accroupi
	bool enSaut; //false = au sol / true = en l'air
	double poids; //poids du perso, afin de gérer sa gravité, la puissance de ses coups, etc
	int pv; //point de vie, démarre tjr à 100
	sf::IntRect rectSourceSprite; //Pour pouvoir le modifier sans le réintialiser à chaque fois
	sf::Sprite sprite;
	double x;
	double y;
	sf::Vector2f pos;
	bool orientation; //false = vers la droite / true = vers la gauche

};


/*

sf::Sprite Personnage::Avancer()
{
	sf::IntRect rectSourceSprite(0, 0, 500, 500);
	sf::Sprite sprite(texture, rectSourceSprite);

	if (rectSourceSprite.left == 1000)
		rectSourceSprite.left = 0;

	else
		rectSourceSprite.left += 500;

	return sprite;
}


//Recule mais se tient toujours face à l'adversaire
void Personnage::Reculer()
{}

//Un seul saut, on est pas dans smash, la fonction utilise la fonction gravité de Moteur
void Personnage::Sauter()
{}

//Peut s'accroupir pour réduire sa hitbox, mais ne peut pas se déplacer
void Personnage::Accroupir()
{}

//Bloque les attaques adverse en partialité lorsque ne fait rien
void Personnage::Bloquer()
{}

//Met un coup de poing, plus puissant que le coup de pied mais moins d'allonge / change selon l'état
void Personnage::CoupDePoing()
{}

//Met un coup de pied, plus faible qu'un coup de poing mais plus d'allonge / change selon l'état
void Personnage::CoupDePied()
{}
*/