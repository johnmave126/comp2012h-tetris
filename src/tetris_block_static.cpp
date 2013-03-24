/*
 * Tetris for COMP2012H
 * Author: TAN, Shuhao
 * Stu ID: 20090398
 * 2013 Spring
 *
 * tetris_block_static.cpp
 *
 * Static members and functions for tetris blocks
 */

#include "tetris_block.h"
#include <qapplication.h>
#include <qobject.h>
#include <qcolor.h>
#include <qstring.h>
#include <qfile.h>
#include <qdir.h>

#include <cstdlib>
#include <cassert>

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

//Static members
bool TetrisBlock::initFlag = false;
int TetrisBlock::blockTypes;
QColor *TetrisBlock::blockColor;
int *TetrisBlock::blockSize;
bool ***TetrisBlock::shape[4];
