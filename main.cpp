//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//																																	//
// Projet INF1015 : Jeux d'�chec																									//
// 																																	//
// Par :																															//
//		G�n�reux, Esm� (2081518)																									//
//		Lachapelle, Justin (2076412)																								//
// 																																	//
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#include "ChessWindow.h"
#include <stdexcept>
#include <QApplication>
#include <iostream>

//////////////////////// Tir� de l'exemple de projet pour une calculatrice par Fran�ois Reymond-Boyer ////////////////////////////////
#if __has_include("bibliotheque_cours.hpp")																							//
#include "bibliotheque_cours.hpp"																									//
#define BIBLIOTHEQUE_COURS_INCLUS																									//
using bibliotheque_cours::cdbg;																										//
#else																																//
auto& cdbg = clog;																													//
#endif																																//
																																	//
#if __has_include("verification_allocation.hpp")																					//
#include "verification_allocation.hpp"																								//
#include "debogage_memoire.hpp"  /* NOTE: Incompatible avec le "placement new", ne pas utiliser cette ent�te si vous utilisez ce    //
								 **	type de "new" dans les lignes qui suivent cette inclusion.										//
								 */																									//
#endif																																//
																																	//
																																	//
void initialiserBibliothequeCours([[maybe_unused]] int argc, [[maybe_unused]] char* argv[])											//
{																																	//
#ifdef BIBLIOTHEQUE_COURS_INCLUS																									//
	bibliotheque_cours::activerCouleursAnsi();			/* Permet sous Windows les "ANSI escape code" pour changer de couleurs 		//
														** https://en.wikipedia.org/wiki/ANSI_escape_code ; 						//
														** les consoles Linux/Mac les supportent normalement par d�faut.			//
														*/																			//
	bibliotheque_cours::executerGoogleTest(argc, argv); /* Attention de ne rien afficher avant cette ligne, sinon l'Explorateur de 	//
														** tests va tenter de lire votre affichage comme un r�sultat de test.		//
														*/																			//
#endif																																//
/* NOTE: C'est normal que la couverture de code dans l'Explorateur de tests de Visual Studio ne couvre pas la fin de cette fonction //
** ni la fin du main apr�s l'appel � cette fonction puisqu'il ex�cute uniquement les tests Google Test dans l'appel ci-dessus.		//
*/																																	//
}																																	//
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////																																

int nouvellePartie()
{
	char partie = 'X';
	std::cout << "Aimeriez-vous commencer une partie d'�chec? [Y/n]" << std::endl;
	while (partie == 'X')
		std::cin >> partie;

	if (partie != 'Y' && partie != 'y')
		return 0;
}

int main(int argc, char* argv[])
{
	bibliotheque_cours::VerifierFuitesAllocations verifierFuitesAllocations;
	QApplication app(argc, argv);

	nouvellePartie();

	initialiserBibliothequeCours(argc, argv);
	UI::ChessWindow chessWindow;
	chessWindow.resize(810, 810);
	chessWindow.show();
	return app.exec();
}
