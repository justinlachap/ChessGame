#pragma once
#include "Piece.h"

class Pion : virtual public Piece
{
	const QString pionBlanc = "images/white_pawn.png";
	const QString pionNoir = "images/black_pawn.png";

public:
	Pion(Echiquier& nouvelEchiquier, std::pair<int, int> position, bool estBlanc);

	/**
	 * Fonctions qui calculent les mouvements disponibles selon la couleur du Pion
	 * @param e : référence de l'echiquier sur lequel se trouve le Pion
	 */
	void mouvementsPionBlanc(Echiquier& e);
	void mouvementsPionNoir(Echiquier& e);
	
	/**
	 * Calcule les mouvements possibles du Pion en appeleant les deux fonctions ci-dessus
	 * @param e_ : echiquier sur lequel se trouve le Pion
	 */
	void calculerMouvements(Echiquier e) override;

	/**
	 * Associe l'image d'un Pion noir ou d'un Pion blanc
	 */
	QString obtenirImage() const override { return estBlanc_ ? pionBlanc : pionNoir; }
};
