#include "Cavalier.h"
#include "gsl/span"

using namespace gsl;
static const int tailleEchiquierMax = 7;
static const Piece *caseVide = nullptr;

Cavalier::Cavalier(Echiquier &nouvelEchiquier, std::pair<int, int> position, bool estBlanc)
	: Piece(nouvelEchiquier, position, 'C', estBlanc)
{
	nouvelEchiquier.cases[position.first][position.second] = this;
}

void Cavalier::calculerMouvements(Echiquier e)
{
	mouvementsDisponibles_.clear();
	std::pair<int, int> deplacements[8] = {std::pair(-1, -2), std::pair(1, -2),
										   std::pair(2, -1), std::pair(2, 1),
										   std::pair(1, 2), std::pair(-1, 2),
										   std::pair(-2, 1), std::pair(-2, -1)};
	const int tailleInt = 8;

	span<std::pair<int, int>> spanDeplacements = {deplacements, sizeof(deplacements) / tailleInt};
	for (auto d : spanDeplacements)
	{
		int x = position_.first + d.first;
		int y = position_.second + d.second;
		if (x >= 0 && x <= tailleEchiquierMax && y >= 0 && y <= tailleEchiquierMax && (e.cases[x][y] == caseVide || (e.cases[x][y]->obtenirCouleur() != estBlanc_)))
			mouvementsDisponibles_.push_back(std::pair(x, y));
	}
};