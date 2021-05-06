#include "Echiquier.h"

static const int tailleEchiquierMax = 7;

void Echiquier::initialiserVide()
{
	for (int i = 0; i <= tailleEchiquierMax; i++)
		for (int j = 0; j <= tailleEchiquierMax; j++)
			cases[i][j] = nullptr;
}