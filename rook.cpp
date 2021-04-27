#include "classes.hpp"
#include "cppitertools/range.hpp"

using namespace iter;
static const int uneCase = 1;
static const int tailleEchiquierMin = 0;
static const int tailleEchiquierMax = 7;
static const Piece* caseVide = nullptr;
Tour::Tour(Echiquier& nouvelEchiquier, std::pair<int, int> position, bool estBlanc)
	: Piece(nouvelEchiquier, position, 'T', estBlanc)
{
	nouvelEchiquier.cases[position.first][position.second] = this;
}

void Tour::calculerMouvements(Echiquier e)
{
	// nombre de position vides vers la droite
	for (int positionsRangeeVersLaDroite : iter::range(position_.first, tailleEchiquierMax))
	{
		if (e.cases[positionsRangeeVersLaDroite + uneCase][position_.second] != caseVide)
		{
			if (e.cases[positionsRangeeVersLaDroite + uneCase][position_.second]->obtenirCouleur() != estBlanc_)
				mouvementsDisponibles_.push_back(std::pair(positionsRangeeVersLaDroite + uneCase, position_.second));
			break;
		}
		if (e.cases[positionsRangeeVersLaDroite + uneCase][position_.second] == caseVide)
			mouvementsDisponibles_.push_back(std::pair(positionsRangeeVersLaDroite + uneCase, position_.second));
	}

	// nombre de position vides vers la gauche
	for (int positionsRangeeVersLaGauche : iter::range(position_.first, 0, -uneCase))
	{
		if (e.cases[positionsRangeeVersLaGauche - uneCase][position_.second] != caseVide)
		{
			if (e.cases[positionsRangeeVersLaGauche - uneCase][position_.second]->obtenirCouleur() != estBlanc_)
				mouvementsDisponibles_.push_back(std::pair(positionsRangeeVersLaGauche - uneCase, position_.second));
			break;
		};
		if (e.cases[positionsRangeeVersLaGauche - uneCase][position_.second] == caseVide)
			mouvementsDisponibles_.push_back(std::pair(positionsRangeeVersLaGauche - uneCase, position_.second));
	}

	// nombre de position vides vers le haut
	for (int positionsRangeeVersLeHaut : iter::range(position_.second, tailleEchiquierMax))
	{
		if (e.cases[position_.first][positionsRangeeVersLeHaut + uneCase] != caseVide)
		{
			if (e.cases[position_.first][positionsRangeeVersLeHaut + uneCase]->obtenirCouleur() != estBlanc_)
				mouvementsDisponibles_.push_back(std::pair(position_.first, positionsRangeeVersLeHaut + uneCase));
			break;
		}
		if (e.cases[position_.first][positionsRangeeVersLeHaut + uneCase] == caseVide)
			mouvementsDisponibles_.push_back(std::pair(position_.first, positionsRangeeVersLeHaut + uneCase));
	}

	// nombre de position vides vers le bas
	for (int positionsRangeeVersLeBas : iter::range(position_.second, 0, -uneCase))
	{
		if (e.cases[position_.first][positionsRangeeVersLeBas - uneCase] != caseVide)
		{
			if (e.cases[position_.first][positionsRangeeVersLeBas - uneCase]->obtenirCouleur() != estBlanc_)
				mouvementsDisponibles_.push_back(std::pair(position_.first, positionsRangeeVersLeBas - uneCase));
			break;
		}
		if (e.cases[position_.first][positionsRangeeVersLeBas - uneCase] == caseVide)
			mouvementsDisponibles_.push_back(std::pair(position_.first, positionsRangeeVersLeBas - uneCase));
	}
};