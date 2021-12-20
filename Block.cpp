#include <SFML/Graphics.hpp>
#include <vector>
#include "Block.h"

using namespace std;

Block::Block() {
		coordinates.x = 400;
		coordinates.y = 50;

		sprite.setTextureRect(rectangle);
		sprite.setScale(sf::Vector2f(FACTOR, FACTOR));

}
void Block::setX(double x) {
	coordinates.x = x;
	sprite.setPosition(coordinates);
};
void Block::setY(double y) {
	coordinates.y = y;
	sprite.setPosition(coordinates);

}

double Block::getX() const {
	return coordinates.x;
};

double Block::getY() const {
	return coordinates.y;
};


void Block::changeTexture(int n){
	rectangle.left = 128*(n-1);
	sprite.setTextureRect(rectangle);
}



const float Block::FACTOR = 0.25f;