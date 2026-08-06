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

  wmove(win, ((maxy / 2) - BY / 2), (maxx / 2) - (BX / 2));
  for (int i = 0; i < BY; i++) {
    wmove(win, ((maxy / 2) - (BY / 2) + i), ((maxx / 2) - (BX / 2)));
    for (int j = 0; j < BX; j++) {
      waddch(win, board[i][j].c);
    }
  }

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


  //center cursor
  wmove(win, maxy / 2, maxx / 2);

  //game loop
  while (ch != 'q') {
    ch = wgetch(win);
    getyx(win, cursy, cursx);
    if (errno) {
      fprintf(stderr, "error getch%d\n", errno);
      return errno;
    }



    if (ch == 'h') {
      wmove(win, cursy, cursx-1);
    }
    else if (ch == 'j') {
      wmove(win, cursy+1, cursx);
    }
    else if (ch == 'k') {
      wmove(win, cursy-1, cursx);
    }
    else if (ch == 'l') {
      wmove(win, cursy, cursx+1);
    }





    else if (ch == 'f') {
      if (turn.black == 0) {
       mvwaddch(win, cursy, cursx, 'O');
       wmove(win, cursy, cursx);
        turn.black = 1;
      }
      else {
       mvwaddch(win, cursy, cursx, '@');
       wmove(win, cursy, cursx);
        turn.black = 0;
      }
    }

    if (errno) {
      fprintf(stderr, "error move%d\n", errno);
      return errno;
    }

    errno = wrefresh(win);
  }
  if (errno)
    fprintf(stderr, "error refreshing%d\n", errno);
  endwin();
  return 0;
}
