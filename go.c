#include <ncurses.h>
#include <errno.h>

int main(int argv, char** argc) {

  WINDOW* win = initscr();
  errno = noecho();
  if (errno)
    fprintf(stderr, "error noecho%d\n", errno);
  keypad(win, TRUE);

  char ch = 0;
  int cursy, cursx = 0;
  while (ch != 27) {
    ch = wgetch(win);
    getyx(win, cursy, cursx);
    if (errno)
      fprintf(stderr, "error getch%d\n", errno);
    printf("%d ", ch);

    if (ch == 7) {
      printf("hello");
      errno = mvwdelch(win, cursy-0, cursx-1);
      if (errno)
        fprintf(stderr, "error move%d\n", errno);
    }
    else {
      waddch(win, ch);
    }
    errno = wrefresh(win);
  }
  if (errno)
    fprintf(stderr, "error refreshing%d\n", errno);
  endwin();
  return 0;
}
