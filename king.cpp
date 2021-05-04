#include "classes.hpp"
#include <iostream>
static const int uneCase = 1;
static const int tailleEchiquierMin = 0;
static const int tailleEchiquierMax = 7;
static const Piece* caseVide = nullptr;
Roi::Roi(Echiquier& nouvelEchiquier, std::pair<int, int> position, bool estBlanc)
	: Piece(nouvelEchiquier, position, 'R', estBlanc)
{
	try
	{
		compteurInstances_++;
		if (compteurInstances_ > 2)
		{
			throw std::logic_error("Il ne peux pas y avoir plus de 2 rois sur l'Èchiquier");
		}
		nouvelEchiquier.cases[position.first][position.second] = this;
	}
	catch (std::logic_error& e)
	{
		std::cout << e.what() << std::endl
			<< "	Le roi a la position (" << obtenirPosition().first << ", " << obtenirPosition().second << ") a ÈtÈ dÈtruit" << std::endl;
		delete this;
	}
};




void Roi::calculerMouvements(Echiquier e)
{
	mouvementsDisponibles_.clear();
	// vers la droite
	if (position_.first < tailleEchiquierMax)
		if (((e.cases[position_.first + uneCase][position_.second] == caseVide)
			|| e.cases[position_.first + uneCase][position_.second]->obtenirCouleur() != estBlanc_))
			mouvementsDisponibles_.push_back(std::pair(position_.first + uneCase, position_.second));

	// vers la gauche
	if (position_.first > tailleEchiquierMin)
		if (((e.cases[position_.first - uneCase][position_.second] == caseVide)
			|| e.cases[position_.first - uneCase][position_.second]->obtenirCouleur() != estBlanc_))
			mouvementsDisponibles_.push_back(std::pair(position_.first - uneCase, position_.second));

	// vers le haut
	if (position_.second < tailleEchiquierMax)
		if (((e.cases[position_.first][position_.second + uneCase] == caseVide)
			|| e.cases[position_.first][position_.second + uneCase]->obtenirCouleur() != estBlanc_))
			mouvementsDisponibles_.push_back(std::pair(position_.first, position_.second + uneCase));

	// vers le bas
	if (position_.second > tailleEchiquierMin)
		if (((e.cases[position_.first][position_.second - uneCase] == caseVide)
			|| e.cases[position_.first][position_.second - uneCase]->obtenirCouleur() != estBlanc_))
			mouvementsDisponibles_.push_back(std::pair(position_.first, position_.second - uneCase));

	// droite-haut
	if (position_.second < tailleEchiquierMax && position_.first < tailleEchiquierMax)
		if (((e.cases[position_.first + uneCase][position_.second + uneCase] == caseVide)
			|| (e.cases[position_.first + uneCase][position_.second + uneCase]->obtenirCouleur() != estBlanc_)))
			mouvementsDisponibles_.push_back(std::pair(position_.first + uneCase, position_.second + uneCase));

	// gauche-haut
	if (position_.second < tailleEchiquierMax && position_.first > tailleEchiquierMin)
		if (((e.cases[position_.first - uneCase][position_.second + uneCase] == caseVide)
			|| (e.cases[position_.first - uneCase][position_.second + uneCase]->obtenirCouleur() != estBlanc_))
			&& ((position_.second != tailleEchiquierMax) && (position_.first != tailleEchiquierMin)))
			mouvementsDisponibles_.push_back(std::pair(position_.first - uneCase, position_.second + uneCase));

	// droite-bas
	if (position_.second > tailleEchiquierMin && position_.first < tailleEchiquierMax)
		if (((e.cases[position_.first + uneCase][position_.second - uneCase] == caseVide)
			|| (e.cases[position_.first + uneCase][position_.second - uneCase]->obtenirCouleur() != estBlanc_)))
			mouvementsDisponibles_.push_back(std::pair(position_.first + uneCase, position_.second - uneCase));

	//mouvement gauche-bas
	if (position_.second > tailleEchiquierMin && position_.first > tailleEchiquierMin)
		if (((e.cases[position_.first - uneCase][position_.second - uneCase] == caseVide)
			|| (e.cases[position_.first - uneCase][position_.second - uneCase]->obtenirCouleur() != estBlanc_)))
			mouvementsDisponibles_.push_back(std::pair(position_.first - uneCase, position_.second - uneCase));
};





bool Roi::estEn…chec(std::vector<std::pair<int, int>> mouvementsPiecesAdverses) {
	for (std::pair<int, int> mouvement : mouvementsPiecesAdverses) {
		if (mouvement == position_)
			return true;
	}
	return false;
};