/*
** Livrable 1
** Par Justin Lachapelle, matricule 2076412 et Esm� G�n�reux, matricule 2081518.
*/

#pragma once
#pragma warning(push, 0) // Sinon Qt fait des avertissements � /W4.
#include <QObject>
#pragma pop()
#include <functional>
#include <vector>

class Echiquier // public QObject
{
public:
	void initialiserVide();
	int cases[8][8];
	// Toutes les pi�ces doivent pouvoir acc�der facilement aux cases de l'�chiquier. 
	// C'est pourquoi l'attribut cases est public et qu'il n'y a pas d'encapsulation.
};

class Calcule // classe virtuelle d'o� provient la fonction calculeMouvements utilis�e par toutes les pi�ces.
{
public:
	virtual void calculeMouvements(Echiquier e) = 0;
};


class Piece : public Calcule
{

protected:
	std::pair<int, int> position_;
	bool estBlanc_;
	std::vector<std::pair<int, int>> mouvementsDisponibles_;



public:
	Piece(Echiquier& nouvelEchiquier, std::pair<int, int> position, bool estBlanc);
	int conversionCouleurInt() const;
	void afficheMouvements();
	void calculeMouvements(Echiquier e) override = 0;
	void estCaptur�() {};
	std::vector<std::pair<int, int>> obtenirMouvements() { return mouvementsDisponibles_; }
};

class Pion : virtual public Piece
{
	const static int pionBlanc_ = 6; // Ces constantes serviront plus tard � bien afficher les bonnes pi�ces sur l'interface
	const static int pionNoir_ = 12;

public:
	Pion(Echiquier& nouvelEchiquier, std::pair<int, int> position, bool estBlanc);
	void calculeMouvements(Echiquier e) override;
};

class Cavalier : virtual public Piece
{
	const static int cavalierBlanc_ = 3;
	const static int cavalierNoir_ = 9;

public:
	Cavalier(Echiquier& nouvelEchiquier, std::pair<int, int> position, bool estBlanc);
	void calculeMouvements(Echiquier e) override;
};

class Roi : virtual public Piece
{
	const static int roiBlanc_ = 1;
	const static int roiNoir_ = 7;

public:
	Roi(Echiquier& nouvelEchiquier, std::pair<int, int> position, bool estBlanc);
	void calculeMouvements(Echiquier e) override;
	bool estEn�chec(std::vector<std::pair<int, int>>);
};

class Dame : virtual public Piece
{
	const static int dameBlanc_ = 2;
	const static int dameNoir_ = 8;

public:
	Dame(Echiquier& nouvelEchiquier, std::pair<int, int> position, bool estBlanc);
	void calculeMouvements(Echiquier e) override;
};

class Tour : virtual public Piece
{
	const static int tourBlanc_ = 4;
	const static int tourNoir_ = 10;

public:
	Tour(Echiquier& nouvelEchiquier, std::pair<int, int> position, bool estBlanc);
	void calculeMouvements(Echiquier e) override;
};

class Fou : virtual public Piece
{
	const static int fouBlanc_ = 5;
	const static int fouNoir_ = 11;

public:
	Fou(Echiquier& nouvelEchiquier, std::pair<int, int> position, bool estBlanc);
	void calculeMouvements(Echiquier e) override;
};