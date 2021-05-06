/////////////////////////////////////////////////////////////////////
//																   //
// La vue de l'interface graphique utilisateur du jeux d'échec	   //
// 																   //
// Par :														   //
//		Généreux, Esmé (2081518)								   //
//		Lachapelle, Justin (2076412)							   //
// 																   //
/////////////////////////////////////////////////////////////////////

#include "ChessWindow.hpp"
#include "Pion.h"
#include "Tour.h"
#include "Cavalier.h"
#include "Fou.h"
#include "Dame.h"
#include "Roi.h"

#pragma warning(push, 0) // Sinon Qt fait des avertissements à /W4.

#include <QPixmap>
#pragma pop()
#include <QThread>
#include <iostream>
#include <QGraphicsSceneEvent>
#include <Qgraphicsview>
#include <QDebug>
#include <QVBoxLayout>
#include <QComboBox>
#include <QPushButton>
#include <QListWidget>

using std::pair;

// 100 représente un huitième de la taille de l'image pour l'echiquier (800)
const int uneRangee = 100;		
const int uneColonne = 100;

UI::ChessWindow::ChessWindow(QWidget* parent)
	: QMainWindow(parent)
{
	setWindowTitle("Jeu d'échecs");
	setMouseTracking(true);
	//setUI();

	// Initalisation de l'échiquier
	e_.initialiserVide();
	QPixmap echiquier;
	echiquier.load(e_.obtenirImage());
	echiquier = echiquier.scaled(800, 800, Qt::KeepAspectRatio);

	scene_ = new QGraphicsScene(this);
	scene_->setSceneRect(0, 0, 800, 800);
	view_ = new QGraphicsView(scene_);

	//choisir type de layout
	int choix = 0;
	std::cout << "\n";
	std::cout << "Choisir une position parmi les suivantes en rentrant le numéro: \n";
	std::cout << "		1. Position initiale \n";
	std::cout << "		2. Défense berlinoise \n";
	std::cout << "		3. Défense sicilienne variation Najdorf \n";
	std::cout << "		4. Position de fin de partie \n";

	while (choix == 0)
		std::cin >> choix;

	QGraphicsPixmapItem* item = new QGraphicsPixmapItem(echiquier);
	item->setPos(0, 0);
	scene_->addItem(item);

	// set position initiales des pieces de l'echiquier
	if (choix == 1)
		positionInitiale();
	else if (choix == 2)
		berlinDefense();
	else if (choix == 3)
		sicilianNajdorf();
	else if (choix == 4)
		endGame();

	for (Piece* piece : pieces_)
	{
		QPixmap img = piece->obtenirImage();
		img = img.scaled(uneRangee, uneColonne, Qt::KeepAspectRatio);
		CustomItem* c = new CustomItem(img, piece, &e_, scene_, &tourAuBlanc_);
		c->setPos(piece->obtenirPosition().first * uneRangee, uneColonne * (7 - piece->obtenirPosition().second));
		scene_->addItem(c);
	}

	for (Piece* piece : pieces_)
		piece->calculerMouvements(e_);

	setCentralWidget(view_);
}

UI::CustomItem::CustomItem(QPixmap img, Piece* piece, Echiquier* echiquier, QGraphicsScene* scene, bool* tour) 
	: QGraphicsPixmapItem(img), p_(piece), ech_(echiquier), s_(scene), tourDeJouer_(tour)
{
	setFlag(QGraphicsItem::ItemIsMovable, true);
}

void UI::ChessWindow::setUI() {
	// Le sélecteur pour filtrer ce que l'on souhaite dans la liste
	QComboBox* showCombobox = new QComboBox(this);
	showCombobox->addItem("Nouvelle Partie"); // Index 0
	connect(showCombobox, SIGNAL(currentIndexChanged(int)),
		this, SLOT(filterList(int)));

	// Le bouton pour congédier tout le monde
	QPushButton* nouvelePartieButton = new QPushButton(this);
	nouvelePartieButton->setText("Nouvelle partie");
	connect(nouvelePartieButton, SIGNAL(clicked()), this, SLOT(nouvellePartie()));

	QVBoxLayout* listLayout = new QVBoxLayout;
	listLayout->addWidget(showCombobox);
	listLayout->addWidget(nouvelePartieButton);
	QThread::sleep(5);
}

