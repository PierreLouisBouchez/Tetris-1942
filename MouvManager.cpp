#include "MouvManager.h"

using namespace std;


MouvManager::MouvManager(int mid, int line, int col, int mod){
	srand((unsigned int) time(0));
	currentPiece = new Piece(mid);
	nextPiece = new Piece(mid);
	this->mod = mod;
	int randPiece = rand() % NBPIECE + 1;
	precPiece.push_back(randPiece);
	while (precPiece.size() != 2) {
		randPiece = rand() % NBPIECE + 1;
		if(find(precPiece.begin(), precPiece.end(), randPiece) == precPiece.end()) {
			precPiece.push_back(randPiece);
		}
	}
	precColor.push_back(randPiece);
	while (precColor.size() != 2){
		randPiece = rand() % NBPIECE + 1;
		if (find(precColor.begin(), precColor.end(), randPiece) == precColor.end()) {
			precColor.push_back(randPiece);
		}
	}
	currentPiece->replacePiece(precColor[0], precPiece[0]);
	nextPiece->replacePiece(precColor[1], precPiece[1]);
	plateau = new Plateau(line, col);
	speed = 1.25;
	delta = 0.8;
	points = 0;
	level = 0;
	
	fstream f;
	f.open("data/score.bin");
	f.read((char*) &maxScore, sizeof(maxScore));
	if (f.fail()) {
		maxScore = 0;
	}
	f.close();
}


void MouvManager::resetGame(int mid, int line, int col) {
	speed = 1.25;
	delta = 0.8;
	points = 0;
	plateau->clear();
	level = 0;

}

void MouvManager::goLeft(){
	if (left(plateau, currentPiece)) {
		currentPiece->goLeft();
	}
}

void MouvManager::goRight(){
	if (right(plateau, currentPiece)) {
		currentPiece->goRight();
	}
}

vector<int> MouvManager::goDown(){

	if (down(plateau, currentPiece)) {
		currentPiece->goDown();
	}
	else {
		plateau->addPiece(currentPiece);
		*currentPiece = *nextPiece;
		if (precPiece.size() == 3) {
			precPiece.erase(precPiece.begin());
			precColor.erase(precColor.begin());
		}
		generatePiece();
		
	}
	vector<int> listLineDel = plateau->DelLinePlateau(mod);
	if (listLineDel.size() == 1) {
		points += (40 * (level+1));
	}
	else if (listLineDel.size() == 2) {
		points += (100 * (level+1));
	}
	else if (listLineDel.size() == 3) {
		points += (300 * (level+1));
	}
	else if (listLineDel.size() == 4) {
		points += (1200 * (level+1));
	}
	else if (listLineDel.size() >= 20) {
		points += (3000 * (level+1));
	}
	if (points >= 1200 * (level+1)) {
		++level;
		if (delta > 0.3) {
			delta *= 0.93;
			speed = 1 / delta;
		}
	}
	return listLineDel;

}

void MouvManager::turnLeft(){
	int tmp[4][2];
	for (int i = 0; i < 4; ++i) {
		for (int j = 0; j < 2; ++j) {
			tmp[i][j] = currentPiece->compoPiece[i][j];
		}
	}
	if (verifTurnLeft(plateau, currentPiece)) {
		currentPiece->turnLeft();
		if (!verifIntegrity(plateau, currentPiece)) {
			for (int i = 0; i < 4; ++i) {
				for (int j = 0; j < 2; ++j) {
					currentPiece->compoPiece[i][j] = tmp[i][j];
				}
			}
		}
	}
}

bool MouvManager::verifLose(){
	if (!verifIntegrity(plateau, currentPiece)) {
		if (points > maxScore) {
			maxScore = points;
		}
		fstream f;
		f.open("data/score.bin");
		f.write((char*)&maxScore, sizeof(maxScore));
		f.close();
		return true;
	}
	return false;
}

void MouvManager::generatePiece(){
	int randPiece;
	while (precPiece.size() != 3) {
		randPiece = rand() % NBPIECE + 1;
		if (find(precPiece.begin(), precPiece.end(), randPiece) == precPiece.end()) {
			precPiece.push_back(randPiece);
		}
	}
	while (precColor.size() != 3) {
		randPiece = rand() % NBPIECE + 1;
		if (find(precColor.begin(), precColor.end(), randPiece) == precColor.end()) {
			precColor.push_back(randPiece);
		}
	}
	nextPiece->replacePiece(precColor[2], precPiece[2]);
}

MouvManager::~MouvManager(){
	delete currentPiece;
	delete nextPiece;
	delete plateau;
	
}



