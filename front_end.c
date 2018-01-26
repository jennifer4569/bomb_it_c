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

void display_map(struct map * m, int time){
  clear();
  //prints the grid one by one
  int i = 0;
  int j = 0;
  while(i < ROW){
    j = 0;
    while(j < COL){
      char curr = m->grid[i][j];
      char c;
      if(curr == SAFE){
	c = ' ';
      }
      if(curr==UNSAFE){
	c='-';
      }
      if(curr==DESTRUCT){
	c='=';
      }
      if(curr == INDESTRUCT){
	c = '#';
      }
      if(curr == PLAYER){
	c = 'P';
      }
      if(curr==BOMB){
	//alternates between the two characters
	if(time%2){
	  c='O';
	}
	else{
	  c='o';
	}
      }
      if(curr==POWERUP_ADD_BMB){
	c='+';
      }
      if(curr==POWERUP_BMB_PWR){
	c='*';
      }
      if(curr==POWERUP_ADD_GLV){
	c='m';
      }
      printw("%c", c);
      j++;
    }
    i++;
    printw("\n");
  }
}

void display_stats(struct player*p){
  printw("\n\n");
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


//pos is a char array with size ROW * (COL + 1) + 1
void mapDisplay(char* pos, struct map * m, int time){
  int r = 0;
  while(r < ROW){
    int c = 0;
    while(c < COL){
      char curr = m->grid[i][j];
      char sym;
      if(curr == SAFE){sym = ' ';}
      else if(curr==UNSAFE){sym ='-';}
      else if(curr==DESTRUCT){sym ='=';}
      else if(curr == INDESTRUCT){sym = '#';}
      else if(curr == PLAYER){sym = 'P';}
      else if(curr==BOMB){
	//alternates between the two characters
	if(time%2){sym ='O';}
	else{sym ='o';}
      }
      else if(curr==POWERUP_ADD_BMB){sym ='+';}
      else if(curr==POWERUP_BMB_PWR){sym ='*';}
      else if(curr==POWERUP_ADD_GLV){sym='m';}
      *pos = c;
      c ++;
      pos ++;
    }
    r ++;
    *pos = '\n';
    pos ++;
  }
  pos = '\0';
}
