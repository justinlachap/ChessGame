//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//																																	//
// Le fou est un type de pièce												 														//
// 																																	//
// Par :																															//
//		Généreux, Esmé (2081518)																									//
//		Lachapelle, Justin (2076412)																								//
// 																																	//
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
#pragma once
#include "Piece.h"

class Fou : virtual public Piece
{
	const QString fouBlanc = "images/white_bishop.png";
	const QString fouNoir = "images/black_bishop.png";

public:
	Fou(Echiquier& nouvelEchiquier, std::pair<int, int> position, bool estBlanc);

	/**
	 * Fonctions qui calculent les mouvements disponibles sur chacune des diagonales du Fou
	 * @param e : référence de l'echiquier sur lequel se trouve le Fou
	 */
	void diagonaleHautGauche(Echiquier& e);
	void diagonaleHautDroite(Echiquier& e);
	void diagonaleBasGauche(Echiquier& e);
	void diagonaleBasDroite(Echiquier& e);

	/**
	 * Calcule les mouvements possibles du Fou en appelant les 4 fonctions ci-dessus
	 * @param e_ : echiquier sur lequel se trouve le Fou
	 */
	void calculerMouvements(Echiquier e_) override;

	/**
	 * Associe l'image d'un Fou noir ou d'un Fou blanc
	 */
	QString obtenirImage() const override { return estBlanc_ ? fouBlanc : fouNoir; }
};
