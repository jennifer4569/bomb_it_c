#include "bomb_it.h"

struct player* create_player(int is_cpu, int x, int y){
  struct player* p = (struct player *)malloc(sizeof(p));
  p->num_bombs=1;
  p->shield=0;
  p->bomb_power=1;
  p->has_gloves=0;
  p->location[0]=x;
  p->location[1]=y;
  return p;
}

struct player * move(struct player * p, struct map * m, int move){
  int prev_x=p->location[0];
  int prev_y=p->location[1];
  m->grid[prev_x][prev_y]=INDESTRUCT;
  //SEE UPDATE MAP
  
}
