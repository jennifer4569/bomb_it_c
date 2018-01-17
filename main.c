#include "bomb_it.h"

//init_game() initializes the game
//malloc struct map
//load in map
//return map

//NEED TO CHECK FOR CERTAIN CHARACTERS
struct map * init_game(){
  srand(time(NULL));
  struct map* m = malloc(sizeof(*m));

  struct stat sb;
  stat("maps/map0.txt", &sb);
  
  int fd = open("maps/map0.txt", O_RDONLY);
  char rd_info[sb.st_size];
  read(fd, rd_info, sb.st_size);
  
  char * curr_line;
  int curr_map_key;
  int x = 0;
  int y = 0;
  int num_players = 0;
  int num_bombs = 0;
  curr_line = strtok(rd_info, "\n");
  do{
  y = 0;
    while(curr_line[y]){
      curr_map_key = curr_line[y] - '0';
      if(curr_map_key == PLAYER){
	m->players[num_players]=create_player(1, x, y);
	num_players++;
      }
      if(curr_map_key==BOMB){
	m->bombs[num_bombs]=drop_bomb(x, y, 2);
	num_bombs++;
      }
      m->grid[x][y]=curr_map_key;
      y++;
    }
    x++;
  }
  while(curr_line = strtok(NULL, "\n"));
  m->num_players=num_players;
  m->num_bombs=num_bombs;
  return m;
}

int main(int argc, char* argv[]){
  if(!argv[1]){
    printf("There is no argument!\n");
    return -1;
  }
  //host a game
  if(strcmp(argv[1], "-h")==0){
    //waits for the host to start

    //starts game(currently only has cpu players)
    struct map* m = init_game();
    int time = 0;
    while(1){  
      m = update_map(m);
      display_map(m, time);
      display_stats(m->players[0]); //that's you
      time++;
      usleep(500000);
    }
    return 1;
  }
  //connect to game with key
  if(strcmp(argv[1], "-c")==0){
    if(!argv[2]){
      printf("Please enter a key!\n");
      return -1;
    }
    else{
      
      return 1;
    }
  }
  //rules of the game
  if(strcmp(argv[1], "-r")==0){

    return 1;
  }
  //list maps
  if(strcmp(argv[1], "-m")==0){
    
    return 1;
  }
  printf("Arguments are incorrect. Try again.\n");
  return -1;
}
