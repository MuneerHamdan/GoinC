#include <ncurses.h>

int main(int argv, char** argc) {
  WINDOW* window = initscr();
  endwin();
  return 0;
}
