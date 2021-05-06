/*
** Livrable 2
** Par Justin Lachapelle, matricule 2076412 et Esmé Généreux, matricule 2081518.
*/

#pragma once
#pragma warning(push, 0) // Sinon Qt fait des avertissements à /W4.
#include <QObject>
#pragma pop()
#include <functional>
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
	// Toutes les pièces doivent pouvoir accéder facilement aux cases de l'échiquier. 
	// C'est pourquoi l'attribut cases est public et qu'il n'y a pas d'encapsulation.
};
