struct player{
  //front end changes these values based on powerups
  /*int num_bombs = 1;
  int health = 100;
  int bomb_power = 1;
  int has_gloves = 0;*/

  int num_bombs;
  int health;
  int bomb_power;
  int has_gloves;

  //location, xy
  int location[2];
};

struct bomb{
  int location[2];
  int power;
  //int timer = 10;
  int timer;
};


//move() takes in the player's location and the player's move
//it will return the player's new location if the move is going to be made

//**front end decides whether or not the move is valid**  
//**front end changes player's stats based on powerups after checking the new space**
int * move(int * location, int move);



//drop_bomb() takes in the location it will be placed in and its power
//creates the bomb and returns the newly created bomb
struct bomb drop_bomb(int * location, int power);






