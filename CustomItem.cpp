#include "CustomItem.h"
#include <iostream>
#include <QDebug>

// 100 repr�sente un huiti�me de la taille de l'image pour l'echiquier (800)
const int uneRangee = 100;
const int uneColonne = 100;

UI::CustomItem::CustomItem(QPixmap img, Piece &piece, Echiquier &echiquier, QGraphicsScene *scene, bool *tour)
	: QGraphicsPixmapItem(img), p_(piece), ech_(echiquier), s_(scene), tourDeJouer_(tour)
{
	setFlag(QGraphicsItem::ItemIsMovable, true);
}

void UI::CustomItem::enleverAncienPointsVerts()
{
	for (QGraphicsPixmapItem *x : PixmapVector_)
		s_->removeItem(x);
}

void UI::CustomItem::ajouterPointsVerts()
{
	int grosseurImage = 50;
	for (std::pair<int, int> i : p_.obtenirMouvements())
	{
		QPixmap pix5;
		pix5.load("images/green.png");
		pix5 = pix5.scaled(grosseurImage, grosseurImage);
		QGraphicsPixmapItem *item = new QGraphicsPixmapItem(pix5);
		item->setPos(uneRangee * i.first + 25, uneColonne * (7 - i.second) + 25);
		s_->addItem(item);
		PixmapVector_.push_back(item);
	}
}

void UI::CustomItem::mousePressEvent(QGraphicsSceneMouseEvent *e)
{
	enleverAncienPointsVerts();

	int x(0), y(0);
	QPixmap pix5;
	pix5.load("images/sqaure.png");
	QGraphicsPixmapItem *item = new QGraphicsPixmapItem(pix5);
	item->setPos(uneRangee * p_.obtenirPosition().first, uneColonne * (7 - p_.obtenirPosition().second));
	s_->addItem(item);
	PixmapVector_.push_back(item);

	ajouterPointsVerts();

	QGraphicsPixmapItem::mousePressEvent(e);
}

void UI::CustomItem::centrerLesPiecesSurUneCaseVerte(int &x, int &y)
{
	int milieuCase = 50;
	x = ((int)pos().x() % uneRangee > milieuCase) ? uneRangee + pos().x() - ((int)(pos().x()) % uneRangee) : pos().x() - ((int)(pos().x()) % uneRangee);
	y = ((int)pos().y() % uneColonne > milieuCase) ? uneColonne + pos().y() - ((int)(pos().y()) % uneColonne) : pos().y() - ((int)(pos().y()) % uneColonne);
}

void UI::CustomItem::renouvlerMouvementsDisponibles(int &x, int &y)
{
	int tailleEchiquierMax = 8;
	int tailleEchiquierMin = 0;
	int indexEchiquierMax = 7;
	bool peutBouger = false;

	for (std::pair<int, int> i : p_.obtenirMouvements())
		if ((i.first * uneRangee == x) && (uneColonne * (indexEchiquierMax - i.second) == y) && (*tourDeJouer_ == p_.obtenirCouleur()))
		{
			// ancienne position a nullptr
			ech_.cases[p_.obtenirPosition().first][p_.obtenirPosition().second] = nullptr;

			// enlever un item si il y a une capture
			for (auto item : s_->items())
				if (item->x() == x && item->y() == y)
					s_->removeItem(item);
			setPos(x, y);
			p_.changerPos(i.first, i.second, ech_);

			// recalculer les mouvements disponibles lorsqu'une piece bouge
			for (int j = tailleEchiquierMin; j < tailleEchiquierMax; j++)
				for (int k = tailleEchiquierMin; k < tailleEchiquierMax; k++)
					if (ech_.cases[j][k] != nullptr)
						ech_.cases[j][k]->calculerMouvements(ech_);

			peutBouger = true;
			*tourDeJouer_ ^= true;
			break;
		}

	if (!peutBouger)
	{
		setPos(p_.obtenirPosition().first * uneRangee, (7 - p_.obtenirPosition().second) * uneColonne);
		qDebug() << "Mouvement impossible ou ce n'est pas � votre tour de jouer!";
	}
}

void UI::CustomItem::mouseReleaseEvent(QGraphicsSceneMouseEvent *e)
{
	enleverAncienPointsVerts();

	int x(0), y(0);
	centrerLesPiecesSurUneCaseVerte(x, y);
	renouvlerMouvementsDisponibles(x, y);

	QGraphicsPixmapItem::mouseReleaseEvent(e);
}
