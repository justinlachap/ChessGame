//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//																																	//
// Le roi est un type de pièce et il ne peut être instancié plus de deux fois						 								//
// 																																	//
// Par :																															//
//		Généreux, Esmé (2081518)																									//
//		Lachapelle, Justin (2076412)																								//
// 																																	//
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#pragma once
#include "Piece.h"

class Roi : virtual public Piece
{
	const QString roiBlanc = "images/white_king.png";
	const QString roiNoir = "images/black_king.png";
	inline static int compteurInstances_ = 0;

public:
	Roi(Echiquier& nouvelEchiquier, std::pair<int, int> position, bool estBlanc);

	/**
	 * Fonctions qui calculent les mouvements disponibles sur chacune des axes du Roi
	 * @param e : référence de l'echiquier sur lequel se trouve le Roi
	 */
	void axeHorizontal(Echiquier& e);
	void axeVertical(Echiquier& e);
	void axeDiagonalUn(Echiquier& e);
	void axeDiagonalDeux(Echiquier& e);

	/**
	 * Calcule les mouvements possibles du Roi en appelant les 4 fonctions ci-dessus
	 * @param e_ : echiquier sur lequel se trouve le Roi
	 */
	void calculerMouvements(Echiquier e_) override;

	/**
	 * Fonction qui renvoit un bool vrai si le roi est en èchec
	 */
	bool estEnÉchec(std::vector<std::pair<int, int>>);

	/**
	 * Associe l'image d'un Roi noir ou d'un Roi blanc
	 */
	QString obtenirImage() const override { return estBlanc_ ? roiBlanc : roiNoir; }
};
