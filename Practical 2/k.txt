#include<stdio.h>

void main(){
int a;
printf("-----Program Started-----\n");
printf("Enter any integer: ");
scanf("%d", &a);
printf("-----Program Running-----\n");
for(int i=0;i<10000000; i++){
printf("%d_/",i);
}
printf("-----Program in Sleep-----\n");
sleep(100);

}
