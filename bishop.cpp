#include "classes.hpp"
static const int uneCase = 1;
static const int tailleEchiquierMin = 0;
static const int tailleEchiquierMax = 7;
static const Piece* caseVide = nullptr;
Fou::Fou(Echiquier& nouvelEchiquier, std::pair<int, int> position, bool estBlanc)
	: Piece(nouvelEchiquier, position, 'F', estBlanc)
{
	nouvelEchiquier.cases[position.first][position.second] = this;
}

void Fou::calculerMouvements(Echiquier e)
{
	mouvementsDisponibles_.clear();
	int positionsRangeeVersLaDroite = position_.first;	// nombre de position vides vers la droite
	int positionsRangeeVersLeHaut = position_.second;	// nombre de position vides vers le haut
	while (positionsRangeeVersLaDroite < tailleEchiquierMax && positionsRangeeVersLeHaut < tailleEchiquierMax)
	{
		if ((e.cases[positionsRangeeVersLaDroite + uneCase][positionsRangeeVersLeHaut + uneCase] == caseVide)) {
			mouvementsDisponibles_.push_back(std::pair(positionsRangeeVersLaDroite + uneCase, positionsRangeeVersLeHaut + uneCase));
		}

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


	int positionsRangeeVersLaGauche = position_.first; // nombre de position vides vers la gauche
	positionsRangeeVersLeHaut = position_.second; // nombre de position vides vers le haut
	while (positionsRangeeVersLaGauche > tailleEchiquierMin && positionsRangeeVersLeHaut < tailleEchiquierMax)
	{
		if ((e.cases[positionsRangeeVersLaGauche - uneCase][positionsRangeeVersLeHaut + uneCase] == caseVide)) {
			mouvementsDisponibles_.push_back(std::pair(positionsRangeeVersLaGauche - uneCase, positionsRangeeVersLeHaut + uneCase));
		}

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


	positionsRangeeVersLaGauche = position_.first; // nombre de position vides vers la droite
	int positionsRangeeVersLeBas = position_.second; // nombre de position vides vers le haut
	while (positionsRangeeVersLaGauche > tailleEchiquierMin && positionsRangeeVersLeBas > tailleEchiquierMin)
	{
		if ((e.cases[positionsRangeeVersLaGauche - uneCase][positionsRangeeVersLeBas - uneCase] == caseVide)) {
			mouvementsDisponibles_.push_back(std::pair(positionsRangeeVersLaGauche - uneCase, positionsRangeeVersLeBas - uneCase));
		}

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


	positionsRangeeVersLaDroite = position_.first; // nombre de position vides vers la droite
	positionsRangeeVersLeBas = position_.second; // nombre de position vides vers le haut
	while (positionsRangeeVersLaDroite < tailleEchiquierMax && positionsRangeeVersLeBas > tailleEchiquierMin)
	{
		if ((e.cases[positionsRangeeVersLaDroite + uneCase][positionsRangeeVersLeBas - uneCase] == caseVide)) {
			mouvementsDisponibles_.push_back(std::pair(positionsRangeeVersLaDroite + uneCase, positionsRangeeVersLeBas - uneCase));
		}

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