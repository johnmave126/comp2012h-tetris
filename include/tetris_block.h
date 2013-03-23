/*
 * Tetris for COMP2012H
 * Author: TAN, Shuhao
 * Stu ID: 20090398
 * 2013 Spring
 *
 * tetris_block.h
 *
 * The header file for tetris blocks
 */

#ifndef _TETRIS_BLOCK_H
#define _TETRIS_BLOCK_H

#include "tetris_common.h"
#include <qobject.h>
#include <qwidget.h>
#include <qstring.h>
#include <qcolor.h>

class TetrisBlock: public QObject {
	// All classes that contain signals or slots
	// must mention Q_OBJECT in their declaration.
	Q_OBJECT

	public:
		/*
		 * constructor
		 *
		 * type: -1 for random, other for specified type
		 * direction: -1 for random, 0-3 for specified direction
		 *
		 * contruct a block
		 */
		TetrisBlock(int type = -1, int direction = -1, QObject* parent = 0, const char* name = 0);
		
		/*
		 * copy constructor
		 */
		TetrisBlock(const TetrisBlock&);
		
		~TetrisBlock();
		
		//Static functions
		/*
		 * init
		 *
		 * config: the filename of the block config file
		 *
		 * return the pointer to the shape, a square region with shape in it
		 * 0 for blank, 1 for solid
		 */
		void init(QString config);
		
		/*
		 * getNumType
		 *
		 * return the number of type available
		 */
		int getNumType();
		
		//Non-static functions
		/*
		 * getShape
		 *
		 * size: the size of the square with shape in it
		 * color: to get the color of the block
		 *
		 * return the pointer to the shape, a square region with shape in it
		 * false for blank, true for solid
		 */
		const bool** getShape(int *size, QColor *color) const;
		
		/*
		 * moveLeft
		 *
		 * grid: the current bottom state
		 *
		 * try to move to left
		 */
		void moveLeft(const QColor** grid);
		
		/*
		 * moveRight
		 *
		 * grid: the current bottom state
		 *
		 * try to move to right
		 */
		void moveRight(const QColor** grid);
		
		/*
		 * roateLeft
		 *
		 * grid: the current bottom state
		 *
		 * try to rotate counter-clockwise
		 */
		void roateLeft(const QColor** grid);
		
		/*
		 * roateRight
		 *
		 * grid: the current bottom state
		 *
		 * try to rotate clockwise
		 */
		void roateRight(const QColor** grid);
		
		/*
		 * moveDown
		 *
		 * grid: the current bottom state
		 * will be changed if fixed
		 *
		 * try to move down
		 * return 0 for success, 1 for fixed to grid
		 */
		int moveDown(QColor** grid);
		
		/*
		 * putBoard
		 *
		 * grid: the current bottom state
		 *
		 * judge if it is possible to put on board
		 * return 0 for success, 1 for game over
		 */
		int putBoard(const QColor** grid) const;
		
		/*
		 * paint
		 *
		 * painter: the painter used to paint
		 *
		 * try to paint
		 */
		void paint(QPainter *painter) const;
		
	public slots:
	
	signals:
		
	protected:
		
	private:
		//Static members
		//Initialize at the beginning
		//Number of block type
		static int blockTypes;
		
		//Color for the blocks
		static QColor *blockColor;
		
		//Size array
		static int *blockSize;
		
		//All together 4 possibilities
		//shape[i][j][k][l]represents
		//the jth block type
		//the face with i
		//position(k, l)
		static bool ***shape[4];
		
		//Non-static members
		//Identify the type of this block
		int id;
		
		//The current direction in correspondece to shape
		int face;
		
		//The location of the block on board
		int x, y;
};

#endif
