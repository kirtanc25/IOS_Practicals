#include <netinet/in.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <unistd.h>
#define PORT 8080

int server_fd, new_socket, valread;
struct sockaddr_in address;
int opt = 1;
int addrlen = sizeof(address);
int true = 1;
void start() {
  if ((server_fd = socket(AF_INET, SOCK_STREAM, 0)) == 0) {
    perror("Connection failed");
    exit(EXIT_FAILURE);
  }

  if (setsockopt(server_fd, SOL_SOCKET, SO_REUSEADDR | SO_REUSEPORT, &opt,
                 sizeof(opt))) {
    perror("setsockopt");
    exit(EXIT_FAILURE);
  }
  address.sin_family = AF_INET;
  address.sin_addr.s_addr = INADDR_ANY;
  address.sin_port = htons(PORT);

  if (bind(server_fd, (struct sockaddr *)&address, sizeof(address)) < 0) {
    perror("bind failed");
    exit(EXIT_FAILURE);
  }
  if (listen(server_fd, 3) < 0) {
    perror("listen");
    exit(EXIT_FAILURE);
  }
}

int main(int argc, char const *argv[]) {
  char buffer[1024] = {0};

  char *hello = "Hello!";
  start();

  setsockopt(new_socket, SOL_SOCKET, SO_REUSEADDR, &true, sizeof(int));

  if ((new_socket = accept(server_fd, (struct sockaddr *)&address,
                           (socklen_t *)&addrlen)) < 0) {
    perror("accept");
    exit(EXIT_FAILURE);
  }
  valread = read(new_socket, buffer, 1024);
  printf("%s\n", buffer);
  printf("\n-- Sleeping for 4 seconds! --\n");
  close(new_socket);
  sleep(3);
  if ((new_socket = accept(server_fd, (struct sockaddr *)&address,
                           (socklen_t *)&addrlen)) < 0) {
    perror("accept");
    exit(EXIT_FAILURE);
  }
  //   start();
  valread = read(new_socket, buffer, 1024);
  printf("Message received: %s\n", buffer);
  send(new_socket, hello, strlen(hello), 0);
  printf("\'Hello\' message sent\n");
  return 0;
}

