/*
 * Tetris for COMP2012H
 * Author: TAN, Shuhao
 * Stu ID: 20090398
 * 2013 Spring
 *
 * tetris_board.cpp
 *
 * Board of the tetris game, the main panel players play upon
 */

#include "tetris_board.h"
#include "tetris_block.h"
#include <qmainwindow.h>
#include <qapplication.h>
#include <qpixmap.h>
#include <qcolor.h>
#include <qfont.h>
#include <qpainter.h>

TetrisBoard::TetrisBoard(QWidget* parent, const char* name)
:QWidget(parent, name), bg("background.jpg"),
 state(Tetris::stopped) {
 	int i, j;
 	
	//Resize board to a fixed size
	setFixedSize(BOARD_WIDTH, BOARD_HEIGHT);
	
	//Reset grid
	for(i = 0; i < BOARD_WIDTH; i++)
		for(j = 0; j < BOARD_HEIGHT + 1; j++)
			grid[i][j].setRgb(0, 0, 0);
}

TetrisBoard::~TetrisBoard() {
}

void TetrisBoard::reset() {
	int i, j;
	//Reset grid
	for(i = 0; i < BOARD_WIDTH; i++)
		for(j = 0; j < BOARD_HEIGHT; j++)
			grid[i][j].setRgb(0, 0, 0);
	
	//Call for repaint
	repaint();
	
	//Reset state
	state = Tetris::playing;
}

void TetrisBoard::paintEvent(QPaintEvent* e) {
	int i, j;
	unsigned int zero = qRgb(0, 0, 0);
	QPainter painter;
	QFont font("Helvetica [Cronyx]", 16, QFont::Bold);
	painter.begin(this);
	painter.setPen(QColor(0, 0, 0));
	
	//Draw background
	painter.drawPixmap(0, 0, bg);
	
	//Draw blocks
	for(i = 0; i < BOARD_WIDTH; i++) {
		for(j = 0; j < BOARD_HEIGHT; j++) {
			//The block is present
			if(grid[i][j].rgb() != zero) {
				painter.setBrush(grid[i][j]);
				painter.drawRect(i * TET_SIZE,
					(GRID_HEIGHT - j - 1) * TET_SIZE, 
					TET_SIZE, TET_SIZE);
			}
		}
	}
	if(state == Tetris::stopped) {
		painter.setFont(font);
		//Notify user to start using up key
		painter.drawText(0, 0, this->width(), this->height(),
			Qt::AlignCenter, "Press <up> to start");
	}
	else {
		//Paint active block
		currentBlock.paint(&painter);
	}
	
	painter.end();
}
