#include "bomb_it.h"

struct map* update_map(struct map *m){
  int i=0;

  //updates the players
  while(i < m->num_players){
    //if the current player is still alive
    if(m->players[i]){

      struct player * curr = m->players[i];
      //for keyboard interception
      int direction = -1;
      int key = getch();
      //movement
      if(key == 'w' || key == 'W'){
      	direction = UP;
      }
      if(key == 'd' || key == 'D'){
      	direction = RIGHT;
      }
      if(key == 's' || key == 'S'){
      	direction = DOWN;
      }
      if(key == 'a' || key == 'A'){
      	direction = LEFT;
      }
      //drops a bomb if the player is a human and has available bombs
      if(key==' ' && m->players[i]->is_cpu == -1 && m->players[i]->num_bombs!=0){
	
	m->bombs[m->num_bombs]=drop_bomb(curr->location[0], curr->location[1], curr->bomb_power, curr); //creates the bomb
	m->players[i]->num_bombs--; //the player has 1 less available bomb
	m->grid[curr->location[0]][curr->location[1]]=BOMB; //the player's location now is a bomb
	m->num_bombs++; //the map has 1 more bomb
      }

      //the player goes
      curr=go(curr, m, direction);
    }
    i++;
  }
  
  //updates the bombs
  i=0;
  while(i < m-> num_bombs){
    //if the bomb didn't explode yet
    if(m->bombs[i]){
      m->bombs[i]=tick_bomb(m->bombs[i], m);
    }
    i++;
  }

  //4% chance of dropping a powerup in a random location
  if(rand()%25 == 0){
    int rand_row = rand()%ROW;
    int rand_col = rand()%COL;

    //randomly picks a row and col until the space is safe
    while(m->grid[rand_row][rand_col]!=SAFE){
      rand_row= rand()%ROW;
      rand_col=rand()%COL;
    }

    //drops one of the 3 powerups randomly
    m->grid[rand_row][rand_col] = rand() % 3 + POWERUP_ADD_BMB;
  }

  return m;
}

void print_map(int curr, int colorize, int time, int player_num){
  int format=0;//default
  int foreground=232; //white
  int background=100; //gray
  char c;
  if(curr == SAFE){
    c = ' ';
  }
  if(curr==UNSAFE){
    background=41; //red
    c='-';
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
    //alternates between the two characters
    if(time%2){
      c='O';
    }
    else{
      c='o';
    }
  }
  if(curr==POWERUP_ADD_BMB){
    foreground=92;
    //alternates between underlined and not
    if(time%2){
      format=4;
    }
    c='+';
  }
  if(curr==POWERUP_BMB_PWR){
    foreground=95;
    //alternates between underlined and not
    if(time%2){
      format=4;
    }
    c='*';
  }
  if(curr==POWERUP_ADD_GLV){
    foreground=96;
    //alternates between underlined and not
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
  clear();
  //prints the grid one by one
  int i = 0;
  int j = 0;
  while(i < ROW){
    j = 0;
    while(j < COL){
      //if the space has a player on it, then print the player in its respective color
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
  }
}

void display_stats(struct player*p, int colorize){
  if(colorize == -1){
    printf("\n\n");
    if(p){
      printw("Player's num bombs:  \t%d\n", p->num_bombs);
      printw("Player's bomb power: \t%d\n\n", p->bomb_power);
      if(p->has_gloves == -1){
	printw("Player doesn't have gloves\n");
      }
      else{
	printw("Player does    have gloves\n");
      }
    }
    else{
      printw("YOU HAVE DIED!\n");
    }
  }
  else{
    printw("\n\n");
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
}
