#include <arpa/inet.h>
#include <stdio.h>
#include <string.h>
#include <sys/socket.h>
#include <time.h>
#include <unistd.h>
#define PORT 8080

int main() {
  int sent = 0;
  int _received = 0;
  int valread = 0;
  char buffer[1024] = {0};

  //  while not received,
  while (!_received) {
    int sock = 0;
    struct sockaddr_in serv_addr;
    char *hello = "\'Hello\' from client";
    if ((sock = socket(AF_INET, SOCK_STREAM, 0)) < 0) {
      printf("\n Socket creation error \n");
      return -1;
    }

    serv_addr.sin_family = AF_INET;
    serv_addr.sin_port = htons(PORT);

    if (inet_pton(AF_INET, "127.0.0.1", &serv_addr.sin_addr) <= 0) {
      printf("\nInvalid address! Address not supported \n");
      return -1;
    }

    if (connect(sock, (struct sockaddr *)&serv_addr, sizeof(serv_addr)) < 0) {
      printf("\nConnection Failed \n");
      return -1;
    }
    time_t startTime = time(NULL);
    if (sent) {
      printf("\n-- Sending again... --\n");
    }
    send(sock, hello, strlen(hello), 0);
    printf("\'Hello\' message sent\n");
    sent = 1;

    printf("-- Timer for 2 seconds started --\n");
    valread = read(sock, buffer, 1024);
    if (valread) break;
    while (!valread) {
      if (time(NULL) - startTime > 2) {
        printf("-- Oops! Timeout --");
        break;
      }
      valread = read(sock, buffer, 1024);
      if (valread) _received = 1;
    }
  }
  printf("> Message received: %s <\n\n", buffer);
  return 0;
}

