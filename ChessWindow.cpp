// La Vue-Controlleur pour calculatrice simple.
// Par Francois-R.Boyer@PolyMtl.ca

#include "ChessWindow.hpp"

#pragma warning(push, 0) // Sinon Qt fait des avertissements à /W4.
#include <QHBoxLayout>
#include <QPushButton>
#include <QButtonGroup>
#include <QLabel>
#include <QString>
#include <QVariant>
#include <QPixmap>
#pragma pop()
#include <iostream>
#include <type_traits>
#include <cppitertools/range.hpp>
#include "classes.hpp"
#include <QGraphicsRectItem>
#include <Qpen>
#include <QPainter>
#include <Qgraphicsview>
#include <QGraphicsScene>
#include <QRect>
#include <QDebug>

using iter::range;

UI::ChessWindow::ChessWindow(QWidget* parent) :
	QMainWindow(parent)
{
	// Nom de la fenêtre
	setWindowTitle("Jeu d'échecs");

	// Initalisation de l'échiquier
	QLabel* lbl1 = new QLabel(this);
	Echiquier e;
	e.initialiserVide();
	QPixmap echiquier;
	echiquier.load(e.obtenirImage());
	lbl1->setMinimumSize(800, 800); // échiquier en soi
	lbl1->setPixmap(echiquier.scaled(lbl1->width(), lbl1->height(), Qt::KeepAspectRatio));

	// Initialisation des pièces
	positionInitiale(e);
}