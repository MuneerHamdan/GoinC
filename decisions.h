#ifndef DECISIONS_H
#define DECISIONS_H

#include <ncurses.h>
#include "board.h"

/*
  ok so basically do on-place-checks

  so when player places a stone, check from cursor's position's cardinal directions if there are any enemy stones. if there are add that many stones to the player's stone's liberties
*/
int getLiberties(WINDOW* win, Board (*board)[BX], Stone* stone);
int atari();

#endif
