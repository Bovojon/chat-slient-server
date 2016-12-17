#include<stdio.h>
#include<string.h>      // strlen
#include<arpa/inet.h>   // inet_addr
#include<sys/socket.h>
#include<unistd.h>      // write


int main(int argc, char *argv[]){
  int socket_desc, new_socket, c;
  struct sockaddr_in server, client;
  char *message;

  // Create the socket
  socket_desc = socket(AF_INET, SOCK_STREAM, 0);
  if(socket_desc == -1){
    printf("Could not create socket");
  }

  // Prepare the sockaddr_in structure
  server.sin_family = AF_INET;
  server.sin_addr.s_addr = INADDR_ANY;
  server.sin_port = htons(8888);

  // Bind
  if(bind(socket_desc, (struct sockaddr *)&server, sizeof(server)) < 0){
    puts("Binding failed");
    return 1;
  }
  puts("Binding done");

  // listen
  listen(socket_desc, 3);

  // Accept incoming connections
  puts("Waiting for incoming connections...");
  c = sizeof(struct sockaddr_in);
  new_socket = accept(socket_desc, (struct sockaddr *)&client, (socketlen_t*)&c);
  if (new_socket<0){
    perror("Accept failed");
    return 1;
  }
  puts("Connection accepted.");

  // Reply to the client
  message = "Hello! Connection is received!\n";
  write(new_socket, message, strlen(message));

  return 0;

}
