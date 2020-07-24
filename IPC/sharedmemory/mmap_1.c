/*-------------map_normalfile1.c-----------*/
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

int main(int argc, char** argv) // map a normal file as shared mem:
{
	int fd,i;
	people *p_map;
	char temp;

	fd = open("./test_mmap",O_RDWR|O_CREAT|O_TRUNC,0644);

	/*lseek(fd,sizeof(people)*5 - 1,SEEK_SET);
	write(fd,"",1); // 这是在扩展文件大小吧 video中有以下两个方法：
	
	
	lseek(fd,10,SEEK_END);
	write(fd,"\0",1);

	or:*/
	ftruncate(fd, sizeof(people) * 5);
	int len = lseek(fd,0,SEEK_END); // 获取文件长度

	p_map = (people*) mmap( NULL, len , PROT_READ|PROT_WRITE, MAP_SHARED, fd, 0 );
	
	if(p_map == MAP_FAILED){
		perror("mmap error");
		exit(-1);
	}
	printf("[Line:%d]: address: %p value: 0x%llx\n",__LINE__,p_map,*p_map);
	
	close( fd );
	temp = 'a';
	for(i=0; i<10; i++)
	{
		temp += 1;
		memcpy( ( *(p_map+i) ).name, &temp, 2 );
		( *(p_map+i) ).age = 20 + i;
	}
	printf(" initialize over \n ");
	
	sleep(10);
	
	if( munmap( p_map, sizeof(people) * 10 ) > 0)
		printf( "umap ok \n" );
	
	return 0;
}