#include "board.h"
#include "decisions.h"
#include "main.h"
#include <ncurses.h>
#include <stdlib.h>

Stone *makeStone(char c, Vec2i cpos, Vec2i bpos, WINDOW *win, Board (*board)[BX]) {
  Stone *stone = (Stone *)malloc(sizeof(Stone));
  stone->c = c;
  stone->cpos.y = cpos.y;
  stone->cpos.x = cpos.x;
  stone->bpos.y = bpos.y;
  stone->bpos.x = bpos.x;
  stone->liberties = getLiberties(win, board, stone);
  stone->group = stone;
  addtogroup(board, stone);
  return stone;
}
/*
 * ok so basically, wen you add a stone, check if its cardinal adjacent to a same colored group
 * if it is, add that stone to that group
 * else, it becomes its own group
 *
 * POSSIBLY MAKE A GROUP DYNAMIC MEMORY???????????
 */
void addtogroup(Board (*board)[BX], Stone* stone){
  // have to make only join color it belongs to
  if (board[stone->bpos.y][stone->bpos.x-1].stone != NULL && board[stone->bpos.y][stone->bpos.x-1].stone->group != NULL) stone->group = board[stone->bpos.y][stone->bpos.x-1].stone->group;
  else if (board[stone->bpos.y][stone->bpos.x+1].stone != NULL && board[stone->bpos.y][stone->bpos.x+1].stone->group != NULL) stone->group = board[stone->bpos.y][stone->bpos.x+1].stone->group;
  else if (board[stone->bpos.y-1][stone->bpos.x].stone != NULL && board[stone->bpos.y-1][stone->bpos.x].stone->group != NULL) stone->group = board[stone->bpos.y-1][stone->bpos.x].stone->group;
  else if (board[stone->bpos.y+1][stone->bpos.x].stone != NULL && board[stone->bpos.y+1][stone->bpos.x].stone->group != NULL) stone->group = board[stone->bpos.y+1][stone->bpos.x].stone->group;

  // have to make it make the liberties combined and shared among all groups members

  // what if there's two or more valid groups to join
}
void findDead(WINDOW *win, Board (*board)[BX]) {
  // THERE'S PROBABLY AN ALGORITHM TO BE FOUND
  for (int i = 0; i < BY; i++) {
    for (int j = 0; j < BX; j++) {
      if (board[i][j].stone != NULL && board[i][j].stone->liberties == 0) {
        removeStone(win, board, i, j);
      }
    }
  }
}
void removeStone(WINDOW *win, Board (*board)[BX], int bposy, int bposx) {
  free(board[bposy][bposx].stone);
  board[bposy][bposx].stone = NULL;
  board[bposy][bposx].c = '\0';
}
void removeStones(WINDOW *win, Board (*board)[BX]) {
  for (int i = 0; i < BY; i++) {
    for (int j = 0; j < BX; j++) {
      if (board[i][j].stone != NULL) {
        //        mvwprintw(win, i, j, "removing: %d %d\n", i, j);
        free(board[i][j].stone);
        board[i][j].stone = NULL;
        board[i][j].c = '\0';
      }
    }
  }
}

void placeStone(Board *tile, Stone *stone, WINDOW *win) {
  tile->stone = stone;
  tile->c = stone->c;
  //        mvwaddch(win, stone->pos.y, stone->pos.x, tile->stone->c);
  //        wmove(win, stone->pos.y, stone->pos.x);
}
