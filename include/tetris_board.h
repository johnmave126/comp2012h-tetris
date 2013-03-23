/*
 * Tetris for COMP2012H
 * Author: TAN, Shuhao
 * Stu ID: 20090398
 * 2013 Spring
 *
 * tetris_board.h
 *
 * The header file for tetris board, the board where blocks fall
 */

#ifndef _TETRIS_BOARD_H
#define _TETRIS_BOARD_H

#include "tetris_common.h"
#include "tetris_board.h"
#include "tetris_block.h"
#include <qwidget.h>
#include <qpixmap.h>

class TetrisBoard: public QWidget {
	// All classes that contain signals or slots
	// must mention Q_OBJECT in their declaration.
	Q_OBJECT

	public:
		TetrisBoard(QWidget* parent = 0, const char* name = 0);
		~TetrisBoard();
		
	public slots:
		/*
		 * reset
		 *
		 * slot that handle action when try to reset the board
		 */
		void reset();
		
		/*
		 * moveLeft
		 *
		 * slot that handle action when try to move current block left
		 */
		void moveLeft();
		
		/*
		 * moveRight
		 *
		 * slot that handle action when try to move current block right
		 */
		void moveRight();
		
		/*
		 * rotateLeft
		 *
		 * slot that handle action when try to rotate current block counter-clockwise
		 */
		void rotateLeft();
		
		/*
		 * rotateRight
		 *
		 * slot that handle action when try to rotate current block clockwise
		 */
		void rotateRight();
		
		/*
		 * updateMovement
		 *
		 * update a falling of current block
		 */
		void updateMovement();
		
		/*
		 * renewBlock
		 *
		 * block: the new block to add to
		 *
		 * add a new block to the top of the board
		 */
		void renewBlock(const TetrisBlock &block);
	
	signals:
		/*
		 * rowClear
		 *
		 * num: the number of row cleared
		 *
		 * signal emitted when one or more rows cleared
		 */
		void rowClear(int num);
		
		/*
		 * gameover
		 *
		 * signal emitted when game is over
		 */
		void gameover();
		
		/*
		 * blockFallen
		 *
		 * signal emitted when a block has fallen and fixed
		 */
		void blockFallen();
		
	protected:
		/** handler for paint event */
		virtual void paintEvent(QPaintEvent*);
		
	private:
		//Grid of bottom blocks
		//One extra row for convenient
		QColor grid[BOARD_WIDTH][BOARD_HEIGHT + 1];
		
		//Current Block
		TetrisBlock currentBlock;
		
		//Background
		QPixmap bg;
		
		//Current condition
		Tetris::Condition state;
};

#endif
