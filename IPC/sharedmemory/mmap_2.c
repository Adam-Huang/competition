/*-------------map_normalfile2.c-----------*/
#include <sys/mman.h>
#include <sys/types.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

typedef struct{
	char name[4];
	int  age;
}people;

int main(int argc, char** argv)  // map a normal file as shared mem:
{
	int fd,i;
	people *p_map;
	
	fd=open( "./test_mmap",O_CREAT|O_RDWR,00777 );

	p_map = (people*)mmap(NULL,sizeof(people)*10,PROT_READ|PROT_WRITE, MAP_SHARED,fd,0);

	for(i = 0;i<10;i++)
	{
		printf( "name: %s age %d;\n",(*(p_map+i)).name, (*(p_map+i)).age );
	}
	
	if( munmap( p_map, sizeof(people)*10 ) > 0)
		printf( "umap ok \n" );
	return 0;
}