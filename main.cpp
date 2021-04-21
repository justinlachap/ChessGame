#include "ChessWindow.hpp"
#include <iostream>
#include "classes.hpp"
#include "gsl/span"
#include "cppitertools/range.hpp"
#include <stdexcept>

#include <QApplication>

#if __has_include("bibliotheque_cours.hpp")
#include "bibliotheque_cours.hpp"
#define BIBLIOTHEQUE_COURS_INCLUS
using bibliotheque_cours::cdbg;
#else
auto& cdbg = clog;
#endif

#if __has_include("verification_allocation.hpp")
#include "verification_allocation.hpp"
#include "debogage_memoire.hpp"  //NOTE: Incompatible avec le "placement new", ne pas utiliser cette entête si vous utilisez ce type de "new" dans les lignes qui suivent cette inclusion.
#endif

using namespace iter;
using namespace gsl;

static const int uneCase = 1;
static const int tailleEchiquierMin = 0;
static const int tailleEchiquierMax = 7;
static const Piece* caseVide = nullptr;

void Echiquier::initialiserVide()
{
	for (int i = 0; i <= tailleEchiquierMax; i++)
	{
		for (int j = 0; j <= tailleEchiquierMax; j++)
			cases[i][j] = nullptr;
	}
}

Piece::Piece(Echiquier& nouvelEchiquier, std::pair<int, int> position, char nom, bool estBlanc)
	: position_(position), nom_(nom), estBlanc_(estBlanc) {}

Pion::Pion(Echiquier& nouvelEchiquier, std::pair<int, int> position, bool estBlanc)
	: Piece(nouvelEchiquier, position, 'P', estBlanc)
{
	nouvelEchiquier.cases[position.first][position.second] = this;
}
Cavalier::Cavalier(Echiquier& nouvelEchiquier, std::pair<int, int> position, bool estBlanc)
	: Piece(nouvelEchiquier, position, 'C', estBlanc)
{
	nouvelEchiquier.cases[position.first][position.second] = this;
}
Fou::Fou(Echiquier& nouvelEchiquier, std::pair<int, int> position, bool estBlanc)
	: Piece(nouvelEchiquier, position, 'F', estBlanc)
{
	nouvelEchiquier.cases[position.first][position.second] = this;
}
Tour::Tour(Echiquier& nouvelEchiquier, std::pair<int, int> position, bool estBlanc)
	: Piece(nouvelEchiquier, position, 'T', estBlanc)
{
	nouvelEchiquier.cases[position.first][position.second] = this;
}
Dame::Dame(Echiquier& nouvelEchiquier, std::pair<int, int> position, bool estBlanc)
	: Tour(nouvelEchiquier, position, estBlanc), Fou(nouvelEchiquier, position, estBlanc), Piece(nouvelEchiquier, position, 'D', estBlanc)
{
	nouvelEchiquier.cases[position.first][position.second] = this;
}
Roi::Roi(Echiquier& nouvelEchiquier, std::pair<int, int> position, bool estBlanc)
	: Piece(nouvelEchiquier, position, 'R', estBlanc)
{	
	try
	{
		compteurInstances_++;
		if (compteurInstances_ > 2)
		{
			throw std::logic_error("Il ne peux pas y avoir plus de 2 rois sur l'échiquier");
		}
		nouvelEchiquier.cases[position.first][position.second] = this;
	}
	catch (std::logic_error& e)
	{
		std::cout << e.what() << std::endl
			<< "	Le roi a la position (" << obtenirPosition().first << ", " << obtenirPosition().second << ") a été détruit" << std::endl;
		delete this;
	}
};

void Piece::afficheMouvements() const
{
	std::cout << "Cette piece peut se deplacer aux cases: ";
	for (std::pair<int, int> m : mouvementsDisponibles_)
		std::cout << '(' << m.first << ", " << m.second << ") ";
	std::cout << std::endl;
}

