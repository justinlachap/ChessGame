#pragma once

#include "Echiquier.h"
#include "Piece.h"

#pragma warning(push, 0)

#include <QGraphicsScene>
#include <QGraphicsPixmapItem>

#pragma pop()

namespace UI
{
	class CustomItem : public QGraphicsPixmapItem
	{
		Echiquier &ech_;
		Piece &p_;
		QGraphicsScene *s_;
		std::vector<QGraphicsPixmapItem *> PixmapVector_;
		bool *tourDeJouer_;

	public:
		CustomItem(QPixmap img, Piece &piece, Echiquier &echiquier, QGraphicsScene *scene, bool *tour);

		/**
		 * Enl�ve les points verts provenant du dernier click
		 */
		void enleverAncienPointsVerts();

		/**
		 * Affiche les mouvements disponibles sous forme de points verts lors d'un MousePressEvent
		 */
		void ajouterPointsVerts();

		/**
		 * D�f�nit les op�rations � effectuer lors du drag d'une pi�ce ("drag and drop"), en autre, update les points verts
		 * @param e : �v�nement du MousePressEvent
		 */
		void mousePressEvent(QGraphicsSceneMouseEvent *e);

		/**
		 * Permet de centrer les pieces lorsqu'elles sont boug�es sur une case des mouvements disponibles
		 * @param x : position du MouseReleaseEvent sur l'axe des x de l'�chiquier
		 * @param y : position du MouseReleaseEvent sur l'axe des y de l'�chiquier
		 */
		void centrerLesPiecesSurUneCaseVerte(int &x, int &y);

		/**
		 * Permet de renouvler l'affichage des points verts apr�s avoit effectuer un mouvement
		 * @param x : position du MouseReleaseEvent sur l'axe des x de l'�chiquier
		 * @param y : position du MouseReleaseEvent sur l'axe des y de l'�chiquier
		 */
		void renouvlerMouvementsDisponibles(int &x, int &y);

		/**
		 * D�f�nit les op�rations � effectuer lors du drop d'une pi�ce ("drag and drop")
		 * @param e : �v�nement du MouseReleaseEvent
		 */
		void mouseReleaseEvent(QGraphicsSceneMouseEvent *e);
	};
}