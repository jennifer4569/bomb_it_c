#include <ncurses.h>
#include <unistd.h>

void windowSetup(){
  initscr(); //initialize the window
  //noecho(); //don't echo any keypresses
  curs_set(FALSE); //don't display a cursor
  cbreak();
  //start_color();
  
  nodelay(stdscr, TRUE);//makes getch() work in a nonblocking manner
  //getch() returns ERR if key input is not read
}

int main(){
  int ch;
  int x = 0;
  int y = 0;

  
  windowSetup();
  sleep(5);
  
  while(1){
    //clear(); //clear screen of previously printed characters
    //print map server sent back
    //for loop that goes through entire 2D array
    refresh();
    if ((ch = getch()) == ERR) {
      //user hasn't moved
    }
    else {
      //user has pressed key ch
      //send server ch
    }
  }

  sleep(1);
  endwin(); //restore normal terminal behavior
  return 0;
}
