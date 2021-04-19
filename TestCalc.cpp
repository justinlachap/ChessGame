// Les test pour le Modèle pour calculatrice simple.
// Par Francois-R.Boyer@PolyMtl.ca


#include "classes.hpp"

#if __has_include("gtest/gtest.h")
#include "gtest/gtest.h"
#endif
#ifdef TEST

TEST(Mouvements, test_pions) {

	Echiquier echiquier;
	echiquier.initialiserVide();

	// initialisation de 4 pions noir et 4 pions blancs sur l'echiquier
	Pion p1(echiquier, std::pair(1, 1), true);
	Pion p2(echiquier, std::pair(2, 2), true);
	Pion p3(echiquier, std::pair(3, 3), true);
	Pion p4(echiquier, std::pair(4, 2), true);

	Pion p5(echiquier, std::pair(2, 4), false);
	Pion p6(echiquier, std::pair(3, 5), false);
	Pion p7(echiquier, std::pair(1, 4), false);
	Pion p8(echiquier, std::pair(0, 5), false);

	// calcul des mouvements possibles pour chacun de ces pions
	p1.calculeMouvements(echiquier);
	p2.calculeMouvements(echiquier);
	p3.calculeMouvements(echiquier);
	p4.calculeMouvements(echiquier);

	p5.calculeMouvements(echiquier);
	p6.calculeMouvements(echiquier);
	p7.calculeMouvements(echiquier);
	p8.calculeMouvements(echiquier);

	// vecteurs contenants les mouvements possibles calculés pour chaque pion
	std::vector<std::pair<int, int>> calculated_p1 = p1.obtenirMouvements();
	std::vector<std::pair<int, int>> calculated_p2 = p2.obtenirMouvements();
	std::vector<std::pair<int, int>> calculated_p3 = p3.obtenirMouvements();
	std::vector<std::pair<int, int>> calculated_p4 = p4.obtenirMouvements();

	std::vector<std::pair<int, int>> calculated_p5 = p5.obtenirMouvements();
	std::vector<std::pair<int, int>> calculated_p6 = p6.obtenirMouvements();
	std::vector<std::pair<int, int>> calculated_p7 = p7.obtenirMouvements();
	std::vector<std::pair<int, int>> calculated_p8 = p8.obtenirMouvements();

	// vecteurs contenants les mouvements possibles attendues pour chaque pion
	std::vector<std::pair<int, int>> expected_p1 = { std::pair(1, 3), std::pair(1, 2) };
	std::vector<std::pair<int, int>> expected_p2 = { std::pair(2, 3) };
	std::vector<std::pair<int, int>> expected_p3 = { std::pair(3, 4) , std::pair(2, 4) };
	std::vector<std::pair<int, int>> expected_p4 = { std::pair(4, 3) };

	std::vector<std::pair<int, int>> expected_p5 = { std::pair(2, 3) , std::pair(3, 3) };
	std::vector<std::pair<int, int>> expected_p6 = { std::pair(3, 4) };
	std::vector<std::pair<int, int>> expected_p7 = { std::pair(1, 3) };
	std::vector<std::pair<int, int>> expected_p8 = { std::pair(0, 4) };

	EXPECT_EQ(calculated_p1, expected_p1);
	EXPECT_EQ(calculated_p2, expected_p2);
	EXPECT_EQ(calculated_p3, expected_p3);
	EXPECT_EQ(calculated_p4, expected_p4);

	EXPECT_EQ(calculated_p5, expected_p5);
	EXPECT_EQ(calculated_p6, expected_p6);
	EXPECT_EQ(calculated_p7, expected_p7);
	EXPECT_EQ(calculated_p8, expected_p8);
}

