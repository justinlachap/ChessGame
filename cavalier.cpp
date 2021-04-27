#include "cavalier.hpp"
#include "echiquier.hpp"
#include "gsl/span"
#include "cppitertools/range.hpp"
#include "constantes.hpp"

using namespace iter;
using namespace gsl;

Cavalier::Cavalier(Echiquier& nouvelEchiquier, std::pair<int, int> position, bool estBlanc)
	: Piece(nouvelEchiquier, position, 'C', estBlanc)
{
	nouvelEchiquier.cases[position.first][position.second] = this;
}

void Cavalier::calculerMouvements(Echiquier e)
{
	std::pair<int, int> deplacements[8] = { std::pair(-1,-2),std::pair(1,-2),std::pair(2,-1),std::pair(2,1),std::pair(1,2),std::pair(-1,2),std::pair(-2,1),std::pair(-2,-1) };
	const int tailleInt = 8;

	span<std::pair<int, int>>  spanDeplacements = { deplacements, sizeof(deplacements) / tailleInt };
	for (auto d : spanDeplacements)
	{
		int x = position_.first + d.first;
		int y = position_.second + d.second;
		if (x >= 0 && x <= tailleEchiquierMax && y >= 0 && y <= tailleEchiquierMax) {
			if (e.cases[x][y] == caseVide || (e.cases[x][y]->obtenirCouleur() != estBlanc_))
				mouvementsDisponibles_.push_back(std::pair(x, y));
		}
	}
};