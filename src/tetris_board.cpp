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
	//Reset state
	state = Tetris::playing;
	//Call for repaint
	repaint();
}

//Simply pass the control to blocks
void TetrisBoard::moveLeft() {
	currentBlock.moveLeft(grid);
}

void TetrisBoard::moveRight() {
	currentBlock.moveRight(grid);
}

void TetrisBoard::rotateLeft() {
	currentBlock.rotateLeft(grid);
}

void TetrisBoard::rotateRight() {
	currentBlock.rotateRight(grid);
}

void TetrisBoard::updateMovement() {
	int i, j;
	int rowCleared;
	bool flag;
	if(currentBlock.moveDown(grid)) {
		//Fixed to grid
		
		//Check whether can clear rows
		rowCleared = 0;
		//Valid range is shifting when clearing
		i = 0;
		while(i < GRID_HEIGHT - rowCleared) {
			flag = true;
			for(j = 0; j < GRID_WIDTH && flag; j++) {
				//Blank block
				if(grid[j][i + rowCleared].rgb() == 0) {
					flag = false;
				}
			}
			if(flag) {
				//Clear this row
				//Preserve the location
				rowCleared++;
			}
			else {
				//Move the row accordingly
				if(rowCleared > 0) {
					for(j = 0; j < GRID_WIDTH; j++) {
						grid[j][i] = grid[j][i + rowCleared];
					}
				}
				i++;
			}
		}
		//Clear the remaining part
		for(; i < GRID_HEIGHT; i++) {
			for(j = 0; j < GRID_WIDTH; j++) {
				grid[j][i].setRgb(0, 0, 0);
			}
		}
		
		//Emit the signal to add point
		emit rowClear(rowCleared);
		//Emit the signal to renew block
		emit blockFallen();
	}
	//Call for repaint
	repaint();
}

void TetrisBoard::renewBlock(const TetrisBlock &block) {
	currentBlock = block;
	//Test if the block can be put
	if(currentBlock.putBoard(grid)) {
		//Game over
		state = Tetris::stopped;
		
		//Emit gameover signal
		emit gameover();
	}
}

void TetrisBoard::paintEvent(QPaintEvent* e) {
	int i, j, k;
	QPainter painter;
	painter.begin(this);
	painter.setPen(QColor(0, 0, 0));
	
	//Draw background
	painter.drawPixmap(0, 0, bg);
	
	//Draw blocks
	for(i = 0; i < BOARD_WIDTH; i++) {
		for(j = 0; j < BOARD_HEIGHT; j++) {
			//The block is present
			if(grid[i][j].rgb() != 0) {
				painter.setBrush(grid[i][j]);
				paiinter.drawRect(i * TET_SIZE,
					(GRID_HEIGHT - j -1) * TET_SIZE, 
					TET_SIZE, TET_SIZE);
			}
		}
	}
	if(state == Tetris::stopped) {
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
