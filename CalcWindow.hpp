#pragma once
// La Vue-Controlleur pour calculatrice simple.
// Par Francois-R.Boyer@PolyMtl.ca

//#include "classes.hpp"
#pragma warning(push, 0) // Sinon Qt fait des avertissements à /W4.
#include <QMainWindow>
#include <QPushButton>
#include <QString>
#include <QLabel>
#include "classes.hpp"
#pragma pop()

class Case;

namespace ui {
	class MainWindow;
}

class ChessWindow : public QMainWindow {
	Q_OBJECT

public:
	ChessWindow(QWidget* parent = nullptr);
	~ChessWindow() override = default;
	QList<Case*> cases;
	void ajouterPiece(Piece* p) {
		QLabel* lbl4 = new QLabel(this);
		QString qstring = p->obtenirImage();
		QPixmap pix4;
		pix4.load(qstring);

		lbl4->setMinimumSize(100, 100);
		lbl4->setPixmap(pix4.scaled(lbl4->width(), lbl4->height(), Qt::KeepAspectRatio));
		lbl4->setGeometry(QRect(100 * p->obtenirPosition().first, 100 * (7 - p->obtenirPosition().second), 100, 100)); // (Qrect(x,y,height,width)
		lbl4->setTextInteractionFlags(Qt::TextSelectableByMouse);
		
	}
	void positionInitiale(Echiquier e) {
		Roi R1(e, std::pair(4, 0), true);
		Roi R2(e, std::pair(4, 7), false);
		Dame d1(e, std::pair(3, 0), true);
		Dame d2(e, std::pair(3, 7), false);
		Pion P1(e, std::pair(0, 1), true);
		Pion P2(e, std::pair(1, 1), true);
		Pion P3(e, std::pair(2, 1), true);
		Pion P4(e, std::pair(3, 1), true);
		Pion P5(e, std::pair(4, 1), true);
		Pion P6(e, std::pair(5, 1), true);
		Pion P7(e, std::pair(6, 1), true);
		Pion P8(e, std::pair(7, 1), true);
		Pion P9(e, std::pair(0, 6), false);
		Pion P10(e, std::pair(1, 6), false);
		Pion P11(e, std::pair(2, 6), false);
		Pion P12(e, std::pair(3, 6), false);
		Pion P13(e, std::pair(4, 6), false);
		Pion P14(e, std::pair(5, 6), false);
		Pion P15(e, std::pair(6, 6), false);
		Pion P16(e, std::pair(7, 6), false);
		Cavalier c1(e, std::pair(1, 0), true);
		Cavalier c2(e, std::pair(6, 0), true);
		Cavalier c3(e, std::pair(1, 7), false);
		Cavalier c4(e, std::pair(6, 7), false);
		Tour r1(e, std::pair(0, 0), true);
		Tour r2(e, std::pair(7, 0), true);
		Tour r3(e, std::pair(0, 7), false);
		Tour r4(e, std::pair(7, 7), false);
		Fou f1(e, std::pair(2, 0), true);
		Fou f2(e, std::pair(5, 0), true);
		Fou f3(e, std::pair(2, 7), false);
		Fou f4(e, std::pair(5, 7), false);



		ajouterPiece(&d1);
		ajouterPiece(&d2);
		ajouterPiece(&R1);
		ajouterPiece(&R2);
		ajouterPiece(&P1);
		ajouterPiece(&P2);
		ajouterPiece(&P3);
		ajouterPiece(&P4);
		ajouterPiece(&P5);
		ajouterPiece(&P6);
		ajouterPiece(&P7);
		ajouterPiece(&P8);
		ajouterPiece(&P9);
		ajouterPiece(&P10);
		ajouterPiece(&P11);
		ajouterPiece(&P12);
		ajouterPiece(&P13);
		ajouterPiece(&P14);
		ajouterPiece(&P15);
		ajouterPiece(&P16);
		ajouterPiece(&c1);
		ajouterPiece(&c2);
		ajouterPiece(&c3);
		ajouterPiece(&c4);
		ajouterPiece(&r1);
		ajouterPiece(&r2);
		ajouterPiece(&r3);
		ajouterPiece(&r4);
		ajouterPiece(&f1);
		ajouterPiece(&f2);
		ajouterPiece(&f3);
		ajouterPiece(&f4);
	}


private:
	//template <typename T = decltype(nullptr)>
	//QPushButton* nouveauBouton(const QString& text, const T& slot = nullptr);

	//Echiquier echiquier_;  // Le Modèle (pourrait être un pointeur mais pas nécessaire dans ce cas).
	//QGraphicsView* m_view;
	//MaScene* m_scene;
	QLabel* affichage_;  // Pour la version QButtonGroup.
};
