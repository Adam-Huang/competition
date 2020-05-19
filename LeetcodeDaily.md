**时间顺序排列（Chronological order）**

[*19 May 2020*]
## `680. Valid Palindrome II`
我用的双指针，因为最多删除一个，就是左指针left和右指针right有一个跳了一次，即`++left`或者`--right`；I used the double pointer, because at most one is deleted, that is, the `left` pointer left and the `right` pointer have one jump, that is, `++ left` or` --right`;
也就是最多三种情况，两次`O(n)`的循环。That is, at most three cases, two `O (n)` cycles.
**others**

## `面试题 04.06. Successor LCCI`
`Error 1` 标志位传值没有传引用！！！！The Label variable deliver value but reference!!!
## `63. Unique Paths II`
简单的动态规划Simple dynamic programming with an error:
`error 1`: start point is obstacles?!
`dp[0][0] = oG[0][0]?0:1;//error 1: start point is obstacles?!`


[*15 May 2020*]
# Daily Task
## `560. Subarray Sum Equals K`
Prefix & Hash? Yes!

# Game weekly 183
## `1403. 非递增顺序的最小子序列 Minimum Subsequence in Non-Increasing Order`
本题实际上是求刚好大于数组和一半的最短子数组，并逆序排列输出。This question is actually to find the shortest sub-array that is just larger than the half of array, and arrange the output in reverse order.
1. Sort First
2. Find the first time of appear `pre[n] - pre[i] > pre[i]` Simplify as `pre[n] > 2 * pre[i]`, But because I traversal it from left to right, It must satisfy at beginning. so I find first point which `2 * pre[i] >= pre[n]` the i should be substracted 1.

For example, the index of output is `4`:
```
0 1  2  3  4  5
3 4  8  9 10
0 3  7 15 24 34  half is [17]
  6 14 30 48
           |-> satisfy 
```
Using vector construct function:`ans = vector<int>(nums.begin() + i - 1,nums.end());` **Attention to the region with Close Left and Open Right**

**others**
1. Sort by `sort(nums.begin(), nums.end(), greater<int>());` and Without prefix.

## `1404. 将二进制表示减到 1 的步骤数 Number of Steps to Reduce a Number in Binary Representation to One`
就是逻辑题，做的时候还花了点时间。It’s a logic question, and it took some time to do it. However, compared with *substract 1*, *plus 1* is more complicated.

## `1405. 最长快乐字符串 1405. Longest Happy String`
这题写的不优雅，看看别人怎么写的。This question sovled without elegant, see how others wrote it.

**others**
1. This is a elegant one:
```
string longestDiverseString(int a, int b, int c) {
        vector<vector<char>> v;
        v.push_back({(char)a, 'a'});
        v.push_back({(char)b, 'b'});
        v.push_back({(char)c, 'c'});

        string res;
        while (res.size() < a + b + c) {//2. judge condition
            sort(v.rbegin(), v.rend());//1. sort reserve 

            if ((res.size() > 0) && (res.back() == v[0][1])) {
                if (v[1][0]-- > 0) res.push_back(v[1][1]);
                else return res;
            } else {
                if (v[0][0]-- > 0) res.push_back(v[0][1]);// every time push two element.
                if (v[0][0]-- > 0) res.push_back(v[0][1]);
            }
            cout << res << "  -> "<< v[1][1] << endl;
        }
        return res;
    }
```
It is really elegant, but hard to think. But, at least U should know Using a `map` to choose a char insert.

## `1406. 石子游戏 III Stone Game III`
用的是带记忆递归，效率不是特别好。Use recursion with memory, efficiency is not particularly good.一开始被博弈搞糊涂了，这次记住了，博弈就减去别人拿走的值即可。I was confused by the game at first, remember this time, the game just subtracts the value taken by others.

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
# Week 184
## `1408. String Matching in an Array`
[*14 May 2020*] Failed at a easy question - -!
**`Error 1`** sort 是案字母表顺序排列的 The sort algorithm is Alphabetical order
`["leetcoder","leetcode","od","hamlet","am"]` After sort is `am hamlet  leetcode leetcoder od`.

**`Error 2`** 找到之后应该返回，因为以及确定它是一个substring了。After finding it, it should be returned because it is a substring.

**Others**
1. Is better `words[i].find(words[j]) != words[i].npos` using `.npos` or `string::npos`
2. 可以简单的以string长度排序不用lamba表达式。You can simply sort by string length without lamba expression. `sort(words.begin(),words.end(),lengthcompare);` `lengthcompare`

## `1409. 查询带键的排列 Queries on a Permutation With Key`
用了比较笨拙的方法，通过分析可知，`P`数组只有前一部分会发生移位，但是我确遍历了整个`map`。Using a clumsy method, through analysis we can see that only the first part of the `P` array will shift, but I did traverse the entire `map`

**others**
1. vector直接填递增值`itoa`Fill in increments directly `iota(p.begin(), p.end(), 1);`
2. 树状数组


## `1410. HTML 实体解析器 HTML Entity Parser`
用了一个`hash`表做映射，感觉没什么好说的。I used a hash table to do the mapping, I feel there is nothing to say.
为什么没能做到一次bug free？Why can't I do a bug free?
`Error 1` the 2nd parameters of `substr` is length!!
`Error 2` `substr` 2nd parameter can reach `text.size()`

## `1411. 给 N x 3 网格图涂色的方案数 Number of Ways to Paint N × 3 Grid`
一开始通过排列组合的方式分析了一遍，但是细节部分涉及条件概率，后决定用带记忆的递归。It was analyzed by permutation and combination at the beginning, but the details involved conditional probability, and then decided to use recursion with memory.

第0行和第0列比较好计算，但是如果涉及到第1行第1列，有两种情况要考虑。Row 0 and column 0 are easier to calculate, but if it involves row 1, column 1, there are two cases to consider.
1. `p[0][1] == p[1][0]`颜色相同Same color `dp[1][1] = 2`
2. `p[0][1] != p[1][0]`颜色不同Different colors`dp[1][1] = 1`

可能还是回溯法好写一点，然后再加上记忆。It may be better to write a bit backtracking, and then add memory.
1. 回溯就是先只考虑这一层，如果再进入下一层填颜色时发现相同的返回0，填完未发现相同返回1。Backtracking is to only consider this layer first, if you enter the next layer to fill the color and find the same return 0, after filling, you do not find the same return 1.

**others**
1. 大佬的思路真是五花八门还是要找一个适合自己的路子。The idea of the big brother is really diverse, it is important to find a way that suits you.



