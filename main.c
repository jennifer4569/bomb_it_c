#include "bomb_it.h"

//init_game() initializes the game
//malloc struct map
//load in map
//return map
struct map * init_game();


void main(){
  struct map m = init_game();
  while(1){  
    m = update_map(m);
    display_map(m);


    sleep(0.5);

  }

}
