/*
** Livrable 2
** Par Justin Lachapelle, matricule 2076412 et Esmé Généreux, matricule 2081518.
*/

#pragma once
#include "Piece.h"

class Fou : virtual public Piece
{
	const QString fouBlanc = "images/white_bishop.png";
	const QString fouNoir = "images/black_bishop.png";

public:
	Fou(Echiquier& nouvelEchiquier, std::pair<int, int> position, bool estBlanc);

	void calculerMouvements(Echiquier e_) override;

	QString obtenirImage() const override
	{
		if (estBlanc_)
			return fouBlanc;
		else
			return fouNoir;
	}
};
