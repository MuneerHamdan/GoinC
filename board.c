#include "main.h"
#include "board.h"

Stone createStone(char c, int y, int x) {
  Stone stone = {c, {y, x}};
  return stone;
}
int addStone(Stone* stone);
