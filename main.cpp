#include "Calc.hpp"
#include "CalcWindow.hpp"
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

int conversionIntLimite(int caseEchiquier) // Cette fonction sera souvent comparée avec la fonction conversionCouleurInt(), pour déterminer si 2 pièces ont la même couleur.
{
	if ((caseEchiquier <= 6) && (caseEchiquier != 0))
	{
		int blanc = 6;
		return blanc;
	}
	else if (caseEchiquier > 6)
	{
		int noir = 7;
		return noir;
	}
	else
	{
		int none = 0;
		return none;
	}
};

void Echiquier::initialiserVide()
{
	for (int i = 0; i < 8; i++)
	{
		for (int j = 0; j < 8; j++)
			cases[i][j] = 0;
	}
}

Piece::Piece(Echiquier& nouvelEchiquier, std::pair<int, int> position, bool estBlanc)
{
	position_ = position;
	estBlanc_ = estBlanc;
}
Dame::Dame(Echiquier& nouvelEchiquier, std::pair<int, int> position, bool estBlanc)
	: Piece(nouvelEchiquier, position, estBlanc)
{
	nouvelEchiquier.cases[position.first][position.second] = (estBlanc) ? dameBlanc_ : dameNoir_;
}
Cavalier::Cavalier(Echiquier& nouvelEchiquier, std::pair<int, int> position, bool estBlanc)
	: Piece(nouvelEchiquier, position, estBlanc)
{
	nouvelEchiquier.cases[position.first][position.second] = (estBlanc) ? cavalierBlanc_ : cavalierNoir_;
}

Fou::Fou(Echiquier& nouvelEchiquier, std::pair<int, int> position, bool estBlanc)
	: Piece(nouvelEchiquier, position, estBlanc)
{
	nouvelEchiquier.cases[position.first][position.second] = (estBlanc) ? fouBlanc_ : fouNoir_;
}
Pion::Pion(Echiquier& nouvelEchiquier, std::pair<int, int> position, bool estBlanc)
	: Piece(nouvelEchiquier, position, estBlanc)
{
	nouvelEchiquier.cases[position.first][position.second] = (estBlanc) ? pionBlanc_ : pionNoir_;
}
Roi::Roi(Echiquier& nouvelEchiquier, std::pair<int, int> position, bool estBlanc)
	: Piece(nouvelEchiquier, position, estBlanc)
{
	nouvelEchiquier.cases[position.first][position.second] = (estBlanc) ? roiBlanc_ : roiNoir_;
};
Tour::Tour(Echiquier& nouvelEchiquier, std::pair<int, int> position, bool estBlanc)
	: Piece(nouvelEchiquier, position, estBlanc)
{
	nouvelEchiquier.cases[position.first][position.second] = (estBlanc) ? tourBlanc_ : tourNoir_;
}


int Piece::conversionCouleurInt() const
{
	int blanc = 6, noir = 7;
	int delimiteur = (estBlanc_) ? blanc : noir;
	return delimiteur;
}

void Piece::afficheMouvements()
{
	std::cout << "Cette piece peut se deplacer aux cases: ";
	for (std::pair<int, int> m : mouvementsDisponibles_)
		std::cout << '(' << m.first << ", " << m.second << ") ";
	std::cout << std::endl;
}

int uneCase = 1;
int tailleEchiquier = 7;

