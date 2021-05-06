#pragma once
#include "Piece.h"

class Pion : virtual public Piece
{
	const QString pionBlanc = "images/white_pawn.png";
	const QString pionNoir = "images/black_pawn.png";

public:
	Pion(Echiquier& nouvelEchiquier, std::pair<int, int> position, bool estBlanc);

	void calculerMouvements(Echiquier e_) override;

	QString obtenirImage() const override
	{
		if (estBlanc_)
			return pionBlanc;
		else
			return pionNoir;
	}
};
