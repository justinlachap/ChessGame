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



using iter::range;





ChessWindow::ChessWindow(QWidget* parent) :
	QMainWindow(parent)

{
	setWindowTitle("Jeu d'échecs");
	QLabel* lbl1 = new QLabel(this);
	QLabel* lbl2 = new QLabel(this);
	QLabel* lbl3 = new QLabel(this);

	QString echiquier = "Chess_board.png";
	QString reineBlanche = "white_queen.png";
	QString reineNoire = "black_queen";
	QString roiBlanc = "white_king.png";
	QString roiNoir = "black_king";
	QString tourBlanche = "white_rook.png";
	QString tourNoire = "black_rook";
	QString fouBlanc = "white_bishop.png";
	QString fouNoir = "black_bishop";
	QString cavalierBlanc = "white_queen.png";
	QString cavalierNoir = "black_knight";
	QString pionBlanc = "white_pawn.png";
	QString pionNoir = "black_pawn";
	QPixmap pix1;
	QPixmap pix2;
	QPixmap pix3;
	pix1.load(echiquier);
	pix2.load(reineBlanche);
	pix3.load(pionNoir);
	
	lbl1->setMinimumSize(800, 800);
	lbl1->setPixmap(pix1.scaled(lbl1->width(), lbl1->height(), Qt::KeepAspectRatio));
	lbl2->setMinimumSize(100, 100);
	lbl2->setPixmap(pix2.scaled(lbl2->width(), lbl2->height(), Qt::KeepAspectRatio));
	lbl2->setGeometry(QRect(100, 100, 100, 100));
	lbl3->setMinimumSize(100, 100);
	lbl3->setPixmap(pix3.scaled(lbl2->width(), lbl2->height(), Qt::KeepAspectRatio));
	lbl3->setGeometry(QRect(500, 400, 100, 100));

	

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
