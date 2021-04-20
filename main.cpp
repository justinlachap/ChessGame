#include "ChessWindow.hpp"
#include <iostream>
#include "classes.hpp"
#include "gsl/span"
#include "cppitertools/range.hpp"

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

static const int UNE_CASE = 1;
static const int TAILLE_ECHIQUIER_MIN = 0;
static const int TAILLE_ECHIQUIER_MAX = 7;
static const Piece* CASE_VIDE = nullptr;

void Echiquier::initialiserVide()
{
	for (int i = 0; i <= TAILLE_ECHIQUIER_MAX; i++)
	{
		for (int j = 0; j <= TAILLE_ECHIQUIER_MAX; j++)
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
	nouvelEchiquier.cases[position.first][position.second] = this;
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
		if ((position_.second == UNE_CASE) && (e.cases[position_.first][position_.second + avancerDeuxCases] == CASE_VIDE))
			mouvementsDisponibles_.push_back(std::pair(position_.first, position_.second + avancerDeuxCases));

		// si la case d'en avant est disponible, il peut avancer d'une case
		if ((e.cases[position_.first][position_.second + UNE_CASE] == CASE_VIDE))
			mouvementsDisponibles_.push_back(std::pair(position_.first, position_.second + UNE_CASE));

		// si il peut manger une piece a droite, il peut avancer d'une case en diagonale
		if (e.cases[position_.first + UNE_CASE][position_.second + UNE_CASE] != CASE_VIDE
			&& e.cases[position_.first + UNE_CASE][position_.second + UNE_CASE]->obtenirCouleur() != this->estBlanc_
			&& (position_.first != TAILLE_ECHIQUIER_MAX))
			mouvementsDisponibles_.push_back(std::pair(position_.first + UNE_CASE, position_.second + UNE_CASE));

		// si il peut manger une piece a gauche, il peut avancer d'une case en diagonale
		if (e.cases[position_.first - UNE_CASE][position_.second + UNE_CASE] != CASE_VIDE
			&& e.cases[position_.first - UNE_CASE][position_.second + UNE_CASE]->obtenirCouleur() != this->estBlanc_
			&& (position_.first != TAILLE_ECHIQUIER_MIN))
			mouvementsDisponibles_.push_back(std::pair(position_.first - UNE_CASE, position_.second + UNE_CASE));
	}

	// pion noir
	else
	{
		// si pion noir n'a pas bougé, il peut avancer de 2 cases vers l'avant
		if ((position_.second == 6)
			&& (e.cases[position_.first][position_.second - avancerDeuxCases] == CASE_VIDE))
			mouvementsDisponibles_.push_back(std::pair(position_.first, position_.second - avancerDeuxCases));

		// si la case d'en avant est disponible, il peut avancer d'une case
		if ((e.cases[position_.first][position_.second - UNE_CASE] == CASE_VIDE))
			mouvementsDisponibles_.push_back(std::pair(position_.first, position_.second - UNE_CASE));

		// si il peut manger une piece a droite, il peut avancer d'une case en diagonale
		if (e.cases[position_.first - UNE_CASE][position_.second - UNE_CASE] != CASE_VIDE
			&& e.cases[position_.first - UNE_CASE][position_.second - UNE_CASE]->obtenirCouleur() != this->estBlanc_
			&& (position_.first != TAILLE_ECHIQUIER_MIN))
			mouvementsDisponibles_.push_back(std::pair(position_.first - UNE_CASE, position_.second - UNE_CASE));

		// si il peut manger une piece a gauche, il peut avancer d'une case en diagonale
		if (e.cases[position_.first + UNE_CASE][position_.second - UNE_CASE] != CASE_VIDE
			&& e.cases[position_.first + UNE_CASE][position_.second - UNE_CASE]->obtenirCouleur() != this->estBlanc_
			&& (position_.first != TAILLE_ECHIQUIER_MAX))
			mouvementsDisponibles_.push_back(std::pair(position_.first + UNE_CASE, position_.second - UNE_CASE));
	}
}

