//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//																																	//
// La tour est un type de pièce												 														//
// 																																	//
// Par :																															//
//		Généreux, Esmé (2081518)																									//
//		Lachapelle, Justin (2076412)																								//
// 																																	//
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#pragma once
#include "Piece.h"

class Tour : virtual public Piece
{
	const QString tourBlanche = "images/white_rook.png";
	const QString tourNoire = "images/black_rook.png";

public:
	Tour(Echiquier& nouvelEchiquier, std::pair<int, int> position, bool estBlanc);

	/**
	 * Fonctions qui calculent les mouvements disponibles dans chacune des quatres directions de la Tour
	 * @param e : référence de l'echiquier sur lequel se trouve le Fou
	 */
	void mouvementsVersLaDroite(Echiquier& e);
	void mouvementsVersLaGauche(Echiquier& e);
	void mouvementsVersLeHaut(Echiquier& e);
	void mouvementsVersLeBas(Echiquier& e);

	/**
	 * Calcule les mouvements possibles d'une Tour en appelant les 4 fonctions ci-dessus
	 * @param e_ : echiquier sur lequel se trouve le Fou
	 */
	void calculerMouvements(Echiquier e) override;

	/**
	 * Associe l'image d'un Tour noir ou d'un Tour blanc
	 */
	QString obtenirImage() const override { return estBlanc_ ? tourBlanche : tourNoire; }
};