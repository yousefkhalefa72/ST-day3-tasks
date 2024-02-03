#include <stdio.h>

#define E_OK	0
#define E_NOK	-1
#define notdebug

int main(int argc,char * argv[])
{
	//check on num of urgs
	if(argc <= 1)
	{
		printf("Usage:\"%s\" num of commands\n", argv[0]);
		return E_NOK;
	}
	
	printf(">>");				// out >>

	for(int i=1; i<argc; i++)
	{
		printf("%s ",argv[i]);	 	//print all args
	}

	printf("\n");				//new line

	#ifdef debug
	printf("\n----i printed %d argument(s)----\n",argc-1);
	#endif

	return 0;
}
