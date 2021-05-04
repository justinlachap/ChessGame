// La Vue-Controlleur pour calculatrice simple.
// Par Francois-R.Boyer@PolyMtl.ca

#include "ChessWindow.hpp"

#pragma warning(push, 0) // Sinon Qt fait des avertissements à /W4.

#include <QPixmap>
#pragma pop()
#include <iostream>
#include <QGraphicsSceneEvent>
#include <Qgraphicsview>
#include <QDebug>

using std::pair;

UI::ChessWindow::ChessWindow(QWidget* parent) :
	QMainWindow(parent)
{
	// Nom de la fenêtre
	setWindowTitle("Jeu d'échecs");
	setMouseTracking(true);

	// Initalisation de l'échiquier
	e.initialiserVide();
	QPixmap echiquier;
	echiquier.load(e.obtenirImage());
	echiquier = echiquier.scaled(800, 800, Qt::KeepAspectRatio);

	// Initialisation des pièces
	scene = new QGraphicsScene(this);
	scene->setSceneRect(0, 0, 800, 800);
	view = new QGraphicsView(scene);


	QGraphicsPixmapItem* item = new QGraphicsPixmapItem(echiquier);
	item->setPos(0, 0);
	scene->addItem(item);

	/*Choisir une position parmi les suivantes*/
		//positionInitiale();
		berlinDefense();
	//sicilianNajdorf();
	//endGame();
/*										  */

	for (auto& piece : pieces) {
		QPixmap img = piece->obtenirImage();
		img = img.scaled(100, 100, Qt::KeepAspectRatio);
		customitem* c = new customitem(img, piece, &e, scene);
		c->setPos(piece->obtenirPosition().first * 100, 100 * (7 - piece->obtenirPosition().second));
		scene->addItem(c);

	}

	for (auto& piece : pieces) {
		piece->calculerMouvements(e);
	}

	setCentralWidget(view);
	qDebug() << "Constructeur appele" << Qt::endl;

}



void  customitem::mouseReleaseEvent(QGraphicsSceneMouseEvent* e) {
	//qDebug() << pos().x();
	for (auto& x : v) {
		s->removeItem(x);
	}
	int x(0), y(0);
	if ((int)pos().x() % 100 > 50)
		x = 100 + pos().x() - ((int)(pos().x()) % 100);
	else
		x = pos().x() - ((int)(pos().x()) % 100);

	if ((int)pos().y() % 100 > 50)
		y = 100 + pos().y() - ((int)(pos().y()) % 100);
	else
		y = pos().y() - ((int)(pos().y()) % 100);

	bool peuxBouger = false;
	for (auto i : p->obtenirMouvements()) {
		if (i.first * 100 == x && (100 * (7 - i.second) == y)) {
			setPos(x, y);
			p->changerPos(i.first, i.second, ech);
			for (int j = 0; j < 8; j++)
				for (int k = 0; k < 8; k++) {
					if (ech->cases[j][k] != nullptr)
						ech->cases[j][k]->calculerMouvements(*ech);
					// À compléter, pour les captures de pièces, enlever la piece capturee
					/*if (ech->cases[j][k]->obtenirPosition() == pair(i.first, i.second))
						s->removeItem*/
				}
			
			peuxBouger = true;
			break;
		}
	}
	if (!peuxBouger)
		qDebug() << "Mouvement impossible";


	QGraphicsPixmapItem::mouseReleaseEvent(e);
};

void customitem::mousePressEvent(QGraphicsSceneMouseEvent* e) {
	for (auto& x : v) {
		s->removeItem(x);
	}
	int x(0), y(0);
	QPixmap pix5;
	pix5.load("images/sqaure.png");
	QGraphicsPixmapItem* item = new QGraphicsPixmapItem(pix5);
	item->setPos(100 * p->obtenirPosition().first, 100 * (7 - p->obtenirPosition().second));
	s->addItem(item);
	v.push_back(item);
	//p->calculerMouvements(*ech);
	for (auto i : p->obtenirMouvements()) {
		QPixmap pix5;
		pix5.load("images/green.png");
		pix5 = pix5.scaled(50, 50);
		QGraphicsPixmapItem* item = new QGraphicsPixmapItem(pix5);
		item->setPos(100 * i.first + 25, 100 * (7 - i.second) + 25);
		s->addItem(item);
		v.push_back(item);
	}
	QGraphicsPixmapItem::mousePressEvent(e);


};

