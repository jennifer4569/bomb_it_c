#include "bomb_it.h"

//init_game() initializes the game
//malloc struct map
//load in map
//return map

//NEED TO CHECK FOR CERTAIN CHARACTERS
struct map * init_game(){
  struct map* m = malloc(sizeof(*m));

  struct stat sb;
  stat("maps/map0.txt", &sb);
  
  int fd = open("maps/map0.txt", O_RDONLY);
  char rd_info[sb.st_size];
  read(fd, rd_info, sb.st_size);
  
  char * curr_line;
  char curr_char;
  int curr_map_key;
  int x = 0;
  int y = 0;
  int num_players = 0;
  curr_line = strtok(rd_info, "\n");
  do{
  y = 0;
    while(curr_line[y]){
      curr_char = curr_line[y];
      if(curr_char == ' '){
	curr_map_key = SAFE;
      }
      /*
	if(curr_char == '-'){
	curr_map_key = UNSAFE;
	}
	if(curr_char == ' beleh'){
	curr_map_key = DESTRUCT;
	}
	
      */
      if(curr_char == '#'){
	curr_map_key = INDESTRUCT;
      }
      /*
	if(curr_char == '+' || curr_char == '*' || curr_char == 'm'){
	curr_map_key = POWERUP;
	//need a way to save which powerup it is
	}
      */
      if(curr_char == 'P'){
	curr_map_key = PLAYER;
	m->players[num_players]=create_player(1, x, y);
	num_players++;
      }
      if(curr_char == 'O'){
	curr_map_key = BOMB;
      }
      m->grid[x][y]=curr_map_key;
      y++;
    }
    x++;
  }
  while(curr_line = strtok(NULL, "\n"));
  m->num_players=num_players;
  return m;
}


void main(){
  struct map* m = init_game();
  int i = 0;
  while(1){  
    m = update_map(m);
    display_map(m);
    sleep(1);
  }
}
