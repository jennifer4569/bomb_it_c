#include "bomb_it.h"
struct map* update_map(struct map *m){
  int i=0;
  
  while(i < m->num_players){
    if(m->players[i]){
      m->players[i]=go(m->players[i], m, -1);
    }
    i++;
  }
  i=0;
  while(i < m-> num_bombs){
    if(m->bombs[i]){
      m->bombs[i]=tick_bomb(m->bombs[i], m);
    }
    i++;
  }

  if(rand()%25 == 0){
    int rand_row = rand()%ROW;
    int rand_col = rand()%COL;

    while(m->grid[rand_row][rand_col]!=SAFE){
      rand_row= rand()%ROW;
      rand_col=rand()%COL;
    }
    m->grid[rand_row][rand_col] = rand() % 3 + POWERUP_ADD_BMB;
    
  }
  
  return m;

}

void print_map(int curr, int colorize, int time, int player_num){
  int format=0;//default
  int foreground=232; //white
  //int background=40; //black
  int background=100;
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
    if(player_num==0){
      foreground=33;
    }
    if(player_num==1){
      foreground=32;
    }
    if(player_num==2){
      foreground=34;
    }
    if(player_num==3){
      foreground=35;
    }
    format = 1;
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
    printw("%c", c);
  }
  else{
    printw("\033[%d;%d;%dm%c", format, foreground, background, c);
  }
}
void display_map(struct map * m, int time){
  //printw("%s", CLEAR_SCREEN); //clears screen
  clear();
  int i = 0;
  int j = 0;
  while(i < ROW){
    j = 0;
    while(j < COL){
      if(m->grid[i][j]==PLAYER){
	int k = 0;
	while(k < 4){
	  if(m->players[k]){
	    if(m->players[k]->location[0]==i && m->players[k]->location[1]==j){
	    print_map(m->grid[i][j], -1, time, k);
	    }
	  }
	  k++;
	}
      }
      else{
	print_map(m->grid[i][j], -1, time, -1);
      }
      j++;
    }
    i++;
    printw("\n");
    //printw("\033[0;%d;%dm\n", 39, 40); //makes new line and clear screen not make the entire screen white
  }
}

void display_stats(struct player*p){
  printf("\n\n");
  if(p){
    printw("\033[0;92mPlayer's num bombs:  \t%d\n", p->num_bombs);
    printw("\033[0;95mPlayer's bomb power: \t%d\n\n", p->bomb_power);
    if(p->has_gloves == -1){
      printw("\033[0;96mPlayer \033[4;96mdoesn't\033[0;96m have gloves\n");
    }
    else{
      printw("\033[0;96mPlayer \033[4;96mdoes\033[0;96m    have gloves\n");
    }
  }
  else{
    printw("\033[0;91mYOU HAVE DIED!\n");
  }
}
