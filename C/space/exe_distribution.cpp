#include <stdio.h>
#include <malloc.h>
#include <unistd.h>

int g_var;         //bss
int data_var0 = 1; //初始化数据

static int s_gvar;

const int cdw_var = 10;
constexpr int cdw_var2 = 20;

class TestStatic
{
public:
	int fuc();
	int p;
	static int s_dwCount;
	void addfuc();
};

int TestStatic::s_dwCount = 30;

void TestStatic::addfuc()
{
	printf("s_dwCount addr: %llX, value: %d \n", &s_dwCount, s_dwCount);// s_dwCount addr: 601050, value: 30 KEY1
	s_dwCount++;
}

int TestStatic::fuc() {
	void (TestStatic::*paf)() = &TestStatic::addfuc;
	printf("[__LINE__:%d] 0x%llX\n",__LINE__,paf);//0x4006F6
	printf("[__LINE__:%d] 0x%llX\n",__LINE__,&paf);// 0x7FFF4CA0F900 KEY4
	printf("[__LINE__:%d] 0x%llX\n",__LINE__,(void *&) paf);//0x4006F6
	printf("[__LINE__:%d] 0x%p\n",__LINE__,&TestStatic::addfuc); //0x4006F6 %p -> 指针的值 
	printf("[__LINE__:%d] 0x%llX\n",__LINE__,&TestStatic::addfuc);//0x4006F6 KEY3
	return 0;
}

int main(){
	printf("[__LINE__:%d] Address of main(Code Segment):%p\n",__LINE__,main);// 0x400871
	
	printf("[__LINE__:%d] Data Location: Address of data_var(Data Segment):%p\n",__LINE__,&data_var0); // 0x602058
	static int data_var1=4;
	printf("[__LINE__:%d] Local static variable: Address of data_var(Data Segment):%p\n",__LINE__,&data_var1); // 0x602060
	
	printf("[__LINE__:%d] BSS Location: g_var: 0x%llX, value:%d\n",__LINE__,&g_var,g_var); //   g_var: 0x602068, value:0
	printf("[__LINE__:%d] s_gvar: 0x%llX, value:%d\n",__LINE__,&s_gvar,s_gvar);//s_gvar: 0x60206C, value:0 KEY1
	
	int* p1 = (int*)&cdw_var;
	int* p2 = (int*)&cdw_var2;
	printf("[__LINE__:%d] p1: 0x%llX, value:0x%llX\n",__LINE__,&p1,p1); //p1: 0x7FFF4CA0F950, value:400A18
	printf("[__LINE__:%d] p2: 0x%llX, value:0x%llX\n",__LINE__,&p2,p2); //p2: 0x7FFF4CA0F958, value:400A1C KEY2
	
	char *b = (char *)sbrk((ptrdiff_t)0);
	printf("[__LINE__:%d] Heap Location: Initial end of heap:%p\n",__LINE__,b); // 0x259d000 KEY7
	
	TestStatic* t = new TestStatic;
	t->addfuc();
	t->fuc();
	printf("[__LINE__:%d]: the object address:0x%llX\n", __LINE__,t);//1777030 
	printf("[__LINE__:%d]: the object variable address:0x%llX\n", __LINE__,&t); // 7FFF4CA0F960 stack address
	
	printf("[__LINE__:%d]: the first variable address:0x%llX\n", __LINE__,&(t->p));//1777030 KEY5
	delete t; t = nullptr;
	
	return 0;
}
/*
(base) ejior@ejior-XPS-8930:~/huangyue/linuxcode$ ./exe
[__LINE__:41] Address of main(Code Segment):0x400871
[__LINE__:43] Data Location: Address of data_var(Data Segment):0x602058
[__LINE__:45] Local static variable: Address of data_var(Data Segment):0x602060
[__LINE__:47] BSS Location: g_var: 0x602068, value:0
[__LINE__:48] s_gvar: 0x60206C, value:0
[__LINE__:52] p1: 0x7FFD9B58C038, value:0x400AC8
[__LINE__:53] p2: 0x7FFD9B58C040, value:0x400ACC
[__LINE__:56] Heap Location: Initial end of heap:0x105d000
s_dwCount addr: 60205C, value: 30 
[__LINE__:32] 0x400736
[__LINE__:33] 0x7FFD9B58BFE0
[__LINE__:34] 0x400736
[__LINE__:35] 0x0x400736
[__LINE__:36] 0x400736
[__LINE__:61]: the object address:0x103D030
[__LINE__:62]: the object variable address:0x7FFD9B58C048
[__LINE__:64]: the first variable address:0x103D030
*/
