#include "bomb_it.h"
/*
  temporary testing main for networking functions
*/

client(char * server){
  int server_socket;
  char buffer[BUFFER_SIZE];

  fd_set read_fds;

  // if given server connect to it else assume loopback
  if(server)
    server_socket = client_setup( server );
  else
    server_socket = client_setup( TEST_IP );

  while (1) {

    printf("enter data: ");
    //the above printf does not have \n
    //flush the buffer to immediately print
    fflush(stdout);

    //select() modifies read_fds
    //we must reset it at each iteration
    FD_ZERO(&read_fds);
    FD_SET(STDIN_FILENO, &read_fds); //add stdin to fd set
    FD_SET(server_socket, &read_fds); //add socket to fd set

    //select will block until either fd is ready
    select(server_socket + 1, &read_fds, NULL, NULL, NULL);

    if (FD_ISSET(STDIN_FILENO, &read_fds)) {
      fgets(buffer, sizeof(buffer), stdin);
      *strchr(buffer, '\n') = 0;
      write(server_socket, buffer, sizeof(buffer));
      read(server_socket, buffer, sizeof(buffer));
      printf("received: [%s]\n", buffer);
    }//end stdin select

    //currently the server is not set up to
    //send messages to all the clients, but
    //this would allow for broadcast messages
    if (FD_ISSET(server_socket, &read_fds)) {
      read(server_socket, buffer, sizeof(buffer));
      printf("[SERVER BROADCAST] [%s]\n", buffer);
      printf("enter data: ");
      //the above printf does not have \n
      //flush the buffer to immediately print
      fflush(stdout);
    }//end socket select

  }//end loop
}



// helper function for server
void subserver(int client_socket) {
  char buffer[BUFFER_SIZE];

  //for testing client select statement
  strncpy(buffer, "hello client", sizeof(buffer));
  write(client_socket, buffer, sizeof(buffer));

  while (read(client_socket, buffer, sizeof(buffer))) {

    printf("[subserver %d] received: [%s]\n", getpid(), buffer);
    process(buffer);
    write(client_socket, buffer, sizeof(buffer));
  }//end read loop
  close(client_socket);
  exit(0);
}

void process(char * s) {
  while (*s) {
    if (*s >= 'a' && *s <= 'z')
      *s = ((*s - 'a') + 13) % 26 + 'a';
    else  if (*s >= 'A' && *s <= 'Z')
      *s = ((*s - 'a') + 13) % 26 + 'a';
    s++;
  }
}



int main(int argc, char* argv[]){
  if(!argv[1]){
    printf("There is no argument!\n");
    return -1;
  }
  //host a game
  if(strcmp(argv[1], "-h")==0){

    // if parent, become server; else become client
    if(fork()){

    }else{
      client()
    }

    //waits for the host to start

    //starts game(currently only has cpu players)
    struct map* m = init_game();
    int time = 0;
    while(1){
      m = update_map(m);
      display_map(m, time);
      display_stats(m->players[0]); //that's you
      time++;
      usleep(500000);
    }
    return 1;
  }
  //connect to game with key
  if(strcmp(argv[1], "-c")==0){
    if(!argv[2]){
      printf("Please enter a key!\n");
      return -1;
    }
    else{
      client(argv[2]);
      return 1;
    }
  }
  //rules of the game
  if(strcmp(argv[1], "-r")==0){

    return 1;
  }
  //list maps
  if(strcmp(argv[1], "-m")==0){

    return 1;
  }
  printf("Arguments are incorrect. Try again.\n");
  return -1;
}
