#include<stdio.h>
#include<sys/socket.h>

/*
argc and argv are how command line arguments are passed where argc is the
 number of arguments being passed into your program from the command line and
 argv is the array of arguments.
*/

int main(int argc, char *argv[]){
  int socket_desc;
  socket_desc = socket(AF_INET, SOCK_STREAM, 0);      // socket() creates a socket and returns a descriptor
  /*
    A socket with the following properties will be created:
      Address Family: AF_INET (IPv4)
      Type: SOCK_STREAM (enables connection oriented TCP protocol)
      Protocol: 0 (IP protocol which could also be IPPROTO_IP)
  */
  if (socket_desc == -1){
    printf("Could not create socket");
  }

  server.sin_addr .s_addr = inet_addr("74.125.235.20");                       // inet_addr() converts IP address to a long format.
  server.sin_family = AF_INET;
  server.sin_port = htons(80);

  // Connect to remote server
  if(connect(socket_desc, (struct sockaddr *)&server, sizeof(server))<0 ){
    puts("connection error");
    return 1;
  }

  puts("Connected");
  return 0

}
