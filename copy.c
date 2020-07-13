#include<stdio.h>
#include<sys/types.h>
#include<sys/stat.h>
#include<fcntl.h>
#include<pthread.h>
#include<string.h>
#include<stdlib.h>

int main( int argc, char *argv[] ){
	FILE *fd, *dest;
	char buf[257];
	int len;
	char *odirname;
	odirname = argv[argc-1];

	if (argc < 3) {
		printf("Usage: <file1> <file2> ... <dir name>\n");
		printf("At least two argvs needed\n");
		exit(1);
	}

	
	sprintf(odirname, "%s%s", odirname, "/");
	//printf("\n\n%s\n\n",odirname);
	
	int direxist = access(odirname, 0);
	if (direxist == -1 ){
		int mkdResult = mkdir(odirname, 0755);
		if ( mkdResult != 0 ){
			printf("Error: Failed To Creating Directory.");
			exit(1);
		}
	}


	for(int i = 0; i < argc-2 ; i++ ){
		char dirname[100];
		sprintf(dirname, "%s%s", odirname, argv[i+1]);
		//printf("%s",dirname);
		//printf("\n");
		fd = fopen(argv[i+1], "r");
		dest = fopen(dirname, "w");
		while(len = fread(buf, 1, 256, fd)){
			buf[len] = "\0";
			fwrite(buf, 1, len, dest);
			//printf("Length : %d\n", len);
			//printf("%s\n", buf);
		}
		fclose(dest);
		fclose(fd);
		printf("Successfly copied files to %s.\n",dirname);
	}
	return 0;
}
