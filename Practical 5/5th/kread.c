#include<sys/types.h>
#include<sys/ipc.h>
#include<sys/shm.h>
#include<stdio.h>

void main(){
 key_t  k1,k2;
 int s_id, *s_ptr, *s, sum = 0;

 k2= ftok("./", 'k');
 printf("%d\n",k2);
 
 s_id = shmget(k2, 100*sizeof(int),0666);
 printf("%d\n",s_id);

 s_ptr = shmat(s_id,NULL,0);
 
 if(s_ptr == (int *)-1){ printf("ERROR FOUND\n");}
 else{ printf("in READER\n");}
printf("Reading content...\n");
printf("s_ptr(before):%d\n\n", *s_ptr);
 s = s_ptr;

// int store[100];

 for(int i=0; i<100; i++){
  printf("%d, ",*s);
  sum += *s;
  *s++;
 }
 
 *s_ptr = 0;
 printf("\n\ns_ptr(after):%d", *s_ptr);
 shmdt(s_ptr);
/*
 for(int i=1; i<=100;i++){
     printf("%d, ", store[i]);}*/
 printf("\nReading completed\n");
 printf("Sum is %d\n", sum);
}
