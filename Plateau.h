#pragma once
#include "Piece.h"
#include <stdio.h>
#include <algorithm>
#include <vector>

class Plateau {
public:
	int nbLine;
	int nbCol;
	int **plateau;


	Plateau(int nbLine, int nbCol);
	/* creation d'un plateau Tetris avec un certain nombre de ligne (nbLine) et de colonne (nbCol) */
	void addPiece(Piece* newPiece);
	/* ajout d'une piece dans le tableau en suivant les coordonnées indiqué dans la piece (newPiece) ainsi que sa couleur */
	bool lineEmpty(int line);
	/* vérifie si la ligne (line) est vide */
	std::vector<int> DelLinePlateau(int mod);
	/* supprime une ligne du plateau */
	void downPlateau();
	/* remonte une ligne vide au dessus de toute les lignes avec des blocks dedans*/
	void clear();
	/* nettoie le tableau de tout les block, mets toute la matrice a 0 */
	~Plateau();
	/* supprime les élements stocké en mémoire */
};