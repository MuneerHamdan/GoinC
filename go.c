#include <ncurses.h>
#include <errno.h>

int main(int argv, char** argc) {
  WINDOW* win;/* = initscr();*/
  errno = leaveok(win, false);
  errno = wrefresh(win);
//  if (r == -1)
  if (errno)
    fprintf(stderr, "error refreshing%d\n", errno);
  endwin();
  return 0;
}
