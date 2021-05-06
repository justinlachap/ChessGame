#include "Piece.h"
#include <iostream>

Piece::Piece(Echiquier& nouvelEchiquier, std::pair<int, int> position, char nom, bool estBlanc)
	: position_(position), nom_(nom), estBlanc_(estBlanc) {}

void Piece::afficheMouvements() const
{
	std::cout << "Cette piece peut se deplacer aux cases: ";

	for (std::pair<int, int> m : mouvementsDisponibles_)
		std::cout << '(' << m.first << ", " << m.second << ") ";

	std::cout << std::endl;
}

void Piece::changerPos(int x, int y, Echiquier* e_)
{
	position_.first = x;
	position_.second = y;
	e_->cases[x][y] = this;
}
