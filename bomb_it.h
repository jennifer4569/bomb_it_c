#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <string.h>
#include <errno.h>
#include <unistd.h>
#include <time.h>
#include <netdb.h>
#include <errno.h>
#include <arpa/inet.h>
#include <netinet/in.h>
#include <sys/socket.h>
#include <ncurses.h>

#ifndef HEADERS
#define HEADERS



/*
  ====================================================
  DEFINED VARIABLES
  ====================================================
*/

//FOR MAP'S GRID
#define SAFE 0 //if the space is empty and isn't in a bomb's explosion range (when it explodes)
#define UNSAFE 1 //if the space is empty and is in a bomb's explosion range
#define DESTRUCT 2 //if the space has an obstacle and if it's bombable
#define INDESTRUCT 3 //if the space has an obstacle and if it's indestructable
#define PLAYER 4 //if the space has a player on it
#define BOMB 5 //if the space has a bomb on it
#define POWERUP_ADD_BMB 6 //if the space has a add bomb powerup on it
#define POWERUP_BMB_PWR 7 //if the space has a add bomb power powerup on it
#define POWERUP_ADD_GLV 8 //if the space has an add gloves powerup on it

#define ROW 20
#define COL 40

//FOR PLAYER MOVEMENT
#define UP 0
#define RIGHT 1
#define DOWN 2
#define LEFT 3

//FOR NETWORKING
#define BUFFER_SIZE 256
#define PORT "9001"
#define TEST_IP "127.0.0.1"



/*
  ====================================================
  STRUCTS USED
  ====================================================
*/

struct player{
  int num_bombs; //number of bombs a player can have at once
  int bomb_power; //how strong a player's bombs are
  int has_gloves; //if the player has gloves, it can push bombs
  int is_cpu; //if -1, then the player is a human, else it's a cpu player

  int location[2]; //player's location
};

struct bomb{
  int location[2]; //bomb's location
  int power; //how far the bomb's explosion range goes
  int timer; 
  struct player* p; //the player that dropped the bomb
};

struct map{
  struct player* players[4]; //all the players on the map
  struct bomb* bombs[20000000]; //all the bombs on the map
  int grid[ROW][COL]; //the grid itself
  int num_players;
  int num_bombs;
};

/*
  ====================================================
  INITIALIZATION FUNCTIONS (see main.c)
  ====================================================
*/


/*
  struct map * init_game()
  initializes the game
  returns the newly created map
*/
struct map * init_game();

/*
  void windowSetup()
  sets up the window (for ncurses)
*/
void windowSetup();

/*
  ====================================================
  PLAYER FUNCTIONS (see bomb_player.c)
  ====================================================
*/


/*
  create_player(int is_cpu, int x, int y) 
  creates a new player based on the given parameters:
     int is_cpu: -1 if the player is human, else it is a cpu
     int x: the player's x location
     int y: the player's y location
  returns the newly created player
*/
struct player* create_player(int is_cpu, int x, int y);

/*
  struct bomb* drop_bomb(int x, int y, int power, struct player* p)
  creates a new bomb based on the given parameters:
     int x: the bomb's x location
     int y: the bomb's y location
     int power: the bomb's power
     struct player *p: the player that dropped the bomb
  returns the newly created bomb
*/
struct bomb* drop_bomb(int x, int y, int power, struct player* p);

/*
  struct bomb* tick_bomb(struct bomb* b, struct map*m)
  the bomb's version of go(): every frame, it updates the bomb's timer, and explodes it when time is up
     struct player *b: the bomb that's being ticked
     struct map *m: the map
  returns the updated bomb
*/
struct bomb* tick_bomb(struct bomb* b, struct map*m);

/*
  struct player * go(struct player* p, struct map * m, int move)
  every frame, it updates the player's movement
     struct player *p: -1 if the player is human, else it is a cpu
           if the player is a human, then it will take in the move that was given, and move the player
	   else, the cpu will use its own judgement to move to another location
     struct map *m: the map
     int move: the direction that the player is going (only considered if the player is a human)
  returns the updated player
*/
struct player * go(struct player* p, struct map * m, int move);

/*
  int find_best_move(struct player* p, struct map* m)
  the cpu's judgement of which direction it should go to
     struct player *p: the cpu player
     struct map *m: the map
  returns the direction that the cpu believes it should go to
*/
int find_best_move(struct player* p, struct map* m);

/*
  int * try_move(int * location, int move, int move_pwr)
  using the given parameters:
     int * location: the old location
     int move: the direction of the move
     int move_pwr: how many spaces to the given direction it goes into
  returns the new location (not taking to account the map and obstacles)
*/
int * try_move(int * location, int move, int move_pwr);




/*
  ====================================================
  MAP AND FRONT END FUNCTIONS (see front_end.c)
  ====================================================
*/

/*
  struct map* update_map(struct map* m)
  updates the map every tick
     struct map *m: the map
  returns the newly updated map
*/
struct map* update_map(struct map* m);

/*
  void print_map(int curr, int colorize, int time, int player_num)
  prints the map one character at a time, with proper coloring
     int curr: the key code of the current space
     int colorize: if colorize is -1, then the printing will not be colorized; else, it will
     int time: the time
     int player_num: what number player the current space is; -1 if the space isn't a player
*/
void print_map(int curr, int colorize, int time, int player_num);

// display_map() takes in the map, and displays it
/*
  void display_map(struct map* m, int time)
  displays the entire map
     struct map *m: the map
     int time: the time
*/
void display_map(struct map* m, int time);

/*
  void display_stats(struct player*p, int colorize)
  displays the player's stats
     struct map *p: the player
     int colorize: if colorize is -1, then the printing will not be colorized; else, it will
*/
void display_stats(struct player*p, int colorize);



/*
  ====================================================
  NETWORKING FUNCTIONS
  ====================================================
*/

// functions from dwsource
void error_check(int i, char *s);
int server_setup();
int server_connect(int sd);
int client_setup(char * server);



#endif
