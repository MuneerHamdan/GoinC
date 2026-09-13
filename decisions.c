#include <ncurses.h>
#include "main.h"
#include "board.h"

int getLiberties(WINDOW* win, Board (*board)[BX], Stone* stone) {
  stone->liberties = 4;
  if (board[stone->bpos.y][stone->bpos.x-1].stone != NULL) stone->liberties--;
  if (board[stone->bpos.y][stone->bpos.x+1].stone != NULL) stone->liberties--;
  if (board[stone->bpos.y-1][stone->bpos.x].stone != NULL) stone->liberties--;
  if (board[stone->bpos.y+1][stone->bpos.x].stone != NULL) stone->liberties--;

  if (stone->bpos.y == 0 || stone->bpos.y == BY) stone->liberties--;
  if (stone->bpos.x == 0 || stone->bpos.x == BX) stone->liberties--;
  return stone->liberties;
}
void updateLiberties(WINDOW* win, Board (*board)[BX]) {
  for (int i = 0; i < BY; i++) {
    for (int j = 0; j < BX; j++) {
      if (board[i][j].stone != NULL)
        board[i][j].stone->liberties = getLiberties(win, board, board[i][j].stone);
    }
  }
}
int atari();
