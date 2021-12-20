#pragma once

#include <SFML/Graphics.hpp>
#include <vector>
using namespace std;

class Block
{
protected:
	sf::Vector2f coordinates;
	/*Coordonnées*/


public:
	static const float FACTOR;
	/*Facteur taille sprite*/
	static const int TEXTURE_SIZE = 32;
	/*Taille block*/

	sf::Sprite sprite;

	sf::IntRect rectangle = sf::IntRect(0, 0, 128, 128);


	Block();

	void setX(double x);
	void setY(double y);
	double getX() const;
	double getY() const;

	void changeTexture(int n);
};

