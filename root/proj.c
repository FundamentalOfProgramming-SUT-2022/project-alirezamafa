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
     void cat (char *filename );
       void insertstr(char * address);
       void createdirectory(char * mysit); 
      void createdir(char *mysit);
      void removedoubleqoute(char *s);
      void removesubstring(char *s1,char *s2);
       int main(){
        mkdir("root");
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
            else 
            printf("invalid input\n");
        }
            else if(strcmp(input,"insertstr")==0){
                scanf("%s",input2);
                if(strcmp(input2,"--file")==0){
                    scanf("%s",address);
                    insertstr(address);
                }
                else 
                printf("invalid input\n");
            }
            else if(strcmp(input,"cat")==0){
                  scanf("%s",input2);
                  if(strcmp(input2,"--file")==0){
                    scanf("%s",address);
                    cat(address);
                  }
                  else
                  printf("invalid input\n");
            }
            else {
                printf("invalid input\n");
            }
        
        }
        return 0;
       }
       void createdir(char *mysit){
        long lengofsit=strlen(mysit);
        char *copyofstr;
        char *copyofstr2;
        char *root;
        int num_of_slash=0;
        strcpy(copyofstr,mysit);
        if(mysit[0]=='\"'){
            removedoubleqoute(mysit);
        }
        strcpy(root,"/root/");
        removesubstring(mysit,root);
        strcpy(copyofstr2,mysit);
        for (int i=0;i<lengofsit;i++){
            if(mysit[i]=='/'){
                num_of_slash++;
            }
        }
        char indexofslash[num_of_slash-1];
        for (int i=0;i<=num_of_slash-1;i++){
            indexofslash[i]=strtok(mysit,"/");
            removesubstring(mysit,indexofslash[i]);
            removesubstring(mysit,"/");
        }
        if(!num_of_slash){
            createfile(copyofstr);
        }
        else{
             for(int j=0;j<=num_of_slash-1;j++){
                createdir(indexofslash[j]);
             }
             createfile(copyofstr);
        }
       }

       void removedoubleqoute(char *s)
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
    printf("this file already exist\n");
}
else{
    FILE *file2=fopen (mysit,"w");
    fclose (file2);
}
}
void createdirectroy(char *mysit){
 struct stat st={0};
 if(stat(mysit,&st)==-1){
    mkdir(mysit);
    printf("directory created \n");
 }
 else if(errno!=EEXIST){
    printf("err:unknown error\n");
 }
 else{
    printf("err:this directory already exist\n");
 }
}
void insertstr(char* address){
    FILE* temp;
    int lenofstr;
    FILE* defile ;
    char *string;
    char *str;
    char *pos;
    char imp;
    int row=0,clumn=0;
    int  rowofpos,clumnofpos;
    scanf("%s",string);
    if(strcmp(string,"--str")){
        printf("invalid input\n");
    }
    else{
    scanf("%s",str);
    lenofstr=strlen(str);
    scanf("%s",pos);
    if(strcmp(pos,"--pos")){
        printf("invalid input\n");
    }
    else{
      scanf("%d:%d",&rowofpos,&clumnofpos);
    char *root ;
    int num_of_slash=0;
    if(address[0]=='"'){
        removedoubleqoute(address);    
    }
if(str[0]=='"'){
    removedoubleqoute(str);
}
defile=fopen(address,"r");
if(defile==0){
    printf("file dosent exist\n");
}

temp=fopen("root/temp/","w");
     while (row!=rowofpos-1){
   imp=fgetc(defile);
   if(imp=='\n'){
    row++;
   }
  else if(imp==EOF){
    imp='\n';
   }
   fputc(imp,temp);
     }
     while (clumn!=clumnofpos-1){
          imp=fgetc(defile);
          if(imp==EOF){
            imp=' ';
          }
          fputc(imp,temp);
     clumn++;
     }
     int i=0;
     while (i<lenofstr)
     {
        if(str[i]=='\\'&& str[i+i]=='n'){
            fprintf(temp,"\n");
            i++;
        }
        else if(str[i]=='\\'&&str[i+1]=='\\'&&str[i+2]=='n'){
            fprintf(temp,"\\n");
            i+=2;
        }
        else{
        imp=str[i];
        fputc(imp,temp);
        }
        i++;
     }
     while (imp=fgetc(defile)!=EOF)
     {
        fputc(imp,temp);
     }
     fclose(defile);
     fclose (temp);
     defile=fopen(address,"r");
     temp=fopen("temp","w");
     imp=fgetc(temp);
     while (imp!=EOF)
     {
        fputc(imp,defile);
        imp=fgetc(temp);
     }
     fclose(temp);
     fclose(defile);
     rmdir(temp);
     printf("text inserted\n");
    }    
}
}
void cat(char *filename){
char imp;
FILE* file=fopen(filename,"r");
if(file==0){
    printf("file dosent exist");
    return;
}
if(filename[0]='"'){
    removedoubleqoute(filename);
} 
if (access(filename,F_OK)!=0){
    printf("file dosent exists\n");
}
else{
  while (imp=fgetc(file)!=EOF)
  {
    printf("%c",&imp);
  }
  fclose(file);
}
}

