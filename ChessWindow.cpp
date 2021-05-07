#include "ChessWindow.h"
#include "CustomItem.h"
#include "Pion.h"
#include "Tour.h"
#include "Cavalier.h"
#include "Fou.h"
#include "Dame.h"
#include "Roi.h"
#pragma warning(push, 0)
#include <iostream>
#include <QPixmap>
#include <QThread>
#include <QGraphicsview>
#include <QGraphicsPixmapItem>
#include <QVBoxLayout>
#include <QComboBox>
#include <QPushButton>

using std::pair;

// 100 représente un huitième de la taille de l'image pour l'echiquier (800)
const int uneRangee = 100;
const int uneColonne = 100;
const int tailleImageEchiquier = 800;

UI::ChessWindow::ChessWindow(QWidget* parent) : QMainWindow(parent)
{
	setWindowTitle("Jeu d'échecs");

	setMouseTracking(true);

	setEchiquier();

	calculerMouvementsVecteurPieces();

	setCentralWidget(view_);
}

void UI::ChessWindow::choisirLayoutPiece(QPixmap& echiquier)
{
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
	int classic = 1, berlinoise = 2, sicilienne = 3, finDeJeux = 4;
	if (choix == classic)
		positionInitiale();
	else if (choix == berlinoise)
		defenseBerlinoise();
	else if (choix == sicilienne)
		defenseSicilienneNajdorf();
	else if (choix == finDeJeux)
		finale();
}

void UI::ChessWindow::positionInitiale()
{
	Roi* R1 = new Roi(e_, pair(4, 0), true);
	Roi* R2 = new Roi(e_, pair(4, 7), false);
	Roi* R3 = new Roi(e_, pair(3, 3), true);	// On essaie de creer un troisieme roi

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

void UI::ChessWindow::defenseBerlinoise()
{
	Roi* R1 = new Roi(e_, pair(4, 0), true);
	Roi* R2 = new Roi(e_, pair(4, 7), false);

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

void UI::ChessWindow::defenseSicilienneNajdorf()
{
	Roi* R1 = new Roi(e_, pair(4, 0), true);
	Roi* R2 = new Roi(e_, pair(4, 7), false);

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

void UI::ChessWindow::finale()
{
	Roi* R1 = new Roi(e_, pair(0, 4), true);
	Roi* R2 = new Roi(e_, pair(1, 7), false);

	Pion* P1 = new Pion(e_, pair(1, 5), true);
	Pion* P2 = new Pion(e_, pair(6, 1), true);
	Pion* P3 = new Pion(e_, pair(2, 6), false);
	Pion* P4 = new Pion(e_, pair(5, 4), false);

	pieces_ = { R1,R2, P1, P2, P3, P4 };
}

void UI::ChessWindow::afficherImagesPieces()
{
	const int indexMaxEchiquier = 7;
	for (Piece* piece : pieces_)
	{
		QPixmap img = piece->obtenirImage();
		img = img.scaled(uneRangee, uneColonne, Qt::KeepAspectRatio);
		CustomItem* c = new CustomItem(img, piece, &e_, scene_, &tourAuBlanc_);
		c->setPos(piece->obtenirPosition().first * uneRangee, uneColonne * (indexMaxEchiquier - piece->obtenirPosition().second));
		scene_->addItem(c);
	}
}

void UI::ChessWindow::setEchiquier()
{
	e_.initialiserVide();
	QPixmap echiquier;
	echiquier.load(e_.obtenirImage());
	echiquier = echiquier.scaled(tailleImageEchiquier, tailleImageEchiquier, Qt::KeepAspectRatio);

	scene_ = new QGraphicsScene(this);
	scene_->setSceneRect(0, 0, tailleImageEchiquier, tailleImageEchiquier);
	view_ = new QGraphicsView(scene_);

	choisirLayoutPiece(echiquier);

	afficherImagesPieces();
}

void UI::ChessWindow::calculerMouvementsVecteurPieces()
{
	for (Piece* piece : pieces_)
		piece->calculerMouvements(e_);
}