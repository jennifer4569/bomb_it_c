#include "bomb_it.h"

//init_game() initializes the game
//malloc struct map
//load in map
//return map
struct map * init_game(){
  struct map* m = malloc(sizeof(*m));
  int i = 0;
  int j = 0;
  while(i < ROW){
    j = 0;
    while(j < COL){
      if(i == 0 || i == ROW-1 || j == 0 || j == COL-1){
	m->grid[i][j] = INDESTRUCT;
      }
      else{
	m->grid[i][j] = SAFE;
      }
      j++;
    }
    i++;
  }
  m->grid[2][18] = PLAYER;
  

  struct player* p1 = malloc(sizeof(*p1));
  p1->location[0]=2;
  p1->location[1]=18;

  m->players[0] = *p1;

  return m;
  
}


void main(){
  struct map* m = init_game();
  int i = 0;
  while(1){  
    m = update_map(m);
    display_map(m);
    sleep(1.5);
  }
}