void Roi::calculerMouvements(Echiquier e)
{
	// vers la droite
	if (((e.cases[position_.first + UNE_CASE][position_.second] == CASE_VIDE)
		|| e.cases[position_.first + UNE_CASE][position_.second]->obtenirCouleur() != this->estBlanc_)
		&& (position_.first != TAILLE_ECHIQUIER_MAX))
		mouvementsDisponibles_.push_back(std::pair(position_.first + UNE_CASE, position_.second));

	// vers la gauche
	if (((e.cases[position_.first - UNE_CASE][position_.second] == CASE_VIDE)
		|| e.cases[position_.first - UNE_CASE][position_.second]->obtenirCouleur() != this->estBlanc_)
		&& (position_.first != TAILLE_ECHIQUIER_MIN))
		mouvementsDisponibles_.push_back(std::pair(position_.first - UNE_CASE, position_.second));

	// vers le haut
	if (((e.cases[position_.first][position_.second + UNE_CASE] == CASE_VIDE)
		|| e.cases[position_.first][position_.second + UNE_CASE]->obtenirCouleur() != this->estBlanc_)
		&& (position_.second != TAILLE_ECHIQUIER_MAX))
		mouvementsDisponibles_.push_back(std::pair(position_.first, position_.second + UNE_CASE));

	// vers le bas
	if (((e.cases[position_.first][position_.second - UNE_CASE] == CASE_VIDE)
		|| e.cases[position_.first][position_.second - UNE_CASE]->obtenirCouleur() != this->estBlanc_)
		&& (position_.second != TAILLE_ECHIQUIER_MIN))
		mouvementsDisponibles_.push_back(std::pair(position_.first, position_.second - UNE_CASE));

	// droite-haut
	if (((e.cases[position_.first + UNE_CASE][position_.second + UNE_CASE] == CASE_VIDE)
		|| (e.cases[position_.first + UNE_CASE][position_.second + UNE_CASE]->obtenirCouleur() != this->estBlanc_))
		&& ((position_.second != TAILLE_ECHIQUIER_MAX) && (position_.first != TAILLE_ECHIQUIER_MAX)))
		mouvementsDisponibles_.push_back(std::pair(position_.first + UNE_CASE, position_.second + UNE_CASE));

	// gauche-haut
	if (((e.cases[position_.first - UNE_CASE][position_.second + UNE_CASE] == CASE_VIDE)
		|| (e.cases[position_.first - UNE_CASE][position_.second + UNE_CASE]->obtenirCouleur() != this->estBlanc_))
		&& ((position_.second != TAILLE_ECHIQUIER_MAX) && (position_.first != TAILLE_ECHIQUIER_MIN)))
		mouvementsDisponibles_.push_back(std::pair(position_.first - UNE_CASE, position_.second + UNE_CASE));

	// droite-bas
	if (((e.cases[position_.first + UNE_CASE][position_.second - UNE_CASE] == CASE_VIDE)
		|| (e.cases[position_.first + UNE_CASE][position_.second - UNE_CASE]->obtenirCouleur() != this->estBlanc_))
		&& ((position_.second != TAILLE_ECHIQUIER_MIN) && (position_.first != TAILLE_ECHIQUIER_MAX)))
		mouvementsDisponibles_.push_back(std::pair(position_.first + UNE_CASE, position_.second - UNE_CASE));

	//mouvement gauche-bas
	if (((e.cases[position_.first - UNE_CASE][position_.second - UNE_CASE] == CASE_VIDE)
		|| (e.cases[position_.first - UNE_CASE][position_.second - UNE_CASE]->obtenirCouleur() != this->estBlanc_))
		&& ((position_.second != TAILLE_ECHIQUIER_MIN) && (position_.first != TAILLE_ECHIQUIER_MIN)))
		mouvementsDisponibles_.push_back(std::pair(position_.first - UNE_CASE, position_.second - UNE_CASE));
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
		if (x >= 0 && x <= TAILLE_ECHIQUIER_MAX && y >= 0 && y <= TAILLE_ECHIQUIER_MAX) {
			if (e.cases[x][y] == CASE_VIDE || (e.cases[x][y]->obtenirCouleur() != this->estBlanc_))
				mouvementsDisponibles_.push_back(std::pair(x, y));
		}
	}
};

