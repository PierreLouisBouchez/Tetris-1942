#include "Plateau.h"

using namespace std; 

Plateau::Plateau(int nbLine, int nbCol){
	this->nbLine = nbLine;
	this->nbCol = nbCol;
	plateau = new int*[nbLine];
	for (int i = 0; i < nbLine; ++i) {
		plateau[i] = new int[nbCol];
		for (int w = 0; w < nbCol; ++w) {
			plateau[i][w] = 0;
		}
	}
}

void Plateau::addPiece(Piece* newPiece){
	plateau[newPiece->compoPiece[0][1]][newPiece->compoPiece[0][0]] = newPiece->color;
	plateau[newPiece->compoPiece[1][1]][newPiece->compoPiece[1][0]] = newPiece->color;
	plateau[newPiece->compoPiece[2][1]][newPiece->compoPiece[2][0]] = newPiece->color;
	plateau[newPiece->compoPiece[3][1]][newPiece->compoPiece[3][0]] = newPiece->color;
}

bool Plateau::lineEmpty(int line){
	for (int i = 0; i < nbCol; ++i) {
		if (plateau[line][i] != 0) {
			return false;
		}
	}
	return true;
}

vector<int> Plateau::DelLinePlateau(int mod){
	int typeColor = 0;
	vector<int> ret;

	for (int i = 0; i < nbLine; ++i) {
		bool notEmpty = 0;
		bool same = 1;
		bool samebutNot = 1;
		int precColor = plateau[i][0];
		typeColor = plateau[i][0];
		for (int j = 0; j < nbCol; ++j) {
			if (plateau[i][j] == 0) {
				notEmpty = 0;
				break;	
			}
			if (precColor != plateau[i][j]) {
				same = 0;
			}
			if (plateau[i][j] != 3 && plateau[i][j] != 6) {
				samebutNot = 0;
			}
			notEmpty = 1;
		}
		if (notEmpty) {
			if (mod == 1 && samebutNot == 1) {
				ret.push_back(i - 1);
				if (i != nbLine - 1) {
					ret.push_back(i + 1);
				}	
			}
			ret.push_back(i);
			if (mod == 1 && plateau[i][0] == 6 && same == 1) {
				clear();
				for (int w = 0; w < 19; ++w) {
					ret.push_back(i);
				}
			}
			for (int j = 0; j < nbCol; ++j) {
				if (mod == 1 && samebutNot == 1) {
					plateau[i - 1][j] = 0;
					if (i < nbLine-1) {
						plateau[i + 1][j] = 0;
					}
				}
				plateau[i][j] = 0;
			}
			if (mod == 1) {
				downPlateau();
				downPlateau();
			}
			downPlateau();
		}
	}
	return ret;
}

void Plateau::downPlateau(){
	bool precEmpty = lineEmpty(nbLine - 1);
	bool currentEmpty;
	for (int i = nbLine - 2; i >= 0; --i) {
		currentEmpty = lineEmpty(i);
		if (precEmpty && !currentEmpty) {
			std::swap(plateau[i + 1], plateau[i]);
		}
		else {
			precEmpty = currentEmpty;
		}
	}
}

void Plateau::clear() {
	for (int i = 0; i < nbLine; ++i) {
		for (int j = 0; j < nbCol; ++j) {
			plateau[i][j] = 0;
		}
	}
}

Plateau::~Plateau(){
	for (int i = 0; i < nbLine; ++i) {
		delete[] plateau[i];
	}
	delete[] plateau;
}

