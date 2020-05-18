# Countdown
Easy question. Time complexity is at most `10^7`.

# Stable Wall
当时题目没看懂，先做了后面的题目。第四题花了太久时间，导致也没时间做这一题了。I didn't understand the questions at that time, so I did the following questions first.The fourth question took too long, so there was no time to do this question.

我能想到的居然是模拟？参考了[别人的代码](https://codingcompetitions.withgoogle.com/kickstart/submissions/000000000019ff43/SGVsdGlvbg)区别如下：What I can think of is actually simulation? The difference between referring to others' code is as follows:
1. 数组的输入可以这样。The input of array can be like this:
```cpp
char s[maxn][maxn];
for(int i = 0; i < R; i += 1) cin >> s[i];
```
2. 不需要挨个尝试各种可能，可以在遍历时直接记录`A`的下面是否还是`A`，如果是就继续，不是就需要记录。You don't need to try every possibility one by one. You can directly record whether `A` is still under `A` during traversal.  记录内容可以简化成两个：第一，`A`依赖多少个其他字母；第二，`A`被谁依赖了。The content of the record can be simplified into two: first, how many other letters `A` depends on; second, who depends on `A`. 开始处理，Start processing, 首先放置无依赖项的字母`A`，同时处理刚刚记录（除去依赖）数据中依赖字母`A`的项。First place the letter A without dependencies, and process (remove dependencies) the items that depend on the letter A in the data that was just recorded .
```cpp
#include<bits/stdc++.h>
using namespace std;
using LL = long long;

void work(){
    int R = 0, C = 0;
    cin >> R >> C;
    set<int> st;
    vector<vector<char>> A(R,vector<char>(C));
    for(int i = 0; i < R; i++){
        for(int j = 0; j < C; ++j) {
            cin >> A[i][j];
            st.insert(A[i][j] - 'A');
        }
    }
    vector<int> dep(26,0);
    vector<vector<int>> G(26);
    for(int i = 0; i < R - 1; i++){
        for(int j = 0; j < C; ++j) {
            if(A[i][j] != A[i + 1][j]){
                dep[A[i][j] - 'A']++;
                G[A[i + 1][j] - 'A'].push_back(A[i][j] - 'A');
            }
        }
    }
    queue<int> q;
    for(int i = 0; i < 26; ++i) if(!dep[i] && st.find(i) != st.end()) q.push(i);
    
    string ans;
    while(q.size()){
        int now = q.front(); q.pop();
        ans.push_back(now + 'A');
        for(auto v: G[now]) if(--dep[v] == 0) q.push(v);
    }
    
    if(ans.size() == st.size()) cout << ans << "\n";
    else cout << "-1\n";
}
int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);
    int T;
    cin >> T;
    for(int t = 1; t <= T; t += 1){
        cout << "Case #" << t << ": ";
        work();
    }
    return 0;
}
```
=。=！以后不要傻呵呵的模拟，重要的是保留相互关系。Don't imitate silly simulations in the future, the important thing is to preserve the relationship.

# Perfect Subarray

# Candies
这题是不是有什么套路呀，大家都这样做Is there any routine for this question, everyone does this
refer 1:
```cpp
#include<bits/stdc++.h>
using namespace std;
using LL = long long;
constexpr int maxn = 200000;
#define ls (v << 1)
#define rs (ls | 1)
#define tm ((tl + tr) >> 1)
LL A[maxn + 1];
struct Node{
    LL ans, sum, size;
    Node operator + (const Node& node)const{
        Node res;
        res.size = size + node.size;
        if(size & 1) res.sum = sum - node.sum;
        else res.sum = sum + node.sum;
        if(size & 1) res.ans = ans - node.ans - size * node.sum;
        else res.ans = ans + node.ans + size * node.sum;
        return res; 
    }
}T[maxn << 2];
void build(int v, int tl, int tr){
    if(tl == tr){
        T[v].size = 1;
        T[v].ans = T[v].sum = A[tm];
    }
    else{
        build(ls, tl, tm);
        build(rs, tm + 1, tr);
        T[v] = T[ls] + T[rs];
    }
}
void update(int v, int tl, int tr, int x, int V){
    if(tl == tr)
        T[v].ans = T[v].sum = V;
    else{
        if(x <= tm) update(ls, tl, tm, x, V);
        else update(rs, tm + 1, tr, x, V);
        T[v] = T[ls] + T[rs];
    }
}
Node query(int v, int tl, int tr, int L, int R){
    if(tl >= L and tr <= R) return T[v];
    if(R <= tm) return query(ls, tl, tm, L, R);
    if(L > tm) return query(rs, tm + 1, tr, L, R);
    return query(ls, tl, tm, L, R) + query(rs, tm + 1, tr, L, R);
}
void work(){
   int N, Q;
   cin >> N >> Q;
   for(int i = 1; i <= N; i += 1) cin >> A[i];
   build(1, 1, N);
   LL ans = 0;
   for(int i = 1; i <= Q; i += 1){
       string s;
       cin >> s;
       if(s == "U"){
           LL X, V;
           cin >> X >> V;
           update(1, 1, N, X, V);
       }
       else{
           int L, R;
           cin >> L >> R;
           //cout << query(1, 1, N, L, R).ans << "\n";
           ans += query(1, 1, N, L, R).ans;
       }
   }
   cout << ans << "\n";
}
int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);
    int T;
    cin >> T;
    for(int t = 1; t <= T; t += 1){
        cout << "Case #" << t << ": ";
        work();
    }
    return 0;
}
```

refer 2:
```cpp
#include <iostream>
#include <cstdio>
#include <vector>
#include <algorithm>
#include <cstring>
#include <string>
#include <queue>
using namespace std;
long long ans;
int ql, qr, qx;
long long s1, s2;
const int maxn = 1000010;
#define L (2 * x)
#define R (2 * x + 1)
struct node{
  long long sum1;
  long long sum2;
  long long sum3;
  long long sum4;
  //int l,r;//l=2x, r=2x+1
}tr[maxn*4];//Note:*4
void upd(int x) {
  tr[x].sum1 = tr[x*2].sum1 + tr[x*2+1].sum1;
  tr[x].sum2 = tr[x*2].sum2 + tr[x*2+1].sum2;
  tr[x].sum3 = tr[x*2].sum3 + tr[x*2+1].sum3;
  tr[x].sum4 = tr[x*2].sum4 + tr[x*2+1].sum4;

}
void Insert(int x, int l, int r, int ql, int qr, long long qx){//结点编号x表示区间[l,r] //操作区间[ql,qr] 如果修改：qx表示加了qx大小
  if(ql<=l && qr>=r){
    if (ql % 2 == 1) {
      tr[x].sum1 = qx;
      tr[x].sum3 = qx * ql;
    } else {
      tr[x].sum2 = qx;
      tr[x].sum4 = qx * ql;
    }
    return;
  }
  int mid = (l+r) / 2;
  if(ql<=mid) Insert(L, l, mid, ql, qr, qx);
  if(mid+1<=qr) Insert(R, mid + 1, r, ql, qr, qx);
  upd(x);
}

void Query(int x, int l, int r, int ql, int qr){//结点编号x表示区间[l,r] //操作区间[ql,qr] 如果修改：qx表示加了qx大小
  if(ql<=l && qr>=r){
    s1 += -tr[x].sum1 * (ql  - 1) + tr[x].sum3;
    s2 += -tr[x].sum2 * (ql  - 1) + tr[x].sum4;
    return;
  }
  int mid = (l+r) / 2;
  if(ql<=mid) Query(L, l, mid, ql, qr);
  if(mid+1<=qr) Query(R, mid + 1, r, ql, qr);
  upd(x);
}

void solve(){
  memset(tr, 0, sizeof(tr));
  int n,m;
  cin>>n>>m;
  for(int i = 1;i <= n;i++) {
    cin>>qx;
    ql=qr=i;
    Insert(1, 1, n, ql, qr, qx);
  }
  ans = 0;
  for(int i=1;i<=m;i++){
    char x;
    cin>>x;
    //cout << "x="<<x << endl;
    while (x!='U' && x !='Q') cin >> x;

    if(x=='U') {
      cin>>ql>>qx;
      qr = ql;
      Insert(1, 1, n, ql, qr, qx);
    }
    else if (x == 'Q'){
      cin>>ql>>qr;
      s1 = 0, s2 = 0;
      Query(1, 1, n, ql, qr);
      //cout << s1 <<" " <<s2 << endl;
      if (ql % 2 == 0) ans  += s2 - s1;
      else ans += s1 - s2;
      //cout << ans <<endl;
    }
  }
  cout << ans <<endl;
}

int main() {
 
  ios_base::sync_with_stdio(false);
  cin.tie(NULL); cout.tie(NULL);
  int t;
  cin >> t;
  for(int casenum = 1; casenum <= t; casenum++) {
    cout << "Case #" << casenum << ": ";
    solve();
  }
}
```