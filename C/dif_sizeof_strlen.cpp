#include <iostream>

using namespace std;

void Test(int Array[],int Size)
{
    //作为参数传递时，数组作为指针，sizeof(Array) == 8
    int Num = sizeof(Array) / sizeof(int);
    for(int i = 0;i < Num && i < Size;i++){
        cout << Array[i] << " ";
    }
    cout << endl;
}

int main(){

    char *string1 = "tencent20188888888";
    int size1 = sizeof(string1);            //8 是指针的大小
    cout << size1 << endl;
    int size2 = sizeof(*string1);           //1 是char的大小
    cout << size2 << endl;
    char string2[100] = "tencent2018";
    int size3 = sizeof(string2);            //100，并不是把string2当成一个指针处理
    char string3[] = "hello";               
    int size4 = sizeof(string3);            //6，保存结尾\0

    int arr1[] = {1,2,3,4};
    int arr2[10] = {1};
    cout << sizeof(arr1) << endl;           //16，没有当作指针 4 * 4
    cout << sizeof(arr2) << endl;           //40，没有当作指针 4 * 10

    Test(arr1, sizeof(arr1)/sizeof(int));

    return 0;
}

/* --> more: https://www.cnblogs.com/carekee/articles/1630789.html

sizeof 是运算符，在头文件中typedef为unsigned int，其值在编译时即计算好了，参数可以是数组、指针、类型、对象、函数等。
strlen(...)是函数，要在运行时才能计算。参数必须是字符型指针（char*）。当数组名作为参数传入时，实际上数组就退化成指针了。
*/

