//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//																																	//
// L'échiquier. Chaque case est intialisé avec des nullptr					 														//
// 																																	//
// Par :																															//
//		Généreux, Esmé (2081518)																									//
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
		/**
		 * Associe l'image d'une pièce ou d'un échiquier à une instance.
		 */
		virtual QString obtenirImage() const = 0;
	};
}

class Echiquier : public UI::MethodeVirtuelleQt
{
public:
	Piece* cases[8][8];

	/**
	 * Remplit l'échiquier de nullptrs
	 */
	void initialiserVide();
	
	/**
	* Associe l'image de l'échiquier à une instance d'échiquier
	*/
	QString obtenirImage() const override { return echiquier; }

private:
	const QString echiquier = "images/Chess_board.png";	// Toutes les pièces doivent pouvoir accéder facilement aux cases de 
														// l'échiquier. C'est pourquoi l'attribut cases est public et qu'il n'y a
														// pas d'encapsulation.
	
};
