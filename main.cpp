#include "Calc.hpp"
#include "CalcWindow.hpp"
#include <iostream>
#include "classes.hpp"

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



int conversionIntLimite(int caseEchiquier) // Cette fonction sera souvent comparée avec la fonction conversionCouleurInt(), pour déterminer si 2 pièces ont la même couleur.
{
	if ((caseEchiquier <= 6) && (caseEchiquier != 0))
		return 6;
	else if (caseEchiquier > 6)
		return 7;
	else
		return 0;
};

void Echiquier::initialiserVide()
{
	for (int i = 0; i < 8; i++)
	{
		for (int j = 0; j < 8; j++)
			cases[i][j] = 0;
	}
}

Piece::Piece(Echiquier& nouvelEchiquier, std::pair<int, int> position, std::string couleur)
{
	m_position = position;
	m_couleur = couleur;
}
Dame::Dame(Echiquier& nouvelEchiquier, std::pair<int, int> position, std::string couleur)
	: Piece(nouvelEchiquier, position, couleur)
{
	nouvelEchiquier.cases[position.first][position.second] = (couleur == "blanc") ? m_dameBlanc : m_dameNoir;
}
Cavalier::Cavalier(Echiquier& nouvelEchiquier, std::pair<int, int> position, std::string couleur)
	: Piece(nouvelEchiquier, position, couleur)
{
	nouvelEchiquier.cases[position.first][position.second] = (couleur == "blanc") ? m_cavalierBlanc : m_cavalierNoir;
}

Fou::Fou(Echiquier& nouvelEchiquier, std::pair<int, int> position, std::string couleur)
	: Piece(nouvelEchiquier, position, couleur)
{
	nouvelEchiquier.cases[position.first][position.second] = (couleur == "blanc") ? m_fouBlanc : m_fouNoir;
}
Pion::Pion(Echiquier& nouvelEchiquier, std::pair<int, int> position, std::string couleur)
	: Piece(nouvelEchiquier, position, couleur)
{
	nouvelEchiquier.cases[position.first][position.second] = (couleur == "blanc") ? m_pionBlanc : m_pionNoir;
}
Roi::Roi(Echiquier& nouvelEchiquier, std::pair<int, int> position, std::string couleur)
	: Piece(nouvelEchiquier, position, couleur)
{
	nouvelEchiquier.cases[position.first][position.second] = (couleur == "blanc") ? m_roiBlanc : m_roiNoir;
};
Tour::Tour(Echiquier& nouvelEchiquier, std::pair<int, int> position, std::string couleur)
	: Piece(nouvelEchiquier, position, couleur)
{
	nouvelEchiquier.cases[position.first][position.second] = (couleur == "blanc") ? m_tourBlanc : m_tourNoir;
}


int Piece::conversionCouleurInt()
{
	int delimiteur = (m_couleur == "blanc") ? 6 : 7;
	return delimiteur;
}

void Piece::afficheMouvements()
{
	std::cout << "Cette piece peut se deplacer aux cases: ";
	for (std::pair<int, int> m : m_mouvementsDisponibles)
		std::cout << '(' << m.first << ", " << m.second << ") ";
	std::cout << std::endl;
}

