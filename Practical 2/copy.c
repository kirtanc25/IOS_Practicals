#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<fcntl.h>
#include<errno.h>
#include<dirent.h>
#include<sys/stat.h>
#include<sys/types.h>
#include<string.h>
#define BUFF_SIZE 1024
int is_file(const char* path) {
struct stat buf;
stat(path, &buf);
return S_ISREG(buf.st_mode);
}
int is_dir(const char* path) {
struct stat buf;
stat(path, &buf);
return S_ISDIR(buf.st_mode);
}
void copy_file(char* source_file, char* desti_file) {
int srcFD, dstFD, nbread, nbwrite;
char *buff[BUFF_SIZE];
srcFD = open(source_file, O_RDONLY);
if(srcFD == -1) {
printf("\nError opening file %s errno = %d\n",source_file,errno);
exit(EXIT_FAILURE);
}
dstFD = open(desti_file, O_RDWR);

if(dstFD == -1) {
dstFD = creat(desti_file, S_IRWXU|S_IWUSR|S_IRGRP|S_IROTH);
}
dstFD = open(desti_file, O_WRONLY | O_CREAT | O_TRUNC, S_IRUSR | S_IWUSR | S_IWGRP | S_IROTH | S_IWOTH);
if(dstFD == -1) {
printf("\nError opening file %s errno = %d\n",desti_file,errno);
exit(EXIT_FAILURE);
}
while((nbread = read(srcFD, buff, BUFF_SIZE)) > 0) {
if(write(dstFD, buff, nbread) != nbread) {
printf("\n Error in writing data to %s\n",desti_file);
}
}
if(nbread == -1)
printf("\nError in reading data from file %s\n",source_file);
if(close(srcFD) == -1)
printf("\nError in closing file %s\n",source_file);
if(close(dstFD) == -1)
printf("\nError in closing file %s\n",desti_file);
}
void copy_dir(char* source, char* destination){
DIR *dir_ptr = NULL;
    struct dirent *direntp;
    int srcLen=strlen(source);
    int destLen=strlen(destination);
    char tempSrc[100];
    char tempDest[100];
    char tempSrc_[100];
    char tempDest_[100];
    int i=0;
for(i=0;i<destLen;i++){
tempDest[i]=*(destination+i);
}
tempDest[i]='/';
tempDest[i+1]='\0';
for(i=0;i<srcLen;i++){
tempSrc[i]=*(source+i);
}
tempSrc[i]='/';
tempSrc[i+1]='\0';
strcpy(tempSrc_, tempSrc);
strcpy(tempDest_, tempDest);

struct stat fileinfo;
dir_ptr = opendir(source);
    if( dir_ptr == NULL ){
      fprintf(stderr, "cp1: cannot open %s for copying\n", source);
    }
    else{
    struct stat buf;
int err = stat(tempDest, &buf);
    if(err==-1){
    mkdir(tempDest, S_IRWXU|S_IWUSR|S_IRGRP|S_IROTH);
    }
      while((direntp = readdir(dir_ptr))){
      if(!strcmp(direntp->d_name, ".")||!strcmp(direntp->d_name, "..")){
      continue;
      }
  for(i=0;i<strlen(direntp->d_name);i++){
tempSrc[srcLen+1+i]=*(direntp->d_name+i);
}
tempSrc[srcLen+i+1]='\0';
  for(i=0;i<strlen(direntp->d_name);i++){
tempDest[destLen+1+i]=*(direntp->d_name+i);
}
tempDest[destLen+i+1]='\0';
  if(is_file(tempSrc)){
  copy_file(tempSrc, tempDest);        
  }
  else{
  copy_dir(tempSrc, tempDest);        
  }
   strcpy(tempDest, tempDest_);
   strcpy(tempSrc, tempSrc_);  
    }
    closedir(dir_ptr);
   }
}
int main(int argc, char* argv[]){
int chkfl1,chkfl2,chkdir1,chkdir2;
chkfl1 = is_file(argv[1]);
chkfl2 = is_file(argv[2]);
chkdir1 = is_dir(argv[1]);
chkdir2 = is_dir(argv[2]);
if((chkfl1 == 1)&&(chkfl2 == 1)){
copy_file(argv[1], argv[2]);
}
else if((chkdir1 == 1)&&(chkdir2 == 1)){
copy_dir(argv[1], argv[2]);
}
else{
printf("Please, Correct your arguments.");
}
return 0;
}
	
	
	

