#pragma once
#include "Piece.h"
#include "Fou.h"
#include "Tour.h"

class Dame : virtual public Piece,
	public Fou,
	public Tour
{
	const QString reineBlanche = "images/white_queen.png";
	const QString reineNoire = "images/black_queen.png";

public:
	Dame(Echiquier& nouvelEchiquier, std::pair<int, int> position, bool estBlanc);

	void calculerMouvements(Echiquier e_) override;

	QString obtenirImage() const override
	{
		if (estBlanc_)
			return reineBlanche;
		else
			return reineNoire;
	}
};
