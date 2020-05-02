#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <pwd.h>

#define SYS 200
void bsh_cd(char **dir){
	struct passwd *p;
	char *name;
	char *home = malloc(40*sizeof(char));
	if ((p = getpwuid(getuid())) != NULL)
			 name = p->pw_name;
	strcpy(home,"/home/");
	strcat(home,name);
	if(dir[1]!=NULL){
		if(strcmp(dir[1],"~")==0){
			chdir(home);

		}
    else
      chdir(dir[1]);
	}
  else{
    chdir(home);
  }
  	free(home);
}

void bsh_clear(){
  system("clear");
}
int bsh_cat(char **command){
	int i=1,count=0, opened = 0;
	if(command[1]==NULL){
					printf("Usage: cat <filename>\n");
					return 1;
	}
	while(command[i]!=NULL){
		count++;
		i++;
	}


	FILE** files = malloc(count*sizeof(FILE));
	for(i=0;i<count;i++){

		files[i] = fopen(command[i+1],"r");
		if(files[i]!=NULL)
			opened++;
		else{
			files[i]=NULL;
			printf("cat: %s: Invalid Filename\n",command[i+1]);
			}
	}
	if(opened>0){
	for(i=0;i<count;i++){
			char text;
			if(files[i]!=NULL){
	      while((text = fgetc(files[i]))!=EOF)
                printf("%c",text);
        				fclose(files[i]);
				}
			}
		}
	return 0;
}
void bsh_create(char **command){
	int i=1;
	while(command[i]!=NULL){
		FILE* fp = fopen(command[i],"w+");
		fprintf(fp," ");
		fclose(fp);
		i++;
	}
}
void bsh_systemrun(char **command){
	int i=1, count=0;
  char *string = malloc(SYS*sizeof(char));
	while(command[i]!=NULL){
		count++;
		i++;
	}
	strcpy(string,command[0]);
	for(i=1;i<=count; i++){
		strcat(string," ");
    strcat(string,command[i]);
	}
  system(string);
}