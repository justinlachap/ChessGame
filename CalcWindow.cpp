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




CalcWindow::CalcWindow(QWidget* parent) :
	QMainWindow(parent)
	//(new Ui::MainWindow)
	
{
	//ui->setupUi(this);

	QPixmap bkgnd("C:/Users/justi/source/repos/ProjetTestQt/Chess_Board.png");
	bkgnd = bkgnd.scaled(this->size(), Qt::IgnoreAspectRatio);
	QPixmap pix();

	setWindowTitle("Jeu échecs");
}


// Pour la version QButtonGroup.
// Pourrait aussi être sans paramètre et faire calc_.obtenirValeur()
void CalcWindow::changerValeurAffichee(int valeur)
{
	//affichage_->setText(QString::number(valeur));
}


// Pour la version setProperty.
void CalcWindow::chiffreAppuye()
{
	// QObject::sender() est l'objet d'où vient le signal connecté à ce slot; attention qu'il sera nullptr si le slot est appelé directement au lieu de passer par un signal.
	//calc_.ajouterChiffre(QObject::sender()->property("chiffre").value<int>());
}