void Pion::calculeMouvements(Echiquier e)
{
	// pion blanc
	if (m_couleur == "blanc")
	{
		// si n'a pas bougé, il peut avancer de 2 cases vers l'avant
		if ((m_position.second == 1) && (e.cases[m_position.first][m_position.second + 2] == 0))
			m_mouvementsDisponibles.push_back(std::make_pair(m_position.first, m_position.second + 2));

		// si la case d'en avant est disponible, il peut avancer d'une case
		if ((e.cases[m_position.first][m_position.second + 1] == 0))
			m_mouvementsDisponibles.push_back(std::make_pair(m_position.first, m_position.second + 1));

		// si il peut manger une piece a droite, il peut avancer d'une case en diagonale
		if (conversionIntLimite(e.cases[m_position.first + 1][m_position.second + 1]) != conversionCouleurInt()
			&& conversionIntLimite(e.cases[m_position.first + 1][m_position.second + 1]) != 0
			&& (m_position.first != 7))
			m_mouvementsDisponibles.push_back(std::make_pair(m_position.first + 1, m_position.second + 1));

		// si il peut manger une piece a gauche, il peut avancer d'une case en diagonale
		if (conversionIntLimite(e.cases[m_position.first - 1][m_position.second + 1]) != conversionCouleurInt()
			&& conversionIntLimite(e.cases[m_position.first - 1][m_position.second + 1]) != 0
			&& (m_position.first != 0))
			m_mouvementsDisponibles.push_back(std::make_pair(m_position.first - 1, m_position.second + 1));
	}

	// pion noir
	else
	{
		// si pion noir n'a pas bougé, il peut avancer de 2 cases vers l'avant
		if ((m_position.second == 6)
			&& (e.cases[m_position.first][m_position.second - 2] == 0))
			m_mouvementsDisponibles.push_back(std::make_pair(m_position.first, m_position.second - 2));

		// si la case d'en avant est disponible, il peut avancer d'une case
		if ((e.cases[m_position.first][m_position.second - 1] == 0))
			m_mouvementsDisponibles.push_back(std::make_pair(m_position.first, m_position.second - 1));

		// si il peut manger une piece a droite, il peut avancer d'une case en diagonale
		if (conversionIntLimite(e.cases[m_position.first - 1][m_position.second - 1]) != conversionCouleurInt()
			&& conversionIntLimite(e.cases[m_position.first - 1][m_position.second - 1]) != 0
			&& (m_position.first != 0))
			m_mouvementsDisponibles.push_back(std::make_pair(m_position.first - 1, m_position.second - 1));

		// si il peut manger une piece a gauche, il peut avancer d'une case en diagonale
		if (conversionIntLimite(e.cases[m_position.first + 1][m_position.second - 1]) != conversionCouleurInt()
			&& conversionIntLimite(e.cases[m_position.first + 1][m_position.second - 1]) != 0
			&& (m_position.first != 7))
			m_mouvementsDisponibles.push_back(std::make_pair(m_position.first + 1, m_position.second - 1));
	}
}

void Roi::calculeMouvements(Echiquier e)
{
	// vers la droite
	if (((e.cases[m_position.first + 1][m_position.second] == 0)
		|| conversionIntLimite(e.cases[m_position.first + 1][m_position.second]) != conversionCouleurInt())
		&& (m_position.first != 7))
		m_mouvementsDisponibles.push_back(std::make_pair(m_position.first + 1, m_position.second));

	// vers la gauche
	if (((e.cases[m_position.first - 1][m_position.second] == 0)
		|| conversionIntLimite(e.cases[m_position.first - 1][m_position.second]) != conversionCouleurInt())
		&& (m_position.first != 0))
		m_mouvementsDisponibles.push_back(std::make_pair(m_position.first - 1, m_position.second));

	// vers le haut
	if (((e.cases[m_position.first][m_position.second + 1] == 0)
		|| conversionIntLimite(e.cases[m_position.first][m_position.second + 1]) != conversionCouleurInt()) && (m_position.second != 7))
		m_mouvementsDisponibles.push_back(std::make_pair(m_position.first, m_position.second + 1));

	// vers le bas
	if (((e.cases[m_position.first][m_position.second - 1] == 0)
		|| conversionIntLimite(e.cases[m_position.first][m_position.second - 1]) != conversionCouleurInt())
		&& (m_position.second != 0))
		m_mouvementsDisponibles.push_back(std::make_pair(m_position.first, m_position.second - 1));

	// droite-haut
	if (((e.cases[m_position.first + 1][m_position.second + 1] == 0)
		|| (conversionIntLimite(e.cases[m_position.first + 1][m_position.second + 1]) != conversionCouleurInt()))
		&& ((m_position.second != 7) && (m_position.first != 7)))
		m_mouvementsDisponibles.push_back(std::make_pair(m_position.first + 1, m_position.second + 1));

	// gauche-haut
	if (((e.cases[m_position.first - 1][m_position.second + 1] == 0)
		|| (conversionIntLimite(e.cases[m_position.first - 1][m_position.second + 1]) != conversionCouleurInt()))
		&& ((m_position.second != 7) && (m_position.first != 0)))
		m_mouvementsDisponibles.push_back(std::make_pair(m_position.first - 1, m_position.second + 1));

	// droite-bas
	if (((e.cases[m_position.first + 1][m_position.second - 1] == 0)
		|| (conversionIntLimite(e.cases[m_position.first + 1][m_position.second - 1]) != conversionCouleurInt()))
		&& ((m_position.second != 0) && (m_position.first != 7)))
		m_mouvementsDisponibles.push_back(std::make_pair(m_position.first + 1, m_position.second - 1));

	//mouvement gauche-bas
	if (((e.cases[m_position.first - 1][m_position.second - 1] == 0)
		|| (conversionIntLimite(e.cases[m_position.first - 1][m_position.second - 1]) != conversionCouleurInt()))
		&& ((m_position.second != 0) && (m_position.first != 0)))
		m_mouvementsDisponibles.push_back(std::make_pair(m_position.first - 1, m_position.second - 1));
};

