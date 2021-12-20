#pragma once

#include <SFML/Graphics.hpp>
#include <vector>
#include "EventsManager.h"
#include "Block.h"
using namespace std;

class GraphicsManager
{

	public:

		int Render(sf::RenderWindow* window, MouvManager* mManager, sf::Time time);
		/*Rendu du jeu */
		int RenderMenu(sf::RenderWindow* window,MouvManager& mManager, sf::Clock& c,int& menubutton);
		/*Rendu du Menu*/

		Block* tetromino;
		/*Tetromino actuel*/
		Block* blockplateau;
		/*Piece pour dessiner les blocks du plateau*/

		sf::Sprite background;
		sf::Sprite spitfire;

		/*Sprite du background*/
		sf::RectangleShape *plate;
		vector<int> destroyed;
		double Delta;
		GraphicsManager();
};

