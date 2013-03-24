/*
 * Tetris for COMP2012H
 * Author: TAN, Shuhao
 * Stu ID: 20090398
 * 2013 Spring
 *
 * tetris_board_control.cpp
 *
 * The control part for board
 */

#include "tetris_board.h"
#include "tetris_block.h"
#include <qmainwindow.h>
#include <qapplication.h>
#include <qpixmap.h>
#include <qcolor.h>
#include <qfont.h>
#include <qpainter.h>

//Simply pass the control to blocks
void TetrisBoard::moveLeft() {
	currentBlock.moveLeft(grid);
	//Call for repaint
	repaint();
}

void TetrisBoard::moveRight() {
	currentBlock.moveRight(grid);
	//Call for repaint
	repaint();
}

void TetrisBoard::rotateLeft() {
	currentBlock.rotateLeft(grid);
	//Call for repaint
	repaint();
}

void TetrisBoard::rotateRight() {
	currentBlock.rotateRight(grid);
	//Call for repaint
	repaint();
}

void TetrisBoard::updateMovement() {
	int i, j;
	int rowCleared;
	unsigned int zero = qRgb(0, 0, 0);
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
				if(grid[j][i + rowCleared].rgb() == zero) {
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
	//Call for repaint
	repaint();
}