void Pion::calculeMouvements(Echiquier e)
{
	
	int avancerDeuxCases = 2;
	// pion blanc
	if (estBlanc_)
	{
		// si n'a pas bougé, il peut avancer de 2 cases vers l'avant
		if ((position_.second == uneCase) && (e.cases[position_.first][position_.second + avancerDeuxCases] == 0))
			mouvementsDisponibles_.push_back(std::make_pair(position_.first, position_.second + avancerDeuxCases));

		// si la case d'en avant est disponible, il peut avancer d'une case
		if ((e.cases[position_.first][position_.second + uneCase] == 0))
			mouvementsDisponibles_.push_back(std::make_pair(position_.first, position_.second + uneCase));

		// si il peut manger une piece a droite, il peut avancer d'une case en diagonale
		if (conversionIntLimite(e.cases[position_.first + uneCase][position_.second + uneCase]) != conversionCouleurInt()
			&& conversionIntLimite(e.cases[position_.first + uneCase][position_.second + uneCase]) != 0
			&& (position_.first != tailleEchiquier))
			mouvementsDisponibles_.push_back(std::make_pair(position_.first + uneCase, position_.second + uneCase));

		// si il peut manger une piece a gauche, il peut avancer d'une case en diagonale
		if (conversionIntLimite(e.cases[position_.first - uneCase][position_.second + uneCase]) != conversionCouleurInt()
			&& conversionIntLimite(e.cases[position_.first - uneCase][position_.second + uneCase]) != 0
			&& (position_.first != 0))
			mouvementsDisponibles_.push_back(std::make_pair(position_.first - uneCase, position_.second + uneCase));
	}

	// pion noir
	else
	{
		// si pion noir n'a pas bougé, il peut avancer de 2 cases vers l'avant
		if ((position_.second == 6)
			&& (e.cases[position_.first][position_.second - avancerDeuxCases] == 0))
			mouvementsDisponibles_.push_back(std::make_pair(position_.first, position_.second - avancerDeuxCases));

		// si la case d'en avant est disponible, il peut avancer d'une case
		if ((e.cases[position_.first][position_.second - uneCase] == 0))
			mouvementsDisponibles_.push_back(std::make_pair(position_.first, position_.second - uneCase));

		// si il peut manger une piece a droite, il peut avancer d'une case en diagonale
		if (conversionIntLimite(e.cases[position_.first - uneCase][position_.second - uneCase]) != conversionCouleurInt()
			&& conversionIntLimite(e.cases[position_.first - uneCase][position_.second - uneCase]) != 0
			&& (position_.first != 0))
			mouvementsDisponibles_.push_back(std::make_pair(position_.first - uneCase, position_.second - uneCase));

		// si il peut manger une piece a gauche, il peut avancer d'une case en diagonale
		if (conversionIntLimite(e.cases[position_.first + uneCase][position_.second - uneCase]) != conversionCouleurInt()
			&& conversionIntLimite(e.cases[position_.first + uneCase][position_.second - uneCase]) != 0
			&& (position_.first != tailleEchiquier))
			mouvementsDisponibles_.push_back(std::make_pair(position_.first + uneCase, position_.second - uneCase));
	}
}

void Roi::calculeMouvements(Echiquier e)
{
	// vers la droite
	if (((e.cases[position_.first + uneCase][position_.second] == 0)
		|| conversionIntLimite(e.cases[position_.first + uneCase][position_.second]) != conversionCouleurInt())
		&& (position_.first != tailleEchiquier))
		mouvementsDisponibles_.push_back(std::make_pair(position_.first + uneCase, position_.second));

	// vers la gauche
	if (((e.cases[position_.first - uneCase][position_.second] == 0)
		|| conversionIntLimite(e.cases[position_.first - uneCase][position_.second]) != conversionCouleurInt())
		&& (position_.first != 0))
		mouvementsDisponibles_.push_back(std::make_pair(position_.first - uneCase, position_.second));

	// vers le haut
	if (((e.cases[position_.first][position_.second + uneCase] == 0)
		|| conversionIntLimite(e.cases[position_.first][position_.second + uneCase]) != conversionCouleurInt()) && (position_.second != tailleEchiquier))
		mouvementsDisponibles_.push_back(std::make_pair(position_.first, position_.second + uneCase));

	// vers le bas
	if (((e.cases[position_.first][position_.second - uneCase] == 0)
		|| conversionIntLimite(e.cases[position_.first][position_.second - uneCase]) != conversionCouleurInt())
		&& (position_.second != 0))
		mouvementsDisponibles_.push_back(std::make_pair(position_.first, position_.second - uneCase));

	// droite-haut
	if (((e.cases[position_.first + uneCase][position_.second + uneCase] == 0)
		|| (conversionIntLimite(e.cases[position_.first + uneCase][position_.second + uneCase]) != conversionCouleurInt()))
		&& ((position_.second != tailleEchiquier) && (position_.first != tailleEchiquier)))
		mouvementsDisponibles_.push_back(std::make_pair(position_.first + uneCase, position_.second + uneCase));

	// gauche-haut
	if (((e.cases[position_.first - uneCase][position_.second + uneCase] == 0)
		|| (conversionIntLimite(e.cases[position_.first - uneCase][position_.second + uneCase]) != conversionCouleurInt()))
		&& ((position_.second != tailleEchiquier) && (position_.first != 0)))
		mouvementsDisponibles_.push_back(std::make_pair(position_.first - uneCase, position_.second + uneCase));

	// droite-bas
	if (((e.cases[position_.first + uneCase][position_.second - uneCase] == 0)
		|| (conversionIntLimite(e.cases[position_.first + uneCase][position_.second - uneCase]) != conversionCouleurInt()))
		&& ((position_.second != 0) && (position_.first != tailleEchiquier)))
		mouvementsDisponibles_.push_back(std::make_pair(position_.first + uneCase, position_.second - uneCase));

	//mouvement gauche-bas
	if (((e.cases[position_.first - uneCase][position_.second - uneCase] == 0)
		|| (conversionIntLimite(e.cases[position_.first - uneCase][position_.second - uneCase]) != conversionCouleurInt()))
		&& ((position_.second != 0) && (position_.first != 0)))
		mouvementsDisponibles_.push_back(std::make_pair(position_.first - uneCase, position_.second - uneCase));
};

