﻿#pragma once
// La Vue-Controlleur pour calculatrice simple.
// Par Francois-R.Boyer@PolyMtl.ca

//#include "classes.hpp"
#pragma warning(push, 0) // Sinon Qt fait des avertissements à /W4.
#include <QMainWindow>
#include <QPushButton>
#include <QString>
#include <QLabel>
#include <QPainter>
#include "classes.hpp"
#pragma pop()

class Case;

namespace UI
{
	class MainWindow;

	class ChessWindow : public QMainWindow
	{
		Q_OBJECT
	public:
		ChessWindow(QWidget* parent = nullptr);
		~ChessWindow() override = default;
		QList<Case*> cases;

		void ajouterPiece(Piece* p)
		{
			QLabel* lbl4 = new QLabel(this);
			QString qstring = p->obtenirImage();
			QPixmap pix4;
			pix4.load(qstring);

			lbl4->setMinimumSize(100, 100);
			lbl4->setPixmap(pix4.scaled(lbl4->width(), lbl4->height(), Qt::KeepAspectRatio));
			lbl4->setGeometry(QRect(100 * p->obtenirPosition().first, 100 * (7 - p->obtenirPosition().second), 100, 100)); // (Qrect(x,y,height,width)
			lbl4->setTextInteractionFlags(Qt::TextSelectableByMouse);
		}

		void afficherMouvementsDisponiblesEchiquier(std::vector<std::pair<int, int>> v, std::pair<int, int> pos) {
			//QLabel* lbl4 = new QLabel(this);
			QString greenCircle = "images/green.png";
			QString square = "images/sqaure.png";
			QPixmap pix4;
			pix4.load(greenCircle);
			QPixmap pix5;
			pix5.load(square);
			QLabel* lbl5 = new QLabel(this);
			lbl5->setMinimumSize(100, 100);
			lbl5->setPixmap(pix5.scaled(lbl5->width(), lbl5->height(), Qt::KeepAspectRatio));
			lbl5->setAlignment(Qt::AlignHCenter | Qt::AlignVCenter);

			lbl5->setGeometry(QRect(100 * pos.first, 100 * (7 - pos.second), 100, 100)); // (Qrect(x,y,height,width)
			for (auto i : v) {

				QLabel* lbl4 = new QLabel(this);
				lbl4->setMinimumSize(50, 50);
				lbl4->setPixmap(pix4.scaled(lbl4->width(), lbl4->height(), Qt::KeepAspectRatio));
				lbl4->setAlignment(Qt::AlignHCenter | Qt::AlignVCenter);

				lbl4->setGeometry(QRect(100 * i.first, 100 * (7 - i.second), 100, 100)); // (Qrect(x,y,height,width)
			}
		}

		void positionInitiale(Echiquier e)
		{

			Roi* R1 = new Roi(e, std::pair(4, 0), true);
			//Roi R1();

			Roi* R2 = new Roi(e, std::pair(4, 7), false);
			Dame* d1 = new Dame(e, std::pair(3, 0), true);
			Dame* d2 = new Dame(e, std::pair(3, 7), false);
			Pion* P1 = new Pion(e, std::pair(0, 1), true);
			Pion* P2 = new Pion(e, std::pair(1, 1), true);
			Pion* P3 = new Pion(e, std::pair(2, 1), true);
			Pion* P4 = new Pion(e, std::pair(3, 1), true);
			//Pion P5(e, std::pair(4, 1), true);
			Pion* P6 = new Pion(e, std::pair(5, 1), true);
			Pion* P7 = new Pion(e, std::pair(6, 1), true);
			Pion* P8 = new Pion(e, std::pair(7, 1), true);
			Pion* P9 = new Pion(e, std::pair(0, 6), false);
			Pion* P10 = new Pion(e, std::pair(1, 6), false);
			Pion* P11 = new Pion(e, std::pair(2, 6), false);
			Pion* P12 = new Pion(e, std::pair(3, 6), false);
			Pion* P13 = new Pion(e, std::pair(4, 6), false);
			Pion* P14 = new Pion(e, std::pair(5, 6), false);
			Pion* P15 = new Pion(e, std::pair(6, 6), false);
			Pion* P16 = new Pion(e, std::pair(7, 6), false);
			Cavalier* c1 = new Cavalier(e, std::pair(1, 0), true);
			Cavalier* c2 = new Cavalier(e, std::pair(6, 0), true);
			Cavalier* c3 = new Cavalier(e, std::pair(1, 7), false);
			Cavalier* c4 = new Cavalier(e, std::pair(6, 7), false);
			Tour* r1 = new Tour(e, std::pair(0, 0), true);
			Tour* r2 = new Tour(e, std::pair(7, 0), true);
			Tour* r3 = new Tour(e, std::pair(0, 7), false);
			Tour* r4 = new Tour(e, std::pair(7, 7), false);
			Fou* f1 = new Fou(e, std::pair(2, 0), true);
			Fou* f2 = new Fou(e, std::pair(5, 0), true);
			Fou* f3 = new Fou(e, std::pair(2, 7), false);
			Fou* f4 = new Fou(e, std::pair(5, 7), false);

			std::vector<Piece*> pieces = { R1 , R2, d1, d2, P1,P2,P3,P4,P6,P7,P8,P9,P10,P11,P12,P13,P14,P15,P16,c1,c2,c3,c4,r1,r2,r3,r4,f1,f2,f3,f4 };
			for (auto piece : pieces) {
				ajouterPiece(piece);
				piece->calculerMouvements(e);
			}
			afficherMouvementsDisponiblesEchiquier(f2->obtenirMouvements(), f2->obtenirPosition());
		}

	private:
		//template <typename T = decltype(nullptr)>
		//QPushButton* nouveauBouton(const QString& text, const T& slot = nullptr);

		//Echiquier echiquier_;  // Le Modèle (pourrait être un pointeur mais pas nécessaire dans ce cas).
		//QGraphicsView* m_view;
		//MaScene* m_scene;
		QLabel* affichage_;  // Pour la version QButtonGroup.
	};
}