TEST(Mouvements, test_cavaliers) {

	Echiquier echiquier;
	echiquier.initialiserVide();

	// initialisation de 4 pions noir et 4 pions blancs sur l'echiquier
	Cavalier c1(echiquier, std::pair(2, 2), true);
	Cavalier c2(echiquier, std::pair(2, 5), true);
	Pion p1(echiquier, std::pair(4, 3), true);

	Cavalier c3(echiquier, std::pair(4, 4), false);
	Cavalier c4(echiquier, std::pair(5, 5), false);

	// calcul des mouvements possibles pour chacun de ces pions
	c1.calculeMouvements(echiquier);
	c2.calculeMouvements(echiquier);

	c3.calculeMouvements(echiquier);
	c4.calculeMouvements(echiquier);

	// vecteurs contenants les mouvements possibles calculés pour chaque pion
	std::vector<std::pair<int, int>> calculated_c1 = c1.obtenirMouvements();
	std::vector<std::pair<int, int>> calculated_c2 = c2.obtenirMouvements();

	std::vector<std::pair<int, int>> calculated_c3 = c3.obtenirMouvements();
	std::vector<std::pair<int, int>> calculated_c4 = c4.obtenirMouvements();

	// vecteurs contenants les mouvements possibles attendues pour chaque pion
	std::vector<std::pair<int, int>> expected_c1 = {
		std::pair(1, 0), std::pair(3, 0),
		std::pair(4, 1), std::pair(3, 4),
		std::pair(1, 4), std::pair(0, 3),
		std::pair(0, 1) };
	std::vector<std::pair<int, int>> expected_c2 = {
		std::pair(1, 3), std::pair(3, 3),
		std::pair(4, 4), std::pair(4, 6),
		std::pair(3, 7), std::pair(1, 7),
		std::pair(0, 6), std::pair(0, 4) };

	std::vector<std::pair<int, int>> expected_c3 = {
		std::pair(3, 2), std::pair(5, 2),
		std::pair(6, 3), std::pair(6, 5),
		std::pair(5, 6), std::pair(3, 6),
		std::pair(2, 5), std::pair(2, 3) };
	std::vector<std::pair<int, int>> expected_c4 = {
		std::pair(4, 3), std::pair(6, 3),
		std::pair(7, 4), std::pair(7, 6),
		std::pair(6, 7), std::pair(4, 7),
		std::pair(3, 6), std::pair(3, 4) };

	EXPECT_EQ(calculated_c1, expected_c1);
	EXPECT_EQ(calculated_c2, expected_c2);
	EXPECT_EQ(calculated_c3, expected_c3);
	EXPECT_EQ(calculated_c4, expected_c4);
}

TEST(Mouvements, test_tours) {

	Echiquier echiquier;
	echiquier.initialiserVide();

	// initialisation de 4 pions noir et 4 pions blancs sur l'echiquier
	Tour t1(echiquier, std::pair(0, 0), true);
	Tour t2(echiquier, std::pair(7, 0), true);
	Fou f1(echiquier, std::pair(2, 0), true);
	Cavalier c1(echiquier, std::pair(6, 0), true);

	Tour t3(echiquier, std::pair(0, 7), false);
	Tour t4(echiquier, std::pair(7, 7), false);
	Pion p1(echiquier, std::pair(0, 3), false);
	Fou f2(echiquier, std::pair(7, 4), false);


	// calcul des mouvements possibles pour chacun de ces pions
	t1.calculeMouvements(echiquier);
	t2.calculeMouvements(echiquier);

	t3.calculeMouvements(echiquier);
	t4.calculeMouvements(echiquier);

	// vecteurs contenants les mouvements possibles calculés pour chaque pion
	std::vector<std::pair<int, int>> calculated_t1 = t1.obtenirMouvements();
	std::vector<std::pair<int, int>> calculated_t2 = t2.obtenirMouvements();

	std::vector<std::pair<int, int>> calculated_t3 = t3.obtenirMouvements();
	std::vector<std::pair<int, int>> calculated_t4 = t4.obtenirMouvements();

	// vecteurs contenants les mouvements possibles attendues pour chaque pion
	std::vector<std::pair<int, int>> expected_t1 = {
		std::pair(1, 0), std::pair(0, 1),
		std::pair(0, 2), std::pair(0, 3) };
	std::vector<std::pair<int, int>> expected_t2 = {
		std::pair(7, 1), std::pair(7, 2),
		std::pair(7, 3), std::pair(7, 4) };

	std::vector<std::pair<int, int>> expected_t3 = {
		std::pair(1, 7), std::pair(2, 7),
		std::pair(3, 7), std::pair(4, 7),
		std::pair(5, 7), std::pair(6, 7),
		std::pair(0, 6), std::pair(0, 5),
		std::pair(0, 4) };
	std::vector<std::pair<int, int>> expected_t4 = {
		std::pair(6, 7), std::pair(5, 7),
		std::pair(4, 7), std::pair(3, 7),
		std::pair(2, 7), std::pair(1, 7),
		std::pair(7, 6), std::pair(7, 5) };

	EXPECT_EQ(calculated_t1, expected_t1);
	EXPECT_EQ(calculated_t2, expected_t2);
	EXPECT_EQ(calculated_t3, expected_t3);
	EXPECT_EQ(calculated_t4, expected_t4);
}

#endif
