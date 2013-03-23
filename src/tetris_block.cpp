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
#include <qobject.h>
#include <qcolor.h>
#include <qpainter.h>
#include <qstring.h>
#include <qfile.h>

#include <cstdlib>
#include <cassert>
#include <typeinfo>

TetrisBlock::TetrisBlock(int type, int direction, QObject* parent, const char* name)
:QObject(parent, name),
 id(type), face(direction),
 x(GRID_WIDTH/2), y(GRID_WIDTH - 3) {
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
:id(block.id), face(block.face),
 x(block.x), y(block.y) {
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
		//Shape
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
}

int TetrisBlock::getNumType() {
	return blockTypes;
}

const bool** TetrisBlock::getShape(int *size, QColor *color) {
	if(size) {
		//Set size
		*size = blockSize[id];
	}
	if(color) {
		//Set color
		*color = blockColor[id];
	}
	return cosnt_cast<const bool**>shape[face][id];
}

void TetrisBlock::moveLeft(const QColor** grid) {
}

void TetrisBlock::moveRight(const QColor** grid) {
}

void TetrisBlock::rotateLeft(const QColor** grid) {
}

void TetrisBlock::rotateRight(const QColor** grid) {
}

int TetrisBlock::moveDown(QColor** grid) {
	return 0;
}

int TetrisBlock::putBoard(const QColor** grid) const {
	return 0;
}

void TetrisBlock::paint(QPainter *painter) const {
}

//Static members
int TetrisBlock::blockTypes;
QColor *TetrisBlock::blockColor;
int *TetrisBlock::blockSize;
bool ***TetrisBlock::shape[4];
