#include<unistd.h>
#include<sys/types.h>
#include<sys/stat.h>
#include<fcntl.h>
#include <stdio.h>
#include<string.h>
int main( void ){
char buf[20];
      
                       read(STDIN_FILENO , buf ,  sizeof( buf ));
                       write(STDOUT_FILENO, buf , strlen( buf ));
                             
        return 0;
}

