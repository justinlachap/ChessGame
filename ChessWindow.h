#pragma once
#include "Echiquier.h"
#pragma warning(push, 0)
#include <QMainWindow>
#include <QGraphicsScene>

namespace UI
{
	class MainWindow;

	class ChessWindow : public QMainWindow
	{
		Q_OBJECT
		Echiquier e_;
		std::vector<Piece *> pieces_;
		QGraphicsScene *scene_;
		QGraphicsView *view_;
		bool tourAuBlanc_ = true;

	public:
		ChessWindow(QWidget *parent = nullptr);
		~ChessWindow() override = default;

		/**
		 * Permet à l'utilisateur de choisir de quelle manière ouvrir le jeu
		 */
		void choisirLayoutPiece(QPixmap &echiquier);

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

		/**
		 * Affiche la bonne image pour chaque pièce qui se trouve sur l'échiquier
		 */
		void afficherImagesPieces();

		/**
		 * Fonctions qui inititialise l'échiquier et qui fait appel aux méthodes ci-dessus
		 */
		void setEchiquier();

		/**
		 * Calcule les mouvements possibles des pièces du vecteur de pièces présente sur l'échiquier
		 */
		void calculerMouvementsVecteurPieces();
	};
}
