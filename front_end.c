#include "bomb_it.h"
struct map* update_map(struct map *m){
  /*int prev_loca[2];
  prev_loca[0] = m->players[0].location[0];
  prev_loca[1] = m->players[0].location[1];
  m->grid[prev_loca[0]][prev_loca[1]] = INDESTRUCT;
    
  int new_loca[2];
  new_loca[0] = prev_loca[0]+1;
  new_loca[1] = prev_loca[1];

  if(new_loca[0] == ROW){
    new_loca[0]--;
  }
  
  m->grid[new_loca[0]][new_loca[1]] = PLAYER;
  m->players[0].location[0] = new_loca[0];
  m->players[0].location[1] = new_loca[1];
  */
  int i=0;
  while(i < m->num_players){
    move(m->players[i], m, -1);
    i++;
  }	      
  return m;

};

void print_map(int curr, int colorize){
  int foreground, background;
  char c;
  if(curr == SAFE){
    foreground = 35;
    background = 40;
    c = ' ';
  }
  if(curr == INDESTRUCT){
    foreground = 37;
    background = 47;
    c = '#';
  }
  if(curr == PLAYER){
    foreground = 33;
    background = 40;
    c = 'P';
  }

  if(colorize == -1){
    printf("%c", c);
  }
  else{
    printf("\033[0;%d;%dm%c", foreground, background, c);
  }
}
void display_map(struct map * m){
  printf("%s", CLEAR_SCREEN); //clears screen
  int i = 0;
  int j = 0;
  while(i < ROW){
    j = 0;
    while(j < COL){
      print_map(m->grid[i][j], 1);
      j++;
    }
    i++;
    printf("\n");
  }
}
