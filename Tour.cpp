#include "Tour.h"
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

void Tour::mouvementsVersLaDroite(Echiquier& e)
{
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
}

void Tour::mouvementsVersLaGauche(Echiquier& e)
{
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
}

void Tour::mouvementsVersLeHaut(Echiquier& e)
{
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
}

void Tour::mouvementsVersLeBas(Echiquier& e)
{
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
}

void Tour::calculerMouvements(Echiquier e_)
{
	mouvementsDisponibles_.clear();

	mouvementsVersLaDroite(e_);
	mouvementsVersLaGauche(e_);
	mouvementsVersLeHaut(e_);
	mouvementsVersLeBas(e_);
}