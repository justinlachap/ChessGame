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
class Echiquier;

namespace Logique
{
	class MethodeVirtuelleLogique
	{
	public:
		virtual void calculerMouvements(Echiquier e) = 0;
	};
}

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

	QString obtenirImage() const override
	{
		return echiquier;
	}

private:
	const QString echiquier = "images/Chess_board.png";
	// Toutes les pièces doivent pouvoir accéder facilement aux cases de l'échiquier. 
	// C'est pourquoi l'attribut cases est public et qu'il n'y a pas d'encapsulation.
};

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

	virtual void calculerMouvements(Echiquier e) override = 0;
	virtual QString obtenirImage() const override = 0;

	void afficheMouvements() const;
	void estCapturé() {};

	bool obtenirCouleur() { return estBlanc_; }
	std::pair<int, int> obtenirPosition() { return position_ ; }
	std::vector<std::pair<int, int>> obtenirMouvements() const { return mouvementsDisponibles_; }
	std::pair<int, int> obtenirPosition() const { return position_; }
};

class Pion : virtual public Piece
{
	const QString pionBlanc = "images/white_pawn.png";
	const QString pionNoir = "images/black_pawn.png";

public:
	Pion(Echiquier& nouvelEchiquier, std::pair<int, int> position, bool estBlanc);

	void calculerMouvements(Echiquier e) override;

	QString obtenirImage() const override
	{
		if (estBlanc_)
			return pionBlanc;
		else
			return pionNoir;
	}
};

class Cavalier : virtual public Piece
{
	const QString cavalierBlanc = "images/white_knight.png";
	const QString cavalierNoir = "images/black_knight.png";

public:
	Cavalier(Echiquier& nouvelEchiquier, std::pair<int, int> position, bool estBlanc);

	void calculerMouvements(Echiquier e) override;

	QString obtenirImage() const override 
	{
		if (estBlanc_)
			return cavalierBlanc;
		else
			return cavalierNoir;
	}
};

class Roi : virtual public Piece
{
	const QString roiBlanc = "images/white_king.png";
	const QString roineNoir = "images/black_king.png";
	inline static int compteurInstances_ = 0;

public:
	Roi(Echiquier& nouvelEchiquier, std::pair<int, int> position, bool estBlanc);

	void calculerMouvements(Echiquier e) override;

	bool estEnÉchec(std::vector<std::pair<int, int>>);

	QString obtenirImage() const override
	{
		if (estBlanc_)
			return roiBlanc;
		else
			return roineNoir;
	}
};

class Tour : virtual public Piece
{
	const QString tourBlanche = "images/white_rook.png";
	const QString tourNoire = "images/black_rook.png";

public:
	Tour(Echiquier& nouvelEchiquier, std::pair<int, int> position, bool estBlanc);

	void calculerMouvements(Echiquier e) override;

	QString obtenirImage() const override
	{
		if (estBlanc_)
			return tourBlanche;
		else
			return tourNoire;
	}
};

class Fou : virtual public Piece
{
	const QString fouBlanc = "images/white_bishop.png";
	const QString fouNoir = "images/black_bishop.png";

public:
	Fou(Echiquier& nouvelEchiquier, std::pair<int, int> position, bool estBlanc);

	void calculerMouvements(Echiquier e) override;

	QString obtenirImage() const override
	{
		if (estBlanc_)
			return fouBlanc;
		else
			return fouNoir;
	}
};

class Dame : virtual public Piece, 
	public Fou, 
	public Tour
{
	const QString reineBlanche = "images/white_queen.png";
	const QString reineNoire = "images/black_queen.png";

public:
	Dame(Echiquier& nouvelEchiquier, std::pair<int, int> position, bool estBlanc);

	void calculerMouvements(Echiquier e) override;

	QString obtenirImage() const override
	{
		if (estBlanc_)
			return reineBlanche;
		else
			return reineNoire;
	}
};