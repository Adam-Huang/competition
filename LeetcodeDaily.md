**时间顺序排列（Chronological order）**

# Game 24 Biweekly
## `1414. 和为 K 的最少斐波那契数字数目（Find the Minimum Number of Fibonacci Numbers Whose Sum Is K`
normal dynamic programming, but didn't skillful.
BUT it's `time limit exceed`
Ok. Fine. Although I don't understand the certification U can remember It..
Greedy Algorithm.
Although the certification is not clear.


## `1415. The k-th Lexicographical String of All Happy Strings of Length n`
```
                                                 n = 3, k = 7
1         a      |      b      |     c           k - 1 / 4 == 1  k - 1 % 4 = 2
2     b      c   |   a     c   |  a     b        k / 2     == 1  k % 2 = 0
3   a   c  a   b | b  c  a   b |b   c  a   c     k / 1     == 0  so it is bca
```
I had label the error I failed in. and anther thing, I think it too slow. And at first I feel diffcult to understand the `Lexicographical`.

```cpp
class Solution {
    int map[3][3] = {{1,2,0},{0,2,1},{0,1,2}}; // Using a transfer Matrix!
public:
    string getHappyString(int n, int k) {
        string ans;
        int t = pow(2,n - 1) * 3;
        if(k <= t){
            --k;
            int th = t / 3;
            int idx = 0, pre = -1;// if set pre = 2, the judge in below can bypass
            while(th){
                idx = k / th;
                if(pre == -1) {
                    ans += map[idx][2] + 'a';
                    pre = idx;
                }
                else {
                    ans += map[pre][idx] + 'a';
                    pre = map[pre][idx];
                }
                //pre = idx; error 1: at first the pre change depend idx, but then, it changes with map[pre][idx];
                k %= th;
                th /= 2;
            }
        }
        return ans;
    }
};
```
[*13 May 2020* ]
Woc. 我之前想到了，现在居然想不到了。我都觉得之前的方法惊艳呀。I thought about it before, but now I can't think of it.I think the previous method is amazing.
以后遇到复杂的转移过程，可以想想用转移矩阵解决。In the future, if you encounter a complicated transfer process, you can think of a transfer matrix.

# `1416. 恢复数组(Restore The Array)`
这题感觉挺简单的，但是递归的方法我没写出来。This question feels quite simple, but I can not write a recursive method.
通过分析还是能明显看出递归规律的，问题是怎么就知道是从左往右推呢？Through the analysis, we can still clearly see the recursive law. The Question is How do we know that it is pushed from left to right?
`dp[i] = sum(dp[0 ~ i - 1]) + 1`
```
1     |[1]
13    |[1,3]    [13]
131   |[1,3,1]  [13,1]   [1,31]  [131]
1317  |[1,3,1,7][13,1,7] [1,31,7][131,7] [1317] [13,17] [1,317] 1,3,17]
```


# `142. Linked List Cycle II`
关键还是数学推导。假设非环部分长度为`a`，环周期为`b`，相遇点距离环`x`，因此有`s = a + x + n * b`以及`f = 2*s = a + x + m * b` The key is mathematical derivation.Suppose the length of the non-ring part is `a`, the period of the ring is `b`, and the meeting point is away from the ring point `x`, so `s = a + x + n * b` and `f = 2 * s = a + x + m * b`
U can Deduced `a = k * b - x`, that means U can start at the point `x` and continuous going foward, then U will meet the point who start at head at the entrance.

# `32. Longest Valid Parentheses`

左括号没有的时候可以直接设置成`0`，还避免了操作When there is no left bracket, it can be directly set to `0`, which also avoids the operation.
```
 0123456789ab
")()(((())))("
 0020000246
          |->
```



