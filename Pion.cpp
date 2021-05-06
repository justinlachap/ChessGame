#include "Pion.h"

static const int uneCase = 1;
static const int tailleEchiquierMin = 0;
static const int tailleEchiquierMax = 7;
static const Piece* caseVide = nullptr;

Pion::Pion(Echiquier& nouvelEchiquier, std::pair<int, int> position, bool estBlanc)
	: Piece(nouvelEchiquier, position, 'P', estBlanc)
{
	nouvelEchiquier.cases[position.first][position.second] = this;
}

void Pion::calculerMouvements(Echiquier e_)
{
	mouvementsDisponibles_.clear();
	int avancerDeuxCases = 2;
	int avancerUneCase = 1;
	// pion blanc
	if (estBlanc_)
	{
		// si n'a pas bougé, il peut avancer de 2 cases vers l'avant
		if ((position_.second == uneCase) && (e_.cases[position_.first][position_.second + avancerDeuxCases] == caseVide) && (e_.cases[position_.first][position_.second + avancerUneCase] == caseVide))
			mouvementsDisponibles_.push_back(std::pair(position_.first, position_.second + avancerDeuxCases));

		// si la case d'en avant est disponible, il peut avancer d'une case
		if ((e_.cases[position_.first][position_.second + uneCase] == caseVide))
			mouvementsDisponibles_.push_back(std::pair(position_.first, position_.second + uneCase));

		// si il peut manger une piece a droite, il peut avancer d'une case en diagonale
		if (position_.first < tailleEchiquierMax)
			if (e_.cases[position_.first + uneCase][position_.second + uneCase] != caseVide
				&& e_.cases[position_.first + uneCase][position_.second + uneCase]->obtenirCouleur() != estBlanc_)
				mouvementsDisponibles_.push_back(std::pair(position_.first + uneCase, position_.second + uneCase));


		// si il peut manger une piece a gauche, il peut avancer d'une case en diagonale
		if (position_.first > tailleEchiquierMin)
			if (e_.cases[position_.first - uneCase][position_.second + uneCase] != caseVide
				&& e_.cases[position_.first - uneCase][position_.second + uneCase]->obtenirCouleur() != estBlanc_)
				mouvementsDisponibles_.push_back(std::pair(position_.first - uneCase, position_.second + uneCase));
	}

	// pion noir
	else
	{
		// si pion noir n'a pas bougé, il peut avancer de 2 cases vers l'avant
		if ((position_.second == tailleEchiquierMax - 1)
			&& (e_.cases[position_.first][position_.second - avancerDeuxCases] == caseVide) && (e_.cases[position_.first][position_.second - avancerUneCase] == caseVide))
			mouvementsDisponibles_.push_back(std::pair(position_.first, position_.second - avancerDeuxCases));

		// si la case d'en avant est disponible, il peut avancer d'une case
		if ((e_.cases[position_.first][position_.second - uneCase] == caseVide))
			mouvementsDisponibles_.push_back(std::pair(position_.first, position_.second - uneCase));

		// si il peut manger une piece a droite, il peut avancer d'une case en diagonale
		if (position_.first > tailleEchiquierMin)
			if (e_.cases[position_.first - uneCase][position_.second - uneCase] != caseVide
				&& e_.cases[position_.first - uneCase][position_.second - uneCase]->obtenirCouleur() != estBlanc_)
				mouvementsDisponibles_.push_back(std::pair(position_.first - uneCase, position_.second - uneCase));

		// si il peut manger une piece a gauche, il peut avancer d'une case en diagonale
		if (position_.first < tailleEchiquierMax)
			if (e_.cases[position_.first + uneCase][position_.second - uneCase] != caseVide
				&& e_.cases[position_.first + uneCase][position_.second - uneCase]->obtenirCouleur() != estBlanc_)
				mouvementsDisponibles_.push_back(std::pair(position_.first + uneCase, position_.second - uneCase));
	}
}