void Tour::calculerMouvements(Echiquier e)
{
	// nombre de position vides vers la droite
	for (int positionsRangeeVersLaDroite : iter::range(position_.first, TAILLE_ECHIQUIER_MAX))
	{
		if (e.cases[positionsRangeeVersLaDroite + UNE_CASE][position_.second] != CASE_VIDE)
		{
			if (e.cases[positionsRangeeVersLaDroite + UNE_CASE][position_.second]->obtenirCouleur() != this->estBlanc_)
				mouvementsDisponibles_.push_back(std::pair(positionsRangeeVersLaDroite + UNE_CASE, position_.second));
			break;
		}
		if (e.cases[positionsRangeeVersLaDroite + UNE_CASE][position_.second] == CASE_VIDE)
			mouvementsDisponibles_.push_back(std::pair(positionsRangeeVersLaDroite + UNE_CASE, position_.second));
	}

	// nombre de position vides vers la gauche
	for (int positionsRangeeVersLaGauche : iter::range(position_.first, 0, -UNE_CASE))
	{
		if (e.cases[positionsRangeeVersLaGauche - UNE_CASE][position_.second] != CASE_VIDE)
		{
			if (e.cases[positionsRangeeVersLaGauche - UNE_CASE][position_.second]->obtenirCouleur() != this->estBlanc_)
				mouvementsDisponibles_.push_back(std::pair(positionsRangeeVersLaGauche - UNE_CASE, position_.second));
			break;
		};
		if (e.cases[positionsRangeeVersLaGauche - UNE_CASE][position_.second] == CASE_VIDE)
			mouvementsDisponibles_.push_back(std::pair(positionsRangeeVersLaGauche - UNE_CASE, position_.second));
	}

	// nombre de position vides vers le haut
	for (int positionsRangeeVersLeHaut : iter::range(position_.second, TAILLE_ECHIQUIER_MAX))
	{
		if (e.cases[position_.first][positionsRangeeVersLeHaut + UNE_CASE] != CASE_VIDE)
		{
			if (e.cases[position_.first][positionsRangeeVersLeHaut + UNE_CASE]->obtenirCouleur() != this->estBlanc_)
				mouvementsDisponibles_.push_back(std::pair(position_.first, positionsRangeeVersLeHaut + UNE_CASE));
			break;
		}
		if (e.cases[position_.first][positionsRangeeVersLeHaut + UNE_CASE] == CASE_VIDE)
			mouvementsDisponibles_.push_back(std::pair(position_.first, positionsRangeeVersLeHaut + UNE_CASE));
	}

	// nombre de position vides vers le bas
	for (int positionsRangeeVersLeBas : iter::range(position_.second, 0, -UNE_CASE))
	{
		if (e.cases[position_.first][positionsRangeeVersLeBas - UNE_CASE] != CASE_VIDE)
		{
			if (e.cases[position_.first][positionsRangeeVersLeBas - UNE_CASE]->obtenirCouleur() != this->estBlanc_)
				mouvementsDisponibles_.push_back(std::pair(position_.first, positionsRangeeVersLeBas - UNE_CASE));
			break;
		}
		if (e.cases[position_.first][positionsRangeeVersLeBas - UNE_CASE] == CASE_VIDE)
			mouvementsDisponibles_.push_back(std::pair(position_.first, positionsRangeeVersLeBas - UNE_CASE));
	}
};

