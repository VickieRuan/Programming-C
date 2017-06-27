#include <stdio.h>
#include <string.h>
 
char* trim(char backup[]);

int main() {
    char answer[9]={};
	char name[9] = {};
	char backup[9]={};
	char temp[9]={};
	int i = 0;
 
	
	printf("Password Game\n");
	printf("=============\n");
	printf("Enter your name (up to 8 characters): ");
	scanf("%s", name);
	printf("WELCOME %s\n", name);
	for (i = 0; i < strlen(name);i++){
		answer[i] = name[i] - 1;
	}
	printf("Guess the password (up to 8 characters) %s: ", name);
	strcpy(backup,name);
    scanf("%s",temp);
    if(strcmp(temp,name)==0){
        printf("You got it, %s!!!\n",name);
        printf("Game Over!\n");
    }
 
    if(strcmp(temp,answer)){
	    trim(backup);
    }
    while(strlen(backup)>0 && strcmp(temp, answer) != 0){
	    printf("FALSE: Guess the password (up to 8 characters) %s: ",backup);
	    scanf("%s",temp);
        if(strcmp(temp,answer)){
	        trim(backup);
        }else{
            printf("You got it, %s!!!\n",name);
	    }
    }
	if(strlen(backup)==0){
		printf("Thou has failed.\n");
	}
	printf("Game Over!\n");
	return 0;
}	

char* trim(char backup[]){
	int i = 0;
	i = strlen(backup) - 1;
	backup[i] = '\0';
    return backup;
}