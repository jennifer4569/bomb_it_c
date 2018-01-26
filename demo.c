#include <ncurses.h>
#include <unistd.h>
#include <time.h>

void windowSetup(){
  initscr(); //initialize the window
  noecho(); //don't echo any keypresses
  curs_set(FALSE); //don't display a cursor
  cbreak();
  //start_color();
  
  nodelay(stdscr, TRUE);//makes getch() work in a nonblocking manner
  //getch() returns ERR if key input is not read
}

void getKeys(int* ch1, int* ch2){
  int ch;
  clock_t begin;
  double time_spent;
  sleep(1);
  begin = clock();
  while(1){
    if ((ch = getch()) == ERR) {
      //user hasn't moved
    }
    else {
      if (*ch1 == ' ' && *ch2 == ' '){
	*ch2 = ch;
      }
      if( *ch1 == 'x' ){
	*ch1 = ch;
      }
    }
    time_spent = (double)(clock() - begin) / CLOCKS_PER_SEC;
    if(time_spent >= 0.5){
      break;
    }
  }
}

void resetKeys(int * ch1, int * ch2){
  *ch1 = 'x';
  *ch2 = ' ';
}

int main(){
  //client establishes connection with server
  windowSetup();

  /*
  char map[10] = "life";
  printw(map);
  refresh();
  sleep(4);
  */
  
  int ch1 = 'x';//default values
  int ch2 = ' ';//default values

  //recieves first map
  //char map[MAP_SIZE];
  //read(server_socket, map, sizeof(map));

  while(1){//game loop
    
    //reads from server the map
    //read(server_socket, map, sizeof(map));
    /*
    if read(){//if server sent updated map
	clear(); //clears screen
	printw(map); //prints updated map
    }
    */

    getKeys(&ch1, &ch2); //keyboard interception

    if( ch1 != 'x'){
      char buffer[3] = { ch1, ch2, '\0'};
      if( ch1 != ' '){
        buffer[2] = '\0';
      }
      //write(server_socket, buffer, sizeof(buffer));
      resetKeys(&ch1, &ch2); //resets keys after writing
    }
  }
  
  endwin(); //restore normal terminal behavior
  return 0;
}