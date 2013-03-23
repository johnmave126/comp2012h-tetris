/*
 * Tetris for COMP2012H
 * Author: TAN, Shuhao
 * Stu ID: 20090398
 * 2013 Spring
 *
 * tetris_manager.h
 *
 * The header file for tetris manager, the mainwindow for all the
 * components
 */

#ifndef _TETRIS_MANAGER_H
#define _TETRIS_MANAGER_H

#include "tetris_common.h"
#include "tetris_board.h"
#include "tetris_stats.h"
#include <qmainwindow.h>
#include <qapplication.h>
#include <qtimer.h>

class TetrisManager: public QMainWindow {
	// All classes that contain signals or slots
	// must mention Q_OBJECT in their declaration.
	Q_OBJECT

	public:
		TetrisManager(QWidget* parent = 0, const char* name = 0);
		~TetrisManager();
		
	public slots:
		/*
		 * blockFallen
		 *
		 * slot that handle action when there is need to replace block
		 */
		void blockFallen();
		
		/*
		 * start
		 *
		 * slot that handle action when start the game
		 */
		void start();
		
		/*
		 * gameover
		 *
		 * slot that handle action when game is over
		 */
		void gameover();
		
		/*
		 * updateMovement
		 *
		 * slot that handle action when try to updateMovement
		 */
		void updateMovement();
		
	protected:
		
		/** handler for keyboard event */
		virtual void keyPressEvent(QKeyEvent*);
		
	private:
		//Game board
		TetrisBoard *gameBoard;
		
		//Game stats
		TetrisStats *gameStats;
		
		//Helper timer
		QTimer *timer;
		
		//Current condition
		Tetris::Condition state;
};

#endif
