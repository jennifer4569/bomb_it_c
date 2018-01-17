#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <string.h>
#include <errno.h>
#include <unistd.h>
#include <time.h>

#ifndef HEADERS
#define HEADERS

//terminal codes
#define CLEAR_SCREEN "\e[1;1H\e[2J"


//used for maps's grid
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

//for computer player
#define UP 0
#define RIGHT 1
#define DOWN 2
#define LEFT 3


/*
  DEFAULT VALUES
  int num_bombs = 1; number of bombs a player can have at once
  int shield = 0; true -> protected against one death; false -> you lose
  int bomb_power = 1; how strong your bombs are
  int has_gloves = 0; true -> can push bombs
  is_alive: if -1, then not alive, else alive
  4 default map locations will be specified by map;
*/
struct player{
  int num_bombs;
  int shield;
  int bomb_power;
  int has_gloves;
  int is_cpu;
  //struct map* b;
  
  int location[2];
};

/*
  location set by player
  time = 5; explodes at t = 0
  power = how far in each direction the explosion goes
*/
struct bomb{
  int location[2];
  int power;
  int timer;
};

struct map{
  struct player* players[4];
  //struct player* cpu[4];
  struct bomb* bombs[20000000];
  //int ** grid; //int will determine each tile's properties
  int grid[ROW][COL];
  int num_players;
  //int num_cpu;
  int num_bombs;
};

//create_player() takes in its location and is_cpu (-1 if isnt cpu, else it is a cpu)
//returns newly created player
struct player* create_player(int is_cpu, int x, int y);

// go() takes in the player, the map, and the player's code for a move
// move won't be considered if the player is a cpu
// it will return the player
struct player * go(struct player*, struct map *, int);

//for cpu player, used for the cpu to find the best move for itself
int find_best_move(struct player* p, struct map* m);

//given the code for the move and the current location, return the new location if the move were to happen
int * try_move(int * location, int move, int move_pwr);

// drop_bomb() takes in a location and its power (player->location, player->bomb_power)
// creates the bomb and returns the newly created bomb
struct bomb* drop_bomb(int x, int y, int power);

//tick_bomb() takes in the bomb, if timer = 0, then explode
struct bomb* tick_bomb(struct bomb* b, struct map*m);


//update_map() takes in the map, updates it, then returns the newly updated map
//calls key_intercept()
//ticks every bomb's timer by 1
//if timer == 0, update spaces to be in explosion range, and the bomb will no longer show on the map
//if timer == -5, update spaces to be safe, then free() the bomb
//checks for the following:
//    if player is on the explosion range, it will lose health
//    if destructable obstacle is on the explosion range, it will be destroyed, with a chance of dropping a powerup
//    if powerup is on the explosion range, it will be destroyed
//    if bomb is on the explosion range, it will also explode
struct map* update_map(struct map*);


// display_map() takes in the map, and displays it
void display_map(struct map* m, int time);

//display_stats() takes in the player, and displays its stats
void display_stats(struct player*p);

//print_map() takes one grid tile's int value at a time, and prints that out as a char
//if colorize is -1, then the printing will not be colorized
//else, it will be
void print_map(int curr, int colorize, int time);

//key_intercept() takes in the map, updates it based on keyboard commands, then returns the new map
struct map* key_intercept(struct map*);

#endif
