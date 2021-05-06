/*
** Livrable 2
** Par Justin Lachapelle, matricule 2076412 et Esmé Généreux, matricule 2081518.
*/

#pragma once
#include "Echiquier.h"

namespace Logique
{
	class MethodeVirtuelleLogique
	{
	public:
		virtual void calculerMouvements(Echiquier e_) = 0;
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

	virtual void calculerMouvements(Echiquier e_) override = 0;
	virtual QString obtenirImage() const override = 0;

	void afficheMouvements() const;
	void changerPos(int x, int y, Echiquier* e_);

	bool obtenirCouleur() { return estBlanc_; }
	std::pair<int, int> obtenirPosition() { return position_; }
	std::vector<std::pair<int, int>> obtenirMouvements() const { return mouvementsDisponibles_; }
};
