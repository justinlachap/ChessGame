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
		 * Associe l'image d'une pi�ce ou d'un �chiquier � une instance.
		 */
		virtual QString obtenirImage() const = 0;
	};
}

class Echiquier : public UI::MethodeVirtuelleQt
{
public:
	Piece *cases[8][8];

	/**
	 * Remplit l'�chiquier de nullptrs
	 */
	void initialiserVide();

	/**
	 * Associe l'image de l'�chiquier � une instance d'�chiquier
	 */
	QString obtenirImage() const override { return echiquier; }

private:
	const QString echiquier = "images/Chess_board.png"; // Toutes les pi�ces doivent pouvoir acc�der facilement aux cases de
														// l'�chiquier. C'est pourquoi l'attribut cases est public et qu'il n'y a
														// pas d'encapsulation.
};
