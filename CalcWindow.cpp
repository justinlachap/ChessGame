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

using iter::range;

ChessWindow::ChessWindow(QWidget* parent) :
	QMainWindow(parent)
{
	QString filename = "Chess_board.png";
	QLabel* lbl = new QLabel(this);

	QPixmap pix;

	lbl->setMinimumSize(900, 900);
	if (pix.load(filename))
	{
		/** scale pixmap to fit in label'size and keep ratio of pixmap */
		pix = pix.scaled(900, 900, Qt::KeepAspectRatio);
		lbl->setPixmap(pix);
	}

	//QPixmap bkgnd("C:/Users/justi/source/repos/ProjetTestQt/Chess_Board.png");
	//bkgnd = bkgnd.scaled(this->size(), Qt::IgnoreAspectRatio);
	

	setWindowTitle("Jeu d'échecs");
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
