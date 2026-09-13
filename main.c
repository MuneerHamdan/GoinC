#include <ncurses.h>
#include <errno.h>
#include "main.h"
#include "board.h"
#include "decisions.h"


int main(void) {

  // check window
  WINDOW* win = initscr();
  errno = cbreak();
  if (errno)
    fprintf(stderr, "error cbreak%d\n", errno);
  errno = notimeout(win, FALSE);
  errno = noecho();
  if (errno)
    fprintf(stderr, "error noecho%d\n", errno);
  errno = notimeout(win, FALSE);
  if (errno)
    fprintf(stderr, "error notimeout%d\n", errno);
  errno = keypad(win, TRUE);
  if (errno)
    fprintf(stderr, "error keypad%d\n", errno);


  char turn = 0;

  // initialize board
  Board _board[BY][BX];
  for (int i = 0; i < BY; i++) {
    for (int j = 0; j < BX; j++) {
      _board[i][j].c = '+';
      _board[i][j].stone = NULL;
    }
  }

  Board board[BY][BX];
  for (int i = 0; i < BY; i++) {
    for (int j = 0; j < BX; j++) {
      board[i][j].c = '+';
      board[i][j].stone = NULL;
    }
  }

  char ch = '\0';
  int maxy, maxx = 0;
  getmaxyx(win, maxy, maxx);
  int bposy = ((BY / 2));
  int bposx = ((BX / 2));
  int cursy = maxy / 2, cursx = maxx / 2;
//  getyx(win, cursy, cursx);


  //game loop
  do {
    //input
    if (errno) {
      fprintf(stderr, "error getch%d\n", errno);
      return errno;
    }
    // move cursor
    if (ch == 'h' && bposx > 0) {
      cursx--;
      bposx--;
//      wmove(win, cursy, cursx-1);
    }
    else if (ch == 'j' && bposy < 8) {
 //     wmove(win, cursy+1, cursx);
      cursy++;
      bposy++;
    }
    else if (ch == 'k' && bposy > 0) {
  //    wmove(win, cursy-1, cursx);
      cursy--;
      bposy--;
    }
    else if (ch == 'l' && bposx < 8) {
   //   wmove(win, cursy, cursx+1);
      cursx++;
      bposx++;
    }
    // place piece
    else if (ch == 'f') {
      if ((turn % 2 == 0) && board[bposy][bposx].stone == NULL) {

        Stone* stone = makeStone('O', (Vec2i){cursy, cursx});
        placeStone(&board[bposy][bposx], stone, win);
        turn++;

        // check if in atari
        if (getLiberties(board, stone, win) == 4) {
        }
      }
      else if ((turn % 2 == 1) && board[bposy][bposx].stone == NULL) {
        Stone* stone = makeStone('@', (Vec2i){cursy, cursx});
        placeStone(&board[bposy][bposx], stone, win);
        turn--;
      }
    }
    else if (ch == 'r') {
      removeStone(win, board, bposy, bposx);
    }
    if (errno) {
      fprintf(stderr, "error move%d\n", errno);
      return errno;
    }

    //update stuff
    //render
    clear();
    // debug
    mvwprintw(win, 0, 0, "curs: %d, %d", cursy, cursx);
    mvwprintw(win, 1, 0, "bpos: %d, %d", bposy, bposx);
    mvwprintw(win, 2, 0, "turn: %c", turn ? 'w' : 'b');
    mvwprintw(win, 3, 0, "stone?: %c", (board[bposy][bposx].stone != NULL) ? 'y' : 'n');
    //make board
    for (int i = 0; i < BY; i++) {
      for (int j = 0; j < BX; j++) {
//        mvwprintw(win, ((maxy / 2) - (BY - 2) - 1 + (2 * i)), ((maxx / 2) - (BX - 2) - 1 + (2 * j)), "%c", '-');
        mvwprintw(win, ((maxy / 2) - (BY / 2)) + i, ((maxx / 2) - (BX / 2)) + j, "%c", _board[i][j].c);
      }
    }
    for (int i = 0; i < BY; i++) {
      for (int j = 0; j < BX; j++) {
        mvwprintw(win, ((maxy / 2) - (BY / 2)) + i, ((maxx / 2) - (BX / 2)) + j, "%c", board[i][j].c);
      }
    }
    wmove(win, cursy, cursx);

    /*
    // make lip around board
    wmove(win, ((maxy / 2) - (BY / 2) - 1), ((maxx / 2) - (BX / 2) - 1));
    for (int i = 0; i < BX+2 ; i++) {
      waddch(win, '-');
      getyx(win, cursy, cursx);
    }
    for (int i = 0; i < BY+1; i++) {
      mvwaddch(win, cursy+1, cursx-1, '|');
      getyx(win, cursy, cursx);
    }
    for (int i = 0; i < BX+1; i++) {
      mvwaddch(win, cursy, cursx-2, '-');
      getyx(win, cursy, cursx);
    }
    for (int i = 0; i < BY+1; i++) {
      mvwaddch(win, cursy-1, cursx-1, '|');
      getyx(win, cursy, cursx);
    }
    */

    errno = wrefresh(win);
    if (errno) {
      fprintf(stderr, "error refreshing%d\n", errno);
    }
  } while ((ch = wgetch(win)) != 'q');

  // outside game loop

  //remove all stones
  removeStones(win, board);

  endwin();
  return 0;
}
