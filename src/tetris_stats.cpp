/*
 * Tetris for COMP2012H
 * Author: TAN, Shuhao
 * Stu ID: 20090398
 * 2013 Spring
 *
 * tetris_stats.cpp
 *
 * Stats of the tetris game, the panel of preview and scores
 */

#include "tetris_stats.h"
#include "tetris_block.h"
#include <qmainwindow.h>
#include <qapplication.h>
#include <qpixmap.h>
#include <qcolor.h>
#include <qpainter.h>

TetrisStats::TetrisStats(QWidget* parent, const char* name)
:QWidget(parent, name),
 predictBlock(NULL), level(1), score(0),
 levelLabel("Level: 1", this, "level"),
 scoreLabel("Score: 0", this, "score") {
	//Resize stats to a fixed size
	setFixedSize(100, BOARD_HEIGHT);
	
	//Move labels to appropriate location
	levelLabel.move(0, 140);
	scoreLabel.move(0, 150 + levelLabel.height());
	
}

TetrisStats::~TetrisStats() {
	if(predictBlock) {
		delete predictBlock;
	}
}

TetrisBlock TetrisStats::getBlock() const {
	return predictBlock?(*predictBlock):TetrisBlock();
}

int TetrisStats::getLevel() const {
	return level;
}

void TetrisStats::reset() {
	//Reset block
	if(predictBlock) {
		delete predictBlock;
		predictBlock = NULL;
	}
	//Reset level and scores
	levelLabel.setText("Level: 1");
	scoreLabel.setText("Score: 0");
	level = 1;
	score = 0;
	
	//Call for repaint
	repaint();
}

void TetrisStats::rowClear(int num) {
	//Add up score
	score += 10 * num * num;
	//Recalculate level
	level = (score >= 900)?(10):(1+score/100);
	
	//Set labels
	levelLabel.setText(QString("Level: %1").arg(level));
	scoreLabel.setText(QString("Score: %1").arg(score));
}

void TetrisStats::generateBlock() {
	if(predictBlock) {
		delete predictBlock;
	}
	//Random generate a block
	predictBlock = new TetrisBlock();
	
	//Call for repaint
	repaint();
}

void TetrisStats::paintEvent(QPaintEvent* e) {
	int i, j;
	float tetSize;
	const bool** shape;
	int size;
	QColor blockCol;
	QPainter painter();
	painter.begin(this);
	painter.setPen(QColor(0, 0, 0));
	
	//Fill preview window
	painter.setBrush(QColor(255, 255, 255));
	painter.drawRect(0, 0, 100, 100);
	
	//Draw predicted block
	if(predictBlock) {
		shape = predictBlock->getShape(&size, &blockCol);
		//Stretch the graph
		tetSize = 1.0 * 100 / size;
		painter.setBrush(blockCol);
		for(i = 0; i < size; i++) {
			for(j = 0; j < size; j++) {
				if(shape[i][j]) {
					painter.drawRect(j * tetSize, i * tetSize,
						tetSize, tetSize);
				}
			}
		}
	}
	painter.end();
}
