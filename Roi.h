/*
** Livrable 2
** Par Justin Lachapelle, matricule 2076412 et Esmé Généreux, matricule 2081518.
*/

#pragma once
#include "Piece.h"

class Roi : virtual public Piece
{
	const QString roiBlanc = "images/white_king.png";
	const QString roineNoir = "images/black_king.png";
	inline static int compteurInstances_ = 0;

public:
	Roi(Echiquier& nouvelEchiquier, std::pair<int, int> position, bool estBlanc);

	void calculerMouvements(Echiquier e_) override;

	bool estEnÉchec(std::vector<std::pair<int, int>>);

	QString obtenirImage() const override
	{
		if (estBlanc_)
			return roiBlanc;
		else
			return roineNoir;
	}
};