/*
**Permet de centrer les pieces lorsqu'elles sont bougées sur une case des mouvements disponibles
*/
void UI::CustomItem::centrerLesPiecesSurUneCase(int& x, int& y) //////////////////////////////////////////Might need to return x and y
{
	int milieuCase = 50;

	if ((int)pos().x() % uneRangee > milieuCase)
		x = uneRangee + pos().x() - ((int)(pos().x()) % uneRangee);
	else
		x = pos().x() - ((int)(pos().x()) % uneRangee);

	if ((int)pos().y() % uneColonne > milieuCase)
		y = uneColonne + pos().y() - ((int)(pos().y()) % uneColonne);
	else
		y = pos().y() - ((int)(pos().y()) % uneColonne);
}

/*
** Permet de renouvler l'affichage des points verts après avoit effectuer un mouvement
*/
void UI::CustomItem::renouvlerMouvementsDisponibles(int& x, int& y)
{
	int tailleEchiquierMax = 8;
	int tailleEchiquierMin = 0;
	int indexEchiquierMax = 7;
	bool peutBouger = false;

	for (std::pair<int, int> i : p_->obtenirMouvements())
		if ((i.first * uneRangee == x) && (uneColonne * (indexEchiquierMax - i.second) == y) && (*tourDeJouer_ == p_->obtenirCouleur()))
		{
			// ancienne position a nullptr
			ech_->cases[p_->obtenirPosition().first][p_->obtenirPosition().second] = nullptr;

			// enlever un item si il y a une capture
			for (auto item : s_->items())
				if (item->x() == x && item->y() == y)
					s_->removeItem(item);
			setPos(x, y);
			p_->changerPos(i.first, i.second, ech_);

			// recalculer les mouvements disponibles lorsqu'une piece bouge
			for (int j = tailleEchiquierMin; j < tailleEchiquierMax; j++)
				for (int k = tailleEchiquierMin; k < tailleEchiquierMax; k++)
					if (ech_->cases[j][k] != nullptr)
						ech_->cases[j][k]->calculerMouvements(*ech_);

			peutBouger = true;
			*tourDeJouer_ ^= true;
			break;
		}

	if (!peutBouger)
	{
		setPos(p_->obtenirPosition().first * uneRangee, (7 - p_->obtenirPosition().second) * uneColonne);
		qDebug() << "Mouvement impossible ou ce n'est pas à votre tour de jouer!";
	}
}

void UI::CustomItem::mouseReleaseEvent(QGraphicsSceneMouseEvent* e)
{
	///////////////////////////////////////////////////////////////////////////////////////////////////// enlever quoi???
	for (QGraphicsPixmapItem* x : v_)
		s_->removeItem(x);
	
	int x(0), y(0);
	centrerLesPiecesSurUneCase(x, y);
	renouvlerMouvementsDisponibles(x, y);

	QGraphicsPixmapItem::mouseReleaseEvent(e);
}

// permet de update les points verts selon le click sur une pièce 
void UI::CustomItem::mousePressEvent(QGraphicsSceneMouseEvent* e)
{
	// enlever les points verts
	for (QGraphicsPixmapItem* x : v_)
		s_->removeItem(x);

	int x(0), y(0);
	QPixmap pix5;
	pix5.load("images/sqaure.png");
	QGraphicsPixmapItem* item = new QGraphicsPixmapItem(pix5);
	item->setPos(uneRangee * p_->obtenirPosition().first, uneColonne * (7 - p_->obtenirPosition().second));
	s_->addItem(item);
	v_.push_back(item);

	// rajouter les points verts
	int grosseurImage = 50;
	for (std::pair<int, int> i : p_->obtenirMouvements())
	{
		QPixmap pix5;
		pix5.load("images/green.png");
		pix5 = pix5.scaled(grosseurImage, grosseurImage);
		QGraphicsPixmapItem* item = new QGraphicsPixmapItem(pix5);
		item->setPos(uneRangee * i.first + 25, uneColonne * (7 - i.second) + 25);
		s_->addItem(item);
		v_.push_back(item);
	}
	QGraphicsPixmapItem::mousePressEvent(e);
}

