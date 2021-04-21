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

		void ajouterPiece(Piece* p);
		
		void afficherMouvementsDisponiblesEchiquier(std::vector<std::pair<int, int>> v, std::pair<int, int> pos);

		void positionInitiale(Echiquier e);

	
	};
}


