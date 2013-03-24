  Tetris
  ===============
  
  This is a project for COMP2012H, 2013 Spring, HKUST
  
  The main purpose is to create a Tetris game
  
  The course web page:
      http://course.cse.ust.hk/comp2012h
      (CSD account required)
  
  Author
  ===============
  Name: TAN, Shuhao
  Student ID: 20090398
  ITSC: stanab
  
  How-to-compile-and-run
  ===============
  >qmake
  >gmake
  >./build_bin/tetris
  
  Technical Details
  ===============
  
  The build of this project involves the following tools:
      UltraEdit (text editor)
      SecureCRT (ssh terminal)
      X-Win32 2012 (X11 server for windows)
      Git (manage code)
      Qt (GUI library)
      GNU toolchain (compiler)
  
  Source file tree:
      Tetris
      |
      |--include
      |  |--tetris_common.h
      |  |--tetris_manager.h
      |  |--tetris_block.h
      |  |--tetris_board.h
      |  |--tetris_stats.h
      |
      |--src
      |  |--tetris.cpp
      |  |--tetris_manager.cpp
      |  |--tetris_block.cpp
      |  |--tetris_block_static.cpp
      |  |--tetris_board.cpp
      |  |--tetris_board_control.cpp
      |  |--tetris_stats.cpp
      |
      |--tetris.pro
  
  Deviation from sample program
      I found that when the game is over, the block that collide with the 
      fixed blocks will still be painted. So it will override some part of 
      the board. I think this is not a correct behaviour, so I change it to 
      "if the last block put on board collides with the block fixed, it will
      not be painted and game is over".

      A little hint to start the game is added.

      The level/score calculation is changed to:
          score = (5 + 5 * level) * combo * combo
          if score is greater than or equal to 2^9 * 100, level is 10
          otherwise if score if score < 2^n * 100 for smallest n, level is n+1
  
  Design of the project:
      From the interface of a tetris programme, it is easily to split it 
      into two parts--game board and status display. So I design a manager 
      as the main window to place these two component and communicate between 
      them. The manager is to control the flow of the game, to deal with 
      events correctly, and to pass values between board and stats.

      The board is one class, however has two cpp file with different 
      aspects. The constructor/destructor and painting are in 
      tetris_board.cpp while functions related to block control are in 
      tetris_board_control.cpp.

      The stats is quite naive, it is quite separate from other components. 
      So I just put everything together. As for level/score calculation, I 
      use the following formula:
          score = (5 + 5 * level) * combo * combo
          level is calculated through a predefined static level set array
      The design of level set ensures the extendibility of level. I believe 
      as the level adds up, it should need more score for next level. So now 
      level is calculated as doubled every levelup. the block in the preview 
      window is scaled to reserve extendibility for larger blocks.

      The implementation of tetris block is the most challenging part of the 
      project. From the beginning, I decided to implement a feature that 
      block shape can be readed through an external config file to improve 
      its extendibility. So I use some static members to store these blocks 
      and require initialization in constructor. At last the format of 
      config file is as follow:
          The first line: num of blocks
          For every block
              The first line: red green blue (colour component of the block)
              The second line: size of the block (s x s)
              The next s lines: each line has s characters
                                '.' represents no solid, '*' represents solid
      To show the center of the block, I set that the input block shape must 
      be a square shape with center in the center. That is, the file input 
      only has one size input, followed by a s x s square. This design makes 
      it convenient to rotate a block. To improve the performance, I 
      store all the possibilities of the block shape in static members so 
      that they can be used instantly. The position of the block is managed 
      by block itself, because I don't want to expose much to board. The 
      calculation of collision is simple. I just assume the block is able to 
      move and try to put it on board. If one little solid square is out of 
      border or collide with original blocks, a collision is detected.
  
  Enjoy!
    TAN, Shuhao

--- end of README ---