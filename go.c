#include <ncurses.h>
#include <errno.h>

int main(int argv, char** argc) {

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

  wmove(win, (maxy / 2) - 5, (maxx / 2) - 10);
  for (int i = 0; i < 20; i++) {
    waddch(win, '-');
    getyx(win, cursy, cursx);
  }
  for (int i = 0; i < 10; i++) {
    mvwaddch(win, cursy+1, cursx-1, '|');
    getyx(win, cursy, cursx);
  }
  for (int i = 0; i < 20; i++) {
    mvwaddch(win, cursy, cursx-2, '-');
    getyx(win, cursy, cursx);
  }
  for (int i = 0; i < 10; i++) {
    mvwaddch(win, cursy-1, cursx-1, '|');
    getyx(win, cursy, cursx);
  }

  //window while not escape pressed
  while (ch != 27) {



    ch = wgetch(win);
    getyx(win, cursy, cursx);
    if (errno) {
      fprintf(stderr, "error getch%d\n", errno);
      return errno;
    }
    

    wmove(win, maxy, maxx);

    //delete
/*    if (ch == 7) {
      if (cursx == 0 && cursy == 0) {
        continue;
      }
      else if (cursx == 0 && cursy != 0) {
        errno = wmove(win, cursy-1, cursx);
        getyx(win, cursy, cursx);
        if (errno) {
          fprintf(stderr, "error move%d\n", errno);
          return errno;
        }
        continue;
      }
      else {
        errno = mvwdelch(win, cursy-0, cursx-1);
        continue;
      }
    }
*/



    if (errno) {
      fprintf(stderr, "error move%d\n", errno);
      return errno;
    }
    else {
 //     waddch(win, ch);
    }

    errno = wrefresh(win);
  }
  if (errno)
    fprintf(stderr, "error refreshing%d\n", errno);
  endwin();
  return 0;
}
