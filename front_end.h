//terminal codes
#define CLEAR_SCREEN "\e[1;1H\e[2J"

//used for keyboard interception, numbers subject to change
#define LEFT 0
#define UP 1
#define RIGHT 2
#define DOWN 3


//map's row and col size
#define ROW 20
#define COL 40

//used for maps's grid
#define SAFE 0 //if the space is empty and isn't in a bomb's explosion range (when it explodes)
#define UNSAFE 1 //if the space is empty and is in a bomb's explosion range
#define DESTRUCT 2 //if the space has an obstacle and if it's bombable
#define INDESTRUCT 3 //if the space has an obstacle and if it's indestructable
#define POWERUP 4 //if the space has a powerup on it
#define PLAYER 5 //if the space has a player on it
#define BOMB 6 //if the space has a bomb on it


struct map{
  struct player players[4];
  struct bomb* bombs;
  
  //int ** grid; //int will determine each tile's properties
  int grid[ROW][COL];
};

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


//display_map() takes in the map, and displays it
void display_map(struct map* );

//print_map() takes one grid tile's int value at a time, and prints that out as a char
//if colorize is -1, then the printing will not be colorized
//else, it will be
void print_map(int curr, int colorize);

//key_intercept() takes in the map, updates it based on keyboard commands, then returns the new map
struct map* key_intercept(struct map*);
