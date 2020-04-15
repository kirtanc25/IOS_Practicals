#include<sys/types.h>
#include<sys/ipc.h>
#include<sys/shm.h>
#include<stdio.h>

void main(){
 key_t  k1,k2;
 int s_id, *s_ptr, *s;
 
 //k1 = 1234;
 //printf("%d\n",k1);

 k2= ftok("./", 'k');
 printf("%d\n",k2);
 
 s_id = shmget(k2, 100*sizeof(int),IPC_CREAT | 0666);
 printf("%d\n",s_id);

 s_ptr = shmat(s_id,NULL,0);
 
 if(s_ptr == (int *)-1){ printf("ERROR FOUND\n");}
 else{ printf("in WRITER\n");}

printf("Writing content...\n\n");
 s = s_ptr;

 for(int i=1; i<=100; i++){
  *s++ = i;
  printf("%d, ", i);
 }
	printf("\n"); 
	printf("\nWriting completed\nWaiting for reading process to complete...\n");

 while(*s_ptr !=0){
    continue;
 }
printf("Successful\n");
 shmdt(s_ptr);

 shmctl(s_id, IPC_RMID, NULL); 

}

