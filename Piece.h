#pragma once
#include "Echiquier.h"

namespace Logique
{
	class MethodeVirtuelleLogique
	{
	public:
		/**
		 * Fonction virtuelle qui calcule les mouvements possibles pour chaque type de pi�ce selon la disposition de l'echiquier
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
	Piece(Echiquier &nouvelEchiquier, std::pair<int, int> position, char nom, bool estBlanc);

	/**
	 * D�clar�e dans la classe Logique::MethodeVirtuelleLogique, m�thode virtuelle pure
	 */
	virtual void calculerMouvements(Echiquier e) override = 0;

	/**
	 * D�clar�e dans la classe UI::MethodeVirtuelleQt, m�thode virtuelle pure
	 */
	virtual QString obtenirImage() const override = 0;

	/**
	 * Permet d'afficher les mouvements possibles calcul�s d'une pi�ce (utilis�e pour fin de d�boggage)
	 */
	void afficheMouvements() const;

	/**
	 * Permet de changer la position d'une Pi�ce
	 * @param x : position de la pi�ce sur les colonnes de l'�chiquier
	 * @param y : position de la pi�ce sur les rang�es de l'�chiquier
	 * @param e_ : l'�chiquier sur lequel se trouve la pi�ce
	 */
	void changerPos(int x, int y, Echiquier &e);

	/**
	 * Getters pour la couleur, la position et les mouvements disponibles d'une pi�ce
	 */
	bool obtenirCouleur() { return estBlanc_; }
	std::pair<int, int> obtenirPosition() { return position_; }
	std::vector<std::pair<int, int>> obtenirMouvements() const { return mouvementsDisponibles_; }
};
