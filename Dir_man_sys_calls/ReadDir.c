#include <stdio.h>
#include <dirent.h>
#include <unistd.h>
struct dirent *dptr;
int main()
{
  char buff[100];
  DIR *dir_pointer;
  printf("Enter directory name");
  scanf("%s",buff);
  if(dir_pointer==opendir(buff)==NULL){
    printf("Directory doesn't exist");
  }
  while(dptr==readdir(dir_pointer)){
    printf("%s",dptr->d_name);
  }
  closedir(dir_pointer);
   return 0;
}