#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <errno.h>
#define  hal 1
#define  no 0
     void createfile(char * mysit);
      void createdir(char *mysit);
      void removedoubleqoute(char *s,char c);
      void removesubstring(char *s1,char *s2);
       int main(){
        mkdir("root",0777);
        char input[1000];
        char input2[1000];
        char address[1000];
        while (1)
        {
        scanf("%s",input);
        if(strcmp(input,"exit")==0){
            break;
            return;
        }          
        else if(strcmp(input,"createfile")==0){
            scanf("%s",input2);
            if(strcmp(input2,"--file")==0){
                scanf("%s",address);
                createdir(address);
            }
            else {
                printf("invalid input\n")
            }
        } 
        }
        return 0;
       }
       viod createdir(char *mysit){
        long lengofsit=strlen(mysit);
        char *copyofstr;
        char *copyofstr2;
        int num_of_slash=0;
        strcpy(copyofstr,mysit);
        if(mysit[0]=='\"'){
            removedoubleqoute(mysit,);
        }
        removesubstring(mysit,"\root\");
        strcpy(copyofstr2,mysit);
        for (int i=0;i<lengofsit;i++){
            if(mysit[i]=='/'){
                num_of_slash++;
            }
        }
        char indexofslash[num_of_slash-1];
        removesubstring(mysit,indexofslash[0]);
        for (int i=0;i<=num_of_slash-1;i++){
            indexofslash[i]=strtok(mysit,"/");
            removesubstring(mysit,indexofslash[i]);
        }
        if(!num_of_slash){
            createfile(copyofstr);
        }
        else{
             for(int j=0;j<=num_of_slash-1;j++){
                createdir(indexofslash[0]);
             }
             createfile(copyofstr);
        }
       }

       void removedoubleqoute(char *s, char c)
{
    int writer = 0, reader = 0;

    while (s[reader])
    {
        if (s[reader]!='\"') 
        {   
            s[writer++] = s[reader];
        }

        reader++;       
    }

    s[writer]=0;
}
void removesubstring(char *s1, char *s2) {
	char *match;
	int len = strlen(s2);
	while ((match = strstr(s1, s2))) {
		*match = '\0';
		strcat(s1, match+len);
	}
}
void createfile(char * mysit){
FILE * file=fopen(mysit, "r");
if(file !=0){
    printf("this file already exist\n")
}
else{
    FILE *file2=fopen (mysit,"w");
    fclose (file2);
}
}
void createdir(char* mysit){
 struct stat st={0};
 if(stat(mysit,&st)==-1){
    mkdir(mysit,0777);
    printf("directory created \n")
 }
 else if(errno!=EEXIST){
    printf("err:unknown error\n")
 }   
 else{
    printf("err:this directory already exist\n");
 }
}