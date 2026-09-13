#include <ncurses.h>
#include "main.h"
#include "board.h"

int getLiberties(WINDOW* win, Board (*board)[BX], Stone* stone) {
  stone->liberties = 4;
  if (board[stone->bpos.y][stone->bpos.x-1].stone != NULL){
    stone->liberties--;
  }
  if (board[stone->bpos.y][stone->bpos.x+1].stone != NULL){
    stone->liberties--;
  }
  if (board[stone->bpos.y-1][stone->bpos.x].stone != NULL){
    stone->liberties--;
  }
  if (board[stone->bpos.y+1][stone->bpos.x].stone != NULL){
    stone->liberties--;
  }
  return stone->liberties;
}
int atari();
