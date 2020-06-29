#include<stdio.h>

int g_var;

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
	printf("[__LINE__:%d] g_var: 0x%llX, value:%d\n",__LINE__,&g_var,g_var); //   g_var: 0x601058, value:0
	printf("[__LINE__:%d] s_gvar: 0x%llX, value:%d\n",__LINE__,&s_gvar,s_gvar);//s_gvar: 0x60105C, value:0 KEY1
	
	int* p1 = (int*)&cdw_var;
	int* p2 = (int*)&cdw_var2;
	printf("[__LINE__:%d] p1: 0x%llX, value:0x%llX\n",__LINE__,&p1,p1); //p1: 0x7FFF4CA0F950, value:400A18
	printf("[__LINE__:%d] p2: 0x%llX, value:0x%llX\n",__LINE__,&p2,p2); //p2: 0x7FFF4CA0F958, value:400A1C KEY2
	
	TestStatic* t = new TestStatic;
	t->addfuc();
	t->fuc();
	printf("[__LINE__:%d]: the object address:%0xllX\n", __LINE__,t);//1777030 
	printf("[__LINE__:%d]: the object variable address:%0xllX\n", __LINE__,&t); // 7FFF4CA0F960 stack address
	
	printf("[__LINE__:%d]: the first variable address:%0xllX\n", __LINE__,&(t->p));//1777030 KEY5
	delete t; t = nullptr;
	
	return 0;
}

