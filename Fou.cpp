#include "Fou.h"
static const int uneCase = 1;
static const int tailleEchiquierMin = 0;
static const int tailleEchiquierMax = 7;
static const Piece* caseVide = nullptr;


Fou::Fou(Echiquier& nouvelEchiquier, std::pair<int, int> position, bool estBlanc)
	: Piece(nouvelEchiquier, position, 'F', estBlanc)
{
	nouvelEchiquier.cases[position.first][position.second] = this;
}

void Fou::diagonaleHautGauche(Echiquier& e)
{
	int positionsRangeeVersLaGauche = position_.first;
	int positionsRangeeVersLeHaut = position_.second;

	while (positionsRangeeVersLaGauche > tailleEchiquierMin && positionsRangeeVersLeHaut < tailleEchiquierMax)
	{
		if ((e.cases[positionsRangeeVersLaGauche - uneCase][positionsRangeeVersLeHaut + uneCase] == caseVide))
			mouvementsDisponibles_.push_back(std::pair(positionsRangeeVersLaGauche - uneCase, positionsRangeeVersLeHaut + uneCase));

		else if ((e.cases[positionsRangeeVersLaGauche - uneCase][positionsRangeeVersLeHaut + uneCase]->obtenirCouleur() == estBlanc_))
			break;

		else
		{
			mouvementsDisponibles_.push_back(std::pair(positionsRangeeVersLaGauche - uneCase, positionsRangeeVersLeHaut + uneCase));
			break;
		}
		positionsRangeeVersLaGauche -= uneCase;
		positionsRangeeVersLeHaut += uneCase;
	}
}

void Fou::diagonaleHautDroite(Echiquier& e)
{
	int positionsRangeeVersLaDroite = position_.first;
	int positionsRangeeVersLeHaut = position_.second;

	while (positionsRangeeVersLaDroite < tailleEchiquierMax && positionsRangeeVersLeHaut < tailleEchiquierMax)
	{
		if ((e.cases[positionsRangeeVersLaDroite + uneCase][positionsRangeeVersLeHaut + uneCase] == caseVide))
			mouvementsDisponibles_.push_back(std::pair(positionsRangeeVersLaDroite + uneCase, positionsRangeeVersLeHaut + uneCase));

		else if ((e.cases[positionsRangeeVersLaDroite + uneCase][positionsRangeeVersLeHaut + uneCase]->obtenirCouleur() == estBlanc_))
			break;

		else
		{
			mouvementsDisponibles_.push_back(std::pair(positionsRangeeVersLaDroite + uneCase, positionsRangeeVersLeHaut + uneCase));
			break;
		}
		positionsRangeeVersLaDroite += uneCase;
		positionsRangeeVersLeHaut += uneCase;
	}
}

void Fou::diagonaleBasGauche(Echiquier& e)
{
	int positionsRangeeVersLaGauche = position_.first;
	int positionsRangeeVersLeBas = position_.second;

	while (positionsRangeeVersLaGauche > tailleEchiquierMin && positionsRangeeVersLeBas > tailleEchiquierMin)
	{
		if ((e.cases[positionsRangeeVersLaGauche - uneCase][positionsRangeeVersLeBas - uneCase] == caseVide))
			mouvementsDisponibles_.push_back(std::pair(positionsRangeeVersLaGauche - uneCase, positionsRangeeVersLeBas - uneCase));

		else if ((e.cases[positionsRangeeVersLaGauche - uneCase][positionsRangeeVersLeBas - uneCase]->obtenirCouleur() == estBlanc_))
			break;

		else
		{
			mouvementsDisponibles_.push_back(std::pair(positionsRangeeVersLaGauche - uneCase, positionsRangeeVersLeBas - uneCase));
			break;
		}
		positionsRangeeVersLaGauche -= uneCase;
		positionsRangeeVersLeBas -= uneCase;
	}
}

void Fou::diagonaleBasDroite(Echiquier& e)
{
	int positionsRangeeVersLaDroite = position_.first;
	int positionsRangeeVersLeBas = position_.second;

	while (positionsRangeeVersLaDroite < tailleEchiquierMax && positionsRangeeVersLeBas > tailleEchiquierMin)
	{
		if ((e.cases[positionsRangeeVersLaDroite + uneCase][positionsRangeeVersLeBas - uneCase] == caseVide))
			mouvementsDisponibles_.push_back(std::pair(positionsRangeeVersLaDroite + uneCase, positionsRangeeVersLeBas - uneCase));

		else if ((e.cases[positionsRangeeVersLaDroite + uneCase][positionsRangeeVersLeBas - uneCase]->obtenirCouleur() == estBlanc_))
			break;

		else
		{
			mouvementsDisponibles_.push_back(std::pair(positionsRangeeVersLaDroite + uneCase, positionsRangeeVersLeBas - uneCase));
			break;
		}
		positionsRangeeVersLaDroite += uneCase;
		positionsRangeeVersLeBas -= uneCase;
	}
}

void Fou::calculerMouvements(Echiquier e)
{
	mouvementsDisponibles_.clear();
	
	diagonaleHautGauche(e);
	diagonaleHautDroite(e);
	diagonaleBasGauche(e);
	diagonaleBasDroite(e);
}