void UI::ChessWindow::positionInitiale()
{
	Roi* R1 = new Roi(e, pair(4, 0), true);
	Roi* R2 = new Roi(e, pair(4, 7), false);
	Roi* R3 = new Roi(e, pair(3, 3), true); // On essaie de creer un troisieme roi
	Dame* d1 = new Dame(e, pair(3, 0), true);
	Dame* d2 = new Dame(e, pair(3, 7), false);
	Pion* P1 = new Pion(e, pair(0, 1), true);
	Pion* P2 = new Pion(e, pair(1, 1), true);
	Pion* P3 = new Pion(e, pair(2, 1), true);
	Pion* P4 = new Pion(e, pair(3, 1), true);
	Pion* P5 = new Pion(e, pair(4, 1), true);
	Pion* P6 = new Pion(e, pair(5, 1), true);
	Pion* P7 = new Pion(e, pair(6, 1), true);
	Pion* P8 = new Pion(e, pair(7, 1), true);
	Pion* P9 = new Pion(e, pair(0, 6), false);
	Pion* P10 = new Pion(e, pair(1, 6), false);
	Pion* P11 = new Pion(e, pair(2, 6), false);
	Pion* P12 = new Pion(e, pair(3, 6), false);
	Pion* P13 = new Pion(e, pair(4, 6), false);
	Pion* P14 = new Pion(e, pair(5, 6), false);
	Pion* P15 = new Pion(e, pair(6, 6), false);
	Pion* P16 = new Pion(e, pair(7, 6), false);
	Cavalier* c1 = new Cavalier(e, pair(1, 0), true);
	Cavalier* c2 = new Cavalier(e, pair(6, 0), true);
	Cavalier* c3 = new Cavalier(e, pair(1, 7), false);
	Cavalier* c4 = new Cavalier(e, pair(6, 7), false);
	Tour* r1 = new Tour(e, pair(0, 0), true);
	Tour* r2 = new Tour(e, pair(7, 0), true);
	Tour* r3 = new Tour(e, pair(0, 7), false);
	Tour* r4 = new Tour(e, pair(7, 7), false);
	Fou* f1 = new Fou(e, pair(2, 0), true);
	Fou* f2 = new Fou(e, pair(5, 0), true);
	Fou* f3 = new Fou(e, pair(2, 7), false);
	Fou* f4 = new Fou(e, pair(5, 7), false);
	pieces = { R1 , R2, d1, d2,P1,P2,P3,P4,P5,P6,P7,P8,P9,P10,P11,P12,P13,P14,P15,P16,c1,c2,c3,c4,r1,r2,r3,r4,f1,f2,f3,f4 };
}

void UI::ChessWindow::berlinDefense()
{
	Roi* R1 = new Roi(e, pair(4, 0), true);
	Roi* R2 = new Roi(e, pair(4, 7), false);
	Roi* R3 = new Roi(e, pair(3, 3), true); // On essaie de creer un troisieme roi
	Dame* d1 = new Dame(e, pair(3, 0), true);
	Dame* d2 = new Dame(e, pair(3, 7), false);
	Pion* P1 = new Pion(e, pair(0, 1), true);
	Pion* P2 = new Pion(e, pair(1, 1), true);
	Pion* P3 = new Pion(e, pair(2, 1), true);
	Pion* P4 = new Pion(e, pair(3, 1), true);
	Pion* P5 = new Pion(e, pair(4, 3), true);
	Pion* P6 = new Pion(e, pair(5, 1), true);
	Pion* P7 = new Pion(e, pair(6, 1), true);
	Pion* P8 = new Pion(e, pair(7, 1), true);
	Pion* P9 = new Pion(e, pair(0, 5), false);
	Pion* P10 = new Pion(e, pair(1, 6), false);
	Pion* P11 = new Pion(e, pair(2, 6), false);
	Pion* P12 = new Pion(e, pair(3, 6), false);
	Pion* P13 = new Pion(e, pair(4, 4), false);
	Pion* P14 = new Pion(e, pair(5, 6), false);
	Pion* P15 = new Pion(e, pair(6, 6), false);
	Pion* P16 = new Pion(e, pair(7, 6), false);
	Cavalier* c1 = new Cavalier(e, pair(1, 0), true);
	Cavalier* c2 = new Cavalier(e, pair(5, 2), true);
	Cavalier* c3 = new Cavalier(e, pair(2, 5), false);
	Cavalier* c4 = new Cavalier(e, pair(5, 5), false);
	Tour* r1 = new Tour(e, pair(0, 0), true);
	Tour* r2 = new Tour(e, pair(7, 0), true);
	Tour* r3 = new Tour(e, pair(0, 7), false);
	Tour* r4 = new Tour(e, pair(7, 7), false);
	Fou* f1 = new Fou(e, pair(2, 0), true);
	Fou* f2 = new Fou(e, pair(1, 4), true);
	Fou* f3 = new Fou(e, pair(2, 7), false);
	Fou* f4 = new Fou(e, pair(5, 7), false);
	pieces = { R1 , R2, d1, d2,P1,P2,P3,P4,P5,P6,P7,P8,P9,P10,P11,P12,P13,P14,P15,P16,c1,c2,c3,c4,r1,r2,r3,r4,f1,f2,f3,f4 };
}

