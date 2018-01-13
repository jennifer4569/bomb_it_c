#include "bomb_it.h"

struct player* create_player(int is_cpu, int x, int y){
  struct player* p = (struct player *)malloc(sizeof(p));
  p->num_bombs=1;
  p->shield=0;
  p->bomb_power=1;
  p->has_gloves=0;
  p->location[0]=x;
  p->location[1]=y;
  //p->is_alive=1;
  return p;
}

struct player * go(struct player* p, struct map * m, int move){
  int *prev_loca=p->location;
  int *new_loca = try_move(p->location, RIGHT);
  int new_key=m->grid[new_loca[0]][new_loca[1]];
  if(new_key==SAFE){
    m->grid[prev_loca[0]][prev_loca[1]]=SAFE;
    p->location[0]=new_loca[0];
    p->location[1]=new_loca[1];
    m->grid[new_loca[0]][new_loca[1]]=PLAYER;
  }/*
  if(new_key==UNSAFE){
    m->grid[prev_loca[0]][prev_loca[1]]=SAFE;
    p->is_alive=-1;
    }*/
  free(new_loca);
  return p;
}

int * try_move(int * location, int move){
  int* new_loca = (int*)malloc(sizeof(new_loca));
  new_loca[0]=location[0];
  new_loca[1]=location[1];
  if(move==UP){
    new_loca[0]+=-1;
    new_loca[1]+=0;
  }
  if(move==RIGHT){
    new_loca[0]+=0;
    new_loca[1]+=1;
  }
  if(move==DOWN){
    new_loca[0]+=1;
    new_loca[1]+=0;
  }
  if(move==LEFT){
    new_loca[0]+=0;
    new_loca[1]+=-1;
  }
  return new_loca;
}
