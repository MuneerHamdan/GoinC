#ifndef BOARD_H
#define BOARD_H

#include <ncurses.h>
#include "main.h"

// max board size
#define BY 9
#define BX 9
/*
#define BY 13
#define BX 13
*/
/*
#define BY 19
#define BX 19
*/

typedef struct Stone {
  char c;
  Vec2i cpos;
  Vec2i bpos;
  int liberties;

  struct Stone* group;
} Stone;

typedef struct {
  char c;
  Stone* stone;
} Board;

Stone* makeStone(char c, Vec2i cpos, Vec2i bpos, WINDOW* win, Board (*board)[BX]);
void addtogroup(Board (*board)[BX], Stone* stone);
void findDead(WINDOW* win, Board (*board)[BX]);
void removeStone(WINDOW* win, Board (*board)[BX], int bposy, int bposx);
void removeStones(WINDOW* win, Board (*board)[BX]);
void placeStone(Board* board, Stone* stone, WINDOW* win);

#endif