void UI::ChessWindow::positionInitiale()
{
	Roi* R1 = new Roi(e_, pair(4, 0), true);
	Roi* R2 = new Roi(e_, pair(4, 7), false);
	Roi* R3 = new Roi(e_, pair(3, 3), true); // On essaie de creer un troisieme roi

	Dame* d1 = new Dame(e_, pair(3, 0), true);
	Dame* d2 = new Dame(e_, pair(3, 7), false);

	Pion* P1 = new Pion(e_, pair(0, 1), true);
	Pion* P2 = new Pion(e_, pair(1, 1), true);
	Pion* P3 = new Pion(e_, pair(2, 1), true);
	Pion* P4 = new Pion(e_, pair(3, 1), true);
	Pion* P5 = new Pion(e_, pair(4, 1), true);
	Pion* P6 = new Pion(e_, pair(5, 1), true);
	Pion* P7 = new Pion(e_, pair(6, 1), true);
	Pion* P8 = new Pion(e_, pair(7, 1), true);
	Pion* P9 = new Pion(e_, pair(0, 6), false);
	Pion* P10 = new Pion(e_, pair(1, 6), false);
	Pion* P11 = new Pion(e_, pair(2, 6), false);
	Pion* P12 = new Pion(e_, pair(3, 6), false);
	Pion* P13 = new Pion(e_, pair(4, 6), false);
	Pion* P14 = new Pion(e_, pair(5, 6), false);
	Pion* P15 = new Pion(e_, pair(6, 6), false);
	Pion* P16 = new Pion(e_, pair(7, 6), false);

	Cavalier* c1 = new Cavalier(e_, pair(1, 0), true);
	Cavalier* c2 = new Cavalier(e_, pair(6, 0), true);
	Cavalier* c3 = new Cavalier(e_, pair(1, 7), false);
	Cavalier* c4 = new Cavalier(e_, pair(6, 7), false);

	Tour* r1 = new Tour(e_, pair(0, 0), true);
	Tour* r2 = new Tour(e_, pair(7, 0), true);
	Tour* r3 = new Tour(e_, pair(0, 7), false);
	Tour* r4 = new Tour(e_, pair(7, 7), false);

	Fou* f1 = new Fou(e_, pair(2, 0), true);
	Fou* f2 = new Fou(e_, pair(5, 0), true);
	Fou* f3 = new Fou(e_, pair(2, 7), false);
	Fou* f4 = new Fou(e_, pair(5, 7), false);

	pieces_ = { R1 , R2, d1, d2,P1,P2,P3,P4,P5,P6,P7,P8,P9,P10,P11,P12,P13,P14,P15,P16,c1,c2,c3,c4,r1,r2,r3,r4,f1,f2,f3,f4 };
}

void UI::ChessWindow::berlinDefense()
{
	Roi* R1 = new Roi(e_, pair(4, 0), true);
	Roi* R2 = new Roi(e_, pair(4, 7), false);
	Roi* R3 = new Roi(e_, pair(3, 3), true); // On essaie de creer un troisieme roi

	Dame* d1 = new Dame(e_, pair(3, 0), true);
	Dame* d2 = new Dame(e_, pair(3, 7), false);

	Pion* P1 = new Pion(e_, pair(0, 1), true);
	Pion* P2 = new Pion(e_, pair(1, 1), true);
	Pion* P3 = new Pion(e_, pair(2, 1), true);
	Pion* P4 = new Pion(e_, pair(3, 1), true);
	Pion* P5 = new Pion(e_, pair(4, 3), true);
	Pion* P6 = new Pion(e_, pair(5, 1), true);
	Pion* P7 = new Pion(e_, pair(6, 1), true);
	Pion* P8 = new Pion(e_, pair(7, 1), true);
	Pion* P9 = new Pion(e_, pair(0, 5), false);
	Pion* P10 = new Pion(e_, pair(1, 6), false);
	Pion* P11 = new Pion(e_, pair(2, 6), false);
	Pion* P12 = new Pion(e_, pair(3, 6), false);
	Pion* P13 = new Pion(e_, pair(4, 4), false);
	Pion* P14 = new Pion(e_, pair(5, 6), false);
	Pion* P15 = new Pion(e_, pair(6, 6), false);
	Pion* P16 = new Pion(e_, pair(7, 6), false);

	Cavalier* c1 = new Cavalier(e_, pair(1, 0), true);
	Cavalier* c2 = new Cavalier(e_, pair(5, 2), true);
	Cavalier* c3 = new Cavalier(e_, pair(2, 5), false);
	Cavalier* c4 = new Cavalier(e_, pair(5, 5), false);

	Tour* r1 = new Tour(e_, pair(0, 0), true);
	Tour* r2 = new Tour(e_, pair(7, 0), true);
	Tour* r3 = new Tour(e_, pair(0, 7), false);
	Tour* r4 = new Tour(e_, pair(7, 7), false);

	Fou* f1 = new Fou(e_, pair(2, 0), true);
	Fou* f2 = new Fou(e_, pair(1, 4), true);
	Fou* f3 = new Fou(e_, pair(2, 7), false);
	Fou* f4 = new Fou(e_, pair(5, 7), false);

	pieces_ = { R1 , R2, d1, d2,P1,P2,P3,P4,P5,P6,P7,P8,P9,P10,P11,P12,P13,P14,P15,P16,c1,c2,c3,c4,r1,r2,r3,r4,f1,f2,f3,f4 };
}

