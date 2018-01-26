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
  //INSERT CLIENT SERVER HANDSHAKE STUFF

  windowSetup();
  
  int ch1 = 'x';//default values
  int ch2 = ' ';//default values
  char buffer[3] = { ch1, ch2, '\0'};

  //recieves first map
  char map[MAP_SIZE];
  //INSERT STARTING MAP, READ FROM SERVER
  //read(server_socket, map, sizeof(map));

  while(1){//game loop
    
    //reads map from server
    select(server_socket + 1, &read_fds, NULL, NULL, NULL);
    read(server_socket, map, sizeof(map));
    clear(); //clears screen
    printw(map); //prints updated map

    getKeys(&ch1, &ch2); //keyboard interception, runs for .5 seconds

    if( ch1 != 'x'){
      buffer[0] = ch1;
      if( ch1 != ' '){ //only send one character
        buffer[2] = '\0';
      }
      //write(server_socket, buffer, sizeof(buffer));
      resetKeys(&ch1, &ch2); //resets keys after writing
    }
  }
  
  endwin(); //restore normal terminal behavior
  return 0;
}
