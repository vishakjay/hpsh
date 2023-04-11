/*
hpeshell
TEAM MEMBERS:
Nishan Rupesh
Dechamma KV
Sameeksha C Shetty
Vishak Jaisimha

*/


#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>
#include "shell.h"
#include<unistd.h>
#include <limits.h>
//#include <conio.h>
#define LINE_MAX_BUFFER_SIZE 255
//char *currpath;
//char *buf;

int main(int argc, char **argv)
{
    char *cmd;
     system("clear"); 
     sleep(2);
     fprintf(stderr,"\n\n\n\n\n\n");
     fprintf(stderr,"        / /\n");
     fprintf(stderr,"       / /\n");
     fprintf(stderr,"      / /_______   __________\n");
     fprintf(stderr,"     /  _____  /  / _______  /\n");
     fprintf(stderr,"    /  /    / /  / /      / /\n");
     fprintf(stderr,"   /  /    / /  / /______/ /\n");
     fprintf(stderr,"  /  /    / /  /  _______ /\n");
     fprintf(stderr,"              /  /\n");
     fprintf(stderr,"             /  /\n");
     fprintf(stderr,"            /  /\n");
     fprintf(stderr,"\n\n");
     fprintf(stderr,"\n***Welcome to HPshell***\n");
     

    do
    {   
        //clrscr();
        //system("clear"); 
        
        print_prompt1();

        cmd = read_cmd();
        if(strcmp(cmd,"ls\n")==0){
         char output[100][LINE_MAX_BUFFER_SIZE];
         int a = runExternalCommand(cmd, output);
         for (int i = 0; i < a; ++ i) {
        printf("%s", output[i]);
       
    }
     continue;
        }

        if(!cmd)
        {
            exit(0);
        }

        if(cmd[0] == '\0' || strcmp(cmd, "\n") == 0)
        {
            free(cmd);
            continue;
        }
        if(strcmp(cmd,"pwd\n")==0){
        //printf("fetching the directory");
        get_cwd();
        
         continue; 
        }
         if(strcmp(cmd,"help\n")==0){
          printf("The following commands are built in:\n cd Change Directory \n exit  Exit the shell \n help prints this text \n The following commands are also executable:\n pwd Print the current working directory \n ls Lists the files in the current directory \n mkdir creates a new directory\n "
           );
           continue;
         }
         int cdsum=0;
         for(int i=0;i<=1;i++){
           cdsum+=cmd[i];
         }
          int cdlen=strlen(cmd);
         /*if(cdsum==199){
          char path[INT_MAX];
          int k=0;
           for(int i=3;i<cdlen;i++){
             path[k]=cmd[i];           
           }   
            get_cwd();  
             currpath=(char *)malloc(100*sizeof(char));
           currpath=buf;
           printf("%s",buf);
           strcat(currpath,path);
           continue; 
           
           
         }*/
         int mksum=0;
         for(int i=0;i<=4;i++){
          
           mksum+=cmd[i];
         }
         if(mksum==535){
         
           char dirName[16];
         int ret = 0;

         printf("Enter directory name: ");
         scanf("%s", dirName);

        ret = mkdir(dirName, 0755);

        if (ret == 0)
        printf("Directory created successfully\n");
        else
        printf("Unable to create directory %s\n\n", dirName);
        continue;

         }
         int rmsum=0;
         for(int i=0;i<=4;i++){
          rmsum+=cmd[i];
         }
         if(rmsum==542){
          char dirName[16] ;
       int ret = 0 ;
         printf("\n Enter directory name: ") ;
     scanf("%s", dirName) ;

     ret = rmdir(dirName) ;
    if (ret == 0)
      printf(" Given empty directory removed successfully\n") ;
     else
      printf(" Unable to remove directory %s\n", dirName) ;
      
      continue;
         }
        

        if(strcmp(cmd, "exit\n") == 0)
        {
            free(cmd);
            break;
        }
        int sum=0;
        for(int i=0;i<=3;i++){
         sum+=cmd[i];
        }
        if(sum==415){
        int len=strlen(cmd);
         for(int i=5;i<len;i++){
          printf("%c",cmd[i]);
         }
         printf("\n");
        }
        else{
         printf("Enter a valid command enter help command to view valid commands\n");
         continue;
        }

        free(cmd);

    } while(1);

    exit(0);
}
void print_prompt1(void)
{   
   
    fprintf(stderr, "$ ");
}

void print_prompt2(void)
{
    fprintf(stderr, "> ");
}

char *read_cmd(void)
{
    char buff[1024];
    char *ptr = NULL;
    char ptrlen = 0;

    while(fgets(buff, 1024, stdin))
    {
        int buflen = strlen(buff);

        if(!ptr)
        {
            ptr = malloc(buflen+1);
        }
        else
        {
            char *ptr2 = realloc(ptr, ptrlen+buflen+1);

            if(ptr2)
            {
                ptr = ptr2;
            }
            else
            {
                free(ptr);
                ptr = NULL;
            }
        }

        if(!ptr)
        {
            fprintf(stderr, "error: failed to alloc buffer: %s\n", strerror(errno));
            return NULL;
        }

        strcpy(ptr+ptrlen, buff);

        if(buff[buflen-1] == '\n')
        {
            if(buflen == 1 || buff[buflen-2] != '\\')
            {
                return ptr;
            }

            ptr[ptrlen+buflen-2] = '\0';
            buflen -= 2;
            print_prompt2();
        }

        ptrlen += buflen;
    }

    return ptr;
}
int runExternalCommand(char *cmd, char lines[][LINE_MAX_BUFFER_SIZE]) {
  FILE *fp;
  char path[LINE_MAX_BUFFER_SIZE];
 
  /* Open the command for reading. */
  fp = popen(cmd, "r");
  if (fp == NULL) {
    return -1;
  }
 
  int cnt = 0;
  while (fgets(path, sizeof(path), fp) != NULL) {
    strcpy(lines[cnt++], path);
  }
  pclose(fp);
  return cnt;  
}
void get_cwd(void){
char *buf;
buf=(char *)malloc(100*sizeof(char));
getcwd(buf,100);
printf("\n %s \n",buf);
//return buf;
}



