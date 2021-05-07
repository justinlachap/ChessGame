//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//																																	//
// L'�chiquier. Chaque case est intialis� avec des nullptr					 														//
// 																																	//
// Par :																															//
//		G�n�reux, Esm� (2081518)																									//
//		Lachapelle, Justin (2076412)																								//
// 																																	//
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#pragma once
#pragma warning(push, 0)
#include <QObject>
#include <vector>

class Piece;

namespace UI
{
	class MethodeVirtuelleQt
	{
	public:
		virtual QString obtenirImage() const = 0;
	};
}

class Echiquier : public UI::MethodeVirtuelleQt
{
public:
	void initialiserVide();
	Piece* cases[8][8];

	QString obtenirImage() const override { return echiquier; }

private:
	const QString echiquier = "images/Chess_board.png";
	// Toutes les pi�ces doivent pouvoir acc�der facilement aux cases de l'�chiquier. 
	// C'est pourquoi l'attribut cases est public et qu'il n'y a pas d'encapsulation.
};