void Tour::calculeMouvements(Echiquier e)
{
	// nombre de position vides vers la droite
	for (int positionsRangeeVersLaDroite : iter::range(position_.first, tailleEchiquier))
	{
		if (e.cases[positionsRangeeVersLaDroite + uneCase][position_.second] != 0)
		{
			if (conversionIntLimite(e.cases[positionsRangeeVersLaDroite + uneCase][position_.second]) != conversionCouleurInt())
				mouvementsDisponibles_.push_back(std::make_pair(positionsRangeeVersLaDroite + uneCase, position_.second));
			break;
		}
		if (e.cases[positionsRangeeVersLaDroite + uneCase][position_.second] == 0)
			mouvementsDisponibles_.push_back(std::make_pair(positionsRangeeVersLaDroite + uneCase, position_.second));
	}

	// nombre de position vides vers la gauche
	for (int positionsRangeeVersLaGauche : iter::range(position_.first, 0, -uneCase))
	{
		if (e.cases[positionsRangeeVersLaGauche - uneCase][position_.second] != 0)
		{
			if (conversionIntLimite(e.cases[positionsRangeeVersLaGauche - uneCase][position_.second]) != conversionCouleurInt())
				mouvementsDisponibles_.push_back(std::make_pair(positionsRangeeVersLaGauche - uneCase, position_.second));
			break;
		};
		if (e.cases[positionsRangeeVersLaGauche - uneCase][position_.second] == 0)
			mouvementsDisponibles_.push_back(std::make_pair(positionsRangeeVersLaGauche - uneCase, position_.second));
	}

	// nombre de position vides vers le haut
	for (int positionsRangeeVersLeHaut : iter::range(position_.second, tailleEchiquier))
	{
		if (e.cases[position_.first][positionsRangeeVersLeHaut + uneCase] != 0)
		{
			if (conversionIntLimite(e.cases[position_.first][positionsRangeeVersLeHaut + uneCase]) != conversionCouleurInt())
				mouvementsDisponibles_.push_back(std::make_pair(position_.first, positionsRangeeVersLeHaut + uneCase));
			break;
		}
		if (e.cases[position_.first][positionsRangeeVersLeHaut + uneCase] == 0)
			mouvementsDisponibles_.push_back(std::make_pair(position_.first, positionsRangeeVersLeHaut + uneCase));
	}

	// nombre de position vides vers le bas
	for (int positionsRangeeVersLeBas : iter::range(position_.second, 0, -uneCase))
	{
		if (e.cases[position_.first][positionsRangeeVersLeBas - uneCase] != 0)
		{
			if (conversionIntLimite(e.cases[position_.first][positionsRangeeVersLeBas - uneCase]) != conversionCouleurInt())
				mouvementsDisponibles_.push_back(std::make_pair(position_.first, positionsRangeeVersLeBas - uneCase));
			break;
		}
		if (e.cases[position_.first][positionsRangeeVersLeBas - uneCase] == 0)
			mouvementsDisponibles_.push_back(std::make_pair(position_.first, positionsRangeeVersLeBas - uneCase));
	}
};

