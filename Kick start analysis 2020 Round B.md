# Kick start analysis Round B
## Bike Tour
### Problem

Li has planned a bike tour through the mountains of Switzerland. His tour consists of  **N**  checkpoints, numbered from 1 to  **N**  in the order he will visit them. The i-th checkpoint has a height of  **Hi**.

A checkpoint is a  _peak_  if:

-   It is not the 1st checkpoint or the  **N**-th checkpoint, and
-   The height of the checkpoint is  _strictly greater than_  the checkpoint immediately before it and the checkpoint immediately after it.

Please help Li find out the number of peaks.

Input

The first line of the input gives the number of test cases,  **T**.  **T**  test cases follow. Each test case begins with a line containing the integer  **N**. The second line contains  **N**  integers. The i-th integer is  **Hi**.

Output

For each test case, output one line containing  `Case #x: y`, where  `x`  is the test case number (starting from 1) and  `y`  is the number of peaks in Li's bike tour.

Limits

Time limit: 10 seconds per test set.  
Memory limit: 1GB.  
1 ≤  **T**  ≤ 100.  
1 ≤  **Hi**  ≤ 100.  

Test set 1

3 ≤  **N**  ≤ 5.  

Test set 2

3 ≤  **N**  ≤ 100.

My Solution is trying to calculate the difference in the array, and see the max value.

```c++
#include <vector>
#include <algorithm>
#include <iostream>
#include <memory.h>

void a() {
	int T = 0, t = 1, i = 0, nNums = 0, sum = 0;
	//FILE *stream1;//
	//freopen_s(&stream1, "D:\\handsome\\VS\\Project\\KSdata\\2020\\round_b\\a.in", "r", stdin);
	std::cin >> T;
	for (; t <= T; ++t) {
		std::cin >> nNums;
		sum = 0;
		if (nNums > 2) {
			int * aHeight = new int[nNums];
			int * aDif = new int[nNums];
			memset(aDif, 0, sizeof(int) * nNums);
			for (i = 0; i < nNums; ++i) {
				std::cin >> aHeight[i];
				if (i > 0) { aDif[i - 1] = aHeight[i] - aHeight[i - 1]; }
			}
			for (i = 0; i < nNums - 1; ++i) {
				if (aDif[i] > 0 && aDif[i + 1] < 0) ++sum;
			}
			delete[] aHeight; aHeight = nullptr;
			delete[] aDif; aDif = nullptr;
		}
		
		std::cout << "Case #" << t << ": " << sum << std::endl;
	}
}

int main()
{
 a();
	return 0;
}

```