void Tour::calculeMouvements(Echiquier e)
{
	// nombre de position vides vers la droite
	int positionsRangeeVersLaDroite = m_position.first;
	for (positionsRangeeVersLaDroite; positionsRangeeVersLaDroite < 7; ++positionsRangeeVersLaDroite)
	{
		if (e.cases[positionsRangeeVersLaDroite + 1][m_position.second] != 0)
		{
			if (conversionIntLimite(e.cases[positionsRangeeVersLaDroite + 1][m_position.second]) != conversionCouleurInt())
				m_mouvementsDisponibles.push_back(std::make_pair(positionsRangeeVersLaDroite + 1, m_position.second));
			break;
		}
		if (e.cases[positionsRangeeVersLaDroite + 1][m_position.second] == 0)
			m_mouvementsDisponibles.push_back(std::make_pair(positionsRangeeVersLaDroite + 1, m_position.second));
	}

	// nombre de position vides vers la gauche
	int positionsRangeeVersLaGauche = m_position.first;
	for (positionsRangeeVersLaGauche; positionsRangeeVersLaGauche > 0; --positionsRangeeVersLaGauche)
	{
		if (e.cases[positionsRangeeVersLaGauche - 1][m_position.second] != 0)
		{
			if (conversionIntLimite(e.cases[positionsRangeeVersLaGauche - 1][m_position.second]) != conversionCouleurInt())
				m_mouvementsDisponibles.push_back(std::make_pair(positionsRangeeVersLaGauche - 1, m_position.second));
			break;
		};
		if (e.cases[positionsRangeeVersLaGauche - 1][m_position.second] == 0)
			m_mouvementsDisponibles.push_back(std::make_pair(positionsRangeeVersLaGauche - 1, m_position.second));
	}

	// nombre de position vides vers le haut
	int positionsRangeeVersLeHaut = m_position.second;
	for (positionsRangeeVersLeHaut; positionsRangeeVersLeHaut < 7; ++positionsRangeeVersLeHaut)
	{
		if (e.cases[m_position.first][positionsRangeeVersLeHaut + 1] != 0)
		{
			if (conversionIntLimite(e.cases[m_position.first][positionsRangeeVersLeHaut + 1]) != conversionCouleurInt())
				m_mouvementsDisponibles.push_back(std::make_pair(m_position.first, positionsRangeeVersLeHaut + 1));
			break;
		}
		if (e.cases[m_position.first][positionsRangeeVersLeHaut + 1] == 0)
			m_mouvementsDisponibles.push_back(std::make_pair(m_position.first, positionsRangeeVersLeHaut + 1));
	}

	// nombre de position vides vers le bas
	int positionsRangeeVersLeBas = m_position.second;
	for (positionsRangeeVersLeBas; positionsRangeeVersLeBas > 0; --positionsRangeeVersLeBas)
	{
		if (e.cases[m_position.first][positionsRangeeVersLeBas - 1] != 0)
		{
			if (conversionIntLimite(e.cases[m_position.first][positionsRangeeVersLeBas - 1]) != conversionCouleurInt())
				m_mouvementsDisponibles.push_back(std::make_pair(m_position.first, positionsRangeeVersLeBas - 1));
			break;
		};
		if (e.cases[m_position.first][positionsRangeeVersLeBas - 1] == 0)
			m_mouvementsDisponibles.push_back(std::make_pair(m_position.first, positionsRangeeVersLeBas - 1));
	}
};

