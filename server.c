/* Internet domain TCP server.
   Usage: ./server <port>
   Really only useful with client
   Original code from Linux HowTos.
*/
#include "c-s-socket.h"

int main(int argc, char *argv[]) {
  int sockfd, new_socket, portno;
  socklen_t clilen;
  char buffer[256];
  struct sockaddr_in serv_addr, cli_addr;
  int n;

  // fd_set is used to represent file descriptor set
  fd_set master_socket;
  fd_set readfds;                      //set of socket descriptors
  int max_sd, i, j, messageSize;
  FD_ZERO(&master_socket);
  FD_ZERO(&readfds);                 //clear the socket set


  if (argc < 2) {
    fprintf(stderr, "usage %s port\n", argv[0]);
    exit(1);
  }

  sockfd = socket(AF_INET, SOCK_STREAM, 0);
  if (sockfd < 0)
    error("ERROR opening socket");

  bzero((char *) &serv_addr, sizeof(serv_addr));
  portno = atoi(argv[1]);
  serv_addr.sin_family = AF_INET;
  serv_addr.sin_addr.s_addr = INADDR_ANY;
  serv_addr.sin_port = htons(portno);
  if (bind(sockfd, (struct sockaddr *) &serv_addr, sizeof(serv_addr)) < 0)
    error("ERROR on binding");

  listen(sockfd,5);

  FD_SET(sockfd, &master_socket);                 //add sockfd to set
  max_sd = sockfd;

  while (TRUE) {
    readfds = master_socket;
    char client_buffer[20];

    if (select(max_sd + 1, &readfds, NULL, NULL, NULL) == -1) {
      perror("Error in selecting");
      exit(1);
    }
    //add child sockets to set
    for (i = 0; i <= max_sd; i++) {
      if (FD_ISSET(i, &readfds)) {
        if (i == sockfd) {
          clilen = sizeof(cli_addr);
          new_socket = accept(sockfd, (struct sockaddr * ) & cli_addr, & clilen);
          inet_ntop(AF_INET, & (cli_addr.sin_addr), client_buffer, 20);
          printf("%s connected\n", client_buffer);
          strcpy(name_buffer[i], client_buffer);
          if (new_socket < 0)
            error("Error accepting");
          FD_SET(new_socket, &master_socket);
          if (new_socket > max_sd)
            max_sd = new_socket;
        } else {
          bzero((char * ) & buffer, sizeof(buffer));
          if (( = recv(i, buffer, sizeof(buffer), 0)) == 0) {
            printf("%s closed\n", client_buffer);
            close(i);
            FD_CLR(i, &master_socket);
          } else {
            if (buffer[0] == '/') {
              char request[10];
              sscanf(buffer, "%s", request);
            } else {
              printf("%s\n",name_buffer[5]);
              printf("%d\n",i);
              printf("%d\n",max_sd);
              for (j = 0; j <= max_sd; j++) {
                if (FD_ISSET(j, &master_socket)) {
                  if ((j != sockfd) && (j != i)) {
                    send(j, name_buffer[i], sizeof(name_buffer[i]), 0);
                    send(j, ": ", 2, 0);
                    if (send(j, buffer, , 0) == -1)
                      perror("error in sending");
                  }
                }
              }
            }
          }
        }
      }
    }
  }


  return(0);
}
