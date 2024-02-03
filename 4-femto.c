#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <dirent.h>

void get_string(char* input, char size);
void parsing(char* input, char* dest[], int size);

#define command		token[0]
#define E_OK		0
#define E_NOK		-1

int main()
{
    char input[50];	//size of command line
    int size = 5;	//number of tokens
    char* token[size];	//storage of args
    char ret_status;

    while(1)
    {
	/****************** Get Command ******************/
    	get_string(input, 50);		
    	parsing(input, token, size);	

    	/****************** debug ************************/
	#ifdef debug
    	for (int i = 0; i < size && token[i] != NULL; i++)
    	{
        	printf("Element %d: %s\n", i, token[i]);
    	}
	#endif

	/************************ exiting ******************/	
	if(strcmp(input, "exit") == 0)	       
	{
		printf(">>Goodbye\n");
		return E_OK;
	}

	/************************ echo *********************/
	else if (strcmp(command, "echo") == 0)
	{
        	char counter = 1;
		while(token[counter] != NULL)
		{
			printf("%s ",token[counter]);
			counter++;
		}
		printf("\n");
    	}

	/************************** pwd ********************/
	else if (strcmp(command, "pwd") == 0)
	{
	        char buf[500]; //buf for the directory path

		//handle getcwd error
		if(getcwd(buf,sizeof(buf)) == NULL)
       		{
			printf(">>can't get current directory\n");
		}	
		else
		{
        		printf(">>Current directory : %s\n",buf);
		}
    	}

	/************************* cd *********************/
	else if (strcmp(command, "cd") == 0)
	{
        	char cd_ret = chdir(token[1]);
		if(cd_ret != E_OK)
		{
			printf("failed to chanage dir\n");
		}	
   	}

	/******************** unknowns commands ************/
	else
	{
		printf("unkown command ->%s\n",command);
	}

	//free allocation dist 
    	for (int i = 0; i < size && token[i] != NULL; i++) {
        	free(token[i]);
    	}
    }
    return E_OK;
}

void get_string(char* input, char size)
{
	//get string from user
	printf("\nyou -> ");
	fgets(input, 50, stdin);

	// Remove the newline character if found
   	if (input[strlen(input) - 1] == '\n')
       	{
         	input[strlen(input) - 1] = '\0';
       	}
}

void parsing(char* input, char* dest[], int size)
 {
    char* token = strtok(input, " ");
    int i = 0;

    while (token != NULL && i < size) {
        dest[i] = strdup(token);
        token = strtok(NULL, " ");
        i++;
    }
    for (; i < size; i++) {
        dest[i] = NULL;
    }
}
