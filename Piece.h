//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//																																	//
// Une pièce à un nom, une couleur, une position, des mouvements disponibles et on y associe une image afin de l'identifier			//
// 																																	//
// Par :																															//
//		Généreux, Esmé (2081518)																									//
//		Lachapelle, Justin (2076412)																								//
// 																																	//
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#pragma once
#include "Echiquier.h"

namespace Logique
{
	class MethodeVirtuelleLogique
	{
	public:
		/**
		 * Fonction virtuelle qui calcule les mouvements possibles pour chaque type de pièce selon la disposition de l'echiquier
		 * @ param e_ : instance de l'echiquier
		 */
		virtual void calculerMouvements(Echiquier e) = 0;
	};
}

class Piece : public Logique::MethodeVirtuelleLogique,
	public UI::MethodeVirtuelleQt
{
protected:
	char nom_;
	bool estBlanc_;
	std::pair<int, int> position_;
	std::vector<std::pair<int, int>> mouvementsDisponibles_;

public:
	Piece(Echiquier& nouvelEchiquier, std::pair<int, int> position, char nom, bool estBlanc);

	/**
	 * Déclarée dans la classe Logique::MethodeVirtuelleLogique, méthode virtuelle pure
	 */
	virtual void calculerMouvements(Echiquier e) override = 0;

	/**
	 * Déclarée dans la classe UI::MethodeVirtuelleQt, méthode virtuelle pure
	 */
	virtual QString obtenirImage() const override = 0;

	/**
	 * Permet d'afficher les mouvements possibles calculés d'une pièce (utilisée pour fin de déboggage)
	 */
	void afficheMouvements() const;

	/**
	 * Permet de changer la position d'une Pièce
	 * @param x : position de la pièce sur les colonnes de l'échiquier 
	 * @param y : position de la pièce sur les rangées de l'échiquier
	 * @param e_ : l'échiquier sur lequel se trouve la pièce
	 */
	void changerPos(int x, int y, Echiquier& e);

	/**
	 * Getters pour la couleur, la position et les mouvements disponibles d'une pièce
	 */
	bool obtenirCouleur() { return estBlanc_; }
	std::pair<int, int> obtenirPosition() { return position_; }
	std::vector<std::pair<int, int>> obtenirMouvements() const { return mouvementsDisponibles_; }
};