void Fou::calculerMouvements(Echiquier e)
{
	// nombre de position vides vers la droite
	int positionsRangeeVersLaDroite = position_.first;
	// nombre de position vides vers le haut
	int positionsRangeeVersLeHaut = position_.second;
	while (positionsRangeeVersLaDroite < TAILLE_ECHIQUIER_MAX && positionsRangeeVersLeHaut < TAILLE_ECHIQUIER_MAX)
	{
		if (e.cases[positionsRangeeVersLaDroite + UNE_CASE][positionsRangeeVersLeHaut + UNE_CASE]->obtenirCouleur() == this->estBlanc_)
			break;
		else
		{
			mouvementsDisponibles_.push_back(std::pair(positionsRangeeVersLaDroite + UNE_CASE, positionsRangeeVersLeHaut + UNE_CASE));
			if (e.cases[positionsRangeeVersLaDroite + UNE_CASE][positionsRangeeVersLeHaut + UNE_CASE]->obtenirCouleur() != this->estBlanc_ &&
				(e.cases[positionsRangeeVersLaDroite + UNE_CASE][positionsRangeeVersLeHaut + UNE_CASE] != CASE_VIDE))
				break;
		}
		positionsRangeeVersLaDroite += UNE_CASE;
		positionsRangeeVersLeHaut += UNE_CASE;
	}


	int positionsRangeeVersLaGauche = position_.first; // nombre de position vides vers la droite
	positionsRangeeVersLeHaut = position_.second; // nombre de position vides vers le haut

	while (positionsRangeeVersLaGauche > 0 and positionsRangeeVersLeHaut < TAILLE_ECHIQUIER_MAX)
	{
		if (e.cases[positionsRangeeVersLaGauche - UNE_CASE][positionsRangeeVersLeHaut + UNE_CASE]->obtenirCouleur() == this->estBlanc_)
			break;
		else
		{
			mouvementsDisponibles_.push_back(std::pair(positionsRangeeVersLaGauche - UNE_CASE, positionsRangeeVersLeHaut + UNE_CASE));
			if (e.cases[positionsRangeeVersLaGauche - UNE_CASE][positionsRangeeVersLeHaut + UNE_CASE]->obtenirCouleur() != this->estBlanc_ &&
				(e.cases[positionsRangeeVersLaGauche - UNE_CASE][positionsRangeeVersLeHaut + UNE_CASE] != CASE_VIDE))
				break;
		}
		positionsRangeeVersLaGauche -= UNE_CASE;
		positionsRangeeVersLeHaut += UNE_CASE;
	}


	positionsRangeeVersLaGauche = position_.first; // nombre de position vides vers la droite
	int positionsRangeeVersLeBas = position_.second; // nombre de position vides vers le haut

	while (positionsRangeeVersLaGauche > 0 && positionsRangeeVersLeBas > 0)
	{
		if (e.cases[positionsRangeeVersLaGauche - UNE_CASE][positionsRangeeVersLeBas - UNE_CASE]->obtenirCouleur() == this->estBlanc_)
			break;
		else
		{
			mouvementsDisponibles_.push_back(std::pair(positionsRangeeVersLaGauche - UNE_CASE, positionsRangeeVersLeBas - UNE_CASE));
			if (e.cases[positionsRangeeVersLaGauche - UNE_CASE][positionsRangeeVersLeBas - UNE_CASE]->obtenirCouleur() != this->estBlanc_
				&& (e.cases[positionsRangeeVersLaGauche - UNE_CASE][positionsRangeeVersLeBas - UNE_CASE] != CASE_VIDE))
				break;
		}
		positionsRangeeVersLaGauche -= UNE_CASE;
		positionsRangeeVersLeBas -= UNE_CASE;
	}


	positionsRangeeVersLaDroite = position_.first; // nombre de position vides vers la droite
	positionsRangeeVersLeBas = position_.second; // nombre de position vides vers le haut

	while (positionsRangeeVersLaDroite < TAILLE_ECHIQUIER_MAX && positionsRangeeVersLeBas > 0)
	{
		if (e.cases[positionsRangeeVersLaDroite + UNE_CASE][positionsRangeeVersLeBas - UNE_CASE]->obtenirCouleur() == this->estBlanc_)
			break;
		else
		{
			mouvementsDisponibles_.push_back(std::pair(positionsRangeeVersLaDroite + UNE_CASE, positionsRangeeVersLeBas - UNE_CASE));
			if (e.cases[positionsRangeeVersLaDroite + UNE_CASE][positionsRangeeVersLeBas - UNE_CASE]->obtenirCouleur() != this->estBlanc_ &&
				(e.cases[positionsRangeeVersLaDroite + UNE_CASE][positionsRangeeVersLeBas - UNE_CASE] != CASE_VIDE))
				break;
		}
		positionsRangeeVersLaDroite += UNE_CASE;
		positionsRangeeVersLeBas -= UNE_CASE;
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
