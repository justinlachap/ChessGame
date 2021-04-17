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
#include <Qpainter>
#include <Qgraphicsview>
#include <QGraphicsScene>

class Case : public QGraphicsRectItem {
public:
	Case(bool estBlanc) {
		setRect(0, 0, 50, 50);
		setPen(QPen(Qt::red));
		if (estBlanc)
			setBrush(QBrush(Qt::red));
		else
			setBrush(QBrush(Qt::red));
	};
	~Case() {};

};
