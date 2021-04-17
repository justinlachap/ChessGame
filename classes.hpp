/*
** Livrable 1
** Par Justin Lachapelle, matricule 2076412 et Esmé Généreux, matricule 2081518.
*/

#pragma once
#pragma warning(push, 0) // Sinon Qt fait des avertissements à /W4.
#include <QObject>
#pragma pop()
#include <functional>
#include <vector>

class Echiquier // public QObject
{
public:
	void initialiserVide();
	int cases[8][8];
	QString obtenirImage() {
		return echiquier;
	}

private:
	const QString echiquier = "Chess_board.png";
	// Toutes les pièces doivent pouvoir accéder facilement aux cases de l'échiquier. 
	// C'est pourquoi l'attribut cases est public et qu'il n'y a pas d'encapsulation.
};

class classeVirtuelle // classe virtuelle d'où provient la fonction calculeMouvements utilisée par toutes les pièces.
{
public:
	virtual void calculeMouvements(Echiquier e) = 0;
	virtual QString obtenirImage() const = 0;
};


class Piece : public classeVirtuelle
{

protected:
	std::pair<int, int> position_;
	bool estBlanc_;
	std::vector<std::pair<int, int>> mouvementsDisponibles_;

public:
	Piece(Echiquier& nouvelEchiquier, std::pair<int, int> position, bool estBlanc);
	int conversionCouleurInt() const;
	void afficheMouvements() const;
	void calculeMouvements(Echiquier e) override = 0;
	QString obtenirImage() const override  = 0;
	void estCapturé() {};
	std::vector<std::pair<int, int>> obtenirMouvements() const { return mouvementsDisponibles_; }
	std::pair<int, int> obtenirPosition() const { return position_; }
};

class Pion : virtual public Piece
{
	const static int pionBlanc_ = 6; // Ces constantes serviront plus tard à bien afficher les bonnes pièces sur l'interface
	const static int pionNoir_ = 12;
	const QString pionBlanc = "white_pawn.png";
	const QString pionNoir = "black_pawn.png";

public:
	Pion(Echiquier& nouvelEchiquier, std::pair<int, int> position, bool estBlanc);
	void calculeMouvements(Echiquier e) override;
	QString obtenirImage() const override {
		if (estBlanc_)
			return pionBlanc;
		else
			return pionNoir;
	}
};

class Cavalier : virtual public Piece
{
	const static int cavalierBlanc_ = 3;
	const static int cavalierNoir_ = 9;
	const QString cavalierBlanc = "white_knight.png";
	const QString cavalierNoir = "black_knight.png";


public:
	Cavalier(Echiquier& nouvelEchiquier, std::pair<int, int> position, bool estBlanc);
	void calculeMouvements(Echiquier e) override;
	QString obtenirImage() const override {
		if (estBlanc_)
			return cavalierBlanc;
		else
			return cavalierNoir;
	}
	
};

class Roi : virtual public Piece
{
	const static int roiBlanc_ = 1;
	const static int roiNoir_ = 7;
	const QString roiBlanc = "white_king.png";
	const QString roineNoir = "black_king.png";

public:
	Roi(Echiquier& nouvelEchiquier, std::pair<int, int> position, bool estBlanc);
	void calculeMouvements(Echiquier e) override;
	bool estEnÉchec(std::vector<std::pair<int, int>>);
	QString obtenirImage() const override {
		if (estBlanc_)
			return roiBlanc;
		else
			return roineNoir;
	}
	
};

class Dame : virtual public Piece
{
	const static int dameBlanc_ = 2;
	const static int dameNoir_ = 8;
	const QString reineBlanche = "white_queen.png";
	const QString reineNoire = "black_queen.png";



public:
	Dame(Echiquier& nouvelEchiquier, std::pair<int, int> position, bool estBlanc);
	void calculeMouvements(Echiquier e) override;
	QString obtenirImage() const override {
		if (estBlanc_)
			return reineBlanche;
		else
			return reineNoire;
	}
	
};

class Tour : virtual public Piece
{
	const static int tourBlanc_ = 4;
	const static int tourNoir_ = 10;
	const QString tourBlanche = "white_rook.png";
	const QString tourNoire = "black_rook.png";

public:
	Tour(Echiquier& nouvelEchiquier, std::pair<int, int> position, bool estBlanc);
	void calculeMouvements(Echiquier e) override;
	QString obtenirImage() const override {
		if (estBlanc_)
			return tourBlanche;
		else
			return tourNoire;
	}
};

class Fou : virtual public Piece
{
	const static int fouBlanc_ = 5;
	const static int fouNoir_ = 11;
	const QString fouBlanc = "white_bishop.png";
	const QString fouNoir = "black_bishop.png";

public:
	Fou(Echiquier& nouvelEchiquier, std::pair<int, int> position, bool estBlanc);
	void calculeMouvements(Echiquier e) override;
	QString obtenirImage() const override {
		if (estBlanc_)
			return fouBlanc;
		else
			return fouNoir;
	}
};