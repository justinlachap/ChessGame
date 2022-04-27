#include "ChessWindow.h"
#include <stdexcept>
#include <QApplication>
#include <iostream>

int nouvellePartie()
{
	char partie = 'X';
	std::cout << "Aimeriez-vous commencer une partie d'échec? [Y/n]" << std::endl;
	while (partie == 'X')
		std::cin >> partie;

	if (partie != 'Y' && partie != 'y')
		exit(0);
}

int main(int argc, char *argv[])
{
	QApplication app(argc, argv);
	nouvellePartie();

	UI::ChessWindow chessWindow;
	chessWindow.resize(810, 810);
	chessWindow.show();
	return app.exec();
}
