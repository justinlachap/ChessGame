﻿#pragma once
// La Vue-Controlleur pour calculatrice simple.
// Par Francois-R.Boyer@PolyMtl.ca

//#include "classes.hpp"
#pragma warning(push, 0) // Sinon Qt fait des avertissements à /W4.
#include <QMainWindow>
#include <QPushButton>
#include <QString>
#include <QLabel>

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



private:
	//template <typename T = decltype(nullptr)>
	//QPushButton* nouveauBouton(const QString& text, const T& slot = nullptr);

	//Echiquier echiquier_;  // Le Modèle (pourrait être un pointeur mais pas nécessaire dans ce cas).
	//QGraphicsView* m_view;
	//MaScene* m_scene;
	QLabel* affichage_;  // Pour la version QButtonGroup.
};
