#pragma once
// La Vue-Controlleur pour calculatrice simple.
// Par Francois-R.Boyer@PolyMtl.ca

//#include "classes.hpp"
#pragma warning(push, 0) // Sinon Qt fait des avertissements à /W4.
#include "Echiquier.h"

#include <QMainWindow>
#include <QDebug>
#include <QGraphicsScene>
#include <QGraphicsPixmapItem>
#pragma pop()

namespace UI
{
	class MainWindow;

	class ChessWindow : public QMainWindow
	{
		Q_OBJECT
	public:
		
		ChessWindow(QWidget* parent = nullptr);
		~ChessWindow() override = default;
		
		void setUI();
		void positionInitiale();
		void berlinDefense();
		void sicilianNajdorf();
		void endGame();

	private:
		Echiquier e_;
		std::vector<Piece*> pieces_;
		QGraphicsScene* scene_;
		QGraphicsView* view_;
		bool tourAuBlanc_ = true;
	};

	class CustomItem :public QGraphicsPixmapItem
	{
	public:
		CustomItem(QPixmap img, Piece* piece, Echiquier* echiquier, QGraphicsScene* scene_, bool* tour);

		void centrerLesPiecesSurUneCase(int x, int y);
		void renouvlerMouvementsDisponibles(int x, int y);

		void mouseReleaseEvent(QGraphicsSceneMouseEvent* e_);
		void mousePressEvent(QGraphicsSceneMouseEvent* e_);

	private:
		Echiquier* ech_;
		Piece* p_;
		QGraphicsScene* s_;
		std::vector<QGraphicsPixmapItem*> v_;
		const int uneRangee_ = 100;
		const int uneColonne_ = 100;
		bool* tourDeJouer_;
	};
}


