#include "Pion.h"

static const int uneCase = 1;
static const int avancerDeuxCases = 2;
static const int avancerUneCase = 1;
static const int tailleEchiquierMin = 0;
static const int tailleEchiquierMax = 7;
static const Piece* caseVide = nullptr;

Pion::Pion(Echiquier& nouvelEchiquier, std::pair<int, int> position, bool estBlanc)
	: Piece(nouvelEchiquier, position, 'P', estBlanc)
{
	nouvelEchiquier.cases[position.first][position.second] = this;
}

void Pion::mouvementsPionBlanc(Echiquier& e)
{
	// si n'a pas bougé, il peut avancer de 2 cases vers l'avant
	if ((position_.second == uneCase) && (e.cases[position_.first][position_.second + avancerDeuxCases] == caseVide) && (e.cases[position_.first][position_.second + avancerUneCase] == caseVide))
		mouvementsDisponibles_.push_back(std::pair(position_.first, position_.second + avancerDeuxCases));

	// si la case d'en avant est disponible, il peut avancer d'une case
	if ((e.cases[position_.first][position_.second + uneCase] == caseVide))
		mouvementsDisponibles_.push_back(std::pair(position_.first, position_.second + uneCase));

	// si il peut manger une piece a droite, il peut avancer d'une case en diagonale
	if (position_.first < tailleEchiquierMax)
		if (e.cases[position_.first + uneCase][position_.second + uneCase] != caseVide
			&& e.cases[position_.first + uneCase][position_.second + uneCase]->obtenirCouleur() != estBlanc_)
			mouvementsDisponibles_.push_back(std::pair(position_.first + uneCase, position_.second + uneCase));


	// si il peut manger une piece a gauche, il peut avancer d'une case en diagonale
	if (position_.first > tailleEchiquierMin)
		if (e.cases[position_.first - uneCase][position_.second + uneCase] != caseVide
			&& e.cases[position_.first - uneCase][position_.second + uneCase]->obtenirCouleur() != estBlanc_)
			mouvementsDisponibles_.push_back(std::pair(position_.first - uneCase, position_.second + uneCase));
}

void Pion::mouvementsPionNoir(Echiquier& e)
{
	// si pion noir n'a pas bougé, il peut avancer de 2 cases vers l'avant
	if ((position_.second == tailleEchiquierMax - 1)
		&& (e.cases[position_.first][position_.second - avancerDeuxCases] == caseVide) && (e.cases[position_.first][position_.second - avancerUneCase] == caseVide))
		mouvementsDisponibles_.push_back(std::pair(position_.first, position_.second - avancerDeuxCases));

	// si la case d'en avant est disponible, il peut avancer d'une case
	if ((e.cases[position_.first][position_.second - uneCase] == caseVide))
		mouvementsDisponibles_.push_back(std::pair(position_.first, position_.second - uneCase));

	// si il peut manger une piece a droite, il peut avancer d'une case en diagonale
	if (position_.first > tailleEchiquierMin)
		if (e.cases[position_.first - uneCase][position_.second - uneCase] != caseVide
			&& e.cases[position_.first - uneCase][position_.second - uneCase]->obtenirCouleur() != estBlanc_)
			mouvementsDisponibles_.push_back(std::pair(position_.first - uneCase, position_.second - uneCase));

	// si il peut manger une piece a gauche, il peut avancer d'une case en diagonale
	if (position_.first < tailleEchiquierMax)
		if (e.cases[position_.first + uneCase][position_.second - uneCase] != caseVide
			&& e.cases[position_.first + uneCase][position_.second - uneCase]->obtenirCouleur() != estBlanc_)
			mouvementsDisponibles_.push_back(std::pair(position_.first + uneCase, position_.second - uneCase));
}

void Pion::calculerMouvements(Echiquier e)
{
	mouvementsDisponibles_.clear();

	if (estBlanc_)
		mouvementsPionBlanc(e);
	else
		mouvementsPionNoir(e);
}