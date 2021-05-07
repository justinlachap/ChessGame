//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//																																	//
// La tour est un type de pi�ce												 														//
// 																																	//
// Par :																															//
//		G�n�reux, Esm� (2081518)																									//
//		Lachapelle, Justin (2076412)																								//
// 																																	//
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#pragma once
#include "Piece.h"

class Tour : virtual public Piece
{
	const QString tourBlanche = "images/white_rook.png";
	const QString tourNoire = "images/black_rook.png";

public:
	Tour(Echiquier& nouvelEchiquier, std::pair<int, int> position, bool estBlanc);

	void calculerMouvements(Echiquier e_) override;

	QString obtenirImage() const override
	{
		if (estBlanc_)
			return tourBlanche;
		else
			return tourNoire;
	}
};