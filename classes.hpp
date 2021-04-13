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
	// Toutes les pièces doivent pouvoir accéder facilement aux cases de l'échiquier. 
	// C'est pourquoi l'attribut cases est public et qu'il n'y a pas d'encapsulation.
};

class Piece // public QObject
{
	// Q_OBJECT
protected:
	std::pair<int, int> m_position;
	std::string m_couleur;
	std::vector<std::pair<int, int>> m_mouvementsDisponibles; 

// public slots:

public:
	Piece(Echiquier& nouvelEchiquier, std::pair<int, int> position, std::string couleur);
	int conversionCouleurInt(); 
	void afficheMouvements();
	void estCapturé() {};
	std::vector<std::pair<int, int>> obtenirMouvements() { return m_mouvementsDisponibles; }
};


class Pion : public Piece
{
public:
	Pion(Echiquier& nouvelEchiquier, std::pair<int, int> position, std::string couleur);
	void calculeMouvements(Echiquier e);

private:
	const static int m_pionBlanc = 6; // Ces constantes serviront plus tard à bien afficher les bonnes pièces sur l'interface
	const static int m_pionNoir = 12;
};

class Cavalier : public Piece
{
public:
	Cavalier(Echiquier& nouvelEchiquier, std::pair<int, int> position, std::string couleur);
	void calculeMouvements(Echiquier e);
private:
	const static int m_cavalierBlanc = 3;
	const static int m_cavalierNoir = 9;
};

class Roi : public Piece
{
public:
	Roi(Echiquier& nouvelEchiquier, std::pair<int, int> position, std::string couleur);
	void calculeMouvements(Echiquier e);
private:
	const static int m_roiBlanc = 1;
	const static int m_roiNoir = 7;
};

class Dame : public Piece
{
public:
	Dame(Echiquier& nouvelEchiquier, std::pair<int, int> position, std::string couleur);
	void calculeMouvements(Echiquier e);
private:
	const static int m_dameBlanc = 2;
	const static int m_dameNoir = 8;
};

class Tour : public Piece
{
public:
	Tour(Echiquier& nouvelEchiquier, std::pair<int, int> position, std::string couleur);
	void calculeMouvements(Echiquier e);
private:
	const static int m_tourBlanc = 4;
	const static int m_tourNoir = 10;
};

class Fou : public Piece
{
public:
	Fou(Echiquier& nouvelEchiquier, std::pair<int, int> position, std::string couleur);
	void calculeMouvements(Echiquier e);
private:
	const static int m_fouBlanc = 5;
	const static int m_fouNoir = 11;
};