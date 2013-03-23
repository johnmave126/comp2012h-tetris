/*
 * Tetris for COMP2012H
 * Author: TAN, Shuhao
 * Stu ID: 20090398
 * 2013 Spring
 *
 * tetris_common.h
 *
 * Common definition inclusion
 */

#ifndef _TETRIS_COMMON_H
#define _TETRIS_COMMON_H

#ifndef FALSE
#define FALSE 0
#endif

#ifndef TRUE
#define TRUE 1
#endif

#ifndef NULL
#define NULL 0
#endif

//Size of tetris(px)
#define TET_SIZE		(20)

//Size of grid used by board
#define GRID_WIDTH		(20)
#define GRID_HEIGHT		(40)

//Size of the board(px)
#define BOARD_WIDTH		(TET_SIZE*GRID_WIDTH)
#define BOARD_HEIGHT	(TET_SIZE*GRID_HEIGHT)

//Container namespace
namespace Tetris {
    //The state of game condition
    enum Condition {
        playing = 0,
        stopped
    };
}

#endif
