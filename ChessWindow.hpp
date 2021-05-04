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
		ChessWindow(QWidget* parent = nullptr);
		~ChessWindow() override = default;

		void positionInitiale();
		void berlinDefense();
		void sicilianNajdorf();
		void endGame();
		
	private:
		Echiquier e;
		std::vector<Piece*> pieces;
		QGraphicsScene* scene;
		QGraphicsView* view;
	};

}


class customitem :public QGraphicsPixmapItem {
public:
	customitem(QPixmap img, Piece* piece, Echiquier* echiquier, QGraphicsScene* scene): QGraphicsPixmapItem(img) {
		setFlag(QGraphicsItem::ItemIsMovable, true);
		p = piece;
		ech = echiquier;
		s = scene;
	};
	
	void mouseReleaseEvent(QGraphicsSceneMouseEvent* e);
	void mousePressEvent(QGraphicsSceneMouseEvent* e);
private:
	Echiquier* ech;
	Piece* p;
	QGraphicsScene* s;
	std::vector<QGraphicsPixmapItem*> v;
};