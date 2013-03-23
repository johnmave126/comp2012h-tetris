/*
 * Tetris for COMP2012H
 * Author: TAN, Shuhao
 * Stu ID: 20090398
 * 2013 Spring
 *
 * tetris_stats.h
 *
 * The header file for tetris stats, displaying current stats
 */

#ifndef _TETRIS_STATS_H
#define _TETRIS_STATS_H

#include "tetris_common.h"
#include "tetris_block.h"
#include <qwidget.h>
#include <qpixmap.h>
#include <qlabel.h>

class TetrisStats: public QWidget {
	// All classes that contain signals or slots
	// must mention Q_OBJECT in their declaration.
	Q_OBJECT

	public:
		TetrisStats(QWidget* parent = 0, const char* name = 0);
		~TetrisStats();
		
		/*
		 * getBlock
		 *
		 * return the predicted block
		 */
		TetrisBlock getBlock() const;
		
		/*
		 * getLevel
		 *
		 * return the current level
		 */
		int getLevel() const;
		
	public slots:
		/*
		 * reset
		 *
		 * slot that handle action when try to reset the stats
		 */
		void reset();
		
		/*
		 * rowClear
		 *
		 * num: number of rows cleared
		 *
		 * slot that handle action when one or more row cleared
		 */
		void rowClear(int num);
		
		/*
		 * generateBlock
		 *
		 * slot that handle action when try to generate a new random block
		 */
		void generateBlock();
	
	signals:
		
	protected:
		/** handler for paint event */
		virtual void paintEvent(QPaintEvent*);
		
	private:
		//Predicted block
		TetrisBlock *predictBlock;
		
		//Store level and score
		int level, score;
		
		//QLabel for level and score
		QLabel *levelLabel, *scoreLabel;
};

#endif
