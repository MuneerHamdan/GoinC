#include <stdlib.h>
#include <ncurses.h>
#include "main.h"
#include "board.h"

Stone* makeStone(char c, Vec2i pos) {
  Stone* stone = (Stone*)malloc(sizeof(Stone));
  stone->c = c;
  stone->pos.y = pos.y;
  stone->pos.x = pos.x;
  stone->liberties = 0; 
  return stone;
}
//void removeStone(Win
void removeStones(WINDOW* win, Board (*board)[BX]){
  for (int i = 0; i < BY; i++) {
    for (int j = 0; j < BX; j++) {
      if (board[i][j].stone != NULL) {
        mvwprintw(win, i, j, "removing: %d %d\n", i, j);
        free(board[i][j].stone);
      }
    }
  }
}

void placeStone(Board* tile, Stone* stone, WINDOW* win) {
        tile->stone = stone;
        mvwaddch(win, stone->pos.y, stone->pos.x, tile->stone->c);
        wmove(win, stone->pos.y, stone->pos.x);
}