but actually, it's not necessrily to calcuate the difference, below is others code.
```c++
#include<bits/stdc++.h>
using namespace std;
using LL = long long;
constexpr int maxn = -1;
int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);
    int T;
    cin >> T;
    for(int _ = 1; _ <= T; _ += 1){
        int N, ans = 0;
        cin >> N;
        vector<int> v(N);
        for(int &x : v) cin >> x;
        for(int i = 1; i + 1 < N; i += 1)
            ans += v[i] > v[i - 1] and v[i] > v[i + 1];
        cout << "Case #" <<  _ << ": " << ans << "\n";
    }
    return 0;
}
```
**bits/stdc++.h** 
> Linux GCC 4.8.0 [/bits/stdc++.h](https://gist.github.com/eduarc/6022859) header definition.
> `#include  <bits/stdc++.h>`  is an implementation file for a precompiled header.
> From, software engineering perspective, it is a good idea to minimize the include. If you use it actually includes a lot of files, which your program may not need, thus increase both compile time and program size unnecessarily.
> But in contests, using this file is a good idea, when you want to reduce the time wasted in doing chores; especially when your rank is time sensitive.

above is from[What is the file bits/stdc++.h?](https://www.quora.com/What-is-the-file-bits-stdc++-h)


**ios::sync_with_stdio(false);**
>  cin慢是有原因的，其实默认的时候，cin与stdin总是保持同步的，也就是说这两种方法可以混用，而不必担心文件指针混乱，同时cout和stdout也一样，两者混用不会输出顺序错乱。正因为这个兼容性的特性，导致cin有许多额外的开销，如何禁用这个特性呢？只需一个语句`std::ios::sync_with_stdio(false);`，这样就可以取消cin于stdin的同步了。

————————————————
from [https://blog.csdn.net/qq_33248299/article/details/52144485](https://blog.csdn.net/qq_33248299/article/details/52144485) and other reference:[用ios::sync_with_stdio(false)有什么坏处？ Zhihu](https://www.zhihu.com/question/62041072)

> 取消后就cin就不能和scanf，sscanf, getchar, fgets之类同时用了，否则就可能会导致输出和预期的不一样。
> 取消同步的目的，是为了让cin不超时，另外cout的时候尽量少用endl，换用”\n”，也是防止超时的方法。
> 当然，尽量用scanf，printf就不用考虑这种因为缓冲的超时了。
```c++
//lambda 表达式，可以立即执行，在main函数之前执行，取消输入输出同步，较快输入输出速度
int x = []() {
    std::ios::sync_with_stdio(false);
    cin.tie(NULL);
    return 0;
}();

class Solution {
public:
    bool isPalindrome(int x) {
        if(x<0) return false;
        int sum=0,n=x;
        while(n>0){
            sum=sum*10+n%10;
            n=n/10;
        }
        if(x==sum) return true;
        else return false;
    }
};
```
————————————————
[[C++] std::ios::sync_with_stdio(false); cin.tie(NULL);](https://blog.csdn.net/lv1224/article/details/80084840)

**cin.tie(nullptr);**

> 原来而cin，cout之所以效率低，是因为先把要输出的东西存入缓冲区，再输出，导致效率降低，而这段语句可以来打消iostream的输入 输出缓存，可以节省许多时间，使效率与scanf与printf相差无几，还有应注意的是scanf与printf使用的头文件应是stdio.h而不是 iostream。
> 在默认的情况下cin绑定的是cout，每次执行 << 操作符的时候都要调用flush，这样会增加IO负担。可以通过tie(0)（0表示NULL）来解除cin与cout的绑定，进一步加快执行效率。


Below is a good competetion structure.
```c++
#include <bits/stdc++.h>

using namespace std;
typedef long long ll;

int N;
int arr[110];

void gogo()
{
    cin >> N;
    for (int i = 0; i < N; i++)
        cin >> arr[i];

    int ans = 0;
    for (int i = 1; i < N - 1; i++)
        if (arr[i] > arr[i-1] && arr[i] > arr[i+1])
            ans++;
    cout << ans << "\n";
}

int main()
{
    ios_base::sync_with_stdio(0);

    int T; cin >> T;
    for (int i = 0; i < T; i++)
    {
        cout << "Case #" << i + 1 << ": ";
        gogo();
    }
}
```

In conclusion, there is no necessarily to apply a memory the save the difference.

## Bus Rotues

### Problem

Bucket is planning to make a very long journey across the countryside by bus. Her journey consists of  **N**  bus routes, numbered from 1 to  **N**  in the order she must take them. The buses themselves are very fast, but do not run often. The i-th bus route only runs every  **Xi**  days.

More specifically, she can only take the i-th bus on day  **Xi**, 2**Xi**, 3**Xi**  and so on. Since the buses are very fast, she can take multiple buses on the same day.

Bucket must finish her journey by day  **D**, but she would like to start the journey as late as possible. What is the latest day she could take the first bus, and still finish her journey by day  **D**?

It is guaranteed that it is possible for Bucket to finish her journey by day  **D**.

Input

The first line of the input gives the number of test cases,  **T**.  **T**  test cases follow. Each test case begins with a line containing the two integers  **N**  and  **D**. Then, another line follows containing  **N**  integers, the i-th one is  **Xi**.

Output

For each test case, output one line containing  `Case #x: y`, where  `x`  is the test case number (starting from 1) and  `y`  is the latest day she could take the first bus, and still finish her journey by day  **D**.

Limits

Time limit: 10 seconds per test set.  
Memory limit: 1GB.  
1 ≤  **T**  ≤ 100.  
1 ≤  **Xi**  ≤  **D**.  
1 ≤  **N**  ≤ 1000.  
It is guaranteed that it is possible for Bucket to finish her journey by day  **D**.  

Test set 1

$1 ≤  D ≤ 100$.  

Test set 2

$1 ≤  D  ≤ 1012$.

My solution: small AC and large WA
```c++
#include <vector>
#include <algorithm>
#include <iostream>


void b() {
	int T = 0, t = 1, i = 0, ntemp = 0, nNums = 0,  sum = 0, pre = 0;
	long long nDay = 0;
	//FILE *stream1;//
	//freopen_s(&stream1, "D:\\handsome\\VS\\Project\\KSdata\\2020\\round_b\\b.in", "r", stdin);
	std::cin >> T;
	for (; t <= T; ++t) {
		std::cin >> nNums >> nDay;
		sum = 0;
		pre = 0;
		long long *aXi = new long long[nNums];
		for (i = 0; i < nNums; ++i) {
			std::cin >> aXi[i];
			//sum = (sum > (aXi[i] - nDay % aXi[i])) ? sum : (aXi[i] - nDay % aXi[i]);
		}
		// from last to first, I calculate the last time he start
		// cause he need travel the city in order, so the last city he travel
		// can't be beyonded
		for (i = nNums - 1; i >= 0; --i) {
			sum = (nDay - pre) % aXi[i];// i-th must start before the nDay-pre
			sum += pre;// add to now before
			pre = sum;
		}
		std::cout << "Case #" << t << ": " << nDay - sum << std::endl;
	}
}

int main()
{
 b();
	return 0;
}

```
### Analysis

We need to take the buses in order from 1 to  **N**. Let the buses be B1, B2, ...., B**N**. Also, let us define a  _good starting day_  to be any day Y in the range [1..**D**] such that it is possible to start the journey on day Y and take all buses in the order from 1 to  **N**  before the end of day  **D**. Note that we do not require Y to be a multiple of  **X1**, so there may be some waiting time involved in the beginning of the journey.

For a fixed day Y, let us see if it is a good starting day or not. The best strategy would be to take bus B1  as early as possible on or after day Y. This is because it would give us more days to take subsequent buses. Let us say we took bus B1  on day D1. Now the best strategy would be to take bus B2  as early as possible on or after day D1. Thus, if we took bus Bi  on day Di, it would be optimal to take bus Bi+1  as early as possible on or after day Di.

Now we need to find out what is the earliest possible day for Bucket to take bus Bi  on or after a particular day K. Since bus Bi  only runs on days that are multiples of  **Xi**, we need to find the smallest multiple of  **Xi**  greater than or equal to K. This can be calculated using the formula ⌈ K /  **Xi**  ⌉ *  **Xi**. Thus if bus Bi  is taken on day Di, then it would be optimal to take bus Bi+1  on day Di+1  = ⌈ Di  /  **Xi+1**  ⌉ *  **Xi+1**. Thus, day Y is a good starting day if D**N**  ≤  **D**, and this question can be answered in O(**N**) time.

Test set 1

**D**  can be at most 100, so we can find the latest good starting day by using the above approach for each day Y in the range [1..**D**]. The time complexity of this naive algorithm is O(**DN**).

Test set 2

Now  **D**  can be at most 1012, so the naive algorithm would time out. Consider the largest good starting day P. Obviously, any day before P would be good as well because we can take the buses on the same days as if we started the journey on day P. Because of this observation, we can binary search on the range from 1 to  **D**  to find the largest good starting day P. The time complexity of the solution is O(**N**  log  **D**). Note that we can reduce the time complexity to O(**N**  log(**D**/**X1**)) by restricting the search to multiples of  **X1**  only.

### Alternate solution

It is possible to solve the problem in linear time by working out the solution backwards. If we want to start our journey as late as possible, we should try to take the last bus B**N**  as late a possible, namely, on day D**N**, which is the largest multiple of  **XN**, less than or equal to day  **D**. Similarly, in order to be on time for the last bus on day D**N**, we have to take bus B**N**-1  no later than on day D**N**-1, which is the largest multiple of  **X**N**-1**, less than or equal to D**N**. In general, bus Bi  should be taken no later than on day Di, which is the largest multiple of  **Xi**, less than or equal to Di+1. The last calculated value D1  is the answer to the problem.

Note that the largest multiple of  **Xi**  that occurs before a day L can be calculated in constant time as L - L mod  **Xi**. Therefore, the overall time complexity of this solution is O(**N**)



### Others

```c++
#include <bits/stdc++.h>

using namespace std;
typedef long long ll;

int N;
ll D;
ll X[1010];// 

bool works (ll K)
{
    for (int i = 0; i < N; i++)
    {
        if (K % X[i] != 0)
            K += (X[i] - K % X[i]);
            // couldn't start at K days, must start before, K % X[i] is K difference with 
            // n*X[i]. And the X[i] mintus that is
            // Let's start with sample:
            // 3 7 2 and 10
            // K = 5, 3 - 5 % 3 = 1
            // K = 6, 7 - 6 % 7 = 1
            // K = 7, 2 - 7 % 2 = 1
            // K = 8 <= D; return ture;
    }
    return K <= D;
}

void gogo()
{
    cin >> N >> D;
    for (int i = 0; i < N; i++)
        cin >> X[i];

    ll lo = 0, hi = D;
    while (lo < hi)
    {
        ll mid = (lo + hi + 1) / 2;// Why there is added 1
        if (works (mid))// binary search, is the point of `mid` satisfed to meet the conditions?
            lo = mid;// Yes, to find in right
        else
            hi = mid - 1;// no, find in left
    }

    cout << lo << "\n";
}

int main()
{
    ios_base::sync_with_stdio(0);

    int T; cin >> T;
    for (int i = 0; i < T; i++)
    {
        cout << "Case #" << i + 1 << ": ";
        gogo();
    }
}
```

```c++
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;


int main() {
  ios::sync_with_stdio(0); cin.tie(0);
  int t;
  cin >> t;
  int cc = 1;
  while (t--) {
    cout << "Case #" << cc++ << ": ";
    ll n, d;
    cin >> n >> d;
    vector<ll> a(n);
    for (ll&v : a) cin >> v;
    ll pass = 0, fail = d+1;
    while (fail-pass > 1) {
      ll mid = pass+fail>>1;
      ll t = mid;
      for (int i = 0; i < n; i++) {
	t = (t+a[i]-1)/a[i]*a[i];
      }
      if (t <= d) pass = mid;
      else fail = mid;
    }
    cout << pass << endl;
  }
}

```

```c++
#include<bits/stdc++.h>
using namespace std;
using LL = long long;
constexpr int maxn = -1;
int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);
    int T;
    cin >> T;
    for(int _ = 1; _ <= T; _ += 1){
        LL n, d;
        cin >> n >> d;
        vector<LL> v(n);
        for(LL &x : v) cin >> x;
        reverse(v.begin(), v.end());
        for(LL x : v){
            d = min(d, d / x * x);
        }
        cout << "Case #" <<  _ << ": " << d << "\n";
    }
    return 0;
}
/*3 7 2 and 10 
d = 10, 10/2 * 2 = 10
d = 10, 10/7 * 7 = 7
d = 7,  7/3 * 3 = 6
d = 6.*/
```
This method is as same as mine, but Why I wrong?
Oh, Jesus, Just because I didn't set the variable `sum` and `pre` type be `long long`. 
```c++
#include <bits/stdc++.h>

using namespace std;

#define ll long long

inline ll Read() {
	ll x = 0; char y; bool z = false;
	do y = getchar(), z |= y == '-'; while (y < '0' || y > '9');
	do x = x * 10 + y - '0', y = getchar(); while (y >= '0' && y <= '9');
	return z ? -x : x;
}

#define N 100050

int T, n, m; ll D, ans, a[N];

void Solve() {
	ans = D;
	for (int i = n; i >= 1; i--)
		ans = ans / a[i] * a[i];
	return;
}

int main() {
	//freopen("input.txt", "r", stdin);
	T = Read();
	for (int t = 1; t <= T; t++) {
		n = Read(); D = Read();
		for (int i = 1; i <= n; i++)
			a[i] = Read();
		Solve();
		printf("Case #%d: %lld\n", t, ans);
	}
	return 0;
}
```
```c++
#include "bits/stdc++.h"
#include <assert.h>
using namespace std;
typedef long long ll;
typedef long double ld;
#define PB push_back
#define MP make_pair
const int MOD=1000000007;
#define endl "\n"
#define fst first
#define snd second
const int UNDEF = -1;
const int INF=1<<30;
template<typename T> inline bool chkmax(T &aa, T bb) { return aa < bb ? aa = bb, true : false; }
template<typename T> inline bool chkmin(T &aa, T bb) { return aa > bb ? aa = bb, true : false; }
typedef pair<ll,ll> pll;typedef vector<ll> vll;typedef vector<vll> vvll;typedef pair<int,int> pii;typedef vector<int> vi;typedef vector<vi> vvi;
#ifdef ONLINE_JUDGE
#define assert(...) /* nothing */
#endif
#define DEBUG_CAT
#ifdef DEBUG_CAT
#define dbg(...)   printf( __VA_ARGS__ )
#else 
#define dbg(...)   /****nothing****/
#endif

void solve(ll casenum) {
vector<ll> v;
ll n,d;
  cin>>n>>d;
  v.resize(n);
  for (ll i=0;i<n;i++) cin>>v[i];
  ll imin=0,imax=d+1;
  while(imin<imax) {
    ll imid=(imin+imax)/2;
    bool ok=true;
    ll x=imid;
    for (auto &y:v) {
      x = ((x+y-1)/y)*y;
      if (x>d) {ok=false; break;}
    }
    if (x>d) {ok=false;}
    if (ok) imin=imid+1;
    else imax=imid;
  }
  cout<<"Case #"<<casenum<<": "<<imin-1<<endl;
}
int main() 
{
  ios_base::sync_with_stdio(false); cin.tie(0);
  ll T; cin>>T;
  for (ll i=1;i<=T;i++) {
    solve(i);
  }
}
```

## Robot Path Decoding

### Problem

Your country's space agency has just landed a rover on a new planet, which can be thought of as a grid of squares containing 109  columns (numbered starting from 1 from west to east) and 109  rows (numbered starting from 1 from north to south). Let (w, h) denote the square in the w-th column and the h-th row. The rover begins on the square (1, 1).

The rover can be maneuvered around on the surface of the planet by sending it a  _program_, which is a string of characters representing movements in the four cardinal directions. The robot executes each character of the string in order:

-   `N`: Move one unit north.
-   `S`: Move one unit south.
-   `E`: Move one unit east.
-   `W`: Move one unit west.

There is also a special instruction  `X(Y)`, where  `X`  is a number between 2 and 9 inclusive and  `Y`  is a non-empty subprogram. This denotes that the robot should repeat the subprogram  `Y`  a total of  `X`  times. For example:

-   `2(NWE)`  is equivalent to  `NWENWE`.
-   `3(S2(E))`  is equivalent to  `SEESEESEE`.
-   `EEEE4(N)2(SS)`  is equivalent to  `EEEENNNNSSSS`.

Since the planet is a torus, the first and last columns are adjacent, so moving east from column 109  will move the rover to column 1 and moving south from row 109  will move the rover to row 1. Similarly, moving west from column 1 will move the rover to column 109  and moving north from row 1 will move the rover to row 109. Given a program that the robot will execute, determine the final position of the robot after it has finished all its movements.

Input

The first line of the input gives the number of test cases,  **T**.  **T**  lines follow. Each line contains a single string: the program sent to the rover.

Output

For each test case, output one line containing  `Case #x: w h`, where  `x`  is the test case number (starting from 1) and  `w h`  is the final square (w, h) the rover finishes in.

Limits

Time limit: 10 seconds per test set.  
Memory limit: 1GB.  
1 ≤  **T**  ≤ 100.  
The string represents a valid program.  
The length of each program is between 1 and 2000 characters inclusive.  

Test set 1

The total number of moves the robot will make in a single test case is at most 104.

Test set 2

No additional constraints.

My solution:
```c++
#include <vector>
#include <algorithm>
#include <iostream>
#include <string>
#include <stack>
typedef long long ll;

void c() {
	ll T = 0, t = 1, i = 0, nw = 0, nh = 0;
	//FILE *stream1;//
	//freopen_s(&stream1, "D:\\handsome\\VS\\Project\\KSdata\\2020\\round_b\\c.in", "r", stdin);
	std::cin >> T;

	for (; t <= T; ++t) {
		std::string sorder;
		std::cin >> sorder;
		std::stack<ll> st;

		ll ofi[2] = { 0,0 };
		std::stack<std::vector<ll>> offi;
		ll times = 0;
		for (i = 0; i < sorder.size(); ++i) {
			if (sorder[i] >= '0' && sorder[i] <= '9') {
				times = times * 10 + ll(sorder[i] - '0');
			}
			else if (sorder[i] == '(') {
				st.push(times);
				times = 0;
				offi.push(std::vector<ll>(2, 0));
			}
			else if (sorder[i] == ')') {
				ll nt = st.top(); st.pop();
				std::vector<ll> vt = offi.top(); offi.pop();
				if (offi.empty()) {
					ofi[0] = (ofi[0] + vt[0] * nt) % 1000000000;
					ofi[1] = (ofi[1] + vt[1] * nt) % 1000000000;
				}
				else {
					std::vector<ll> vt2 = offi.top(); offi.pop();
					vt2[0] = (vt2[0] + vt[0] * nt) % 1000000000;
					vt2[1] = (vt2[1] + vt[1] * nt) % 1000000000;
					offi.push(vt2);
				}
			}
			else {
				if (offi.empty()) {
					switch (sorder[i])
					{
					case 'N': (--ofi[0]) % 1000000000; break;
					case 'S': (++ofi[0]) % 1000000000; break;
					case 'E': (++ofi[1]) % 1000000000; break;
					case 'W': (--ofi[1]) % 1000000000; break;
					default: break;
					}
				}
				else {
					std::vector<ll> t = offi.top(); offi.pop();
					switch (sorder[i])
					{
					case 'N': (--t[0]) % 1000000000; break;
					case 'S': (++t[0]) % 1000000000; break;
					case 'E': (++t[1]) % 1000000000; break;
					case 'W': (--t[1]) % 1000000000; break;
					default: break;
					}
					offi.push(t);
				}
			}
		}
		nw = (1000000000 + ofi[0]) % 1000000000 + 1;
		nh = (1000000000 + ofi[1]) % 1000000000 + 1;
		std::cout << "Case #" << t << ": " << nh << " "<< nw << std::endl;
	}
}

int main()
{
 c();
	return 0;
}
```
### Analysis

To facilitate parsing of the program, let us define  _ClosingBracket_(i) as the index of the closing bracket corresponding to the opening bracket at index i. We can find  _ClosingBracket_(i) for each opening bracket using a stack in linear time, which is similar to checking whether a string is a correct bracket sequence or not, see  [this article](https://www.geeksforgeeks.org/check-for-balanced-parentheses-in-an-expression/)  for more details.

Test Set 1

The total number of moves is limited by 104  per test. Consider the expanded version of a program P to be the string consisting of characters N,S,W,E only and having the same moves as P. For example, the program 2(3(N)EW) would expand to NNNEWNNNEW. Since the number of moves is small, we can generate the expanded program, and calculate the position of the robot easily by taking one step at a time.

For an original subprogram between indices L and R, the equivalent expanded version  _Expanded_(L, R) can be constructed recursively as follows. We start with an empty string  _Result_, iterate the subprogram from the left index L to the right index R, and consider two cases:

-   If the i-th symbol is in {'N','S','E','W'}, append it to  _Result_.
-   If the i-th symbol is a digit D then
    -   Call  _Expanded_(i+2,  _ClosingBracket_(i+1)-1) to construct the expanded version P' of the next subprogram recursively,
    -   Append P' to  _Result_  D times, and
    -   Advance the current position i to  _ClosingBracket_(i+1)+1.

The first case takes constant time. In the second case, it takes O(D × |P'|) time to append the subprogram P' to the result D times. Let LEN be the length of the expanded program. The total expanded length of the subprograms at the second nesting level is at most LEN/2. The total expanded length of subprograms at the third nesting level is at most LEN/4, and so on. Thus the time complexity would be bounded by LEN + LEN / 2 + LEN / 4 + LEN / 8 + .. which is equal to 2 × LEN as this is a geometric progression. Hence, the time complexity to generate the expanded version of the original program would be O(LEN).

Test Set 2

Now it is possible that the number of moves is exponential in the length of the original program. Thus it would be impossible to execute the moves one by one in the given time.

For the ease of explanation, let us assume that the rows and columns are numbered from 0 (inclusive) to 109  (exclusive). Suppose that the robot is at position (a, b) and now we come across instruction X(Y) in the program. Let us say subprogram Y changes the current position of the robot by dx, dy (because of the torus shape of Mars, we can assume that 0 ≤ dx < 109  and 0 ≤ dy < 109). Then the position of the robot after following the instruction X(Y) would be ((a + X * dx) mod 109, (b + X * dy) mod 109) as the subprogram Y is repeated X times. Hence, we just need to find the relative displacement of the robot by each subprogram.

For a subprogram between indices L and R, the relative displacement of the robot can be calculated using  _Evaluate_(L, R) recursively as follows. Consider that we are currently at the square (a, b), which is initially the square (0, 0). Iterate the subprogram from the left index L to the right index R, and consider two cases:

-   If the i-th symbol is in {'N','S','E','W'}, change the current position of the robot accordingly.
-   If the i-th symbol is a digit D then
    -   Call  _Evaluate_(i+2,  _ClosingBracket_(i+1)-1)to get the relative displacement (dx, dy) of the robot by the next subprogram recursively,
    -   Change the current position to ((a + D * dx) mod 109, (b + D * dy) mod 109), and
    -   Advance the current position i to  _ClosingBracket_(i+1)+1.

Clearly, we visit each character in the program exactly once. Hence, the time complexity of the solution is O(N), where N is the length of the program.

### Others

```c++
#include <bits/stdc++.h>

using namespace std;
typedef long long ll;
const int MAXN = 2100;
const ll MOD = 1e9;

int N;
string S;
pair <ll, ll> dp[MAXN][MAXN];

string xf = "NSEW";
int xc[4] = {0, 0, 1, -1};
int yc[4] = {-1, 1, 0, 0};

void figure (int lo, int hi)
{
    //cout << lo << " " << hi << endl;
    ll xres = 0, yres = 0;
    for (int i = lo; i <= hi; i++)
    {
        //cout << i << endl;
        if (S[i] >= '0' && S[i] <= '9')
        {
            int ntot = 1, cloc = i + 2;
            while (ntot)
            {
                if (S[cloc] == '(') ntot++;
                else if (S[cloc] == ')') ntot--;
                cloc++;
            }
            int nv = S[i] - '0';
            figure (i + 2, cloc - 2);
            pair <ll, ll> pv = dp[i + 2][cloc - 2];
            pv.first *= nv;
            pv.second *= nv;
            xres = (xres + pv.first) % MOD;
            yres = (yres + pv.second) % MOD;
            i = cloc - 1;
            continue;
        }
        
        for (int j = 0; j < 4; j++)
            if (xf[j] == S[i])
            {
                xres = (xres + MOD + xc[j]) % MOD;
                yres = (yres + MOD + yc[j]) % MOD;
            }
    }
    dp[lo][hi] = make_pair (xres, yres);
}

void gogo()
{
    cin >> S;
    N = S.length();
    for (int i = 0; i <= N; i++)
        for (int j = 0; j <= N; j++)
            dp[i][j] = make_pair (-1, -1);

    figure (0, N - 1);

    ll x = dp[0][N-1].first % MOD + 1;
    ll y = dp[0][N-1].second % MOD + 1;
    cout << x << " " << y << "\n";
}

int main()
{
    ios_base::sync_with_stdio(0);

    int T; cin >> T;
    for (int i = 0; i < T; i++)
    {
        cout << "Case #" << i + 1 << ": ";
        gogo();
    }
}
```

```c++
#include<bits/stdc++.h>
using namespace std;
using LL = long long;
constexpr int maxn = -1;
constexpr LL mod = 1000000000;
pair<int, int> f(string s){
    auto p = make_pair(0, 0);
    for(int i = 0; i < (int)s.size(); i += 1){
        if(s[i] == 'N') p.first = (p.first + mod - 1) % mod;
        if(s[i] == 'S') p.first = (p.first + 1) % mod;
        if(s[i] == 'E') p.second = (p.second + 1) % mod;
        if(s[i] == 'W') p.second = (p.second + mod - 1) % mod;
        if(isdigit(s[i])){
            int j = i + 1, sum = 0;
            for(;; j += 1){
                if(s[j] == '(') sum += 1;
                if(s[j] == ')') sum -= 1;
                if(sum == 0) break;
            }
            auto q = f(s.substr(i + 2, j - i - 2));
            p.first = (p.first + (LL)(s[i] - '0') * q.first) % mod;
            p.second = (p.second + (LL)(s[i] - '0') * q.second) % mod;
            i = j;
        }
    }
    return p;
}
int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);
    int T;
    cin >> T;
    for(int _ = 1; _ <= T; _ += 1){
        string s;
        cin >> s;
        auto p = f(s);
        cout << "Case #" <<  _ << ": " << p.second + 1 << " " << p.first + 1 << "\n";
    }
    return 0;
}
```
I failed in `long long` type again.

```c
#include <bits/stdc++.h>

using namespace std;

#define ll long long

inline ll Read() {
	ll x = 0; char y; bool z = false;
	do y = getchar(), z |= y == '-'; while (y < '0' || y > '9');
	do x = x * 10 + y - '0', y = getchar(); while (y >= '0' && y <= '9');
	return z ? -x : x;
}

#define N 100050
#define ui unsigned_int
#define mp make_pair
#define PII pair <int, int>
#define INF (int)(1e9)
#define fr first
#define sc second

int T, n, m, cp[N], Stack[N]; char ch[N]; PII ans;

void QAQ(char c, int& x, int& y) {
	if (c == 'N')
		x--; else
	if (c == 'E')
		y++; else
	if (c == 'W')
		y--; else 
	if (c == 'S')
		x++;
}

void TAT(int &x) {
	x = (x % INF + INF) % INF;
}

void Add(int &x, int y, int k) {
	x = (x + 1LL * y * k) % INF; TAT(x);
}

PII DFS(int x, int y) {
	int _x = 0, _y = 0;
	while (x <= y && ch[x] > '9')
		QAQ(ch[x], _x, _y), x++;
	TAT(_x); TAT(_y);
	if (x <= y) {
		int k = ch[x] - '0';
		PII l = DFS(x + 2, cp[x] - 1);
		Add(_x, l.fr, k); Add(_y, l.sc, k);
		x = cp[x] + 1;
	}
	if (x <= y) {
		PII l = DFS(x, y);
		Add(_x, l.fr, 1);
		Add(_y, l.sc, 1);
	}
	return mp(_x, _y);
}

void Solve() {
	n = strlen(ch);
	int ri = -1;
	for (int i = 0; i < n; i++) {
		if (ch[i] >= '0' && ch[i] <= '9')
			Stack[++ri] = i;
		if (ch[i] == ')')
			cp[i] = Stack[ri], cp[Stack[ri]] = i, ri--;
	}
	ans = DFS(0, n - 1);
	return;
}

int main() {
	//freopen("input.txt", "r", stdin);
	T = Read();
	for (int t = 1; t <= T; t++) {
		scanf("%s", ch);
		Solve();
		printf("Case #%d: %d %d\n", t, ans.sc + 1, ans.fr + 1);
	}
	return 0;
}
```
```c
#include "bits/stdc++.h"
#include <assert.h>
using namespace std;
typedef long long ll;
typedef long double ld;
#define PB push_back
#define MP make_pair
const int MOD=1000000000;
#define endl "\n"
#define fst first
#define snd second
const int UNDEF = -1;
const int INF=1<<30;
template<typename T> inline bool chkmax(T &aa, T bb) { return aa < bb ? aa = bb, true : false; }
template<typename T> inline bool chkmin(T &aa, T bb) { return aa > bb ? aa = bb, true : false; }
typedef pair<ll,ll> pll;typedef vector<ll> vll;typedef vector<vll> vvll;typedef pair<int,int> pii;typedef vector<int> vi;typedef vector<vi> vvi;
#ifdef ONLINE_JUDGE
#define assert(...) /* nothing */
#endif
#define DEBUG_CAT
#ifdef DEBUG_CAT
#define dbg(...)   printf( __VA_ARGS__ )
#else 
#define dbg(...)   /****nothing****/
#endif

string s;

pll norm(pll ans) {
  ans.fst = (ans.fst + MOD)%MOD;
  ans.snd = (ans.snd + MOD)%MOD;
  return ans;
}

pair<ll,pll> f(ll x) {
  pll ans=MP(0LL,0LL);
  ll n=s.length();
  while(x<n) {
    char c=s[x];
    if ('0' <= c && c <= '9') {
      //printf("Hit\n");
      ll m=c-'0';
      auto got=f(x+2);
      ans.fst += m*got.snd.fst;
      ans.snd += m*got.snd.snd;
      x=got.fst;
    } else if (c==')') {
      ans=norm(ans);
      //printf("Ret x:%lld r:%lld c:%lld\n",x,ans.fst,ans.snd);
      return MP(x,ans);
    } else if (c=='N') {
      ans.fst--;
    } else if (c=='S') {
      ans.fst++;
    } else if (c=='E') {
      ans.snd++;
    } else if (c=='W') {
      ans.snd--;
    }
    ans=norm(ans);
    //printf("x:%lld r:%lld c:%lld\n",x,ans.fst,ans.snd);
    x++;
  }
  ans=norm(ans);
  //printf("Ret x:%lld r:%lld c:%lld\n",x,ans.fst,ans.snd);
  return MP(x,ans);
}

void solve(ll casenum) {
  cin>>s;
  auto got=f(0);
  ll r=got.snd.fst+1;
  ll c=got.snd.snd+1;
  cout<<"Case #"<<casenum<<": "<<c<<" " <<r<<endl;
}
int main() 
{
  ios_base::sync_with_stdio(false); cin.tie(0);
  ll T; cin>>T;
  for (ll i=1;i<=T;i++) {
    solve(i);
  }
}

```

## Wandering Robot

### Problem

Jemma is competing in a robotics competition. The challenge for today is to build a robot that can navigate around a hole in the arena.

The arena is a grid of squares containing  **W**  columns (numbered 1 to  **W**  from left to right) and  **H**  rows (numbered 1 to  **H**  from top to bottom). The square in the x-th column and y-th row is denoted (x, y). The robot begins in the top left square (1,1) and must navigate to the bottom right square (**W**,  **H**).

A rectangular subgrid of squares has been cut out of the grid. More specifically, all the squares that are in the rectangle with top-left square (**L**,  **U**) and bottom-right square (**R**,  **D**) have been removed.

Jemma did not have much time to program her robot, so it follows a very simple algorithm:

-   If the robot is in the rightmost column, it will always move to the square directly below it. Otherwise,
-   If the robot is in the bottommost row, it will always move to the square directly right of it. Otherwise,
-   The robot will randomly choose to either move to the square directly to the right, or to the square directly below it with equal probability.

Jemma passes the challenge if her robot avoids falling into the hole and makes it to the square (**W**,  **H**). What is the probability she passes the challenge?

Input

The first line of the input gives the number of test cases,  **T**.  **T**  test cases follow. Each test case consists of a single line containing  **W**,  **H**,  **L**,  **U**,  **R**  and  **D**.

Output

For each test case, output one line containing  `Case #x: y`, where  `x`  is the test case number (starting from 1) and  `y`  is a real number between 0 and 1 inclusive, the probability that Jemma passes the challenge.

`y`  will be considered correct if it is within an absolute or relative error of 10-5  of the correct answer. See the  [FAQ](https://codejam.withgoogle.com/codejam/resources/faq#real-number-behavior)  for an explanation of what that means, and what formats of real numbers we accept.

Limits

Time limit: 15 seconds per test set.  
Memory limit: 1GB.  
1 ≤  **T**  ≤ 100.  
1 ≤  **U**  ≤  **D**  ≤  **H**.  
1 ≤  **L**  ≤  **R**  ≤  **W**.  
Neither the top-left nor bottom-right squares will be missing.

Test set 1

1 ≤  **W**  ≤ 300.  
1 ≤  **H**  ≤ 300.  

Test set 2

1 ≤  **W**  ≤ 105.  
1 ≤  **H**  ≤ 105.

```c++
#include <vector>
#include <algorithm>
#include <iostream>

void d() {
	int T = 0, t = 1, i = 0,j = 0;
	int W = 0, H = 0, L = 0, U = 0, R = 0, D = 0;
	//FILE *stream1;//
	//freopen_s(&stream1, "D:\\handsome\\VS\\Project\\KSdata\\2020\\round_b\\d.in", "r", stdin);
	std::cin >> T;
	for (; t <= T; ++t) {
		std::cin >> W >> H >> L >> U >> R >> D;
		--L; --U; --R; --D;
		std::vector<std::vector<double>> map(H, std::vector<double>(W, 0));
		map[0][0] = 1.0;
		for (i = 0; i < H; ++i) {
			for (j = 0; j < W; ++j) {
				if (i + 1 < H && j + 1 < W) {
					map[i][j + 1] += 0.5 * map[i][j];
					map[i + 1][j] += 0.5 * map[i][j];
				}
				else if (i + 1 < H) {
					map[i + 1][j] +=  map[i][j];
				}
				else if (j + 1 < W) {
					map[i][j + 1] += map[i][j];
				}

				if (i >= U && i <= D && j + 1 >= L && j + 1 <= R) { map[i][j + 1] = 0.0; }
				if (i + 1 >= U && i + 1 <= D && j >= L && j <= R) { map[i + 1][j] = 0.0; }
			}
		}
		std::cout << "Case #" << t << ": " << map[H - 1][W - 1] << std::endl;
	}
}

int main()
{
 d();
	return 0;
}

```

### Analysis

Test Set 1

We can solve this test set using dynamic programming. Let f(x, y) be the probability Jemma passes the challenge if she is currently in the square (x, y). The base case of this function is f(**W**,  **H**) = 1. Also, if the square (x, y) has been removed, then f(x, y) = 0.

If there is only one possible square to go to from square (x, y) (i.e. either x =  **W**  or y =  **H**), then f(x, y) = f(x', y'), where (x', y') is the possible next square. Otherwise, let (x1', y1') and (x2', y2') be the possible next squares. Since they have the same probability to become the next square, f(x, y) = 0.5 × f(x1', y1') + 0.5 × f(x2', y2').

The running time and space of this solution is O(**W**  ×  **H**).

Test Set 2

The first observation to solve this problem is to realize that there are two ways to avoid the hole: either going to the left and the bottom of the hole (illustrated by the red path in the figure below), or going to the top and the right of the hole (illustrated by the blue path in the figure below).

![](https://codejam.googleapis.com/dashboard/get_file/AQj_6U0Der7yD-B4hjKyD7egAtgTP9IEeTTQcszH9r8mdkJSRDLHn79-vi63zJ3Tg2G7OWYYnELo/two_paths.png)

It can be seen that the set of paths in the red path and the blue path are disjoint--there is no path that goes both to the left of the hole and to the top of the hole simultaneously. Therefore, we can compute the probability that Jemma passes the challenge by taking the red path and the blue path separately and compute the sum of both probabilities.

Since the probability of passing the challenge by taking the blue path can be computed similarly, we only focus on computing the probability of passing the challenge by taking the red path for the rest of the discussion. The next observation to solve this problem is that we can choose a set of squares diagonally from the bottom-left corner of the hole (illustrated by the green squares below) such that Jemma has to pass exactly one of the squares to pass the challenge by taking the red path. Also, by landing on one of the squares, it is no longer possible that Jemma will fall to the hole, thus passing the challenge by taking the red path is now guaranteed.

![](https://codejam.googleapis.com/dashboard/get_file/AQj_6U3pY1hX0M-HA5EejUCUcHkZxFB96XAZiIpOlBUZhz2ZnYBLQuC5ed2ECMxqKYn2t2ZpWDHbGyU8tZXJ/critical_points.png)

Therefore, computing the probability of passing the challenge by taking the red path is equivalent to computing the probability that Jemma will land on one of the green squares. Similar to the red and blue paths discussion, since Jemma cannot pass two green squares simultaneously, we can compute the probability that Jemma lands on each square separately and compute the sum of all probabilities.

Let us take square X for an example. Consider all paths that go to the square X. For each move in the path, there is a 0.5 probability that the move will follow the path. Since the number of moves to square X is (**L**  +  **D**  - 2), there is a (0.5)(**L**  +  **D**  - 2)  probability that this path will be taken. This number has to be multiplied with the number of paths to go to square X, which can be  [computed using a single binomial coefficient](https://www.geeksforgeeks.org/maths-behind-number-of-paths-in-matrix-problem/). The probability of reaching any particular green square is the same for all but the green square in the last row, which is left to the reader as an exercise.

To handle floating point issues, we can store every huge number in their log representation (i.e. storing log2(x) instead of x). We can then compute the value of C(n, k) / 2n  using 2log2(n! / (k! × (n - k)!) / 2n)  = 2log2(n!) - log2(k!) - log2((n - k)!) - n, which takes constant time to compute if we have precomputed every value of log2(x!). Since there can be at most O(N) green squares, where N is the larger length of the grid (i.e. N = max(**H**,  **W**)), the total running time of this solution is O(N).

### Others

```c++
#include <bits/stdc++.h>

using namespace std;
typedef long long ll;
const int MAXN = 1000100;

int W, H, L, U, R, D;
double lfac[MAXN];
double p2[MAXN];

double choose (int N, int K)
{
    if (K < 0 || K > N) return 0;
    return exp (lfac[N] - lfac[K] - lfac[N-K] - p2[N]);
}

void gogo()
{
    cin >> W >> H >> L >> U >> R >> D;
    W--, H--, L--, U--, R--, D--;

    double ans = 0.0;

    int ly = U, lx = R;
    if (R < W)
    {
        double mult = 1.0;
        while (ly > 0)
        {
            ly--;
            lx++;

            if (lx >= W)
            {
                lx = W - 1;
                mult = 0.5;
            }
            //cout << mult << lx << ly << "\n";
            ans += mult * choose (lx + ly, lx);
        }
    }

    swap (U, L);
    swap (D, R);
    swap (H, W);
    ly = U, lx = R;
    if (R < W)
    {
        double mult = 1.0;
        while (ly > 0)
        {
            ly--;
            lx++;

            if (lx >= W)
            {
                lx = W - 1;
                mult = 0.5;
            }
            ans += mult * choose (lx + ly, lx);
        }
    }
    cout << fixed << setprecision(9);
    cout << ans << "\n";
}

int main()
{
    ios_base::sync_with_stdio(0);

    lfac[0] = 0.0;
    for (int i = 1; i < MAXN; i++)
        lfac[i] = lfac[i-1] + log(i);
    p2[1] = log(2);
    for (int i = 2; i < MAXN; i++)
        p2[i] = p2[i-1] + p2[1];

    //cout << choose (1, 0) << "\n";

    int T; cin >> T;
    for (int i = 0; i < T; i++)
    {
        cout << "Case #" << i + 1 << ": ";
        gogo();
    }
}
```


```c++
#include<bits/stdc++.h>
using namespace std;
using LL = long long;
using LD = long double;
constexpr int maxn = 200000;
LD f[maxn + 1], p[maxn + 1];
LD C(int m, int n){
    return f[m + n] - f[m] - f[n];
}
int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);
    cout << setprecision(20);
    for(int i = 1; i <= maxn; i += 1) f[i] = f[i - 1] + log((LD)i);
    for(int i = 1; i <= maxn; i += 1) p[i] = p[i - 1] + log((LD)2);
    int T;
    cin >> T;
    for(int _ = 1; _ <= T; _ += 1){
        LD ans = 0;
        int W, H, L, U, R, D;
        cin >> W >> H >> L >> U >> R >> D;
        if(R < W) for(int i = 1; i < U; i += 1)
            ans += exp(C(i - 1, R - 1) - p[i + R - 1]);

        if(D < H) for(int i = 1; i < L; i += 1)
            ans += exp(C(i - 1, D - 1) - p[i + D - 1]);
        cout << "Case #" <<  _ << ": " << ans << "\n";
    }
    return 0;
}
```
```c
#include <bits/stdc++.h>

using namespace std;

#define ll long long

inline ll Read() {
	ll x = 0; char y; bool z = false;
	do y = getchar(), z |= y == '-'; while (y < '0' || y > '9');
	do x = x * 10 + y - '0', y = getchar(); while (y >= '0' && y <= '9');
	return z ? -x : x;
}

#define N 100050
#define ld long double
#define ui unsigned_int
#define mp make_pair
#define PII pair <int, int>
#define INF (int)(1e9)
#define fr first
#define sc second

int T, W, H, R, D, L, U; ld ans, a2[N * 10];

long double Calc(int x, int y, int z) {
	ld Now = 1;
	ld Tot = 0;
	int r2 = x;
	if (y == 0)
		Tot += a2[r2 + 1];
	//cout<<x<<' '<<y<<' '<<z<<endl;
	for (int i = 1; i <= z; i++) {
		r2++;
		Now = Now * (x + i) / i;
		while (Now >= 2 && r2) r2--, Now /= 2;
		if (i >= y)
			Tot += Now * a2[r2 + 1];
		//cout<<Now<<' '<<r2<<' '<<Tot<<endl;
	}
	return Tot;
}

void Solve() {
	ans = 0;
	if ((L == 1 && R == W) || (U == 1 && D == H))
		return;
	if ((L == 1 && U == 1) || (R == W && D == H))
		return;
	L--; U--; R--; D--;
	bool up = true, left = true;
	int ux = U, uy = D;
	int lx = L, ly = R;
	if (L == 0) up = false;
	if (R == W - 1) left = false, ux = 0;
	if (U == 0) left = false;
	if (D == H - 1) up = false, lx = 0;
	if (!left && !right)
		return;
	//cout <<left<<' '<<up<<' '<<lx<<' '<<ly<<' '<<ux<<' '<<uy<<endl;
	ans = 1;
	if (left)
		ans -= Calc(U - 1, lx, ly);
	if (up)
		ans -= Calc(L - 1, ux, uy);
	return;
}

int main() {
	//freopen("input.txt", "r", stdin);
	a2[0] = 1;
	for (int i = 1; i < N; i++)
		a2[i] = a2[i - 1] / 2;
	T = Read();
	for (int t = 1; t <= T; t++) {
		W = Read(); H = Read(); L = Read(); U = Read(); R = Read(); D = Read();
		Solve();
		printf("Case #%d: %.6lf\n", t, (double)ans);
	}
	return 0;
}
```
```c
#include "bits/stdc++.h"
#include <assert.h>
using namespace std;
typedef long long ll;
typedef long double ld;
#define PB push_back
#define MP make_pair
const int MOD=1000000007;
#define endl "\n"
#define fst first
#define snd second
const int UNDEF = -1;
const int INF=1<<30;
template<typename T> inline bool chkmax(T &aa, T bb) { return aa < bb ? aa = bb, true : false; }
template<typename T> inline bool chkmin(T &aa, T bb) { return aa > bb ? aa = bb, true : false; }
typedef pair<ll,ll> pll;typedef vector<ll> vll;typedef vector<vll> vvll;typedef pair<int,int> pii;typedef vector<int> vi;typedef vector<vi> vvi;
#ifdef ONLINE_JUDGE
#define assert(...) /* nothing */
#endif
#define DEBUG_CAT
#ifdef DEBUG_CAT
#define dbg(...)   printf( __VA_ARGS__ )
#else 
#define dbg(...)   /****nothing****/
#endif
const ll mn=(3e5)+4;
const ld l2= log(((ld)2.0L));
ld logfac[mn];

ld f(ll n, ll m) {
  return logfac[n] - logfac[m] - logfac[n-m];
}
ll R,C,Clo,Rlo,Chi,Rhi;

ld varc[mn];

void prec() {
  int n=R,k=0;
  varc[0]=exp(-l2*n);
  for (ll c=1;c<=C;c++) {
    varc[c]=varc[c-1] + exp(f(n,k+1)-l2*(n+1));
    n++; k++;
  }
}

ld varr[mn];

void prer() {
  int n=C,k=0;
  varr[0]=exp(-l2*n);
  for (ll r=1;r<=R;r++) {
    varr[r]=varr[r-1] + exp(f(n,k+1)-l2*(n+1));
    n++; k++;
  }
}

ld g(ll r, ll c) { // From (0,0) to (r,c)
  //printf("r:%lld c:%lld R:%lld C:%lld\n",r,c,R,C);
  if (r==R && c==C) {
    return 1;
  } else if (r==R) {
    return varc[c];
  } else if (c==C) {
    return varr[r];
  } else {
    ld logchoose=f(r+c,c);
    ld ans=exp(logchoose - l2 * (r+c));
    //printf("r:%lld c:%lld logchoose:%.3f ans:%.3f\n",r,c,(double)logchoose,(double)ans);
    return ans;
  }
}

void solve(ll casenum) {
  cin>>C>>R>>Clo>>Rlo>>Chi>>Rhi;
  --R; --C;
  Clo--;
  Rlo--;
  Chi--;
  Rhi--;
  prec(); prer();
  ld final=0;
  if (Rlo-1>=0) {
    for (ll c=Clo;c<=Chi;c++) {
      ld got=g(Rlo-1,c);
      ld probdown=(c<C)?0.5:1.0;
      ld contrib=got*probdown;
      //printf("c:%lld contrib:%f\n",c,(double)contrib);
      final+=contrib;
    }
  }
  if (Clo-1 >= 0) {
    for (ll r=Rlo;r<=Rhi;r++) {
      ld got=g(r,Clo-1);
      ld probright=(r<R)?0.5:1.0;
      ld contrib=got*probright;
      //printf("r:%lld contrib:%f\n",r,(double)contrib);
      final+=contrib;
    }
  }
  ld final2 = 1-final;
  if (R==0||C==0) final2=0;
  printf("Case #%lld: %.9f\n",casenum,(double)final2);
}
int main() 
{
  ios_base::sync_with_stdio(false); cin.tie(0);
  logfac[0]=0;
  for (ll x=1;x<mn;x++) logfac[x]=logfac[x-1] + log((ld)x);
  ll T; cin>>T;
  for (ll i=1;i<=T;i++) {
    solve(i);
  }
}
```