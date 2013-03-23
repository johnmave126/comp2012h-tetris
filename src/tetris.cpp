/*
 * Tetris for COMP2012H
 * Author: TAN, Shuhao
 * Stu ID: 20090398
 * 2013 Spring
 *
 * tetris.cpp
 *
 * The entry for the program
*/

#include <qapplication.h>
#include "tetris_manager.h"
#include <cstdlib>
#include <ctime>

int main(int argc, char* argv[])
{
	QApplication a(argc, argv);
	QWidget* w = new TetrisManager();
	a.setMainWidget(w);
	w->show();
	//Randomize seed
	srand((unsigned)time(NULL));
	return a.exec();
};
