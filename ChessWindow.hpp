#pragma once
// La Vue-Controlleur pour calculatrice simple.
// Par Francois-R.Boyer@PolyMtl.ca

//#include "classes.hpp"
#pragma warning(push, 0) // Sinon Qt fait des avertissements à /W4.
#include <QMainWindow>
#include <QDebug>
#include "classes.hpp"
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
		void setUI();
		ChessWindow(QWidget* parent = nullptr);
		~ChessWindow() override = default;

		void positionInitiale();
		void berlinDefense();
		void sicilianNajdorf();
		void endGame();

	private:
		Echiquier e_;
		std::vector<Piece*> pieces_;
		QGraphicsScene* scene_;
		QGraphicsView* view_;
		//bool* tourAuBlanc_;
	};

	class customitem :public QGraphicsPixmapItem
	{
	public:
		customitem(QPixmap img, Piece* piece, Echiquier* echiquier, QGraphicsScene* scene_) : QGraphicsPixmapItem(img)
		{
			setFlag(QGraphicsItem::ItemIsMovable, true);
			p_ = piece;
			ech_ = echiquier;
			s_ = scene_;
		};
		void mouseReleaseEvent(QGraphicsSceneMouseEvent* e_);
		void mousePressEvent(QGraphicsSceneMouseEvent* e_);

	private:
		Echiquier* ech_;
		Piece* p_;
		QGraphicsScene* s_;
		std::vector<QGraphicsPixmapItem*> v_;
		const int uneRangee_ = 100;
		const int uneColonne_ = 100;
	};
}