void UI::ChessWindow::sicilianNajdorf()
{
	Roi* R1 = new Roi(e_, pair(4, 0), true);
	Roi* R2 = new Roi(e_, pair(4, 7), false);
	Roi* R3 = new Roi(e_, pair(3, 3), true); // On essaie de creer un troisieme roi

	Dame* d1 = new Dame(e_, pair(3, 0), true);
	Dame* d2 = new Dame(e_, pair(3, 7), false);

	Pion* P1 = new Pion(e_, pair(0, 1), true);
	Pion* P2 = new Pion(e_, pair(1, 1), true);
	Pion* P3 = new Pion(e_, pair(2, 1), true);
	Pion* P4 = new Pion(e_, pair(3, 1), true);
	Pion* P5 = new Pion(e_, pair(4, 3), true);
	Pion* P6 = new Pion(e_, pair(5, 1), true);
	Pion* P7 = new Pion(e_, pair(6, 1), true);
	Pion* P8 = new Pion(e_, pair(7, 1), true);
	Pion* P9 = new Pion(e_, pair(0, 5), false);
	Pion* P10 = new Pion(e_, pair(1, 6), false);
	//Pion* P11 = new Pion(e, std::pair(2, 6), false);
	Pion* P12 = new Pion(e_, pair(3, 5), false);
	Pion* P13 = new Pion(e_, pair(4, 6), false);
	Pion* P14 = new Pion(e_, pair(5, 6), false);
	Pion* P15 = new Pion(e_, pair(6, 6), false);
	Pion* P16 = new Pion(e_, pair(7, 6), false);

	Cavalier* c1 = new Cavalier(e_, pair(2, 2), true);
	Cavalier* c2 = new Cavalier(e_, pair(3, 3), true);
	Cavalier* c3 = new Cavalier(e_, pair(1, 7), false);
	Cavalier* c4 = new Cavalier(e_, pair(5, 5), false);

	Tour* r1 = new Tour(e_, pair(0, 0), true);
	Tour* r2 = new Tour(e_, pair(7, 0), true);
	Tour* r3 = new Tour(e_, pair(0, 7), false);
	Tour* r4 = new Tour(e_, pair(7, 7), false);

	Fou* f1 = new Fou(e_, pair(2, 0), true);
	Fou* f2 = new Fou(e_, pair(5, 0), true);
	Fou* f3 = new Fou(e_, pair(2, 7), false);
	Fou* f4 = new Fou(e_, pair(5, 7), false);

	pieces_ = { R1 , R2, d1, d2,P1,P2,P3,P4,P5,P6,P7,P8,P9,P10,P12,P13,P14,P15,P16,c1,c2,c3,c4,r1,r2,r3,r4,f1,f2,f3,f4 };
}

void UI::ChessWindow::endGame()
{
	Roi* R1 = new Roi(e_, pair(0, 4), true);
	Roi* R2 = new Roi(e_, pair(1, 7), false);

	Pion* P1 = new Pion(e_, pair(1, 5), true);
	Pion* P2 = new Pion(e_, pair(6, 1), true);
	Pion* P3 = new Pion(e_, pair(2, 6), false);
	Pion* P4 = new Pion(e_, pair(5, 4), false);

	pieces_ = { R1,R2, P1, P2, P3, P4 };
}