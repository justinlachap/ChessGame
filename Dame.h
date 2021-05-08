//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//																																	//
// La Dame hérite des mouvements de la tour et du fou						 														//
// 																																	//
// Par :																															//
//		Généreux, Esmé (2081518)																									//
//		Lachapelle, Justin (2076412)																								//
// 																																	//
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#pragma once
#include "Piece.h"
#include "Fou.h"
#include "Tour.h"

class Dame : virtual public Piece,
	public Fou,
	public Tour
{
	const QString dameBlanche = "images/white_queen.png";
	const QString dameNoire = "images/black_queen.png";

public:
	Dame(Echiquier& nouvelEchiquier, std::pair<int, int> position, bool estBlanc);

	/**
	 * Retourne les mouvements disponibles d'une Tour ayant la même position que la Dame
	 * @param e_ : echiquier sur lequel se trouve la Dame
	 */
	std::vector<std::pair<int, int>> calculerMouvementsTour(Echiquier& e_);

	/**
	 * Ajoute les mouvements disponibles d'une Tour au mouvements disponibles d'un Fou au même emplacement que la Dame
	 * @param e_ : echiquier sur lequel se trouve la Dame
	 * @param MouvementsDipsoniblesTour : valeur de retour de la fonction calculerMouvementsTour(...)
	 */
	void ajouterMouvementsFou(Echiquier& e_, std::vector<std::pair<int, int>>& MouvementsDipsoniblesTour);

	/**
	 * Calcule les mouvements possibles de la Dame
	 * @param e_ : echiquier sur lequel se trouve la Dame
	 */
	void calculerMouvements(Echiquier e_) override;

	/**
	 * Associe l'image d'une Dame noire ou d'une Dame blanche
	 */
	QString obtenirImage() const override { return estBlanc_ ? dameBlanche : dameNoire; }
};
