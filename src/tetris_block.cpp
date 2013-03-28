/*
 * Tetris for COMP2012H
 * Author: TAN, Shuhao
 * Stu ID: 20090398
 * 2013 Spring
 *
 * tetris_block.cpp
 *
 * Tetris blocks
 */

#include "tetris_block.h"
#include <qapplication.h>
#include <qobject.h>
#include <qcolor.h>
#include <qpainter.h>
#include <qstring.h>
#include <qfile.h>
#include <qdir.h>

#include <cstdlib>
#include <cassert>

TetrisBlock::TetrisBlock(int type, int direction, QObject* parent, const char* name)
:QObject(parent, name),
 id(type), face(direction),
 x(GRID_WIDTH/2), y(GRID_HEIGHT - 3) {
 	if(!TetrisBlock::initFlag) {
 		init();
 	}
 	
 	//Validate id and face
 	assert(id >= -1 && id < blockTypes);
 	assert(face >= -1 && face < 4);
 	
	if(id == -1) {
		//Random id
		id = rand() % blockTypes;
	}
	if(face == -1) {
		//Random face
		face = rand() % 3;
	}
}

TetrisBlock::TetrisBlock(const TetrisBlock& block)
:QObject(block.parent(), block.name()),
 id(block.id), face(block.face),
 x(block.x), y(block.y) {
 	if(!TetrisBlock::initFlag) {
 		init();
 	}
}

TetrisBlock& TetrisBlock::operator=(const TetrisBlock& block) {
	//Do the copy
	id = block.id;
	face = block.face;
	x = block.x;
	y = block.y;
	
	return *this;
}

TetrisBlock::~TetrisBlock() {
}

int TetrisBlock::getX() const {
	return x;
}

int TetrisBlock::getY() const {
	return y;
}

const bool** TetrisBlock::getShape(int *size, QColor *color) const {
	if(size) {
		//Set size
		*size = blockSize[id];
	}
	if(color) {
		//Set color
		*color = blockColor[id];
	}
	//Cast from non-const to const
	return const_cast<const bool**>(shape[face][id]);
}

void TetrisBlock::moveLeft(const QColor grid[][BOARD_HEIGHT + 1]) {
	//Assume to move
	x--;
	if(putBoard(grid)) {
		//Cannot move
		x++;
	}
}

void TetrisBlock::moveRight(const QColor grid[][BOARD_HEIGHT + 1]) {
	//Assume to move
	x++;
	if(putBoard(grid)) {
		//Cannot move
		x--;
	}
}

void TetrisBlock::rotateLeft(const QColor grid[][BOARD_HEIGHT + 1]) {
	//Assume to rotate
	face = (face + 3) % 4;
	if(putBoard(grid)) {
		//Cannot move
		face = (face + 1) % 4;
	}
}

void TetrisBlock::rotateRight(const QColor grid[][BOARD_HEIGHT + 1]) {
	//Assume to rotate
	face = (face + 1) % 4;
	if(putBoard(grid)) {
		//Cannot move
		face = (face + 3) % 4;
	}
}

int TetrisBlock::moveDown(QColor grid[][BOARD_HEIGHT + 1]) {
	int i, j;
	int baseX, baseY;
	//Assume to move down
	y--;
	if(putBoard(grid)) {
		//Cannot move
		y++;
		
		//Put it on board
		baseX = x - (blockSize[id] >> 1);
		baseY = y + (blockSize[id] >> 1);
		
		for(j = 0; j < blockSize[id]; j++) {
			for(i = 0; i < blockSize[id]; i++) {
				if(shape[face][id][i][j]) {
					//Solid block
					//Put it
					grid[i + baseX][baseY - j] = blockColor[id];
				}
			}
		}
		return 1;
	}
	else {
		return 0;
	}
}

int TetrisBlock::putBoard(const QColor grid[][BOARD_HEIGHT + 1]) const {
	int i, j;
	int baseX = x - (blockSize[id] >> 1),
		baseY = y + (blockSize[id] >> 1);
	unsigned int zero = qRgb(0, 0, 0);
	for(j = 0; j < blockSize[id]; j++) {
		for(i = 0; i < blockSize[id]; i++) {
			if(shape[face][id][i][j]) {
				//Solid block
				//Border check
				if(baseX + i < 0 || baseX + i >= GRID_WIDTH
				 || baseY - j < 0 || baseY - j >= GRID_HEIGHT) {
					return 1;
				}
				//Collision check
				if(grid[baseX + i][baseY - j].rgb() != zero) {
					return 1;
				}
			}
		}
	}
	return 0;
}

void TetrisBlock::paint(QPainter *painter) const {
	int i, j;
	int baseX = x - (blockSize[id] >> 1),
		baseY = GRID_HEIGHT - 1 - y - (blockSize[id] >> 1);
	painter->setBrush(blockColor[id]);
	//Pass untouchable region
	for(j = 0; baseY + j < 0; j++) {
	}
	for(; j < blockSize[id] && baseY + j < GRID_HEIGHT; j++) {
		//Pass untouchable region
		for(i = 0; baseX + i < 0; i++){
		}
		for(; i < blockSize[id] && baseX + i < GRID_WIDTH; i++) {
			if(shape[face][id][i][j]) {
				//Draw it
				painter->drawRect((baseX + i) * TET_SIZE, (baseY + j) * TET_SIZE,
					TET_SIZE, TET_SIZE);
			}
		}
	}
}
