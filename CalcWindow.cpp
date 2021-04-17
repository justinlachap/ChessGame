// La Vue-Controlleur pour calculatrice simple.
// Par Francois-R.Boyer@PolyMtl.ca

#include "CalcWindow.hpp"

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





ChessWindow::ChessWindow(QWidget* parent) :
	QMainWindow(parent)

{

	// Nom de la fenêtre
	setWindowTitle("Jeu d'échecs");


	// Initialisation des composantes du jeu
	Echiquier e;
	e.initialiserVide();
	Dame d1(e, std::make_pair(0, 0), false);
	Cavalier c1(e, std::make_pair(5, 5), true);

	// Initialisation des labels en fonction du nombre de composantes
	QLabel* lbl1 = new QLabel(this);
	QLabel* lbl2 = new QLabel(this);
	QLabel* lbl3 = new QLabel(this);
	

	// Initalisation des images
	QString echiquier1 = e.obtenirImage();
	QString reineNoire = d1.obtenirImage();
	QString cavalierBlanc = c1.obtenirImage();
	QPixmap echiquier;
	QPixmap pix2;
	QPixmap pix3;
	echiquier.load(echiquier1);
	pix2.load(reineNoire);
	pix3.load(cavalierBlanc);

	// Initalisation des positions sur l'échiquier
	lbl1->setMinimumSize(800, 800); // échiquier en soi
	lbl1->setPixmap(echiquier.scaled(lbl1->width(), lbl1->height(), Qt::KeepAspectRatio));

	lbl2->setMinimumSize(100, 100);
	lbl2->setPixmap(pix2.scaled(lbl2->width(), lbl2->height(), Qt::KeepAspectRatio));
	lbl2->setGeometry(QRect(100*d1.obtenirPosition().first, 100*d1.obtenirPosition().second, 100, 100)); // (Qrect(x,y,height,width)
	
	lbl3->setMinimumSize(100, 100);
	lbl3->setPixmap(pix3.scaled(lbl3->width(), lbl3->height(), Qt::KeepAspectRatio));
	lbl3->setGeometry(QRect(100 * c1.obtenirPosition().first, 100 * c1.obtenirPosition().second, 100, 100)); // (Qrect(x,y,height,width)

}


// Pour la version QButtonGroup.
// Pourrait aussi être sans paramètre et faire calc_.obtenirValeur()
void ChessWindow::changerValeurAffichee(int valeur)
{
	affichage_->setText(QString::number(valeur));
}


// Pour la version setProperty.
void ChessWindow::chiffreAppuye()
{
	// QObject::sender() est l'objet d'où vient le signal connecté à ce slot; attention qu'il sera nullptr si le slot est appelé directement au lieu de passer par un signal.
	//calc_.ajouterChiffre(QObject::sender()->property("chiffre").value<int>());
}
