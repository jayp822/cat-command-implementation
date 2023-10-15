#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>
#include <string.h>

#define BUFFSIZE 128

int main(int argc, char* argv[])
{
	int n;
	char buf[BUFFSIZE];
	char* filename;
	int fd;
	// Check if there is an empty argc after ./cat, if so then do same thing as '-'
	if(argc == 1)
	{				
		while ((n = read(STDIN_FILENO, buf, BUFFSIZE)) > 0)
		{
			if(write(STDOUT_FILENO, buf, n) != n) perror("write");
			if(n == -1) perror("read");
		}
	}

	for(int i = 1; i < argc && argc > 1; i++)
	{	
		// Check if first arguement after ./cat is '-'
		if(*argv[i] == '-')
		{
			while ((n = read(STDIN_FILENO, buf, BUFFSIZE)) > 0)
			{
				if(write(STDOUT_FILENO, buf, n) != n) perror("write");		
			}
			if(n == -1) perror("read");
		}else
		{
		// Outputs the contents of the .txt file if it is a command line arguement
			filename = argv[i];
			fd = open(filename, O_RDONLY);
			while((n = read(fd, buf, BUFFSIZE)) > 0)
			{
				if(write(STDOUT_FILENO, buf, n) != n) perror("write");;
			}
			if(n == -1) perror("read");
			if(close(fd) == -1) perror("close");
		}
	}
}
