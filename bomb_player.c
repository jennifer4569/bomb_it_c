#include "bomb_it.h"

struct player* create_player(int is_cpu, int x, int y){
  struct player* p = (struct player *)malloc(sizeof(p)*50);
  p->num_bombs=1;
  p->shield=0;
  p->bomb_power=1;
  p->has_gloves=-1;
  p->location[0]=x;
  p->location[1]=y;

  p->is_cpu=is_cpu;
  return p;
}

struct bomb* drop_bomb(int x, int y, int power){
  struct bomb* b;
  b = (struct bomb*)malloc(sizeof(b));
  b->location[0] = x;
  b->location[1]=y;
  b->power=power;
  b->timer=8;
  return b;
}
struct bomb* tick_bomb(struct bomb* b, struct map*m){
  b->timer--;
  int bmb_code;
  if(b->timer==0){
    bmb_code=UNSAFE;
  }
  if(b->timer==-1){
    bmb_code=SAFE;
  }
  if(b->timer==0||b->timer==-1){
    //explode the bomb
    m->grid[b->location[0]][b->location[1]]=bmb_code;
    int i=1;
    int j=0;
    while(j<4){
      i=1;
      int check=b->power;

      //makes it look more like a square
      if(j==UP||j==DOWN){
	check=check/2;
      }
      while(i <= check){
	int * temp= try_move(b->location, j, i);
	int curr_code=m->grid[temp[0]][temp[1]];
    	if(curr_code==INDESTRUCT){
	  //free(temp);
	  break;

	}
	if(curr_code==PLAYER){
	  int k = 0;
	  while(k < m->num_players){
	    if(m->players[k]){
	      if(m->players[k]->location[0]==temp[0]&&m->players[k]->location[1]==temp[1]){
		m->players[k]=NULL;
		free(m->players[k]);
		//free(temp);
		break;
	      }
	    }
	    k++;
	  }
	}/*
	if(curr_code==DESTRUCT){
	  int rand_num = rand() % 10;
	  if(rand_num==0){
	    bmb_code=POWERUP_ADD_BMB;
	  }
	  if(rand_num==1){
	    bmb_code=POWERUP_BMB_PWR;
	  }
	  if(rand_num==2){
	    bmb_code=POWERUP_ADD_GLV;
	  }
	  m->grid[temp[0]][temp[1]]=bmb_code;
	  break;
	}
	if(curr_code==POWERUP_ADD_BMB||curr_code==POWERUP_BMB_PWR||curr_code==POWERUP_ADD_GLV){
	  bmb_code=curr_code;
	  }*/
	m->grid[temp[0]][temp[1]]=bmb_code;
	
	free(temp);
    	i++;
      }
      j++;
    }
  }
  return b;
}


struct player * go(struct player* p, struct map * m, int move){
  if(p->is_cpu == -1){
    
  }
  else{
    int move = find_best_move(p, m);
    
    int *prev_loca=p->location;
    int *new_loca = try_move(p->location, move, 1);
    int new_key=m->grid[new_loca[0]][new_loca[1]];
    int can_move=-1;
    if(new_key==SAFE){
      can_move=1;
    }
    if(new_key==INDESTRUCT||new_key==PLAYER){
      m->bombs[m->num_bombs]=drop_bomb(prev_loca[0], prev_loca[1], p->bomb_power);
      m->num_bombs++;
    }
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
    if(can_move==1){
      m->grid[prev_loca[0]][prev_loca[1]]=SAFE;
      p->location[0]=new_loca[0];
      p->location[1]=new_loca[1];
      m->grid[new_loca[0]][new_loca[1]]=PLAYER;
    }
    if(new_key==UNSAFE){
      m->grid[prev_loca[0]][prev_loca[1]]=SAFE;
      p=NULL;
      free(p);
    }
    free(new_loca);
  }
  return p;
}

int find_best_move(struct player* p, struct map* m){
  int direction=0;

  int highest_priority = 10;
  int num_highest_priority = 0;  
  int priority[4];
  
  while(direction<4){
    int* temp=try_move(p->location, direction, 1);
    int curr_code=m->grid[temp[0]][temp[1]];
    int curr_priority;

    //powerup, player, destruct, safe, indestruct, bomb, unsafe 
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
    if(highest_priority > curr_priority){
      highest_priority=curr_priority;
      num_highest_priority = 1;
    }
    if(highest_priority == curr_priority){
      num_highest_priority++;
    }
    direction++;
  }

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