void Fou::calculeMouvements(Echiquier e) {
	// nombre de position vides vers la droite
	int positionsRangeeVersLaDroite = m_position.first;
	// nombre de position vides vers le haut
	int positionsRangeeVersLeHaut = m_position.second;
	while (positionsRangeeVersLaDroite < 7 and positionsRangeeVersLeHaut < 7) {
		if (conversionIntLimite(e.cases[positionsRangeeVersLaDroite + 1][positionsRangeeVersLeHaut + 1]) == conversionCouleurInt())
			break;
		else
		{
			m_mouvementsDisponibles.push_back(std::make_pair(positionsRangeeVersLaDroite + 1, positionsRangeeVersLeHaut + 1));
			if (conversionIntLimite(e.cases[positionsRangeeVersLaDroite + 1][positionsRangeeVersLeHaut + 1]) != conversionCouleurInt() &&
				(conversionIntLimite(e.cases[positionsRangeeVersLaDroite + 1][positionsRangeeVersLeHaut + 1]) != 0))
				break;
		}
		positionsRangeeVersLaDroite += 1;
		positionsRangeeVersLeHaut += 1;
	}


	int positionsRangeeVersLaGauche = m_position.first; // nombre de position vides vers la droite
	positionsRangeeVersLeHaut = m_position.second; // nombre de position vides vers le haut

	while (positionsRangeeVersLaGauche > 0 and positionsRangeeVersLeHaut < 7)
	{
		if (conversionIntLimite(e.cases[positionsRangeeVersLaGauche - 1][positionsRangeeVersLeHaut + 1]) == conversionCouleurInt())
			break;
		else
		{
			m_mouvementsDisponibles.push_back(std::make_pair(positionsRangeeVersLaGauche - 1, positionsRangeeVersLeHaut + 1));
			if (conversionIntLimite(e.cases[positionsRangeeVersLaGauche - 1][positionsRangeeVersLeHaut + 1]) != conversionCouleurInt() &&
				(conversionIntLimite(e.cases[positionsRangeeVersLaGauche - 1][positionsRangeeVersLeHaut + 1]) != 0))
				break;
		}
		positionsRangeeVersLaGauche -= 1;
		positionsRangeeVersLeHaut += 1;
	}


	positionsRangeeVersLaGauche = m_position.first; // nombre de position vides vers la droite
	int positionsRangeeVersLeBas = m_position.second; // nombre de position vides vers le haut

	while (positionsRangeeVersLaGauche > 0 and positionsRangeeVersLeBas > 0)
	{
		if (conversionIntLimite(e.cases[positionsRangeeVersLaGauche - 1][positionsRangeeVersLeBas - 1]) == conversionCouleurInt())
			break;
		else
		{
			m_mouvementsDisponibles.push_back(std::make_pair(positionsRangeeVersLaGauche - 1, positionsRangeeVersLeBas - 1));
			if (conversionIntLimite(e.cases[positionsRangeeVersLaGauche - 1][positionsRangeeVersLeBas - 1]) != conversionCouleurInt() &&
				(conversionIntLimite(e.cases[positionsRangeeVersLaGauche - 1][positionsRangeeVersLeBas - 1]) != 0))
				break;
		}
		positionsRangeeVersLaGauche -= 1;
		positionsRangeeVersLeBas -= 1;
	}


	positionsRangeeVersLaDroite = m_position.first; // nombre de position vides vers la droite
	positionsRangeeVersLeBas = m_position.second; // nombre de position vides vers le haut

	while (positionsRangeeVersLaDroite < 7 and positionsRangeeVersLeBas > 0)
	{
		if (conversionIntLimite(e.cases[positionsRangeeVersLaDroite + 1][positionsRangeeVersLeBas - 1]) == conversionCouleurInt())
			break;
		else
		{
			m_mouvementsDisponibles.push_back(std::make_pair(positionsRangeeVersLaDroite + 1, positionsRangeeVersLeBas - 1));
			if (conversionIntLimite(e.cases[positionsRangeeVersLaDroite + 1][positionsRangeeVersLeBas - 1]) != conversionCouleurInt() &&
				(conversionIntLimite(e.cases[positionsRangeeVersLaDroite + 1][positionsRangeeVersLeBas - 1]) != 0))
				break;
		}
		positionsRangeeVersLaDroite += 1;
		positionsRangeeVersLeBas -= 1;
	}

}

void Cavalier::calculeMouvements(Echiquier e) {
	std::pair<int, int> deplacements[8] = { std::make_pair(-1,-2),std::make_pair(1,-2),std::make_pair(2,-1),std::make_pair(2,1),std::make_pair(1,2),std::make_pair(-1,2),std::make_pair(-2,1),std::make_pair(-2,-1) };
	for (auto d : deplacements) {
		int x = m_position.first + d.first;
		int y = m_position.second + d.second;
		if (x >= 0 and x <= 7 and y >= 0 and y <= 7) {
			if (e.cases[x][y] == 0 or (conversionIntLimite(e.cases[x][y]) != conversionCouleurInt()))
				m_mouvementsDisponibles.push_back(std::make_pair(x, y));
		}
	}
};
void Dame::calculeMouvements(Echiquier e) {
	// Pour des raisons conceptuelles, je n'ai pas fait hérité la Dame de tour et fou.
	Tour t(e, std::make_pair(m_position.first, m_position.second), m_couleur);
	Fou f(e, std::make_pair(m_position.first, m_position.second), m_couleur);
	t.calculeMouvements(e);
	f.calculeMouvements(e);
	for (std::pair<int, int> m : t.obtenirMouvements())
		m_mouvementsDisponibles.push_back(m);
	for (std::pair<int, int> m : f.obtenirMouvements())
		m_mouvementsDisponibles.push_back(m);
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
	
	CalcWindow calcWindow;
	calcWindow.show();
	return app.exec();
}
