#pragma once

#include "Plateau.h"
#include "Piece.h"

bool left (Plateau* plateau, Piece* piece);
/* vérifie si la piece (piece) peut aller vers la gauche dans le plateau (plateau) */
bool right (Plateau* plateau, Piece* piece);
/* vérifie si la piece (piece) peut aller vers la droite dans le plateau (plateau) */
bool down(Plateau* plateau, Piece* piece);
/* vérifie si la piece (piece) peut aller vers le bas dans le plateau (plateau) */
bool verifTurnLeft(Plateau* plateau, Piece* piece);
/* vérifie si la piece (piece) peut tourner vers la gauche dans le plateau (plateau) */
bool verifIntegrity(Plateau* plateau, Piece* piece);
/* vérifie si la piece (piece) peut avoir la position qu'elle a actuellement dans le plateau (plateau) */