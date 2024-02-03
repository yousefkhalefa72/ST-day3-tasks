//to use getcwd
#include <unistd.h>

#include <stdio.h>
#include <stdlib.h>

#define E_OK	0
#define E_NOK	-1

int main()
{
	char buf[500]; //buf for the directory path
	
	//handle getcwd error
	if(getcwd(buf,sizeof(buf)) == NULL)
       	{
		printf(">>can't get current directory\n");
		return E_NOK;
	}
       	
        printf(">>Current directory : %s\n",buf);
    
	return E_OK;	
}
