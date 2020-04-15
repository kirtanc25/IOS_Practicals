#include<stdio.h>
#include <unistd.h> /*Included for dup(2) and write(2)*/
#include <stdlib.h> /*Included for exit(3)*/
 #define MESSAGE "Hey! Who redirected me?\r\n\0"
int main() {
   int newfd = dup(STDOUT_FILENO); /*Call dup for an aliased fd*/
	printf("newfd: %d\n",newfd);
    char buff[] = MESSAGE;
     if (newfd < 0) { /*Negative file descriptors are errors*/
        exit(EXIT_FAILURE);
    }
    else if (write(newfd, buff, sizeof(buff)) < 0) { /*See: man 2 write*/
        exit(EXIT_FAILURE);}
return EXIT_SUCCESS;
}
