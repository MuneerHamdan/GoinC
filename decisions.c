#include <ncurses.h>
#include "main.h"
#include "board.h"

int getLiberties(Board (*board)[BX], Stone* stone, WINDOW* win) {
  if (board[stone->pos.y][stone->pos.x].stone) {
  }
  return stone->liberties;
}
int atari();