void UI::ChessWindow::sicilianNajdorf()
{
	Roi* R1 = new Roi(e, pair(4, 0), true);
	Roi* R2 = new Roi(e, pair(4, 7), false);
	Roi* R3 = new Roi(e, pair(3, 3), true); // On essaie de creer un troisieme roi
	Dame* d1 = new Dame(e, pair(3, 0), true);
	Dame* d2 = new Dame(e, pair(3, 7), false);
	Pion* P1 = new Pion(e, pair(0, 1), true);
	Pion* P2 = new Pion(e, pair(1, 1), true);
	Pion* P3 = new Pion(e, pair(2, 1), true);
	Pion* P4 = new Pion(e, pair(3, 1), true);
	Pion* P5 = new Pion(e, pair(4, 3), true);
	Pion* P6 = new Pion(e, pair(5, 1), true);
	Pion* P7 = new Pion(e, pair(6, 1), true);
	Pion* P8 = new Pion(e, pair(7, 1), true);
	Pion* P9 = new Pion(e, pair(0, 5), false);
	Pion* P10 = new Pion(e, pair(1, 6), false);
	//Pion* P11 = new Pion(e, std::pair(2, 6), false);
	Pion* P12 = new Pion(e, pair(3, 5), false);
	Pion* P13 = new Pion(e, pair(4, 6), false);
	Pion* P14 = new Pion(e, pair(5, 6), false);
	Pion* P15 = new Pion(e, pair(6, 6), false);
	Pion* P16 = new Pion(e, pair(7, 6), false);
	Cavalier* c1 = new Cavalier(e, pair(2, 2), true);
	Cavalier* c2 = new Cavalier(e, pair(3, 3), true);
	Cavalier* c3 = new Cavalier(e, pair(1, 7), false);
	Cavalier* c4 = new Cavalier(e, pair(5, 5), false);
	Tour* r1 = new Tour(e, pair(0, 0), true);
	Tour* r2 = new Tour(e, pair(7, 0), true);
	Tour* r3 = new Tour(e, pair(0, 7), false);
	Tour* r4 = new Tour(e, pair(7, 7), false);
	Fou* f1 = new Fou(e, pair(2, 0), true);
	Fou* f2 = new Fou(e, pair(5, 0), true);
	Fou* f3 = new Fou(e, pair(2, 7), false);
	Fou* f4 = new Fou(e, pair(5, 7), false);
	pieces = { R1 , R2, d1, d2,P1,P2,P3,P4,P5,P6,P7,P8,P9,P10,P12,P13,P14,P15,P16,c1,c2,c3,c4,r1,r2,r3,r4,f1,f2,f3,f4 };
}

void UI::ChessWindow::endGame()
{
	Roi* R1 = new Roi(e, pair(0, 5), true);
	Roi* R2 = new Roi(e, pair(1, 7), false);
	Pion* P1 = new Pion(e, pair(1, 5), true);
	Pion* P2 = new Pion(e, pair(6, 1), true);
	Pion* P3 = new Pion(e, pair(2, 6), false);
	Pion* P4 = new Pion(e, pair(5, 4), false);
	pieces = { R1,R2, P1, P2, P3, P4 };
}
