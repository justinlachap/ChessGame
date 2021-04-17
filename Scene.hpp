#include <QObject>
#include <QgraphicsScene>
#include "Cases.hpp"

class MaScene :public QGraphicsScene{
public:
	MaScene(QObject* parent = Q_NULLPTR) :QGraphicsScene(parent) {
		setSceneRect(0, 0, 800, 800);
		for (int i = 0; i < 8; i++) {
			Case* uneCase = new Case(false);
			uneCase->setPos(i * 100, 50);
			m_items.append(uneCase);
			addItem(uneCase);

		}
	};
	~MaScene() {
	};
	QList<Case*> m_items;
};