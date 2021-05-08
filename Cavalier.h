//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//																																	//
// Le cavalier est un type de pièce											 														//
// 																																	//
// Par :																															//
//		Généreux, Esmé (2081518)																									//
//		Lachapelle, Justin (2076412)																								//
// 																																	//
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#pragma once
#include "Piece.h"

class Cavalier : virtual public Piece
{
	const QString cavalierBlanc = "images/white_knight.png";
	const QString cavalierNoir = "images/black_knight.png";

public:
	Cavalier(Echiquier& nouvelEchiquier, std::pair<int, int> position, bool estBlanc);

	/**
	 * Calcule les mouvements possibles du Cavalier
	 * @param e_ : echiquier sur lequel se trouve la Cavalier
	 */
	void calculerMouvements(Echiquier e) override;
	
	/**
	 * Associe l'image d'un Cavalier noir ou d'un Cavalier blanc
	 */
	QString obtenirImage() const override { return estBlanc_ ? cavalierBlanc : cavalierNoir; }
};
