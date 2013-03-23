/*
 * Tetris for COMP2012H
 * Author: TAN, Shuhao
 * Stu ID: 20090398
 * 2013 Spring
 *
 * tetris_manager.cpp
 *
 * Manager of the tetris, and act as mainwindow
 */

#include "tetris_manager.h"
#include "tetris_board.h"
#include "tetris_stats.h"
#include "tetris_block.h"
#include <qmainwindow.h>
#include <qapplication.h>
#include <qtimer.h>

TetrisManager::TetrisManager(QWidget* parent, const char* name)
:QMainWindow(parent, name),
 gameBoard(this, "board"), gameStats(this, "stats"),
 timer(this),
 state(Tetris::stopped) {
	//Resize window to a fixed size
	setFixedSize(BOARD_WIDTH + 30 + 100, BOARD_HEIGHT + 20);
	
	//Set location
	gameBoard.move(10, 10);
	gameStats.move(BOARD_WIDTH + 20, 10);
	
	//Connect events related to board
	connect(&gameBoard, SIGNAL(gameover()),
		this, SLOT(gameover()));
	connect(&gameBoard, SIGNAL(blockFallen()),
		this, SLOT(blockFallen()));
	
	//Connect events between board and stats
	connect(&gameBoard, SIGNAL(rowClear(int)),
		&gameStats, SLOT(rowClear(int)));
	
	//Connect events related to timer
	connect(&timer, SIGNAL(timeout()),
		this, SLOT(updateMovement()));
	
	//Initialize blocks
	TetrisBlock::init();
}

TetrisManager::~TetrisManager() {
	//Free up memory
	TetrisBlocl::destory();
}

void TetrisManager::blockFallen() {
	//Send the predicted block to board
	gameBoard.renewBlock(gameStats.getBlock());
	
	//Ask stats to generate next block
	gameStats.generateBlock();
}

void TetrisManager::start() {
	//Reset board and stats
	gameBoard.reset();
	gameStats.reset();
	
	//Generate a block for game board
	gameBoard.renewBlock(TetrisBlock());
	
	//Ask stats to generate next block
	gameStats.generateBlock();
	
	//Begin timer
	timer.start(1000 - (gameStats.getLevel() - 1) * 100, true);
}

void TetrisManager::gameover() {
	//Reset state
	state = Tetris::stopped;
	
	//Stop timer
	timer.stop();
}

void TetrisManager::updateMovement() {
	//Ask board to update
	gameBoard.updateMovement();
	
	//Not game over
	if(state == Tetris::playing) {
		//Set next timer
		timer.start(1000 - (gameStats.getLevel() - 1) * 100, true);
	}
}

void TetrisManager::keyPressEvent(QKeyEvent* e) {
	switch(e->key()) {
		case Qt::Key_Up:
			if(state == Tetris::stopped) {
				start();
			}
			break;
		//Block Movement
		case Qt::Key_Down:
			if(state == Tetris::playing) {
				//Forcedly move down
				updateMovement();
			}
			break;
		case Qt::Key_Left:
			if(state == Tetris::playing) {
				//Move left
				gameBoard.moveLeft();
			}
			break;
		case Qt::Key_Right:
			if(state == Tetris::playing) {
				//Move right
				gameBoard.moveRight();
			}
			break;
		case Qt::Key_Z:
			if(state == Tetris::playing) {
				//Rotate clockwise
				gameBoard.rotateRight();
			}
			break;
		case Qt::Key_X:
			if(state == Tetris::playing) {
				//Rotate counter-clockwise
				gameBoard.rotateRight();
			}
			break;
		default:
			//Send the event to parent
			e->ignore();
			break;
	}
}
