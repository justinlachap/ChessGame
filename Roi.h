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
