#include "bomb_it.h"

struct player* create_player(int is_cpu, int x, int y){
  struct player* p = (struct player *)malloc(sizeof(p)*50);
  p->num_bombs=1;
  p->bomb_power=1;
  p->has_gloves=-1;
  p->location[0]=x;
  p->location[1]=y;

  p->is_cpu=is_cpu;
  return p;
}

struct bomb* drop_bomb(int x, int y, int power, struct player* p){
  struct bomb* b = (struct bomb*)malloc(sizeof(b));
  b->location[0] = x;
  b->location[1]=y;
  b->power=power;
  b->timer=8;
  b->p=p;
  return b;
}

struct bomb* tick_bomb(struct bomb* b, struct map*m){
  b->timer--;
  int bmb_code; //what the surrounding characters will be replaced with

  //explodes when timer == 0
  if(b->timer==0){
    bmb_code=UNSAFE;
    b->p->num_bombs++;
  }
  //reverts the surroundings back to normal when timer == -1
  if(b->timer==-1){
    bmb_code=SAFE;
  }
  
  //explode the bomb
  if(b->timer==0||b->timer==-1){
    //if the bomb is exploding and there's a player at the original location, then it dies
    if(bmb_code == UNSAFE){ 
      int k = 0;
      while(k < m->num_players){
	if(m->players[k]){
	  if(m->players[k]->location[0]==b->location[0]&&m->players[k]->location[1]==b->location[1]){
	    m->players[k]=NULL;
	    free(m->players[k]);
	  }
	}
	k++;
      }
    }
    //sets the bomb's original location to bmb_code
    m->grid[b->location[0]][b->location[1]]=bmb_code;
    
    //loops around in each direction
    int i=1;
    int j=0;
    while(j<4){
      i=1;
      int check=b->power; //how far in the current direction it will go

      //makes the explosion look more like a square
      if(j==UP||j==DOWN){
	check=check/2;
      }

      //keeps going in that direction until it's gone check spaces
      while(i <= check){
	int * temp= try_move(b->location, j, i);
	int curr_code=m->grid[temp[0]][temp[1]];
	//checks if the current space is indestructible: if that's the case, break the loop
    	if(curr_code==INDESTRUCT){
	  i = check + 100;
	}
	//if the current space has a player, then it kills the player
	if(curr_code==PLAYER && bmb_code == UNSAFE){
	  int k = 0;
	  while(k < m->num_players){
	    if(m->players[k]){
	      if(m->players[k]->location[0]==temp[0]&&m->players[k]->location[1]==temp[1]){
		m->grid[temp[0]][temp[1]] = UNSAFE;
		m->players[k]=NULL;
		free(m->players[k]);
	      }
	    }
	    k++;
	  }
	}
	//updates the grid to bmb_code
	if(i != check + 100){
	  m->grid[temp[0]][temp[1]]=bmb_code;
	}
	free(temp);
    	i++;
      }
      j++;
    }
  }
  return b;
}


struct player * go(struct player* p, struct map * m, int move){
  //if the player is a cpu, the move is received from its own judgement
  if(p->is_cpu!=-1){
    move = find_best_move(p, m);
  }
  //if the player is a human and there is a move, do nothing
  if(p->is_cpu==-1 && move == -1){
    return p;
  }
  
  int *prev_loca=p->location;
  int *new_loca = try_move(p->location, move, 1);
  int new_key=m->grid[new_loca[0]][new_loca[1]];
  int can_move=-1;

  //if the new space is safe, then you can move
  if(new_key==SAFE){
    can_move=1;
  }
  //if the new space is a destructible obstacle or is a player
  if(new_key==DESTRUCT||new_key==PLAYER){
    //if the player is a cpu and it has bombs left, drop a bomb
    if(p->is_cpu!=-1 && p->num_bombs!=0){
      m->bombs[m->num_bombs]=drop_bomb(prev_loca[0], prev_loca[1], p->bomb_power, p);
      p->num_bombs--;
      m->grid[prev_loca[0]][prev_loca[1]]=BOMB;
      m->num_bombs++;
    }
  }
  //if the new space is a powerup, then add to the player's stats
  if(new_key==POWERUP_ADD_BMB){
    p->num_bombs++;
    can_move=1;
  }
  if(new_key==POWERUP_BMB_PWR){
    p->bomb_power++;
    can_move=1;
  }
  if(new_key==POWERUP_ADD_GLV){
    p->has_gloves=1;
    can_move=1;
  }
  //if the new space is unsafe, then the player dies
  if(new_key==UNSAFE){
    m->grid[prev_loca[0]][prev_loca[1]]=SAFE;
    p=NULL;
    free(p);
  }
  //if the player can move and the player is still alive, then move the player
  if(can_move==1 && p){
    //if the previous location wasn't a bomb, then set the previous location to a safe space
    if(m->grid[prev_loca[0]][prev_loca[1]]!=BOMB){
      m->grid[prev_loca[0]][prev_loca[1]]=SAFE;
    }
    p->location[0]=new_loca[0];
    p->location[1]=new_loca[1];
    m->grid[new_loca[0]][new_loca[1]]=PLAYER;
  }
  free(new_loca);
  return p;
}

int find_best_move(struct player* p, struct map* m){

  int highest_priority = 10; //ranked so that the highest priority is 1
  int num_highest_priority = 0; //number of spaces with the priority as the highest priority
  int priority[4]; //the priority of each direction

  //checks each direction to see which one has the highest priority
  int direction=0;
  while(direction<4){
    int* temp=try_move(p->location, direction, 1);
    int curr_code=m->grid[temp[0]][temp[1]];
    int curr_priority;

    //order of priority:
    //1. powerup
    //2. player, destruct, safe
    //3. indestruct
    //4. bomb
    //5. unsafe 
    if(curr_code==POWERUP_ADD_BMB||curr_code==POWERUP_BMB_PWR||curr_code==POWERUP_ADD_GLV){
      curr_priority=1;
    }
    if(curr_code==PLAYER||DESTRUCT||SAFE){
      curr_priority=2;
    }
    if(curr_code==INDESTRUCT){
      curr_priority=3;
    }
    if(curr_code==BOMB){
      curr_priority=4;
    }
    if(curr_code==UNSAFE){
      curr_priority=5;
    }
    priority[direction]=curr_priority;

    //if the current priority is the same as the highest priority, then increment num_highest_priority by 1
    if(highest_priority == curr_priority){
      num_highest_priority++;
    }
    //if the current priority is higher than the previous highest priority, change the highest priority to the current one
    if(highest_priority > curr_priority){
      highest_priority=curr_priority;
      num_highest_priority = 1;
    }
    direction++;
  }

  //loops through the priorities to make sure that each direction has an equal chance of being picked
  int rand_num = rand() % num_highest_priority;
  direction = 0;
  while(direction < 4){
    if(priority[direction] == highest_priority){
      if(rand_num == 0){
	return direction;
      }
      rand_num--;
    }
    direction++;
  }
}

int * try_move(int * location, int move, int move_pwr){
  int* new_loca = (int*)malloc(sizeof(new_loca));
  new_loca[0]=location[0];
  new_loca[1]=location[1];
  if(move==UP){
    new_loca[0]+=-move_pwr;
    new_loca[1]+=0;
  }
  if(move==RIGHT){
    new_loca[0]+=0;
    new_loca[1]+=move_pwr;
  }
  if(move==DOWN){
    new_loca[0]+=move_pwr;
    new_loca[1]+=0;
  }
  if(move==LEFT){
    new_loca[0]+=0;
    new_loca[1]+=-move_pwr;
  }
  return new_loca;
}