void Fou::calculeMouvements(Echiquier e)
{
	// nombre de position vides vers la droite
	int positionsRangeeVersLaDroite = position_.first;
	// nombre de position vides vers le haut
	int positionsRangeeVersLeHaut = position_.second;
	while (positionsRangeeVersLaDroite < tailleEchiquier && positionsRangeeVersLeHaut < tailleEchiquier)
	{
		if (conversionIntLimite(e.cases[positionsRangeeVersLaDroite + uneCase][positionsRangeeVersLeHaut + uneCase]) == conversionCouleurInt())
			break;
		else
		{
			mouvementsDisponibles_.push_back(std::make_pair(positionsRangeeVersLaDroite + uneCase, positionsRangeeVersLeHaut + uneCase));
			if (conversionIntLimite(e.cases[positionsRangeeVersLaDroite + uneCase][positionsRangeeVersLeHaut + uneCase]) != conversionCouleurInt() &&
				(conversionIntLimite(e.cases[positionsRangeeVersLaDroite + uneCase][positionsRangeeVersLeHaut + uneCase]) != 0))
				break;
		}
		positionsRangeeVersLaDroite += uneCase;
		positionsRangeeVersLeHaut += uneCase;
	}


	int positionsRangeeVersLaGauche = position_.first; // nombre de position vides vers la droite
	positionsRangeeVersLeHaut = position_.second; // nombre de position vides vers le haut

	while (positionsRangeeVersLaGauche > 0 and positionsRangeeVersLeHaut < tailleEchiquier)
	{
		if (conversionIntLimite(e.cases[positionsRangeeVersLaGauche - uneCase][positionsRangeeVersLeHaut + uneCase]) == conversionCouleurInt())
			break;
		else
		{
			mouvementsDisponibles_.push_back(std::make_pair(positionsRangeeVersLaGauche - uneCase, positionsRangeeVersLeHaut + uneCase));
			if (conversionIntLimite(e.cases[positionsRangeeVersLaGauche - uneCase][positionsRangeeVersLeHaut + uneCase]) != conversionCouleurInt() &&
				(conversionIntLimite(e.cases[positionsRangeeVersLaGauche - uneCase][positionsRangeeVersLeHaut + uneCase]) != 0))
				break;
		}
		positionsRangeeVersLaGauche -= uneCase;
		positionsRangeeVersLeHaut += uneCase;
	}


	positionsRangeeVersLaGauche = position_.first; // nombre de position vides vers la droite
	int positionsRangeeVersLeBas = position_.second; // nombre de position vides vers le haut

	while (positionsRangeeVersLaGauche > 0 && positionsRangeeVersLeBas > 0)
	{
		if (conversionIntLimite(e.cases[positionsRangeeVersLaGauche - uneCase][positionsRangeeVersLeBas - uneCase]) == conversionCouleurInt())
			break;
		else
		{
			mouvementsDisponibles_.push_back(std::make_pair(positionsRangeeVersLaGauche - uneCase, positionsRangeeVersLeBas - uneCase));
			if (conversionIntLimite(e.cases[positionsRangeeVersLaGauche - uneCase][positionsRangeeVersLeBas - uneCase]) != conversionCouleurInt() &&
				(conversionIntLimite(e.cases[positionsRangeeVersLaGauche - uneCase][positionsRangeeVersLeBas - uneCase]) != 0))
				break;
		}
		positionsRangeeVersLaGauche -= uneCase;
		positionsRangeeVersLeBas -= uneCase;
	}


	positionsRangeeVersLaDroite = position_.first; // nombre de position vides vers la droite
	positionsRangeeVersLeBas = position_.second; // nombre de position vides vers le haut

	while (positionsRangeeVersLaDroite < tailleEchiquier && positionsRangeeVersLeBas > 0)
	{
		if (conversionIntLimite(e.cases[positionsRangeeVersLaDroite + uneCase][positionsRangeeVersLeBas - uneCase]) == conversionCouleurInt())
			break;
		else
		{
			mouvementsDisponibles_.push_back(std::make_pair(positionsRangeeVersLaDroite + uneCase, positionsRangeeVersLeBas - uneCase));
			if (conversionIntLimite(e.cases[positionsRangeeVersLaDroite + uneCase][positionsRangeeVersLeBas - uneCase]) != conversionCouleurInt() &&
				(conversionIntLimite(e.cases[positionsRangeeVersLaDroite + uneCase][positionsRangeeVersLeBas - uneCase]) != 0))
				break;
		}
		positionsRangeeVersLaDroite += uneCase;
		positionsRangeeVersLeBas -= uneCase;
	}

}

void Cavalier::calculeMouvements(Echiquier e)
{
	std::pair<int, int> deplacements[8] = { std::make_pair(-1,-2),std::make_pair(1,-2),std::make_pair(2,-1),std::make_pair(2,1),std::make_pair(1,2),std::make_pair(-1,2),std::make_pair(-2,1),std::make_pair(-2,-1) };
	const int tailleInt = 8;
	
	span<std::pair<int, int>>  spanDeplacements = { deplacements, sizeof(deplacements) / tailleInt };
	for (auto d : spanDeplacements) 
	{
		int x = position_.first + d.first;
		int y = position_.second + d.second;
		if (x >= 0 && x <= tailleEchiquier && y >= 0 && y <= tailleEchiquier) {
			if (e.cases[x][y] == 0 || (conversionIntLimite(e.cases[x][y]) != conversionCouleurInt()))
				mouvementsDisponibles_.push_back(std::make_pair(x, y));
		}
	}
};
void Dame::calculeMouvements(Echiquier e) 
{
	// Pour des raisons conceptuelles, je n'ai pas fait hérité la Dame de tour et fou.
	Tour t(e, std::make_pair(position_.first, position_.second), estBlanc_);
	Fou f(e, std::make_pair(position_.first, position_.second), estBlanc_);
	t.calculeMouvements(e);
	f.calculeMouvements(e);

	for (std::pair<int, int> m : t.obtenirMouvements())
		mouvementsDisponibles_.push_back(m);
	for (std::pair<int, int> m : f.obtenirMouvements())
		mouvementsDisponibles_.push_back(m);
}
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
	
	ChessWindow chessWindow;
	chessWindow.showMaximized();
	return app.exec();	
}
