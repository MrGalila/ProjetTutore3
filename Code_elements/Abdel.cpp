#include <SFML/Graphics.hpp>
#include "Personnage.cpp"
#include <string>

class Abdel : public Personnage {
public:
	Abdel(bool orient) {
		orientation = orient;
		nom = "Abdelbrecht";
		sf::Texture texture;
		texture.loadFromFile("C:/Users/pc 1/source/repos/PT3/Abdelbrecht_sprite.png");
		this->texture = texture;
		this->poids = 50;
		

	}

};