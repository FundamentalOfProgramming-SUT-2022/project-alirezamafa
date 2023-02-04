#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <errno.h>
#include <stdbool.h>
#define  hal 1
#define  no 0
     void createfile(char * mysit);
     void cat (char *filename );
     void cutstr(char *address);
     void copystr(char *addres);
     void removestr(char *address);
     void pastestr(char *address)
     void removeb(char *address,int rowloc,int clumnloc,int size);
     void removef(char *address,int rowloc,int clumnloc,int size); 
     void insertstr(char * address);
     void copyb(char *address,int rowloc,int clumnloc,int size);
     void copyf(char *address,int rowloc,int clumnloc,int size);
     void createdirectory(char * mysit); 
     void createdir(char *mysit);
     void removedoubleqoute(char *s);
     void removesubstring(char *s1,char *s2);
     char *copyingorcutingbackup;
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
            else if(strcmp(input,"removestr")==0){
                scanf("%s",input2);
                if(strcmp(input2,"--file")==0){
                    scanf("%s",address);
                    removestr(address);
                }
                else
                printf("invalid input\n");
            }
            else if(strcmp(input,"copystr")==0){
                scanf("%s",input2);
                if(strcmp(input2,"--file")==0){
                    scanf("%s",address);
                    copystr(address);
                }
                else{
                    printf("invalid input\n");
                }
            }
            else if(strcmp(input,"cutstr")==0){
                scanf("%s",input2);
                if(strcmp(input2,"--file")==0){
                    scanf("%s",address);
                    cutstr(address);
                }
                else
                printf("invalid input\n");
            }
            else if(strcmp(input,"pastestr")==0){
                scanf("%s",input2);
                if(strcmp(input2,"--file")==0){
                    scanf("%s",address);
                    pastestr(address);
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
    return;
}
else{
  while (imp=fgetc(file)!=EOF)
  {
    printf("%c",&imp);
  }
  fclose(file);
}
}
void removestr(char *address){
   char *pos;
   int rowofpos,clumnofpos;
   int row=0,clumn=0;
   char *size;//removetstr –file /root/file1.txt –pos 2:1 -size 3 -b
   int numofword;
   char * posofremoving;
   scanf("%s",pos);
   if(strcmp(pos,"--pos")){
    printf("invalid input\n");
    return;
   }
   else{
    scanf("%d:%d",&rowofpos,&clumnofpos);
    scanf("%s",size);
    if(strcmp(size,"-size")){
        printf("invalid input\n");
        return;
    }
    else{
        scanf("%d",&numofword);
        scanf("%s",posofremoving);
        if(strcmp(posofremoving,"-b")&&strcmp(posofremoving,"-f")){
            printf("invalid input\n");
            return;
        }
        else {
            if(posofremoving[1]=='b'){
                removeb(address,rowofpos,clumnofpos,numofword);
            }
            else if(posofremoving[1]=='f'){
                removef(numofword);
            }
        }
    }
   }
}
void removeb(char *address,int rowloc,int clumnloc,int size){
int numofchar=0,numofline=0;
bool removecheck=0,checking =1;
FILE *file=fopen(address,"r");
char imp;
if(file ==0){
    printf("file dosent exist\n");
    return;
}
FILE* temp=fopen("./temp","w");
char *tempadd;
strcpy(tempadd,"./temp");
 while (!feof(file))
   {numofchar++;
   imp=fgetc(file);
   if(imp=='\n'){
    numofline++;
   }
 }
 if(numofline==rowloc-1&&removecheck==0){
       for (int  i = 0; i < clumnloc; i++)
       {
        if(checking==1){
        imp =fgetc(file);
        numofchar++;
        if(imp=='\n'||imp==EOF){
            checking=0;
        }
       }
       else if(checking==0){
        fclose(file);
        printf("out of range or there is no enough char to do program\n");
        return;
       }
       }
       removecheck=1;
       fclose(file);
       break;
 }
if(rowloc==1){
    numofline--;
}
for(int i=0;i<numofline;i++){
    imp=fgetc(file);
    fprintf(temp,"%c",imp);
}
for (int  i = 0; i < size; i++)
{
    imp=fgetc(file);
}
while (!feof(file))
{
   imp=fgetc(file);
   fprintf(temp,"%c",imp);
   printf("removing str done\n");
}
fclose(file);
fclose(temp);
rmdir(file);
remove(address);
rename(tempadd,address);

}
void removef(char *address,int rowloc,int clumnloc,int size){
int numofchar=0,numofline=0;
bool removecheck=0,checking =1;
FILE *file=fopen(address,"r");
char imp;
if(file ==0){
    printf("file dosent exist\n");
    return;
}
FILE* temp=fopen("./temp","w");
char *tempadd;
strcpy(tempadd,"./temp");
 while (!feof(file))
   {numofchar++;
   imp=fgetc(file);
   if(imp=='\n'){
    numofline++;
   }
 }
 if(numofline==rowloc-1&&removecheck==0){
       for (int  i = 0; i < clumnloc; i++)
       {
        if(checking==1){
        imp =fgetc(file);
        numofchar++;
        if(imp=='\n'||imp==EOF){
            checking=0;
        }
       }
       else if(checking==0){
        fclose(file);
        printf("out of range or there is no enough char to do program\n");
        return;
       }
       }
       removecheck=1;
       fclose(file);
       break;
 }
if(rowloc==1){
    numofline--;
}
for(int i=0;i<numofline-size;i++){
    imp=fgetc(file);
    fprintf(temp,"%c",imp);
}
for (int  i = 0; i < size; i++)
{
    imp=fgetc(file);
}
while (!feof(file))
{
   imp=fgetc(file);
   fprintf(temp,"%c",imp);
   printf("removing str done\n");
}
fclose(file);
fclose(temp);
rmdir(file);
remove(address);
rename(tempadd,address);
}
void copystr(char *address){
   char *pos;
   int rowofpos,clumnofpos;
   char *size;
   int numofword,row=0,clumn=0;
   char *posofcopying;
   scanf("%s",pos);
   if(strcmp(pos,"--pos")){
      printf("invalid input\n");
      return;
   }
   else
   {
    scanf("%d:%d",&rowofpos,&clumnofpos);
    scanf("%s",size);
    if(strcmp(size,"-size")){
        printf("invalid input\n");
        return;
    }
    scanf("%d",&numofword);
    scanf("%s",posofcopying);
    removedoubleqoute(posofcopying);
    removedoubleqoute(address);
    if(strcmp(posofcopying,"-b")&&strcmp(posofcopying,"-f")){
        printf("invalid input \n");
        return;
    }
    if(posofcopying[1]=='b'){
        copyb(address,rowofpos,clumnofpos,numofword);
    }
    else if(posofcopying[1]=='f'){
        copyf(address,rowofpos,clumnofpos,numofword);
    }
   }
}
void copyb(char *address,int rowloc,int clumnloc,int size){
int numofchar=0,numofline=0;
char imp;
FILE *file=fopen(address,"r");
if(file==0){
    printf("file dosent exist\n");
    return;
}
while (numofline!=rowloc)
{
    imp=fgetc(file);
    if(imp=='\n'){
        numofline++;
    }
    else if(imp==EOF){
        printf("out of range or there is no enough word to do program\n");
        return;
    }
}
while (numofchar!=clumnloc)
{
    imp=fgetc(file);
    if(imp==EOF||imp=='\n'){
        printf("out of range or there is no enough word to do program\n");
        return ;
    }
    numofchar++;
}
if(rowloc==1){
    numofline--;
}
file=fopen(address,"r");
imp=fgetc(file);
for (int  i = 0; i < numofline-size; i++)
{
    imp=fgetc(file);
}
int i;
for (  i = 0; i < size; i++)
{    copyingorcutingbackup[i]=imp;
    imp=fgetc(file);
}
copyingorcutingbackup[i]=NULL;
printf("copying string done\n");
fclose(file);
}
void copyf(char *address,int rowloc,int clumnloc,int size){
int numofchar=0,numofline=0;
char imp;
FILE *file=fopen(address,"r");
if(file==0){
    printf("file dosent exist\n");
    return;
}
while (numofline!=rowloc)
{
    imp=fgetc(file);
    if(imp=='\n'){
        numofline++;
    }
    else if(imp==EOF){
        printf("out of range or there is no enough word to do program\n");
        return;
    }
}
while (numofchar!=clumnloc)
{
    imp=fgetc(file);
    if(imp==EOF||imp=='\n'){
        printf("out of range or there is no enough word to do program\n");
        return ;
    }
    numofchar++;
}
if(rowloc==1){
    numofline--;
}
file=fopen(address,"r");
imp=fgetc(file);
for (int  i = 0; i < numofline; i++)
{
    imp=fgetc(file);
}
int i;
for (  i = 0; i < size; i++)
{
    copyingorcutingbackup[i]=imp;
    imp=fgetc(file);
}
printf("copying string done\n");
copyingorcutingbackup[i]=NULL;
fclose(file);
}
void cutstr(char *address){
char *pos;
   int rowofpos,clumnofpos;
   char *size;
   int numofword,row=0,clumn=0;
   char *posofcopying;
   scanf("%s",pos);
   if(strcmp(pos,"--pos")){
      printf("invalid input\n");
      return;
   }
   else
   {
    scanf("%d:%d",&rowofpos,&clumnofpos);
    scanf("%s",size);
    if(strcmp(size,"-size")){
        printf("invalid input\n");
        return;
    }
    scanf("%d",&numofword);
    scanf("%s",posofcopying);
    removedoubleqoute(posofcopying);
    removedoubleqoute(address);
    if(strcmp(posofcopying,"-b")&&strcmp(posofcopying,"-f")){
        printf("invalid input \n");
        return;
    }
    if(posofcopying[1]=='b'){
        cutb(address,rowofpos,clumnofpos,numofword);
    }
    else if(posofcopying[1]=='f'){
        cutf(address,rowofpos,clumnofpos,numofword);
    }
   }
}
void cutb(char *address,int rowloc,int clumnloc,int size){
   free(copyingorcutingbackup);
   copyb(address,rowloc,clumnloc,size);
   printf("cutting string done\n");
}
void cutf(char *address,int rowloc,int clumnloc,int size){
free (copyingorcutingbackup);
copyf(address,rowloc,clumnloc,size);
removef(address,rowloc,clumnloc,size);
printf("cutting string done\n");
}
void pastestr(char *address){
  char *pos;
  int rowofpos,clumnofpos;
  scanf("%s",pos);
  if(strcmp(pos,"--pos")){
    printf("invalid input\n");
  }
  else
  scanf("%d:%d",&rowofpos,&clumnofpos);
  
}