void Pion::calculerMouvements(Echiquier e)
{
	int avancerDeuxCases = 2;
	// pion blanc
	if (estBlanc_)
	{
		// si n'a pas bougé, il peut avancer de 2 cases vers l'avant
		if ((position_.second == uneCase) && (e.cases[position_.first][position_.second + avancerDeuxCases] == caseVide))
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

	// pion noir
	else
	{
		// si pion noir n'a pas bougé, il peut avancer de 2 cases vers l'avant
		if ((position_.second == 6)
			&& (e.cases[position_.first][position_.second - avancerDeuxCases] == caseVide))
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
}
void Roi::calculerMouvements(Echiquier e)
{
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
void Fou::calculerMouvements(Echiquier e)
{
	int positionsRangeeVersLaDroite = position_.first;	// nombre de position vides vers la droite
	int positionsRangeeVersLeHaut = position_.second;	// nombre de position vides vers le haut
	while (positionsRangeeVersLaDroite < tailleEchiquierMax && positionsRangeeVersLeHaut < tailleEchiquierMax)
	{
		if ((e.cases[positionsRangeeVersLaDroite + uneCase][positionsRangeeVersLeHaut + uneCase] == caseVide)
			|| (e.cases[positionsRangeeVersLaDroite + uneCase][positionsRangeeVersLeHaut + uneCase]->obtenirCouleur() == estBlanc_))
			break;
		else
		{
			mouvementsDisponibles_.push_back(std::pair(positionsRangeeVersLaDroite + uneCase, positionsRangeeVersLeHaut + uneCase));
			if (e.cases[positionsRangeeVersLaDroite + uneCase][positionsRangeeVersLeHaut + uneCase]->obtenirCouleur() != estBlanc_ &&
				(e.cases[positionsRangeeVersLaDroite + uneCase][positionsRangeeVersLeHaut + uneCase] != caseVide))
				break;
		}
		positionsRangeeVersLaDroite += uneCase;
		positionsRangeeVersLeHaut += uneCase;
	}


	int positionsRangeeVersLaGauche = position_.first; // nombre de position vides vers la droite
	positionsRangeeVersLeHaut = position_.second; // nombre de position vides vers le haut
	while (positionsRangeeVersLaGauche > 0 && positionsRangeeVersLeHaut < tailleEchiquierMax)
	{
		if ((e.cases[positionsRangeeVersLaGauche - uneCase][positionsRangeeVersLeHaut + uneCase] == caseVide)
			|| (e.cases[positionsRangeeVersLaGauche - uneCase][positionsRangeeVersLeHaut + uneCase]->obtenirCouleur() == estBlanc_))
			break;
		else
		{
			mouvementsDisponibles_.push_back(std::pair(positionsRangeeVersLaGauche - uneCase, positionsRangeeVersLeHaut + uneCase));
			if (e.cases[positionsRangeeVersLaGauche - uneCase][positionsRangeeVersLeHaut + uneCase]->obtenirCouleur() != estBlanc_ &&
				(e.cases[positionsRangeeVersLaGauche - uneCase][positionsRangeeVersLeHaut + uneCase] != caseVide))
				break;
		}
		positionsRangeeVersLaGauche -= uneCase;
		positionsRangeeVersLeHaut += uneCase;
	}


	positionsRangeeVersLaGauche = position_.first; // nombre de position vides vers la droite
	int positionsRangeeVersLeBas = position_.second; // nombre de position vides vers le haut
	while (positionsRangeeVersLaGauche > 0 && positionsRangeeVersLeBas > 0)
	{
		if ((e.cases[positionsRangeeVersLaGauche - uneCase][positionsRangeeVersLeBas - uneCase] == caseVide)
			|| (e.cases[positionsRangeeVersLaGauche - uneCase][positionsRangeeVersLeBas - uneCase]->obtenirCouleur() == estBlanc_))
			break;
		else
		{
			mouvementsDisponibles_.push_back(std::pair(positionsRangeeVersLaGauche - uneCase, positionsRangeeVersLeBas - uneCase));
			if (e.cases[positionsRangeeVersLaGauche - uneCase][positionsRangeeVersLeBas - uneCase]->obtenirCouleur() != estBlanc_
				&& (e.cases[positionsRangeeVersLaGauche - uneCase][positionsRangeeVersLeBas - uneCase] != caseVide))
				break;
		}
		positionsRangeeVersLaGauche -= uneCase;
		positionsRangeeVersLeBas -= uneCase;
	}


	positionsRangeeVersLaDroite = position_.first; // nombre de position vides vers la droite
	positionsRangeeVersLeBas = position_.second; // nombre de position vides vers le haut
	while (positionsRangeeVersLaDroite < tailleEchiquierMax && positionsRangeeVersLeBas > 0)
	{
		if ((e.cases[positionsRangeeVersLaDroite + uneCase][positionsRangeeVersLeBas - uneCase] == caseVide)
			|| (e.cases[positionsRangeeVersLaDroite + uneCase][positionsRangeeVersLeBas - uneCase]->obtenirCouleur() == estBlanc_))
			break;
		else
		{
			mouvementsDisponibles_.push_back(std::pair(positionsRangeeVersLaDroite + uneCase, positionsRangeeVersLeBas - uneCase));
			if (e.cases[positionsRangeeVersLaDroite + uneCase][positionsRangeeVersLeBas - uneCase]->obtenirCouleur() != estBlanc_ &&
				(e.cases[positionsRangeeVersLaDroite + uneCase][positionsRangeeVersLeBas - uneCase] != caseVide))
				break;
		}
		positionsRangeeVersLaDroite += uneCase;
		positionsRangeeVersLeBas -= uneCase;
	}
}
void Dame::calculerMouvements(Echiquier e)
{
	Tour::calculerMouvements(e);
	Fou::calculerMouvements(e);
}

bool Roi::estEnÉchec(std::vector<std::pair<int, int>> mouvementsPiecesAdverses) {
	for (std::pair<int, int> mouvement : mouvementsPiecesAdverses) {
		if (mouvement == position_)
			return true;
	}
	return false;
};

void initialiserBibliothequeCours([[maybe_unused]] int argc, [[maybe_unused]] char* argv[])
{
#ifdef BIBLIOTHEQUE_COURS_INCLUS
	bibliotheque_cours::activerCouleursAnsi();  // Permet sous Windows les "ANSI escape code" pour changer de couleurs https://en.wikipedia.org/wiki/ANSI_escape_code ; les consoles Linux/Mac les supportent normalement par défaut.

	// cdbg.setTee(&clog);  // Décommenter cette ligne pour que cdbg affiche sur la console en plus de la "Sortie" du débogueur.

	bibliotheque_cours::executerGoogleTest(argc, argv); // Attention de ne rien afficher avant cette ligne, sinon l'Explorateur de tests va tenter de lire votre affichage comme un résultat de test.
#endif
//NOTE: C'est normal que la couverture de code dans l'Explorateur de tests de Visual Studio ne couvre pas la fin de cette fonction ni la fin du main après l'appel à cette fonction puisqu'il exécute uniquement les tests Google Test dans l'appel ci-dessus.
}

int main(int argc, char* argv[])
{
	bibliotheque_cours::VerifierFuitesAllocations verifierFuitesAllocations;
	QApplication app(argc, argv);
	initialiserBibliothequeCours(argc, argv);

	UI::ChessWindow chessWindow;
	chessWindow.resize(800, 800);
	chessWindow.show();

	
	return app.exec();
}
