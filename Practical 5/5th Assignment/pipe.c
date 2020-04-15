#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#define MAX 100

int main() {
  int fd[2], i = 0;
  pipe(fd);
  pid_t pid = fork();

  if (pid > 0) {
    wait(NULL);
    close(0);
    close(fd[1]);
    dup(fd[0]);
    int arr[MAX];

    int n = read(fd[0], arr, sizeof(arr));
    for (i = 0; i < n / 4; i++) printf("%d ", arr[i]);
  } else if (pid == 0) {
    int arr[100];
    for (int i = 1; i < 101; i++) {
      arr[i - 1] = i;
    }
    close(fd[0]);

    close(1);

    dup(fd[1]);
    write(1, arr, sizeof(arr));
  } else {
    perror("[-] Error\n");
  }
  printf("\n");
}

