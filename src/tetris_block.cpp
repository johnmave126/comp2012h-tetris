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

#include <iostream>
#include <cstdlib>
#include <cassert>
using namespace std;

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

void TetrisBlock::init(QString config) {
	int i, j, k;
	int r, g, b;
	QString row;
	
	//Check file existence
	assert(QFile::exists(config));
	
	QFile file(config);
	assert(file.open(IO_ReadOnly));
	//Open successfully
	QTextStream fstream(&file);
	
	fstream >> blockTypes;
	
	//Initialize arrays
	blockColor = new QColor[blockTypes];
	blockSize = new int[blockTypes];
	//Unpack to improve performance
	shape[0] = new bool**[blockTypes];
	shape[1] = new bool**[blockTypes];
	shape[2] = new bool**[blockTypes];
	shape[3] = new bool**[blockTypes];
	
	for(i = 0; i < blockTypes; i++) {
		//Read a block
		//Color
		fstream >> r >> g >> b;
		blockColor[i].setRgb(r, g, b);
		//Size
		fstream >> blockSize[i];
		//Read newline
		fstream.readLine();
		//Shape
		//Allocate memory
		shape[0][i] = new bool*[blockSize[i]];
		shape[1][i] = new bool*[blockSize[i]];
		shape[2][i] = new bool*[blockSize[i]];
		shape[3][i] = new bool*[blockSize[i]];
		for(j = 0; j < blockSize[i]; j++) {
			shape[0][i][j] = new bool[blockSize[i]];
			shape[1][i][j] = new bool[blockSize[i]];
			shape[2][i][j] = new bool[blockSize[i]];
			shape[3][i][j] = new bool[blockSize[i]];
		}
		for(j = 0; j < blockSize[i]; j++) {
			row = fstream.readLine();
			for(k = 0; k < blockSize[i]; k++) {
				if(row[k] == '.') {
					shape[0][i][k][j] = false;
				}
				else {
					shape[0][i][k][j] = true;
				}
			}
		}
		//Rotate accordingly
		//Unpack to improve performance
		for(j = 0; j < blockSize[i]; j++) {
			for(k = 0; k < blockSize[i]; k++) {
				shape[1][i][j][k] = shape[0][i][k][blockSize[i]-j-1];
			}
		}
		for(j = 0; j < blockSize[i]; j++) {
			for(k = 0; k < blockSize[i]; k++) {
				shape[2][i][j][k] = shape[1][i][k][blockSize[i]-j-1];
			}
		}
		for(j = 0; j < blockSize[i]; j++) {
			for(k = 0; k < blockSize[i]; k++) {
				shape[3][i][j][k] = shape[2][i][k][blockSize[i]-j-1];
			}
		}
	}
	//Close file
	file.close();
	
	//Set flag
	TetrisBlock::initFlag = true;
}

void TetrisBlock::destroy() {
	int i, j;
	//Free memory
	for(i = 0; i < blockTypes; i++) {
		for(j = 0; j < blockSize[i]; j++) {
			delete [] shape[0][i][j];
			delete [] shape[1][i][j];
			delete [] shape[2][i][j];
			delete [] shape[3][i][j];
		}
		delete [] shape[0][i];
		delete [] shape[1][i];
		delete [] shape[2][i];
		delete [] shape[3][i];
	}
	delete [] shape[0];
	delete [] shape[1];
	delete [] shape[2];
	delete [] shape[3];
	delete [] blockColor;
	delete [] blockSize;
}

int TetrisBlock::getNumType() {
	return blockTypes;
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
					cout << "Border!" << endl;
					return 1;
				}
				//Collision check
				if(grid[baseX + i][baseY - j].rgb() != zero) {
					cout << "Collision!" << endl;
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

//Static members
bool TetrisBlock::initFlag = false;
int TetrisBlock::blockTypes;
QColor *TetrisBlock::blockColor;
int *TetrisBlock::blockSize;
bool ***TetrisBlock::shape[4];
