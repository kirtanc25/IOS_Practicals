#include<stdio.h> 
#include<fcntl.h> 
#include<errno.h> 
#include<unistd.h>
extern int errno; 
int main() 
{   

	/*printf("fd stdin = %d\n", STDIN_FILENO); 
	printf("fd stdout = %d\n", STDOUT_FILENO);
	printf("fd stderr = %d\n", STDERR_FILENO);   
   //-------------------------------
        int file_desc = open("dup.txt", O_WRONLY | O_APPEND | O_CREAT); 
        if(file_desc < 0) 
            printf("Error opening the file\n"); 
        
	int copy_desc = dup(file_desc);
        write(copy_desc,"This will be output to the file named dup.txt\n", 46);
        write(file_desc,"This will also be output to the file named dup.txt\n", 51);
	printf("\nOriginal file descriptor: %d \t Copy file descriptor: %d \n",file_desc,copy_desc);*/

   //-------------------------------
    /* //dup
	int fd1 = open("n1.txt", O_RDONLY | O_CREAT);                      printf("fd1: %d\n",fd1);
   	int fd2 = open("n2.txt", O_RDONLY | O_CREAT);                      printf("fd2: %d\n",fd2);
    	int fd3 = open("n3.txt", O_RDONLY | O_CREAT);                      printf("fd3: %d\n",fd3);
	close(STDIN_FILENO);
    	int file_desc = open("tricky.txt",O_WRONLY | O_APPEND | O_CREAT);  printf("fileD_before: %d\n",file_desc);
    	int new = dup(file_desc);                                      	   printf("fileD_after: %d\n",new);
    */
   //-------------------------------
	
	int file_desc = open("dup2.txt",O_WRONLY | O_APPEND | O_CREAT); 
	// here the newfd is the file descriptor of stdout (i.e. 1) 
	printf("file_desc: %d\n", file_desc);
    	dup2(file_desc, 1); 

    	printf("I will be printed in the file dup2.txt\n");  
	printf("file_desc_after: %d\n", file_desc);
    return 0; 
} 
