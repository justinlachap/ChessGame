//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//																																	//
// ChessWindow : La vue de l'interface graphique utilisateur du jeux d'échec.													//
// 																																	//
// Par :																															//
//		Généreux, Esmé (2081518)																									//
//		Lachapelle, Justin (2076412)																								//
// 																																	//
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#pragma once

#include "Echiquier.h"

#pragma warning(push, 0) // Sinon Qt fait des avertissements à /W4.

#include <QMainWindow>
#include <QGraphicsScene>

#pragma pop()

namespace UI
{
	class MainWindow;

	class ChessWindow : public QMainWindow
	{
		Q_OBJECT
		Echiquier e_;
		std::vector<Piece*> pieces_;
		QGraphicsScene* scene_;
		QGraphicsView* view_;
		bool tourAuBlanc_ = true;

	public:
		ChessWindow(QWidget* parent = nullptr);
		~ChessWindow() override = default;
		
		/**
		 * Donne la configuration de la fenêtre pricipaleQt
		 */
		void setUI();

		/**
		 * Set les pièces de l'échiquier à leur position initiale
		 */
		void positionInitiale();

		/**
		 * Ouvre le jeu d'échec en défense berlinoise
		 */
		void defenseBerlinoise();

		/**
		 * Ouvre le jeu d'échec en défense sicilenne, variante Najdorf
		 */
		void defenseSicilienneNajdorf();

		/**
		 * Ouvre le jeu d'échec en finale
		 */
		void finale();
	};
}


