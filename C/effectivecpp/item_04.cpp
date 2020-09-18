#include<bits/stdc++.h>

using namespace std;

class A{
public:
    int a;
    int b;
    A(int _a):a(_a),b(_a){ printf("[line %d]: constructor \n", __LINE__); }
// private:
    // A& operator=(const A& oth) = delete;
};


int main(){
    A t(9);
    printf("[line %d]: address of size: %p \n", __LINE__, &t.a, &t.b);
    A t1(10);
    t1 = t;
    printf("[line %d]: address of size: %p \n", __LINE__, &t1.a, &t1.b);
    return 0;
}


