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
#include <QVBoxLayout>
#include <QComboBox>
#include <QPushButton>
#include <QListWidget>

using std::pair;

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
}

UI::ChessWindow::ChessWindow(QWidget* parent)
	: QMainWindow(parent)
{
	//*tourAuBlanc_ = true;

	setWindowTitle("Jeu d'échecs");
	setMouseTracking(true);
	setUI();

	// Initalisation de l'échiquier
	e_.initialiserVide();
	QPixmap echiquier;
	echiquier.load(e_.obtenirImage());
	echiquier = echiquier.scaled(800, 800, Qt::KeepAspectRatio);

	scene_ = new QGraphicsScene(this);
	scene_->setSceneRect(0, 0, 800, 800);
	view_ = new QGraphicsView(scene_);

	//choisir type de layout
	int i = 0;
	std::cout << "\n";
	std::cout << "Choisir une position parmi les suivantes en rentrant le numéro: \n";
	std::cout << "		1. Position initiale \n";
	std::cout << "		2. Défense berlinoise \n";
	std::cout << "		3. Défense sicilienne variation Najdorf \n";
	std::cout << "		4. Position de fin de partie \n";

	while (i == 0)
		std::cin >> i;

	QGraphicsPixmapItem* item = new QGraphicsPixmapItem(echiquier);
	item->setPos(0, 0);
	scene_->addItem(item);

	// set position initiales des pieces de l'echiquier
	if (i == 1)
		positionInitiale();
	else if (i == 2)
		berlinDefense();
	else if (i == 3)
		sicilianNajdorf();
	else if (i == 4)
		endGame();

	for (auto& piece : pieces_)
	{
		QPixmap img = piece->obtenirImage();
		img = img.scaled(100, 100, Qt::KeepAspectRatio);
		customitem* c = new customitem(img, piece, &e_, scene_);
		c->setPos(piece->obtenirPosition().first * 100, 100 * (7 - piece->obtenirPosition().second));
		scene_->addItem(c);
	}

	for (auto& piece : pieces_)
		piece->calculerMouvements(e_);

	setCentralWidget(view_);
	// qDebug() << "Constructeur appele" << Qt::endl;

}

void UI::customitem::mouseReleaseEvent(QGraphicsSceneMouseEvent* e_)
{
	for (auto& x : v_)
		s_->removeItem(x);

	int laMoitie = 50;
	int x(0), y(0);

	// centrer les pieces lorsque sur jeton vert
	const int uneRangee_ = 100;
	if ((int)pos().x() % uneRangee_ > laMoitie)
		x = uneRangee_ + pos().x() - ((int)(pos().x()) % uneRangee_);
	else
		x = pos().x() - ((int)(pos().x()) % uneRangee_);

	const int uneColonne_ = 100;
	if ((int)pos().y() % uneColonne_ > laMoitie)
		y = uneColonne_ + pos().y() - ((int)(pos().y()) % uneColonne_);
	else
		y = pos().y() - ((int)(pos().y()) % uneColonne_);

	// reset mouvement possible apres avoir effectuer un mouvement
	int tailleEchiquierMAx = 8, tailleEchiquierMin = 0;
	int indexEchiquierMAx = 7;
	bool peutBouger = false;
	for (auto i : p_->obtenirMouvements())
		if ((i.first * uneRangee_ == x) && (uneColonne_ * (indexEchiquierMAx - i.second) == y))
		{
			// ancienne position a nullptr
			ech_->cases[p_->obtenirPosition().first][p_->obtenirPosition().second] = nullptr;

			// enlever un item si il y a une capture
			for (auto item : s_->items())
				if (item->x() == x && item->y() == y)
					s_->removeItem(item);
			setPos(x, y);
			p_->changerPos(i.first, i.second, ech_);

			// recalculer un mouvement lorsqu'une piece bouge
			for (int j = tailleEchiquierMin; j < tailleEchiquierMAx; j++)
				for (int k = tailleEchiquierMin; k < tailleEchiquierMAx; k++)
					if (ech_->cases[j][k] != nullptr)
						ech_->cases[j][k]->calculerMouvements(*ech_);

			peutBouger = true;
			break;
		}

	if (!peutBouger)
		qDebug() << "Mouvement impossible";

	QGraphicsPixmapItem::mouseReleaseEvent(e_);
};

// permet de update les points verts selon le click sur une pièce 
void UI::customitem::mousePressEvent(QGraphicsSceneMouseEvent* e_)
{
	// enlever les points verts
	for (auto& x : v_)
		s_->removeItem(x);

	int x(0), y(0);
	QPixmap pix5;
	pix5.load("images/sqaure.png");
	QGraphicsPixmapItem* item = new QGraphicsPixmapItem(pix5);
	item->setPos(100 * p_->obtenirPosition().first, 100 * (7 - p_->obtenirPosition().second));
	s_->addItem(item);
	v_.push_back(item);

	// rajouter les points verts
	int grosseurImage = 50;
	for (auto i : p_->obtenirMouvements())
	{
		QPixmap pix5;
		pix5.load("images/green.png");
		pix5 = pix5.scaled(grosseurImage, grosseurImage);
		QGraphicsPixmapItem* item = new QGraphicsPixmapItem(pix5);
		item->setPos(100 * i.first + 25, 100 * (7 - i.second) + 25);
		s_->addItem(item);
		v_.push_back(item);
	}
	QGraphicsPixmapItem::mousePressEvent(e_);
};

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
