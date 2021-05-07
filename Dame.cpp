#include "Dame.h"

Dame::Dame(Echiquier& nouvelEchiquier, std::pair<int, int> position, bool estBlanc)
	: Tour(nouvelEchiquier, position, estBlanc), Fou(nouvelEchiquier, position, estBlanc), Piece(nouvelEchiquier, position, 'D', estBlanc)
{
	nouvelEchiquier.cases[position.first][position.second] = this;
}

void Dame::calculerMouvements(Echiquier e_)
{
	mouvementsDisponibles_.clear();
	Tour::calculerMouvements(e_);
	std::vector<std::pair<int, int>> mouvementsDisponiblesCopie_ = mouvementsDisponibles_;
	Fou::calculerMouvements(e_);
	for (std::pair<int, int> m : mouvementsDisponiblesCopie_)
		mouvementsDisponibles_.push_back(m);
}