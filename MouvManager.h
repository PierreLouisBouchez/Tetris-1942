#pragma once

#include "Piece.h"
#include "integrityPlateau.h"
#include "Plateau.h"
#include <time.h>
#include <iostream>
#include <random>
#include <algorithm>
#include <iterator>
#include <iostream>
#include <vector>
#include <fstream>

#define NBPIECE 7

using namespace std;

class MouvManager {
	public:
		Piece* currentPiece; /* la piece qui se balade sur le plateau */
		Piece* nextPiece;	/* la piece qui sera sur le plateau ensuite */
		Plateau* plateau;
		int points;
		int maxScore;
		double speed;
		double delta;
		int mod;
		vector<int> precPiece;
		vector<int> precColor;
		int level;



		MouvManager(int mid, int line, int col, int mod);
		/* creer un mouvManager avec les parametres (mid) de la fabrication des pieces et (line, col) qui sont pour la fabrication d'un plateau */

		void resetGame(int mid, int line, int col);

		void goLeft();
		/* appelle la (currentPiece) pour lui dire d'aller sur gauche de 1*/
		void goRight();
		/* appelle la (currentPiece) pour lui dire d'aller sur droite de 1*/
		std::vector<int> goDown();
		/* appelle la (currentPiece) pour lui dire d'aller en bas de 1*/
		void turnLeft();
		/* appelle la (currentPiece) pour lui dire de tourner a gauche de 1*/
		bool verifLose();
		/* verifie si la partie est perdu ou pas */
		void generatePiece();
		/* change la nextPiece par une nouvelle random*/
		~MouvManager();
		/* détruit toute les objects initialisé en mémoire */


};
