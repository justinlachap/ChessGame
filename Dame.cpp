#include "Dame.h"

Dame::Dame(Echiquier& nouvelEchiquier, std::pair<int, int> position, bool estBlanc)
	: Tour(nouvelEchiquier, position, estBlanc), Fou(nouvelEchiquier, position, estBlanc), Piece(nouvelEchiquier, position, 'D', estBlanc)
{
	nouvelEchiquier.cases[position.first][position.second] = this;
}

std::vector<std::pair<int, int>> Dame::calculerMouvementsTour(Echiquier& e_)
{
	mouvementsDisponibles_.clear();
	Tour::calculerMouvements(e_);
	std::vector<std::pair<int, int>> mouvementsDisponiblesCopie = mouvementsDisponibles_;
	return mouvementsDisponiblesCopie;
}

void Dame::ajouterMouvementsFou(Echiquier& e_, std::vector<std::pair<int, int>>& MouvementsDipsoniblesTour)
{
	Fou::calculerMouvements(e_);
	for (std::pair<int, int> m : MouvementsDipsoniblesTour)
		mouvementsDisponibles_.push_back(m);
}

void Dame::calculerMouvements(Echiquier e_)
{
	std::vector<std::pair<int, int>> mouvementsDisponiblesTour = calculerMouvementsTour(e_);
	ajouterMouvementsFou(e_, mouvementsDisponiblesTour);
}