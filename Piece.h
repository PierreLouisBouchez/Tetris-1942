#pragma once

#include <vector>

#define PIECE11 1
#define PIECE12 1
#define PIECE13 0
#define PIECE31 0
#define PIECE32 0
#define PIECE33 0
#define PIECE2471 0
#define PIECE2472 1
#define PIECE2473 0
#define PIECE561 0
#define PIECE562 1
#define PIECE563 1

class Piece {

public:
	int mid;
	int compoPiece[4][2];
	/* stock les coordonnées des block constituant la piece [4] etant le nombre de block et [2] les coordonnées x,y */
	int piece;
	int color;

	Piece(int mid);
	/*defini une piece, null et qui permet de stocker le centre horizontal du plateau (mid) 
		si nbCol de plateau = 10 alors mid = 5 */
	void replacePiece (int color,int piece);
	/*change la piece actuelle, avec une nouvelle couleur (color) et un integer (piece) qui est l'id correspondant a une forme de piece */
	void turnLeft();
	/* fait pivoter la piece par la gauche selon l'axe centré sur les coordonnée du block compoPiece[0][0]*/
	/*void turnRight(); */
	void goDown();
	/* fait aller la piece vers le bas de 1*/
	void goLeft();
	/* fait aller la piece vers la gauche de 1*/
	void goRight();
	/* fait aller la piece vers la droite de 1*/
	Piece& operator =(const Piece& p2);
	/* change l'operateur pour pouvoir donner toute les composantes d'une piece (p2) a la piece (this) */
};
