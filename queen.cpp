#include "classes.hpp"

Dame::Dame(Echiquier& nouvelEchiquier, std::pair<int, int> position, bool estBlanc)
	: Tour(nouvelEchiquier, position, estBlanc), Fou(nouvelEchiquier, position, estBlanc), Piece(nouvelEchiquier, position, 'D', estBlanc)
{
	nouvelEchiquier.cases[position.first][position.second] = this;
}

void Dame::calculerMouvements(Echiquier e)
{
	Tour::calculerMouvements(e);
	Fou::calculerMouvements(e);
}