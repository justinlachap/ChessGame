#pragma once
#include "Piece.h"

class Cavalier : virtual public Piece
{
	const QString cavalierBlanc = "images/white_knight.png";
	const QString cavalierNoir = "images/black_knight.png";

public:
	Cavalier(Echiquier& nouvelEchiquier, std::pair<int, int> position, bool estBlanc);

	void calculerMouvements(Echiquier e_) override;

	QString obtenirImage() const override
	{
		if (estBlanc_)
			return cavalierBlanc;
		else
			return cavalierNoir;
	}
};
