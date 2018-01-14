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
    //if(m->players[i]->is_alive != -1){
      go(m->players[i], m, -1);
      //}
    i++;
  }	      
  return m;

};

void print_map(int curr, int colorize, int time){
  int format=0;//default
  int foreground=232; //white
  int background=40; //black
  char c;
  if(curr == SAFE){
    c = ' ';
  }
  if(curr==UNSAFE){
    background=41; //red
    c=' ';
  }
  if(curr==DESTRUCT){
    c='#';
  }
  if(curr == INDESTRUCT){
    foreground = 37; //white
    background = 47; //white
    c = '#';
  }
  if(curr == PLAYER){
    foreground = 33; //yellow
    c = 'P';
  }
  if(curr==BOMB){
    foreground=91; //red
    //alternates
    if(time%2){
      c='O';
    }
    else{
      c='o';
    }
  }
  if(curr==POWERUP_ADD_BMB){
    foreground=92;
    if(time%2){
      format=4;
    }
    c='+';
  }
  if(curr==POWERUP_BMB_PWR){
    foreground=95;
    if(time%2){
      format=4;
    }
    c='*';
  }
  if(curr==POWERUP_ADD_GLV){
    foreground=96;
    if(time%2){
      format=4;
    }
    c='m';
  }


  if(colorize == -1){
    printf("%c", c);
  }
  else{
    printf("\033[%d;%d;%dm%c", format, foreground, background, c);
  }
}
void display_map(struct map * m, int time){
  printf("%s", CLEAR_SCREEN); //clears screen
  int i = 0;
  int j = 0;
  while(i < ROW){
    j = 0;
    while(j < COL){
      print_map(m->grid[i][j], 1, time);
      j++;
    }
    i++;
    printf("\033[0;%d;%dm\n", 39, 40); //makes new line and clear screen not make the entire screen white
  }
  printf("\n\n");
  printf("\033[0;92mPlayer's num bombs:  \t%d\n", m->players[0]->num_bombs);
  printf("\033[0;95mPlayer's bomb power: \t%d\n\n", m->players[0]->bomb_power);
  if(m->players[0]->has_gloves == -1){
    printf("\033[0;96mPlayer \033[4;96mdoesn't\033[0;96m have gloves\n");
  }
  else{
    printf("\033[0;96mPlayer \033[4;96mdoes\033[0;96m    have gloves\n");
  }
}
