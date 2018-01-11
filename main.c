#include "bomb_it.h"

//init_game() initializes the game
//malloc struct map
//load in map
//return map
struct map * init_game(){
  /*struct map* m = malloc(sizeof(*m));
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
  */
  struct map* m = malloc(sizeof(*m));

  struct stat sb;
  stat("maps/map0.txt", &sb);
  
  int fd = open("maps/map0.txt", O_RDONLY);
  char rd_info[sb.st_size];
  read(fd, rd_info, sb.st_size);
  
  char * curr_line;
  char curr_char;
  int curr_map_key;
  int i = 0;
  int j = 0;
  curr_line = strtok(rd_info, "\n");
  do{
  j = 0;
    while(curr_line[j]){
      curr_char = curr_line[j];
      if(curr_char == ' '){
	curr_map_key = SAFE;
      }
      /*
	if(curr_char == ' beleh'){
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
	struct player* p0 = (struct player *)malloc(sizeof(p0));
	p0->location[0]=i;
	p0->location[1]=j;
	m->players[0]=*p0;
      }
      if(curr_char == 'O'){
	curr_map_key = BOMB;
      }
      m->grid[i][j]=curr_map_key;
      j++;
    }
    i++;
  }
  while(curr_line = strtok(NULL, "\n"));
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
