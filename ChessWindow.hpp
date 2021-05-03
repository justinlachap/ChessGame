#pragma once
// La Vue-Controlleur pour calculatrice simple.
// Par Francois-R.Boyer@PolyMtl.ca

//#include "classes.hpp"
#pragma warning(push, 0) // Sinon Qt fait des avertissements à /W4.
#include <QMainWindow>
#include <QPushButton>
#include <QString>
#include <QLabel>
#include <QPainter>
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

		//void ajouterPiece(Piece* p);
		
		//void afficherMouvementsDisponiblesEchiquier(std::vector<std::pair<int, int>> v, std::pair<int, int> pos);

		//void mousePressEvent(QMouseEvent* event);
		


	private:
		Echiquier e;
		QLabel* lbl1;
		Piece* pieceSelectionnee;
		std::vector<Piece*> pieces;
		std::vector <QLabel*> affichages;
		QGraphicsScene* scene;
		QGraphicsView* view;
	};

}


class customitem :public QGraphicsPixmapItem {
public:
	customitem(QPixmap img): QGraphicsPixmapItem(img) {
		setFlag(QGraphicsItem::ItemIsMovable, true);
		//setFlag(QGraphicsItem::ItemIsSelectable, true);
	};
	void setPiece(Piece* piece) {
		p = piece;
	}
	void setEchiquier(Echiquier* echiquier) { ech = echiquier; }
	void setScene(QGraphicsScene* scene) { s = scene; };
	void mouseReleaseEvent(QGraphicsSceneMouseEvent* e);
	void mousePressEvent(QGraphicsSceneMouseEvent* e);
private:
	Echiquier* ech;
	Piece* p;
	QGraphicsScene* s;
	std::vector<QGraphicsPixmapItem*> v;
};