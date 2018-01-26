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

int main(){
  char ch;
  //int x = 0;
  //int y = 0;

  
  windowSetup();
  /*
  char ch1 = 'x';
  char ch2 = ' ';
  clock_t begin;
  double time_spent;
  begin = clock();
  while (1){
    if ((ch = getch()) == ERR) {
      //user hasn't moved
    }
    else {
      if (ch1 == ' ' && ch2 == ' '){
	ch2 = ch;
      }
      if( ch1 == 'x' ){
	ch1 = ch;
      }
    }
    time_spent = (double)(clock() - begin) / CLOCKS_PER_SEC;
    if(time_spent >= 0.5){
      break;
    }
  }
  */

  char ch1 = 'x';
  char ch2 = ' ';
  sleep(5);
  int i = 100;
  for(int i = 0; i > 0; i--){
    if ((ch = getch()) == ERR) {
      //user hasn't moved
    }
    else {
      if (ch1 == ' ' && ch2 == ' '){
	ch2 = ch;
      }
      if(ch1 == 'x'){
	ch1 = ch;
      }
    }
  }
  
  printw(&ch1);
  printw(&ch2);
  refresh();  

  sleep(4);
  endwin(); //restore normal terminal behavior
  return 0;
}
