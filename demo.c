#include <ncurses.h>
#include <unistd.h>

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
  int x = 3, y = 0;
  int ch;
  
  windowSetup();
  
  while(1){
    clear(); //clear screen of previously printed characters
    mvprintw(y, x, "o");
    //for loop that goes through entire 2D array
    refresh();
    if ((ch = getch()) == ERR) {
      //user hasn't moved
    }
    else {
      //user has pressed key ch
      if(ch == 'w'  && y > 0 ){
	y -= 1;
      }
      else if(ch == 'a' && x > 0){
	x -= 1;
      }
      else if(ch == 's'){
	y += 1;
      }
      else if(ch =='d'){
	x += 1;
      }
    }
  }
  sleep(1);
  endwin(); //restore normal terminal behavior
  return 0;
}
