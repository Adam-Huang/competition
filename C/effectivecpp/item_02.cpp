#include<bits/stdc++.h>

using namespace std;

#define CALL_WITH_MAX(a,b) ((a) > (b) ?  (a) : (b))

inline int call_with_max(int a, int b){
    return a > b? a: b;
}

enum state{
    Hello = 5,
    world
};

int main(){
    // state t = Hello;
    // printf("[line %d]: address of enum is %p %d", __LINE__, &t, t);
    
    int a = 5, b = 0;
    CALL_WITH_MAX(++a,b);
    printf("[line %d]: value of a: %d, value of b: %d \n", __LINE__,a, b);
    
    CALL_WITH_MAX(++a,b + 10);
    printf("[line %d]: value of a: %d, value of b: %d \n", __LINE__,a, b);
    
    call_with_max(++a,b);
    printf("[line %d]: value of a: %d, value of b: %d \n", __LINE__,a, b);
    
    call_with_max(++a,b + 10);
    printf("[line %d]: value of a: %d, value of b: %d \n", __LINE__,a, b);
    return 0;
}

