TARGET = tetris
INCLUDEPATH += include
DEPENDPATH  += include src
HEADERS += \
	tetris_common.h tetris_manager.h tetris_block.h tetris_board.h \
	tetris_stats.h
SOURCES += \
	tetris.cpp tetris_manager.cpp tetris_block.cpp tetris_block_static.cpp \
	tetris_board.cpp tetris_board_control.cpp tetris_stats.cpp
RES_DIR = resource
CONFIG += qt warn_on
DESTDIR = build_bin
MOC_DIR = build_tmp
OBJECTS_DIR = build_tmp

#copy resource to destination directory
QMAKE_POST_LINK= cp -r $${RES_DIR}/* $${DESTDIR}