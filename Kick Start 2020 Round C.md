# reference
[1.](https://mp.weixin.qq.com/s/YMC7mpYSMUIWKkvBzD5jbQ)

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
如何压缩耗时？How to compress time-consuming?
核心代码Core code:`if (mp.count(sum[i] - j * j)) ans += mp[sum[i] - j * j];`
```
idx 0   1   2   3   4   5   6
arr    30  30   9   1   30
pre 0  30  60  69  70   100
--------------------------------------------------
        |       |       ->         My Solution:
       p1       p2      -> dobule pointers O(n^2) 
--------------------------------------------------
                |
              <-| trun back       Refer Solution
```
这个方法好就好在，限定了搜索范围为`[minvalue~pre[i]]`，而且搜索步长为`i * i`。The good thing about this method is that the search range is limited to `[minvalue ~ pre [i]]`, and the search step size is `i * i`.

1. 前缀和的最小值，为跳出循环的条件。The minimum value of the prefix sum is the condition for break of the loop.因为`pre[i] - pre[j]`可以获得`[j,i)`的区间和，如果`per[j]`已经取得最小值，则区间和不可能更大。Because `pre [i]-pre [j]` can obtain the interval sum of `[j, i)`, if `per [j]` has already obtained the minimum value, the interval sum cannot be larger.再想上寻找已经没有意义了。It doesn't make sense to find upper again.

其实和leetcode的第一个twosum不是一样的嘛。In fact, it is not the same as the first twosum of leetcode.

以下是参考代码和调试打印。The following is the reference code and debug printing.
[Referring code](https://blog.csdn.net/tomjobs/article/details/106184623):
```cpp
#include <cstdio>
#include <cstring>
#include <map>
#include <algorithm>
#include <unordered_map>
using namespace std;

typedef long long ll;
const int maxn = 2e5 + 7;
const int INF = 1e7 + 7;

unordered_map<int, int> mp;
int a[maxn], sum[maxn];

int main() {
	int T; scanf("%d", &T);
	int kase = 0;
	while (T--) {
		int n; scanf("%d", &n);
		int mi = 0;
		for (int i = 1; i <= n; i++) {
			scanf("%d", &a[i]);
			sum[i] = sum[i - 1] + a[i];
			mi = min(mi, sum[i]);//First, set the minimum value for prefix
		}
		mp.clear();
		ll ans = 0;
		mp[0] = 1;
		printf("_______________\n");
		for (int i = 1; i <= n; i++) {
			for (int j = 0; j * j < INF; j++) {
				printf("i:%d |sum[i]:%d |j: %d | mp.size():%d | find:%d | ans:%d\n",i, sum[i],j,mp.size(), sum[i] - j * j,ans);
				if (mp.count(sum[i] - j * j)) ans += mp[sum[i] - j * j];
				if (sum[i] - j * j < mi) break;
			}
			printf("_______________\n");
			mp[sum[i]]++;
		}

		printf("Case #%d: %lld\n", ++kase, ans);
	}
	return 0;
}
```
```
3
3
2 2 6
_______________
i:1 |sum[i]:2 |j: 0 | mp.size():1 | find:2 | ans:0
i:1 |sum[i]:2 |j: 1 | mp.size():1 | find:1 | ans:0
i:1 |sum[i]:2 |j: 2 | mp.size():1 | find:-2 | ans:0
_______________
i:2 |sum[i]:4 |j: 0 | mp.size():2 | find:4 | ans:0
i:2 |sum[i]:4 |j: 1 | mp.size():2 | find:3 | ans:0
i:2 |sum[i]:4 |j: 2 | mp.size():2 | find:0 | ans:0
i:2 |sum[i]:4 |j: 3 | mp.size():2 | find:-5 | ans:1
_______________
i:3 |sum[i]:10 |j: 0 | mp.size():3 | find:10 | ans:1
i:3 |sum[i]:10 |j: 1 | mp.size():3 | find:9 | ans:1
i:3 |sum[i]:10 |j: 2 | mp.size():3 | find:6 | ans:1
i:3 |sum[i]:10 |j: 3 | mp.size():3 | find:1 | ans:1
i:3 |sum[i]:10 |j: 4 | mp.size():3 | find:-6 | ans:1
_______________
Case #1: 1
------------------------------------------------------------------
5
30 30 9 1 30
_______________
i:1 |sum[i]:30 |j: 0 | mp.size():1 | find:30 | ans:0
i:1 |sum[i]:30 |j: 1 | mp.size():1 | find:29 | ans:0
i:1 |sum[i]:30 |j: 2 | mp.size():1 | find:26 | ans:0
i:1 |sum[i]:30 |j: 3 | mp.size():1 | find:21 | ans:0
i:1 |sum[i]:30 |j: 4 | mp.size():1 | find:14 | ans:0
i:1 |sum[i]:30 |j: 5 | mp.size():1 | find:5 | ans:0
i:1 |sum[i]:30 |j: 6 | mp.size():1 | find:-6 | ans:0
_______________
i:2 |sum[i]:60 |j: 0 | mp.size():2 | find:60 | ans:0
i:2 |sum[i]:60 |j: 1 | mp.size():2 | find:59 | ans:0
i:2 |sum[i]:60 |j: 2 | mp.size():2 | find:56 | ans:0
i:2 |sum[i]:60 |j: 3 | mp.size():2 | find:51 | ans:0
i:2 |sum[i]:60 |j: 4 | mp.size():2 | find:44 | ans:0
i:2 |sum[i]:60 |j: 5 | mp.size():2 | find:35 | ans:0
i:2 |sum[i]:60 |j: 6 | mp.size():2 | find:24 | ans:0
i:2 |sum[i]:60 |j: 7 | mp.size():2 | find:11 | ans:0
i:2 |sum[i]:60 |j: 8 | mp.size():2 | find:-4 | ans:0
_______________
i:3 |sum[i]:69 |j: 0 | mp.size():3 | find:69 | ans:0
i:3 |sum[i]:69 |j: 1 | mp.size():3 | find:68 | ans:0
i:3 |sum[i]:69 |j: 2 | mp.size():3 | find:65 | ans:0
i:3 |sum[i]:69 |j: 3 | mp.size():3 | find:60 | ans:0
i:3 |sum[i]:69 |j: 4 | mp.size():3 | find:53 | ans:1
i:3 |sum[i]:69 |j: 5 | mp.size():3 | find:44 | ans:1
i:3 |sum[i]:69 |j: 6 | mp.size():3 | find:33 | ans:1
i:3 |sum[i]:69 |j: 7 | mp.size():3 | find:20 | ans:1
i:3 |sum[i]:69 |j: 8 | mp.size():3 | find:5 | ans:1
i:3 |sum[i]:69 |j: 9 | mp.size():3 | find:-12 | ans:1
_______________
i:4 |sum[i]:70 |j: 0 | mp.size():4 | find:70 | ans:1
i:4 |sum[i]:70 |j: 1 | mp.size():4 | find:69 | ans:1
i:4 |sum[i]:70 |j: 2 | mp.size():4 | find:66 | ans:2
i:4 |sum[i]:70 |j: 3 | mp.size():4 | find:61 | ans:2
i:4 |sum[i]:70 |j: 4 | mp.size():4 | find:54 | ans:2
i:4 |sum[i]:70 |j: 5 | mp.size():4 | find:45 | ans:2
i:4 |sum[i]:70 |j: 6 | mp.size():4 | find:34 | ans:2
i:4 |sum[i]:70 |j: 7 | mp.size():4 | find:21 | ans:2
i:4 |sum[i]:70 |j: 8 | mp.size():4 | find:6 | ans:2
i:4 |sum[i]:70 |j: 9 | mp.size():4 | find:-11 | ans:2
_______________
i:5 |sum[i]:100 |j: 0 | mp.size():5 | find:100 | ans:2
i:5 |sum[i]:100 |j: 1 | mp.size():5 | find:99 | ans:2
i:5 |sum[i]:100 |j: 2 | mp.size():5 | find:96 | ans:2
i:5 |sum[i]:100 |j: 3 | mp.size():5 | find:91 | ans:2
i:5 |sum[i]:100 |j: 4 | mp.size():5 | find:84 | ans:2
i:5 |sum[i]:100 |j: 5 | mp.size():5 | find:75 | ans:2
i:5 |sum[i]:100 |j: 6 | mp.size():5 | find:64 | ans:2
i:5 |sum[i]:100 |j: 7 | mp.size():5 | find:51 | ans:2
i:5 |sum[i]:100 |j: 8 | mp.size():5 | find:36 | ans:2
i:5 |sum[i]:100 |j: 9 | mp.size():5 | find:19 | ans:2
i:5 |sum[i]:100 |j: 10 | mp.size():5 | find:0 | ans:2
i:5 |sum[i]:100 |j: 11 | mp.size():5 | find:-21 | ans:3
_______________
Case #2: 3
------------------------------------------------------------------
4
4 0 0 16
_______________
i:1 |sum[i]:4 |j: 0 | mp.size():1 | find:4 | ans:0
i:1 |sum[i]:4 |j: 1 | mp.size():1 | find:3 | ans:0
i:1 |sum[i]:4 |j: 2 | mp.size():1 | find:0 | ans:0
i:1 |sum[i]:4 |j: 3 | mp.size():1 | find:-5 | ans:1
_______________
i:2 |sum[i]:4 |j: 0 | mp.size():2 | find:4 | ans:1
i:2 |sum[i]:4 |j: 1 | mp.size():2 | find:3 | ans:2
i:2 |sum[i]:4 |j: 2 | mp.size():2 | find:0 | ans:2
i:2 |sum[i]:4 |j: 3 | mp.size():2 | find:-5 | ans:3
_______________
i:3 |sum[i]:4 |j: 0 | mp.size():2 | find:4 | ans:3
i:3 |sum[i]:4 |j: 1 | mp.size():2 | find:3 | ans:5
i:3 |sum[i]:4 |j: 2 | mp.size():2 | find:0 | ans:5
i:3 |sum[i]:4 |j: 3 | mp.size():2 | find:-5 | ans:6
_______________
i:4 |sum[i]:20 |j: 0 | mp.size():2 | find:20 | ans:6
i:4 |sum[i]:20 |j: 1 | mp.size():2 | find:19 | ans:6
i:4 |sum[i]:20 |j: 2 | mp.size():2 | find:16 | ans:6
i:4 |sum[i]:20 |j: 3 | mp.size():2 | find:11 | ans:6
i:4 |sum[i]:20 |j: 4 | mp.size():2 | find:4 | ans:6
i:4 |sum[i]:20 |j: 5 | mp.size():2 | find:-5 | ans:9
_______________
Case #3: 9
```
# Candies
这题是不是有什么套路呀，大家都这样做Is there any routine for this question, everyone does this

[*22 May 2020*]
## line tree: 
reference: [线段树详解](https://www.cnblogs.com/AC-King/p/7789013.html)、[线段树从零开始](https://blog.csdn.net/zearot/article/details/52280189)、[本题讲解](https://blog.csdn.net/tomjobs/article/details/106184670)
关于线段树的基本概念和图解上述第二个链接说的挺好的了。The basic concept and illustration of the line tree is quite good. 以下是一些细节Here are some details

### 存储结构
可类比完全二叉树的数组存储结构。The storage structure can be compared with the array storage structure of the complete binary tree. 每个节点存储的是一个区间的和（或者其他的什么都可以）Each node stores the sum of an interval (or anything else)
```
[ 0 1 2 3 4 5 6 7 8 9 10 11 12 13 14 15 16] -> the index of array.
-> Line Tree : complete binary Tree
              0[1,5]
		/              \
		1[1,3]          2[4,5]
	/       \       /      \
	3[1,2]  4      5        6
  /   \   /   \  /    \   /    \
  7   8   9   10 11   12  13   14
 / \ / \ / \ / \/ \   / \/ \   / \
15 16 ...
```
![图示](https://img-blog.csdn.net/20150909172350036?watermark/2/text/aHR0cDovL2Jsb2cuY3Nkbi5uZXQv/font/5a6L5L2T/fontsize/400/fill/I0JBQkFCMA==/dissolve/70/gravity/SouthEast)
### construct
构造是从下到上的（树的角度）。The structure is from bottom to top (tree perspective).
```cpp
#define maxn 100007  //元素总个数  
int Sum[maxn<<2];//Sum求和，开四倍空间
int A[maxn],n;//存原数组下标[1，n]

//PushUp函数更新节点信息，这里是求和
void PushUp(int rt){
    Sum[rt]=Sum[rt<<1]+Sum[rt<<1|1];
}
//Build函数建立线段树
void Build(int l,int r,int rt){ //[l,r]表示当前节点区间，rt表示当前节点的实际存储位置 
    if(l==r) {//若到达叶节点 
        Sum[rt]=A[l];//存储A数组的值
        return;
        }
    int m=(l+r)>>1; 
    //左右递归
    Build(l,m,rt<<1); //左子树
    Build(m+1,r,rt<<1|1); //右节点
    //更新信息
    PushUp(rt); //根据左右节点的值更新父节点
}

```


## refer code:
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