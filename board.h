#ifndef BOARD_H
#define BOARD_H

typedef struct {
  char c;
  vec2i pos;
  int liberties;
} Stone;

typedef struct {
  char c;
  Stone stone;
} Tile;


Stone createStone(char c, int y, int x);
int addStone(Stone* stone);

#endif
