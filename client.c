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
  *ch1 = getch();
  if (*ch1 == ' '){
    while(1){
      *ch2 = getch();
      if(*ch2 == ERR){
	*ch2='\0';
	break;
      }
      if(*ch2 != ' '){
	break;
      }
    }
  }
}

void resetKeys(int * ch1, int * ch2){
  *ch1 = '\0';
  *ch2 = '\0';
}

int main(){

  windowSetup();
  
  int ch1 = 'w';//default values
  int ch2 = '\0';//default values

  sleep(4);
  //getKeys(&ch1, &ch2);
  if(ch1){
    printw("Hello world!");
  }
  //printw("|%c%c|", ch1, ch2);
  refresh();
  sleep(10);
  /*
  
  while(1){//game loop

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
  */
  endwin(); //restore normal terminal behavior
  return 0;
}
