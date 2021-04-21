// Livrable 1
// Par Justin Lachapelle, matricule 2076412 et Esmé Généreux, matricule 2081518.

#include <assert.h>
#include <vector>
#include <algorithm>
#include "classes.hpp"
#include <iostream>

class Test {
public:
	void testPion() {
		//Echiquier e;
		e.initialiserVide();
		// pions blanc
		Pion p1(e, std::pair(0, 1), true);
		Pion p2(e, std::pair(2, 2), true);
		Pion p3(e, std::pair(2, 3), true);
		Pion p4(e, std::pair(6, 1), true);

		// pions noirs
		Pion p5(e, std::pair(5, 6), false);
		Pion p6(e, std::pair(7, 2), false);
		p1.calculerMouvements(e);
		p2.calculerMouvements(e);
		p3.calculerMouvements(e);
		p4.calculerMouvements(e);
		p5.calculerMouvements(e);
		p6.calculerMouvements(e);

		std::vector<std::pair<int, int>> reponseP1 = { std::pair(0,3), std::pair(0,2) };
		std::sort(reponseP1.begin(), reponseP1.end());
		std::vector<std::pair<int, int>> tentativeP1 = p1.obtenirMouvements();
		std::sort(tentativeP1.begin(), tentativeP1.end());
		assert(tentativeP1 == reponseP1);

		std::vector<std::pair<int, int>> reponseP2;
		std::sort(reponseP2.begin(), reponseP2.end());
		std::vector<std::pair<int, int>> tentativeP2 = p2.obtenirMouvements();
		std::sort(tentativeP2.begin(), tentativeP2.end());
		assert(tentativeP2 == reponseP2);

		std::vector<std::pair<int, int>> reponseP3 = { std::pair(2,4) };
		std::sort(reponseP3.begin(), reponseP3.end());
		std::vector<std::pair<int, int>> tentativeP3 = p3.obtenirMouvements();
		std::sort(tentativeP3.begin(), tentativeP3.end());
		assert(tentativeP3 == reponseP3);

		std::vector<std::pair<int, int>> reponseP4 = { std::pair(7,2), std::pair(6,2), std::pair(6,3) };
		std::sort(reponseP4.begin(), reponseP4.end());
		std::vector<std::pair<int, int>> tentativeP4 = p4.obtenirMouvements();
		std::sort(tentativeP4.begin(), tentativeP4.end());
		assert(tentativeP4 == reponseP4);

		std::vector<std::pair<int, int>> reponseP5 = { std::pair(5,5), std::pair(5,4) };
		std::sort(reponseP5.begin(), reponseP5.end());
		std::vector<std::pair<int, int>> tentativeP5 = p5.obtenirMouvements();
		std::sort(tentativeP5.begin(), tentativeP5.end());
		assert(tentativeP5 == reponseP5);

		std::vector<std::pair<int, int>> reponseP6 = { std::pair(6,1), std::pair(7,1) };
		std::sort(reponseP6.begin(), reponseP6.end());
		std::vector<std::pair<int, int>> tentativeP6 = p6.obtenirMouvements();
		std::sort(tentativeP6.begin(), tentativeP6.end());
		assert(tentativeP6 == reponseP6);

		std::cout << "Les tests des pions ont passe" << std::endl;



	};
	void testDame() {
		e.initialiserVide();
		// Dames blanches
		Dame d1(e, std::pair(0, 0), true);
		Dame d2(e, std::pair(6, 0), true);
		// Dames noires
		Dame d3(e, std::pair(4, 2), false);

		d1.calculerMouvements(e);
		d2.calculerMouvements(e);
		d3.calculerMouvements(e);

		std::vector<std::pair<int, int>> reponseD1 = { std::pair(0,1), std::pair(0,2),std::pair(0,3), std::pair(0,4),std::pair(0,5), std::pair(0,6),std::pair(0,7), std::pair(1,0),std::pair(2,0),std::pair(3,0), std::pair(4,0),std::pair(5,0),std::pair(1,1), std::pair(2,2),std::pair(3,3),std::pair(4,4),std::pair(5,5), std::pair(6,6),std::pair(7,7) };
		std::sort(reponseD1.begin(), reponseD1.end());
		std::vector<std::pair<int, int>> tentativeD1 = d1.obtenirMouvements();
		std::sort(tentativeD1.begin(), tentativeD1.end());
		assert(tentativeD1 == reponseD1);

		std::vector<std::pair<int, int>> reponseD2 = { std::pair(6,1), std::pair(6,2),std::pair(6,3), std::pair(6,4),std::pair(6,5), std::pair(6,6),std::pair(6,7), std::pair(5,0),std::pair(4,0),std::pair(3,0), std::pair(2,0),std::pair(1,0), std::pair(5,1),std::pair(4,2), std::pair(7,0), std::pair(7,1) };
		std::sort(reponseD2.begin(), reponseD2.end());
		std::vector<std::pair<int, int>> tentativeD2 = d2.obtenirMouvements();
		std::sort(tentativeD2.begin(), tentativeD2.end());
		assert(tentativeD2 == reponseD2);

		std::vector<std::pair<int, int>> reponseD3 = { std::pair(0,2), std::pair(1,2),std::pair(2,2), std::pair(3,2),std::pair(5,2), std::pair(6,2),std::pair(7,2), std::pair(4,0),std::pair(4,1),std::pair(4,3), std::pair(4,4),std::pair(4,5), std::pair(4,6),std::pair(4,7), std::pair(5,1), std::pair(6,0),std::pair(5,3), std::pair(6,4),std::pair(7,5), std::pair(3,3),std::pair(2,4), std::pair(1,5), std::pair(0,6), std::pair(3,1), std::pair(2,0) };
		std::sort(reponseD3.begin(), reponseD3.end());
		std::vector<std::pair<int, int>> tentativeD3 = d3.obtenirMouvements();
		std::sort(tentativeD3.begin(), tentativeD3.end());
		assert(tentativeD3 == reponseD3);
		std::cout << "Les tests des reines ont passe" << std::endl;
	};
	void testRoi() {
		e.initialiserVide();
		// Rois blancs
		Roi r1(e, std::pair(0, 0), true);
		Roi r2(e, std::pair(7, 7), true);
		Roi r3(e, std::pair(2, 3), true);
		// Rois noirs
		Roi r4(e, std::pair(7, 6), false);
		Roi r5(e, std::pair(7, 0), false);
		Roi r6(e, std::pair(6, 0), false);

		r1.calculerMouvements(e);
		r2.calculerMouvements(e);
		r3.calculerMouvements(e);
		r4.calculerMouvements(e);
		r5.calculerMouvements(e);
		r6.calculerMouvements(e);

		std::vector<std::pair<int, int>> reponseR1 = { std::pair(0,1), std::pair(1,0),std::pair(1,1)};
		std::sort(reponseR1.begin(), reponseR1.end());
		std::vector<std::pair<int, int>> tentativeR1 = r1.obtenirMouvements();
		std::sort(tentativeR1.begin(), tentativeR1.end());
		assert(tentativeR1 == reponseR1);

		std::vector<std::pair<int, int>> reponseR2 = { std::pair(7,6), std::pair(6,6),std::pair(6,7) };
		std::sort(reponseR2.begin(), reponseR2.end());
		std::vector<std::pair<int, int>> tentativeR2 = r2.obtenirMouvements();
		std::sort(tentativeR2.begin(), tentativeR2.end());
		assert(tentativeR2 == reponseR2);

		std::vector<std::pair<int, int>> reponseR3 = { std::pair(2,2), std::pair(2,4),std::pair(1,3),std::pair(3,3), std::pair(3,4),std::pair(3,2),  std::pair(1,2), std::pair(1,4) };
		std::sort(reponseR3.begin(), reponseR3.end());
		std::vector<std::pair<int, int>> tentativeR3 = r3.obtenirMouvements();
		std::sort(tentativeR3.begin(), tentativeR3.end());
		assert(tentativeR3 == reponseR3);

		std::vector<std::pair<int, int>> reponseR4 = { std::pair(7,7), std::pair(6,7),std::pair(6,6),std::pair(6,5), std::pair(7,5)};
		std::sort(reponseR4.begin(), reponseR4.end());
		std::vector<std::pair<int, int>> tentativeR4 = r4.obtenirMouvements();
		std::sort(tentativeR4.begin(), tentativeR4.end());
		assert(tentativeR4 == reponseR4);

		std::vector<std::pair<int, int>> reponseR5 = { std::pair(7,1), std::pair(6,1) };
		std::sort(reponseR5.begin(), reponseR5.end());
		std::vector<std::pair<int, int>> tentativeR5 = r5.obtenirMouvements();
		std::sort(tentativeR5.begin(), tentativeR5.end());
		assert(tentativeR5 == reponseR5);

		std::vector<std::pair<int, int>> reponseR6 = { std::pair(7,1), std::pair(6,1), std::pair(5,1), std::pair(5,0) };
		std::sort(reponseR6.begin(), reponseR6.end());
		std::vector<std::pair<int, int>> tentativeR6 = r6.obtenirMouvements();
		std::sort(tentativeR6.begin(), tentativeR6.end());
		assert(tentativeR6== reponseR6);

		std::cout << "Les tests des rois ont passe" << std::endl;
	};
	void testCavalier() {
		e.initialiserVide();
		// Cavaliers blancs
		Cavalier c1(e, std::pair(1, 1), true);
		Cavalier c2(e, std::pair(3, 2), true);
		// Cavaliers noirs
		Cavalier c3(e, std::pair(4, 0), false);
		Cavalier c4(e, std::pair(5, 6), false);

		c1.calculerMouvements(e);
		c2.calculerMouvements(e);
		c3.calculerMouvements(e);
		c4.calculerMouvements(e);

		std::vector<std::pair<int, int>> reponseC1 = { std::pair(0,3), std::pair(2,3), std::pair(3,0) };
		std::sort(reponseC1.begin(), reponseC1.end());
		std::vector<std::pair<int, int>> tentativeC1 = c1.obtenirMouvements();
		std::sort(tentativeC1.begin(), tentativeC1.end());
		assert(tentativeC1 == reponseC1);

		std::vector<std::pair<int, int>> reponseC2 = { std::pair(2,0), std::pair(4,0), std::pair(1,3), std::pair(2,4),std::pair(4,4), std::pair(5,3) , std::pair(5,1)};
		std::sort(reponseC2.begin(), reponseC2.end());
		std::vector<std::pair<int, int>> tentativeC2 = c2.obtenirMouvements();
		std::sort(tentativeC2.begin(), tentativeC2.end());
		assert(tentativeC2 == reponseC2);

		std::vector<std::pair<int, int>> reponseC3 = { std::pair(2,1), std::pair(3,2), std::pair(5,2), std::pair(6,1) };
		std::sort(reponseC3.begin(), reponseC3.end());
		std::vector<std::pair<int, int>> tentativeC3 = c3.obtenirMouvements();
		std::sort(tentativeC3.begin(), tentativeC3.end());
		assert(tentativeC3 == reponseC3);

		std::vector<std::pair<int, int>> reponseC4 = { std::pair(7,7), std::pair(3,7), std::pair(3,5), std::pair(7,5), std::pair(4,4), std::pair(6,4) };
		std::sort(reponseC4.begin(), reponseC4.end());
		std::vector<std::pair<int, int>> tentativeC4 = c4.obtenirMouvements();
		std::sort(tentativeC4.begin(), tentativeC4.end());
		assert(tentativeC4 == reponseC4);
		std::cout << "Les tests des cavaliers ont passe" << std::endl;
	};
	void testTour() {
		e.initialiserVide();
		// Tours blancs
		Tour t1(e, std::pair(6, 3), true);
		// Tours noirs
		Tour t2(e, std::pair(0, 0), false);
		Tour t3(e, std::pair(7, 3), false);

		t1.calculerMouvements(e);
		t2.calculerMouvements(e);
		t3.calculerMouvements(e);

		std::vector<std::pair<int, int>> reponseT1 = { std::pair(0,3), std::pair(1,3), std::pair(2,3), std::pair(3,3),std::pair(4,3), std::pair(5,3), std::pair(7,3), std::pair(6,0),std::pair(6,1), std::pair(6,2), std::pair(6,4), std::pair(6,5),std::pair(6,6), std::pair(6,7) };
		std::sort(reponseT1.begin(), reponseT1.end());
		std::vector<std::pair<int, int>> tentativeT1 = t1.obtenirMouvements();
		std::sort(tentativeT1.begin(), tentativeT1.end());
		assert(tentativeT1 == reponseT1);

		std::vector<std::pair<int, int>> reponseT2 = { std::pair(1,0), std::pair(2,0), std::pair(3,0), std::pair(4,0),std::pair(5,0), std::pair(6,0), std::pair(7,0),std::pair(0,1), std::pair(0,2), std::pair(0,3) ,std::pair(0,4), std::pair(0,5), std::pair(0,6), std::pair(0,7) };
		std::sort(reponseT2.begin(), reponseT2.end());
		std::vector<std::pair<int, int>> tentativeT2 = t2.obtenirMouvements();
		std::sort(tentativeT2.begin(), tentativeT2.end());
		assert(tentativeT2 == reponseT2);

		std::vector<std::pair<int, int>> reponseT3 = { std::pair(6,3), std::pair(7,0), std::pair(7,1), std::pair(7,2),std::pair(7,4), std::pair(7,5), std::pair(7,6), std::pair(7,7) };
		std::sort(reponseT3.begin(), reponseT3.end());
		std::vector<std::pair<int, int>> tentativeT3 = t3.obtenirMouvements();
		std::sort(tentativeT3.begin(), tentativeT3.end());
		assert(tentativeT3 == reponseT3);

		std::cout << "Les tests des tours ont passe" << std::endl;
	};
	void testFou() {
		//Echiquier e;
		e.initialiserVide();
		// Fou blancs
		Fou f1(e, std::pair(0, 5), true);
		Fou f2(e, std::pair(1, 1), true);
		// Fou noirs
		Fou f3(e, std::pair(4, 1), false);

		f1.calculerMouvements(e);
		f2.calculerMouvements(e);
		f3.calculerMouvements(e);

		std::vector<std::pair<int, int>> reponseF1 = { std::pair(1,4), std::pair(2,3), std::pair(3,2), std::pair(4,1),std::pair(1,6), std::pair(2,7) };
		std::sort(reponseF1.begin(), reponseF1.end());
		std::vector<std::pair<int, int>> tentativeF1 = f1.obtenirMouvements();
		std::sort(tentativeF1.begin(), tentativeF1.end());
		assert(tentativeF1 == reponseF1);

		std::vector<std::pair<int, int>> reponseF2 = { std::pair(0,0), std::pair(2,0), std::pair(0,2), std::pair(2,2),std::pair(3,3), std::pair(4,4), std::pair(5,5),std::pair(6,6), std::pair(7,7) };
		std::sort(reponseF2.begin(), reponseF2.end());
		std::vector<std::pair<int, int>> tentativeF2 = f2.obtenirMouvements();
		std::sort(tentativeF2.begin(), tentativeF2.end());
		assert(tentativeF2 == reponseF2);

		std::vector<std::pair<int, int>> reponseF3 = { std::pair(0,5), std::pair(1,4), std::pair(2,3), std::pair(3,2),std::pair(5,0), std::pair(3,0), std::pair(5,2), std::pair(6,3), std::pair(7,4) };
		std::sort(reponseF3.begin(), reponseF3.end());
		std::vector<std::pair<int, int>> tentativeF3 = f3.obtenirMouvements();
		std::sort(tentativeF3.begin(), tentativeF3.end());
		assert(tentativeF3 == reponseF3);

		std::cout << "Les tests des fous ont passe" << std::endl;
	};
	void tester() {
			//testPion();
		//testDame();
		//testRoi();
		//testCavalier();
		//testTour();
		testFou();
	};
	private:
		Echiquier e;
};
