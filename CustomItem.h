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
		Echiquier& ech_;
		Piece& p_;
		QGraphicsScene* s_;
		std::vector<QGraphicsPixmapItem*> PixmapVector_;
		bool* tourDeJouer_;

	public:
		CustomItem(QPixmap img, Piece& piece, Echiquier& echiquier, QGraphicsScene* scene, bool* tour);
		
		/**
		 * Enlève les points verts provenant du dernier click
		 */
		void enleverAncienPointsVerts();
		
		/**
		 * Affiche les mouvements disponibles sous forme de points verts lors d'un MousePressEvent
		 */
		void ajouterPointsVerts();
		
		/**
		 * Défénit les opérations à effectuer lors du drag d'une pièce ("drag and drop"), en autre, update les points verts
		 * @param e : événement du MousePressEvent
		 */
		void mousePressEvent(QGraphicsSceneMouseEvent* e);

		/**
		 * Permet de centrer les pieces lorsqu'elles sont bougées sur une case des mouvements disponibles
		 * @param x : position du MouseReleaseEvent sur l'axe des x de l'échiquier
		 * @param y : position du MouseReleaseEvent sur l'axe des y de l'échiquier
		 */
		void centrerLesPiecesSurUneCaseVerte(int& x, int& y);

		/**
		 * Permet de renouvler l'affichage des points verts après avoit effectuer un mouvement
		 * @param x : position du MouseReleaseEvent sur l'axe des x de l'échiquier
		 * @param y : position du MouseReleaseEvent sur l'axe des y de l'échiquier
		 */
		void renouvlerMouvementsDisponibles(int& x, int& y);

		/**
		 * Défénit les opérations à effectuer lors du drop d'une pièce ("drag and drop")
		 * @param e : événement du MouseReleaseEvent
		 */
		void mouseReleaseEvent(QGraphicsSceneMouseEvent* e);
	};
}