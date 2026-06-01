#include <ncurses.h>
#include <errno.h>

int main(int argv, char** argc) {
  WINDOW* win = initscr();
  //  errno = leaveok(win, false);
  //  if (r == -1)


  char ch = 0;
  while (ch != 27) {
    ch = wgetch(win);
    waddch(win, ch);
    errno = wrefresh(win);
  }



  //  if (errno)
  //   fprintf(stderr, "error refreshing%d\n", errno);
  endwin();
  return 0;
}
