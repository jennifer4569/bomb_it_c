#include "bomb_it.h"

struct map * init_game(){
  srand(time(NULL));
  struct map* m = malloc(sizeof(*m));

  //reads the map from a text file, and converts it into a map
  struct stat sb;
  stat("maps/map4.txt", &sb);
  
  int fd = open("maps/map4.txt", O_RDONLY);
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
    //converts the string to an int
    while(curr_line[y]){
      curr_map_key = curr_line[y] - '0';
      if(curr_map_key == PLAYER){
	if(num_players==0){
	  m->players[num_players]=create_player(-1, x, y);
	}
	else{
	  m->players[num_players]=create_player(1, x, y);

	}num_players++;
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

void windowSetup(){
  initscr(); //initialize the window
  noecho(); //don't echo any keypresses
  curs_set(FALSE); //don't display a cursor
  cbreak();

  nodelay(stdscr, TRUE);//makes getch() work in a nonblocking manner
  //getch() returns ERR if key input is not read
}

int main(int argc, char* argv[]){
  if(!argv[1]){

    printf("\n\n\nThere is no argument!");
    struct stat sb;
    stat("instructions.txt", &sb);
    
    int fd = open("instructions.txt", O_RDONLY);
    char rules[sb.st_size];
    read(fd, rules, sb.st_size);
    
    printf("%s", rules);
    
   
    return -1;
  }
  if(strcmp(argv[1], "-s")==0){
    //starts a single player game
    windowSetup();
    struct map* m = init_game();
    int time = 0;
    while(1){  
      m = update_map(m);
      display_map(m, time);
      display_stats(m->players[0], -1); //that's you
      time++;
      refresh();
      usleep(500000);
      
    }
    endwin();
    return 1;
  }
  //rules of the game
  if(strcmp(argv[1], "-r")==0){

    struct stat sb;
    stat("rules.txt", &sb);
    
    int fd = open("rules.txt", O_RDONLY);
    char rules[sb.st_size];
    read(fd, rules, sb.st_size);
    
    printf("%s", rules);
    
    return 1;
  }
  printf("\n\n\nArguments are incorrect. Try again.");
  
  struct stat sb;
  stat("instructions.txt", &sb);
    
  int fd = open("instructions.txt", O_RDONLY);
  char rules[sb.st_size];
  read(fd, rules, sb.st_size);
    
  printf("%s", rules);
    
   
  return -1;
}
