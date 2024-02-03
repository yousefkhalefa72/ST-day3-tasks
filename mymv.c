#include <stdio.h>

//to use system call "open"
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

//to use system calls "read" "write" "unkink"
#include <unistd.h>

#define E_OK	0
#define E_NOK	-1
#define nodebug  
#define STDOUT	1

int main(int argc, char *argv[])
{
	int fd1, fd2, num_read, num_write, rm_ret;
	unsigned char buf[100];

	//check the argument must be 3 "command name" "file1" "file2"
	if(argc != 3)
	{
		printf(">>>> Usage: %s file_name\n", argv[0]);
		return E_NOK;
	}

	//open file1 that path in second argument as read only
	fd1 = open(argv[1], O_RDONLY);
	
	//check opening file1
	if(-1 == fd1)
	{
		printf(">>>> can't open file %s\n",argv[1]);
		return E_NOK;
	}

	#ifdef debug
	printf(">>>> file1 opened with fd = %d\n", fd1);
	#endif
	
	//(open or create) and trunc file2
	fd2 = open(argv[2], O_WRONLY | O_CREAT | O_TRUNC, 0644);

	//check opening file2
	if(-1 == fd2)
	{
		printf(">>>> can't open file %s\n",argv[2]);
		return E_NOK;
	}

	#ifdef debug
	printf(">>>> file2 opened with fd = %d\n", fd2);
	#endif

	//read from fd1 into buf
	while((num_read = read(fd1, buf, 100)) != 0)
	{
		//check reading file
		if(num_read < 0)
		{
			printf(">>>> can't read file %s\n",argv[1]);
			return E_NOK;
		}

		#ifdef debug
		printf("\n>>>> I read %d byte(s) from %s\n", num_read, argv[1]);
		#endif
		
		//write from buf into file2
		num_write = write(fd2, buf, num_read);

		//check writing
		if(num_write < 0)
		{
			printf(">>>> can't write to %s\n",argv[2]);
			return E_NOK;
		}

		#ifdef debug
		printf("\n>>>> I write %d byte(s) to %s\n", argv[2]);
		#endif
	}

	//remove first file
	rm_ret = unlink(argv[1]);
	
	//check removing file1
	if(0 != rm_ret)
	{
		printf(">>can't remove file1 \"%s\" \n",argv[1]);
		return E_NOK;
	}

	#ifdef debug
	printf(">>file1 \"%s\" removed\n",argv[1]);
	#endif

	close(fd1);
	close(fd2);
	
	return E_OK;
}
