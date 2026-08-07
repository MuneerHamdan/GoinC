#include <ncurses.h>
#include <errno.h>

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

typedef struct {
  char black;
} Turn;

typedef struct {
  char c;
} Board;


int main(int argv, char** argc) {

  // change turns
  Turn turn;
  turn.black = 0;

  // initialize board
  Board _board[BY][BX];
  for (int i = 0; i < BY; i++) {
    for (int j = 0; j < BX; j++) {
      _board[i][j].c = '+';
    }
  }

  Board board[BY][BX];
  for (int i = 0; i < BY; i++) {
    for (int j = 0; j < BX; j++) {
      board[i][j].c = '+';
    }
  }

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

  char ch = 0;
  int cursy, cursx = 0;
  int maxy, maxx = 0;
  getmaxyx(win, maxy, maxx);
  int bposy = ((BY / 2) + 1);
  int bposx = ((BX / 2) + 1);


  wmove(win, ((maxy / 2) - BY / 2), (maxx / 2) - (BX / 2));
  for (int i = 0; i < BY; i++) {
    wmove(win, ((maxy / 2) - (BY / 2) + i), ((maxx / 2) - (BX / 2)));
    for (int j = 0; j < BX; j++) {
      waddch(win, board[i][j].c);
    }
  }

  // make lip around board
  wmove(win, ((maxy / 2) - (BY / 2) - 1), ((maxx / 2) - (BX / 2) - 1));
  printf("y:%d, x:%d\n", bposy, bposx);
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


  //center cursor
  wmove(win, maxy / 2, maxx / 2);

  //game loop
  while (ch != 'q') {
//  wmove(win, maxy / 2, maxx / 2);

    // get char
    ch = wgetch(win);
    // get y x of cursor
    getyx(win, cursy, cursx);
    if (errno) {
      fprintf(stderr, "error getch%d\n", errno);
      return errno;
    }
    mvwaddch(win, 1, 1, bposx);


    // move cursor
    if (ch == 'h' && bposx > 1) {
      wmove(win, cursy, cursx-1);
      bposx--;
    }
    else if (ch == 'j' && bposy < 9) {
      wmove(win, cursy+1, cursx);
      bposy++;
    }
    else if (ch == 'k' && bposy > 1) {
      wmove(win, cursy-1, cursx);
      bposy--;
    }
    else if (ch == 'l' && bposx < 9) {
      wmove(win, cursy, cursx+1);
      bposx++;
    }
    if (errno) {
      fprintf(stderr, "error move%d\n", errno);
      return errno;
    }

    // place piece
    if (ch == 'f') {
      if (turn.black == 0 && board[bposy][bposy].c != '@') { // maybe change later, as it literally means "if black is not place black."
        board[bposy][bposx].c = 'O';
        wmove(win, cursy, cursx);
        mvwaddch(win, cursy, cursx, board[bposy][bposx].c);
        wmove(win, cursy, cursx);
        turn.black = 1;
      }
      else if (turn.black == 1 && board[bposy][bposy].c != '@') {
        board[bposy][bposx].c = '@';
        wmove(win, bposy, bposx);
        mvwaddch(win, cursy, cursx, board[bposy][bposx].c);
        wmove(win, cursy, cursx);
        turn.black = 0;
      }
    }

//    printf(",%d %d ", bposy, bposx);
 //   getyx(win, bposy, bposx);
  //  printf(",%d %d ", bposy, bposx);
//    mvwaddch(win, cursy, cursx, board[bposy][bposx].c);
    //printf(",%d %d ", bposy, bposx);


    errno = wrefresh(win);
    if (errno)
      fprintf(stderr, "error refreshing%d\n", errno);
  }

  // outside game loop
  endwin();
  return 0;
}
