**A summary with Algorithm**
旨在通过归纳总结做过的习题以及遇到的问题，抽象提炼以完善自身思维和代码能力。
It aims at summarizing the exercises and problems encountered, and abstracting them to improve my thoughts and coding skills.

# Array

## Analysis

有些题目需要先分析一波，从细节出发：

[`1014. Best Sightseeing Pair`](https://leetcode-cn.com/problems/best-sightseeing-pair/) 

这个感觉真是不容易想到，从表达式出发`A[i] + A[j] + i - j`看成`A[i] + i`和`A[j] - j`的和，维护一个其中的最大值即可。说难吧，也不难，但是为啥就是想不到呢？

## Trapping rain water
- [`42. Trapping Rain Water`](https://leetcode-cn.com/problems/trapping-rain-water/)接雨水相关的，因为是短边决定的雨水量，因此每次只移动短边即可。It is related to rainwater, because it is the amount of rainwater determined by the short side, so you only need to move the short side each time.

## 寻找重复或消失
此类问题有一个最典型的特点就是数组中数字范围为：`[1,n]`其中`n`是数组长度：
[`287. Find the Duplicate Number`](https://leetcode-cn.com/problems/find-the-duplicate-number/)：这个有点类似链表找环的入口点。
[`448. Find All Numbers Disappeared in an Array`](https://leetcode-cn.com/problems/find-all-numbers-disappeared-in-an-array/)：这个题消失的数字不止一个，但是允许你对原数组进行修改
[`41. First Missing Positive`](https://leetcode-cn.com/problems/first-missing-positive/)：这个隐含了`answer`范围在[1,n + 1]之中。

## Remove duplicate

在回溯算法哪里也有部分去重的任务，主要是生成排列组合数组。这里主要针对的是几数之和的相关题目。

### [15. 3Sum](https://leetcode-cn.com/problems/3sum/) & [18. 4Sum](https://leetcode-cn.com/problems/4sum/)

三数之和，主要是细节去重：

```c++
vector<vector<int>> threeSum(vector<int>& nums) {
        vector<vector<int>> ans;
        sort(nums.begin(),nums.end());
        int n = nums.size();
        for(int i = 0; i < n; ++i){
            while(i > 0 && i < n && nums[i] == nums[i - 1]) ++i; /*若相同则过滤*/
            int s = i + 1, e = n - 1;
            while(s < e){
                int now = nums[i] + nums[s] + nums[e];
                if(now > 0) --e;
                else if(now < 0) ++s;
                else ans.push_back({nums[i],nums[s++],nums[e--]});

                while(s > i + 1 && s < e && nums[s] == nums[s - 1]) ++s;
                while(s < e && e < n - 1 && nums[e] == nums[e + 1]) --e;
                /*关键：
                1. 要在使用过s和e之后考虑去重；
                2. 要考虑这次的s或e是否与最近一次使用的相同，相同则过滤；
                3. 因为是向后比较（s & s - 1）（e & e + 1）因此退出条件是s < e*/
            }
        }
        return ans;
    }
```

按照上述逻辑，其实4数之和也是一样的。


# Back Tracking
## `Permutations`
可见`46. Permutations` 以及`47. Permutations II`，
总而言之，排列问题是比较好写的，因为终点明确，就是`now.size() == nums.size()`。 In short, the Permutations problem is relatively easy to write, because the end point is clear, that is `now.size() == nums.size()`.

### `47. Permutations II`
此题重点在去重复项。This question focuses on removing duplicates.
去重的题目有几个，方法也有不少，这里总结这个：There are several topics for deduplication, and there are many methods. Here is a summary:
Key code: `if(i > 0 && nums[i] == nums[i - 1] && L[i - 1]) continue;` or `if(i > 0 && nums[i] == nums[i - 1] && !L[i - 1]) continue;`

```
                  [1,1,2]
         |           |-> be cut off if !L[i - 1] and safe with L[i - 1]
         1           1            2
      /     \     /     \      /     \
	  1     2     1     2      1     1 |-> be cut off if !L[i - 1]
	  |     |     |     |      |     |
	  2     1     2     1      1     1
	                           |-> be cut off if L[i - 1]
```
这里的去重可以有两种选择，关键都是考察上一个相同的数字是否被用过。There are two options for deduplication here, the key is to check whether the last same number has been used.

### `60. Permutation Sequence`
第`K`个排列，`K`th Permutation. 
这个题和`1415. The k-th Lexicographical String of All Happy Strings of Length n`很类似，只不过那个限定了只使用`"abc"`。This question is very similar to `1415. The k-th Lexicographical String of All Happy Strings of Length n`, except that it is limited to the use of` "abc" `
思路是一样的，**先计算一个数枝上的总的节点数**，利用商和余计算。有两点需要注意：The idea is the same, **first calculate the total number of nodes on a branch**, and Calculate with Quotient and Remainder.There are two points to note:
1. `K`的取值范围不是`[1,K]`而是`[0,K - 1]`，因此计算前需要`--k`。The value range of `K` is not `[1, K]` but `[0, K-1]`, so `--k` is required before calculation.
2. 排列每次都是从头开始计数的，不是从上一次的结果，这一点从前一题的全排列实现也能看出来。The permutation is counted from the beginning every time, not from the last result. This can also be seen from the realization of the whole permutation of the previous question.
FOR EXAMPLE:
```
                                                 n = 3, k = 3
1         1      |      2      |     3           total = 6  
2     2      3   |   1     3   |  1     2        total = 2  
3     3      2   |   3     1   |  2     1        total = 1
      |      |   |   |     |   |  |     |
	  1      2       3     4      5     6
```
**Be careful that the middle colmnu row 2 is `1 -- 3` not `3 -- 1`**

## `Combinations`
### `77. Combinations`
这是一个常规组合问题。This is a conventional combination problem.画出递归树后很容易发现，要想去重只要设置每次只放置比前一个值大的值即可。After drawing the recursive tree, it is easy to find that if you want to deduplicate, you only need to set a value greater than the previous one each time.
`if(now.empty() || now.back() < i)`

```shell
n = 4, k = 2
     1       2       3        4
   / | \   / | \   / | \    / | \
   2 3 4   1 3 4   1 2 4    1 2 3
```
### `39. Combination Sum`
求组合和等于`target`的所有情况。Find all cases where the combined sum is equal to target. I draw the recursive tree again.
```shell
[2,3,6,7] target = 7
       2       C  3         6         7
	/ | | \    / | | \   / | | \   / | | \
	2 3 6 7    2 3 6 7   2 3 6 7   2 3 6 7
	| |        | |
	....
```
If I want to cut the duplicates all I need do is Just find target forward.
### `40. Combination Sum II`
It have same target as `39`, But each number in the `candidates` may only be used once in the combinations. Recursive Tree:
```
[10,1,2,7,6,1,5]  target = 8
    1     1     2     5      6    7   10
  /...\ /...\
  1 2.. 2 5..
         |-> be included by 1
---------------------------------------
[2,5,2,1,2]  target = 5
          1             2   2   2   5
        /...\
      2   2   2
     / \ / \  |
     2 2 2 5  5 
```
这题相对上一题限定了每个元素只能用一次，但是元素值会有重复项。Compared with the previous question, this question limits the use of each element only once, but the element value will have duplicates. 
我之前[*16 May 2020*]用的是：
现在用的是：
1. 承接上一题思路，排序之后`i`元素查找范围限定在`[i + 1, n)`；Following the ideas of the previous question, the search range of the `i` element after sorting is limited to `[i + 1, n)`
2. 遇到重复项，只有在第一次使用重复项时后面的重复项才会被使用。Encountered duplicate items, only the next duplicate items will be used when the duplicate items are used for the first time. 还是这句话：Still this sentence: 
    `if(i > 0 && nums[i] == nums[i - 1] && !L[i - 1]) continue;`
    换而言之，如果前面的`ele[i]`没被用过，那么和`ele[i]`值相等的`ele[i + 1]`也不使用。In other words, if the previous `ele [i]` has not been used, then `ele [i + 1]` with the same value as `ele [i]` will not be used.

## `Find the Kth permutations`

[`1415. The k-th Lexicographical String of All Happy Strings of Length n`](https://leetcode-cn.com/problems/the-k-th-lexicographical-string-of-all-happy-strings-of-length-n/)

```shell
                                                 n = 3, k = 7
1         a      |      b      |     c           k - 1 / 4 == 1  k - 1 % 4 = 2
2     b      c   |   c     a   |  a     b        k / 2     == 1  k % 2 = 0
3   a   c  a   b | a   b  b  c |b   c a   c      k / 1     == 0  so it is bab
```

这个还有一个第k个排列的，这样的题目就是要先画出递归树，然后找到规律，基本上都是取余和取商的过程。	不过这一题我转移矩阵用的真是太帅了。


# Bit manipulation
## `137. Single Number II`
Have I sloved the problem? Yes , at: 5 mothes ago [*2020 28 April*]

Because I just slove a question that find two single number in array. I remember the meaning of a bit. so:
- I divide the array for certain of bit is `0` or `1`

but it will use new space.

Jesus! the solution is so hard to think:
- if a number appear twice all bit is `0`, and if thrice the first bit of `1` will turn to `1` again. so use a variable save the bit appear to `1`

for example: `2,2,3,2`
![from reference](https://pic.leetcode-cn.com/Figures/137/xor.png)

Analysis from example:
```c
[2,2,3,2]
	seen_once ^ num | ~seen_twice | seen_once | seen_twice ^ num | ~seen_once | seen_twice
	                                   0000                                         0000
2      0010               1111         0010          0010              1101         0000
2      0000               1111         0000          0010              1111         0010
3      0011               1101         0001          0001              1110         0000
2      0011               1111         0011          0010              1100         0000
```
it still hard to understand, and others has alanysised:
[137. 只出现一次的数字 II（有限状态自动机 + 位运算，清晰图解）](https://leetcode-cn.com/problems/single-number-ii/solution/single-number-ii-mo-ni-san-jin-zhi-fa-by-jin407891/)

This is really good, from a state machine perspective,
- Focus on observing the number of occurrences of `1` in a certain bit，Because at most 3 times (3 times will be cleared), So there are 3 states, 00, 01, 10; 
- Two variables are needed to maintain this state transition process.

```python
if two == 0: # if two 0; it mean the bit 1 appear 1 or 2 times
  if n == 0: # the number is 0 in this bit, the state maintaining.
    one = one
  if n == 1: # if 1, we will add 1; but to binary: 0 + 1 = 1; 1 + 1 = 0; so we can Directly reverse
    one = ~one 
if two == 1: # if two is 0;
    one = 0
```
[*13 May 2020*]
I. 统计各数字在`bit`位上出现的次数，这个思路要有。Count the number of times each number appears on the bit, this idea must have.
II. 更进一步，如何利用`32`比特位自身的规则记录。Further, how to use the 32-bit own rule record

# Binary
[`1461. 检查一个字符串是否包含所有长度为 K 的二进制子串`](https://leetcode-cn.com/problems/check-if-a-string-contains-all-binary-codes-of-size-k/)
这题一开始也不会做，没有理解二进制的特点呀！！
- [哈希表中存字符串，时间复杂度不是 O(n)，真正的 O(n) 解在这里。](https://leetcode-cn.com/problems/check-if-a-string-contains-all-binary-codes-of-size-k/solution/ha-xi-biao-zhong-cun-zi-fu-chuan-shi-jian-fu-za-du/)这个题解写的真好。

# Binary serach
## `14. Longest Common Prefix`
这个勉强算是一个二分查找的应用吧。This is barely a binary search question. 再优化可以利用分治法两两之间先比较，最终输出。比较过程可以使用二分法。Re-optimization can use the divide-and-conquer method to compare two pairs first, and finally output.The comparison process can use the Binary serach.

## `35. Search Insert Position`
这是二分法的典型应用，用区间搜索的思想很容易写出。This is a typical application of binary search, and it is easy to write with the idea of interval search.总结一下二分法的几个关键点：Summarize the key points of the binary search:
1. 区间，明确输出值的取值范围很重要，是判断end点和循环终止条件的关键。Interval, it is very important to clarify the range of the output value, which is the key to judging the end point and the end condition of the loop.
2. 下标。index比如这题，For example,找到了当然就是输出下标了，if found, of course, you will output the index.找不到呢？输出的其实是**刚好小于这个数的后一位，注意是后一位** If not, The output is actually **just the last digit less than this number, pay attention to the last digit which is smaller than `target`**
`[1,3,5,6] target = 2` The output is `1`, which is position of `1` in the array add 1.
为什么我要强调这个，比如输出整数开根号那题中，二分查找就是刚好大于`target`的结果。Why should I emphasize this? For example, in the problem of outputting the sqrt of a number, the binary search is just the result of being greater than the target.所以返回值是`s - 1`So the return value is `s-1`
`8` the output of binary search is `2 = 3 - 1`

## `34. Find First and Last Position of Element in Sorted Array`
这题是二分法的延伸，找区间，值得注意的是找右区间时记得减去1，原因如上。This question is an extension of the dichotomy. Find the interval. It is worth noting that you should subtract 1 when you find the right interval. The reason is as above.

## `162. Find Peak Element`
找到任意一个峰值即可，我用的方法是二分，但是考察的是`middle`两侧的值，这个有点类似[这题]。You can find any peak. The method I used is Binary Serach, but the values on both sides of the middle are cased. This is similar to [this question].
**others**
```cpp
int findPeakElement(vector<int>& nums) {
        int l=0,r=nums.size();
        while(l<r){
            int mid=l+(r-l)/2;
            if((mid+1<nums.size())&&nums[mid]<nums[mid+1]) l=mid+1;
            else r=mid;
        }
        return l;
    }
```
这种解法，还有其他题目的一些精简解法，本质思想是一样的。This solution, as well as some simplified solutions to other topics, the essential idea is the same.
二分查找，不是左边就是右边。如果能在一个特定的条件下，确实是左边。那超出这个条件就是右边。（这话说着我有点心虚呀- -!）Binary search, either left or right.If it can be under a specific condition, it is indeed the left.That exceeds this condition is the right.(This is saying with a guilty conscience!- -!)

## [33. Search in Rotated Sorted Array](https://leetcode-cn.com/problems/search-in-rotated-sorted-array/) & [81. Search in Rotated Sorted Array II](https://leetcode-cn.com/problems/search-in-rotated-sorted-array-ii/)
旋转了一次的数组中查找，关键是找好度量指标，不然代码写的会很复杂。
正确的判断条件是：

1. `mid`值的左边或右边哪一个是单调的？`if(nums[m] >= nums[s])`则`[s,m]`单调，否则`[m,e]`单调
2. 判断`mid`是否在单调的一端，不在，则在另一端。
```cpp
int search(vector<int>& nums, int target){
	int s = 0, e = nums.size() - 1, m = 0;
	while(s <= e){
		m = (s + e) / 2;
		if(nums[m] == target) return m;
		if(nums[m] >= nums[s]){// s - m -> rised 
		// err 1: there is a =, why need a =?
			if(nums[s] <= target && nums[m] > target){
				e = m;
			}
			else s = m + 1;
		}
		else{//m - e must rised
			if(nums[m] < target && nums[e] >= target){// err 2: not add a =
				s = m + 1;
			}
			else e = m;
		}
	}
	return -1;
}
```
**下面是代码中细节的考量**
- 细节分析，为什么需要额外判断`target < nums[mid]`？为防止单调数组，即未旋转或以`0`旋转的。
```
 0 1 2 3 4
[1,3]   target = 3 without `target < nums[mid]`
sm e
[1,3,5] target = 5
 s m e
 | |
 s < target But the target in the right.
```
- 细节分析，为什么`if(nums[m] >= nums[s])`中`nums[m] == nums[s]`要归为一类？其一，因为是单调无重复的数组，`nums[m] == nums[s]`只有一种情况，就是`m == s`了，其二，要清楚经过此条件判断的作用是什么，是为了划分出来一个确定的单调数组，但此时`nums[e]`不知道是大于还是小于`nums[m]`所以把他划分到左边是比较明智的选择。
```
[3,1] target = 1
sm e
```
- 更新左区间选择`e = m;`也是可以的。
- 为什么`e`初始化为`e = nums.size() - 1`，并判断`while(s <= e)`？这两点是绑定的，因为`e`被初始化如上，所以`while`中需要加上`=`，因为下标的取值范围是`[0,n - 1]`所以，要么`e = nums.size()`配上`while(s < e)`，要么如上。但为什么一定要初始化为`e = nums.size() - 1`呢，因为`nums[e]`将会作为一个标准在循环中被用到。

[`81. Search in Rotated Sorted Array II`](https://leetcode-cn.com/problems/search-in-rotated-sorted-array-ii/) As same as [`33. Search in Rotated Sorted Array`](https://leetcode-cn.com/problems/search-in-rotated-sorted-array/)

[**There is a good solution  Reference**](https://leetcode-cn.com/problems/search-in-rotated-sorted-array-ii/solution/zai-javazhong-ji-bai-liao-100de-yong-hu-by-reedfan/)

Error 1:可以看出来，这个`if(nums[m] < target && nums[m] < nums[e])`不足以判断，目标在`m`的左边还是右边。还是要换成`if(nums[m] < target && target < nums[e])`
```
   0    1     2
   5    1     3   target = 5
   s    m     e
```
Error 2: 基于error1: `if(nums[m] < target && target < nums[e])`之后因为要`s = m + 1`或者`e = m`,因此，若`nums[e] == target`就会错失正确答案。要断定`target`等于边界值时的区域归属。

Error2:
```
   0    1     2
   5    1     3   target = 3
   s    m     e
```

## [74. Search a 2D Matrix](https://leetcode-cn.com/problems/search-a-2d-matrix/)
常规的二分查找题，注意题目是问有没有值在矩阵其中，如果`int s = 0, e = r * c`并且`while(s < e)`可能最后会超出边界，即退出的时候是`s = r * c`，因为最后需要考虑`nums[s] == target`，此时就有可能报错。应加判断`return s != r * c && matrix[x][y] == target;`
**或者：**
初始化为：`int s = 0, e = r * c - 1`，判别为：`while(s <= e)`，但是要注意，更新右值时使用：`e = m - 1;`否则：`[[1,1]] target = 0` endless Loop.

[378. 有序矩阵中第K小的元素](https://leetcode-cn.com/problems/kth-smallest-element-in-a-sorted-matrix/)

这个题用二分法的时候还是有很多需要注意的地方的。
因为虽然对值二分，但是最终需要这个值是刚好`<=`左边界。但是为了避免死循环e和s的取值方法不变，变的就是当值相等的时候，是左边还是查找左边还是右边？

```c++
int kthSmallest(vector<vector<int>>& mtx, int k) {
        int n = mtx.size();
        int s = mtx[0][0], e = mtx[n - 1][n - 1], m = 0;
        while(s < e){
            m = s + ( e - s ) / 2;
            int smt = 0, c = 0;
            for(int i = n - 1; i >= 0; --i){
                while(c < n && mtx[i][c] <= m) ++c;
                smt += c;
            }
            if(smt >= k) e = m;
            else s = m + 1;
        }
        return s;
    }
```

事后分析，满足条件是分给左边即`e = m`，因为退出循环的时候一定是`s == e`，那么相等的情况分给左边就有可能取到等值。

# Design

## `146. LRU(Least Recently Used) Cache`
**错了几次，过一段时间再写写看。**

# Double pointers
## fast & slow
[`80. 删除排序数组中的重复项 II`](https://leetcode-cn.com/problems/remove-duplicates-from-sorted-array-ii/)


## [355. Design Twitter](https://leetcode-cn.com/problems/design-twitter/)


# Dynamic Programming
[1. Reference Classification](https://zhuanlan.zhihu.com/p/126546914)

## `53. Maximum Subarray`
连续子数组。Unexpectedly, dynamic programming came so fast, continuous sub-arrays.
记得一开始是没想到动态规划的，一开始是想既然是连续子数组，那前缀和加双指针能解决。I remember that I didn't expect dynamic programming at the beginning. At the beginning, I thought that since it is a continuous subarray, the prefix and double pointers can be solved.
为什么可以用动态规划，这个思想是最重要的。Why dynamic programming can be used is the most important idea.

## Array
### [1458. Max Dot Product of Two Subsequences](https://leetcode-cn.com/problems/max-dot-product-of-two-subsequences/)

## knapsack
### [1449. Form Largest Integer With Digits That Add up to Target](https://leetcode-cn.com/problems/form-largest-integer-with-digits-that-add-up-to-target/)
这个题本身不难，是明显的`完全背包`问题，但是边界条件怎么选是重点：This question is not difficult in itself, it is obviously a `complete knapsack` problem, but how to choose the boundary conditions is the key:
1. 什么都不给，需要凑出一系列`target`是不可能的。Nothing is given, it is impossible to make a series of `target`. 
2. 给了一堆数，凑出是`target = 0`是空。Gave a bunch of numbers, and it came out that `target = 0` is empty.


## Stock related 
[Good reference](https://leetcode-cn.com/problems/best-time-to-buy-and-sell-stock/solution/yi-ge-fang-fa-tuan-mie-6-dao-gu-piao-wen-ti-by-l-3/)

### `121. Best Time to Buy and Sell Stock`
感觉还是不是很清楚还需要多看看。I still don't feel very clear. I need to see more.
```cpp
int maxProfit(vector<int>& prs) {
        int n = prs.size();
        int dp_i_1_1 = -1e9, dp_i_1_0 = 0, dp_i_0_0 = 0, dp_i_0_1 = -1e9;
        for(int i = 0; i < n; ++i){
            dp_i_1_0 = max(dp_i_1_0,dp_i_1_1 + prs[i]);
            dp_i_1_1 = max(dp_i_1_1,dp_i_0_0 - prs[i]);
        }
        return dp_i_1_0;
    }
```
`dp_i_1_1` 三个下划线分割的意思分别是：第`i`天，交易了`1`或`0`次，目前手上是持有`1`或没有`0`股票。The meaning of the three underscores is: on the `i` day, the` 1` or `0` transaction was traded, currently holding` 1` or `0` no stock.

初始化的时候虽然我写的也是`i`天，但其实是第`0`天啦。Although I wrote the `i` day during initialization, it was actually the` 0` day. 在第`0`天，持有股票是不可能事件，可以将这种情况设置为成本极高`-1e9`，不持有股票的成本是`0`。On the day of `0`, holding stocks is an impossible event. You can set this to an extremely high cost of` -1e9`, and the cost of not holding stocks is `0`.

### `122. Best Time to Buy and Sell Stock II`
没有交易次数限制就是减少一个维度 No limit on the number of transactions is to reduce one dimension
```cpp
int maxProfit(vector<int>& prices) {
        int dp_i_0 = 0, dp_i_1 = -1e9, n = prices.size();
        for(int i = 0; i < n; ++i){
            dp_i_0 = max(dp_i_0,dp_i_1 + prices[i]);
            dp_i_1 = max(dp_i_1,dp_i_0 - prices[i]);
        }
        return dp_i_0;
    }
```

## 掷骰子

[`837. 新21点`](https://leetcode-cn.com/problems/new-21-game/)虽然不是掷骰子，但是很想，得分是`1~W`求得分在大于等于`K`时小于`N`的概率。时间复杂度要求较高，关键还是能准确的推出递推公式。可以用类似前缀和的思想优化之。
 - [反推的代表，官方题解](https://leetcode-cn.com/problems/new-21-game/solution/xin-21dian-by-leetcode-solution/)
 - 正推的代表在官解的评论中，如下：
```cpp
// dp[i] = sum { dp[i - {min(W, 1), 1}] * (1 / W) }
// 1 --> dp[1] = dp[0] *=  1 / W 
// 2 --> dp[2] = (dp[0]  + dp[1]) / W
// 3 --> dp[3] = (dp[0] + dp[1] + .. ) / W
// dp[i] = prefix[min(i - 1, K) ,max(i - K, 0)] 前缀和优化

using db = double;
const int N = 2e5 + 5;
db dp[N], prefix[N];

class Solution {
public:
    double new21Game(int N, int K, int W) {
        db ans = 0.0;
        if (K == 0) return 1.0;
        memset(dp, 0, sizeof(dp));
        memset(prefix, 0, sizeof(prefix));

        dp[0] = prefix[0] = 1;

        for (int i = 1; i <= K + W; ++ i){
            dp[i] = db(1.0 / W) * (prefix[min(i - 1, K - 1)] - (i - W <= 0 ? 0 : prefix[i - W - 1]));
            prefix[i] = (dp[i] + prefix[i - 1]);
        }
        ans = prefix[min(N, K + W - 1)] - prefix[K - 1];

        return ans;
    }
};
```

## Matrix

`221. Maximal Square`

这道题就比较容易看出来是动态规划。而且递推方程也好写。

[`1504. 统计全 1 子矩形`](https://leetcode-cn.com/problems/count-submatrices-with-all-ones/) & [`85. 最大矩形`](https://leetcode-cn.com/problems/maximal-rectangle/)

这两道题相当于最大正方形的加强版，思考方式略有不同。参考[动态规划 - 使用柱状图的优化暴力方法](<https://leetcode-cn.com/problems/maximal-rectangle/solution/zui-da-ju-xing-by-leetcode/>) 主要是需要一个矩阵`D[i][j]`保存第`i`行以上`j`列以左连续`1`的个数。

- 对于`1504`题，如果`D[i][j] == 3`那么，在遍历到`i,j`时，其能组成的矩阵个数就是`min(mn,D[i][j]) + pre`，当然此题还需要一个记录以`i,j`结尾的矩形的个数。
- 对于`85`，则需要一个记录最大矩形的矩阵。

## string

[`139. 单词拆分`](https://leetcode-cn.com/problems/word-break/)& [`面试题 17.13. 恢复空格`](https://leetcode-cn.com/problems/re-space-lcci/)

这两道题类似，都是用`dictionary`的单词尽可能匹配字符串的题目，`139`相对单调点，只需要说明是或者不是即可，`17.13`则要返回前端有多少不是的。需要注意的是要清楚`最大匹配个数`的概念，即不可拆分单词。



## 石头游戏

[石子游戏](https://leetcode-cn.com/problems/stone-game/) 

# Graph

[`1462. 课程安排 IV`](https://leetcode-cn.com/problems/course-schedule-iv/)
这题用的数据结构算是邻接矩阵吧，一开始我用的是邻接表，显然很蠢。

- [并查集思想 双百](https://leetcode-cn.com/problems/course-schedule-iv/solution/bing-cha-ji-si-xiang-shuang-bai-by-tiooo/)这个并查集很牛逼，很牛逼。
- [Floyd也可以，但是效率稍弱一点](https://leetcode-cn.com/problems/course-schedule-iv/solution/floyd-by-over-lord/)

## 优化

搜索过程如何优化，目前接触到两种

1. 利用优先队列`priority_queue`对待处理的队列进行排序，典型如[1514. 概率最大的路径](https://leetcode-cn.com/problems/path-with-maximum-probability/)。
2. 双向广度优先搜索，典型如[127. 单词接龙](https://leetcode-cn.com/problems/word-ladder/) 解释:

> 广度优先搜索的搜索空间大小依赖于每层节点的分支数量。假如每个节点的分支数量相同，搜索空间会随着层数的增长指数级的增加。考虑一个简单的二叉树，每一层都是满二叉树的扩展，节点的数量会以 2 为底数呈指数增长。
> [作者：LeetCode|链接](https://leetcode-cn.com/problems/word-ladder/solution/dan-ci-jie-long-by-leetcode/)

```c++
class Solution {
public:
    int ladderLength(string beginWord, string endWord, vector<string>& wordList) {
        unordered_set<string> wordSet (wordList.begin(), wordList.end());
        if(!wordSet.count(endWord)) return 0;
        unordered_set<string> beginSet {beginWord};
        unordered_set<string> endSet {endWord};

        int stepcount = 1;
        int n = wordList.size();
        int wordsize = beginWord.size();
        while(beginSet.size()){
            ++stepcount;
            unordered_set<string> nextSet;
            for(string s : beginSet){
                wordSet.erase(s); // 从原数据集里删除
            }            
            for(auto &str : beginSet){
                for(int i = 0; i < wordsize; ++i){
                    string s = str;
                    for(char j = 'a'; j <= 'z'; ++j){ //这样找固定就找26次，如果直接在wordset里找不知道要找多少次呢
                        s[i] = j;
                        if(!wordSet.count(s)) continue;
                        if(endSet.count(s)) return stepcount;
                        else{
                            nextSet.emplace(s);
                        }
                    }
                }
            }
            beginSet = move(nextSet);// move用的好呀
            if(beginSet.size() > endSet.size()) swap(beginSet, endSet); //swap 每次只处理较短的队列
        }
        return 0;
    }
};
```

# Greedy
以跳跃游戏为例，是贪心算法。如何从题目中分离出是贪心算法才是关键。Take the jump game as an example, it is a greedy algorithm.How to separate from the problem is the greedy algorithm is the key. 此外还有一些细节需要考虑：There are also some details to consider:
1. 跳（动作）、在一个范围内搜索、选择下一次跳跃点（同时也会确定下一次搜索范围）是三个分开的过程。Jumping (the action), searching within a range, and selecting the next jump point (also determining the next search range) are three separate processes. 保险起见，一开始可以申请尽可能多的变量，以免死循环。For insurance purposes, you can apply for as many variables as possible to avoid endless loops.


# Hash
## `1. two sum`
[*13 May 2020*]
这是一个基础题，但是解题思想很常用。This is a basic question, but the idea of solving the problem is very common

1. 通过排序`O(N logN)` 降低时间复杂度。Reduce time complexity by sorting with `O (N logN)`.
2. 利用`hash`的特点，用空间换时间。将查找组合问题换成了固定一个数在`hash`中找另一个数的问题。Use the features of `hash` to trade space for time.Replace the search combination problem with the problem of fixing one number to find another number in `hash`.


# Integer boundary
## `7. Reverse Integer`
[*1st January 2020*] 
`error 1` 0 value
`error 2` `-2147483648` only the `INT_MIN` cannot reverse to positive directly.
[*14 May 2020*]
`error 3` `1534236469` when reversed it may beyond boundary.

## `50. Pow(x, n)`
I sloved it again [*6 May 2020*] with an error:
`error 1: ` ` n1 = - n; //if n = -2147483648; it error!` How to convert it should be noted.
转换负数为正数时，要先强制类型转换成`long long`，不然也是溢出。When converting negative numbers to positive numbers, you must first cast the type to `long long`, otherwise it will also integer overflow
`ll pow = (flag ? n : -(ll)n); // Attention`

# Link
## `21. Merge Two Sorted Lists`
这个是基础，太重要了，必须快速、准确的写出代码。This is the foundation, which is too important. The code must be written quickly and accurately.

## Two array or links
[`2. Add Two Numbers`](https://leetcode-cn.com/problems/add-two-numbers/)  You can read more details
[`88. Merge Sorted Array` ](https://leetcode-cn.com/problems/merge-sorted-array/)

## Ring
[`287. Find the Duplicate Number`](https://leetcode-cn.com/problems/find-the-duplicate-number/) & 
抽象一层来分析这个题目，如何想到是快慢指针，如何与环联系思考？
首先限定时间复杂度`O(n^2)`以下，要么`O(nlogn)`，要么是`O(n)`；
数字值域为`[1,n]`，重复次数不定。展开看确实像一个链表，如下图`s`指示：

```shell
 0 1 2 3 4
[3,1,3,4,2]

s 0|3 -> 3|4 -> 4|2 -> 2|3 -> 3|4 -> 4|2 -> 
 - - - - - - - - - - - - - - - - - - - - - - - - -
f 0|3 -> 4|2 -> 3|4 -> 2|3 -> 4|2 -> 3|4 ->

          |   <--  cycle  -->  | So There is no way to break the loop of while(s == f || nums[s] != nums[f]);
```

## Reverse

[`206. Reverse Linked List`](https://leetcode-cn.com/problems/reverse-linked-list/)

两种实现方法，主要关注迭代法。关键点：需要两个记录指针和一个临时指针。

```c++
ListNode* reverseList(ListNode* head) {
        ListNode* pre = head; //指向当前处理指针的前一个指针
        if(head){
            ListNode* cur = head->next;//指向当前需要改变next指向的指针
            while(cur){
                ListNode* nt = cur->next;//临时指针，就是为了记录cur没改之前指向的指针
                cur->next = pre;
                pre = cur;
                cur = nt;
            }
            head->next = nullptr;
            head = pre;
        }
        return head;
    }
```

[92. Reverse Linked List II](https://leetcode-cn.com/problems/reverse-linked-list-ii/)

此题难度稍微提升了一点，就是只反转制定区间的link，相比之前的，需要记录的值多了**`1`个**。

```c++
ListNode* reverseBetween(ListNode* head, int m, int n) {
        ListNode* dm = new ListNode(-1);
        dm->next = head;
        ListNode* dh = dm;//dh 指向反转区间[m,n]中m的前一个link
        for(int i = 1; i < m; ++i) dh = dh->next;

        ListNode* pre = dh->next, *cur = pre->next;//常规反转
        for(int i = m; i < n; ++i){//不同点是反转结束的条件不再是cur == nullptr了
            ListNode* nt = cur->next;
            cur->next = pre;
            pre = cur;
            cur = nt;
        }
    /*无论反转了多少个最后退出时一定是这样的：
    dm->1->2<-3<-4...<-i | i + 1-> i + 2->...
        |              | 断  |
       dh             pre   cur
    */
        dh->next->next = cur;//如上图需要让link(2)指向link(i + 1)
        dh->next = pre; //link(1)指向link(i)
        head = dm->next;
        delete dm;dm = nullptr;
        return head;
    }
```



# Pattern matching

## `28. Implement strStr()`
此题就是KMP算法的实现，关键是理解KMP的思想，可能会有变种，比如之前做过一个树形匹配。This question is the realization of KMP algorithm, the key is to understand the idea of KMP, there may be variants, such as doing a tree match before.
[参考：KMP 算法详解](https://leetcode-cn.com/problems/implement-strstr/solution/kmp-suan-fa-xiang-jie-by-labuladong/)
KMP关键点是通过模式串的信息生成状态转换表，使得匹配串不至于退回。The Key point of KMP is to generate a state transition table through the information of the `pattern` string, so that the index of matching string `text` will not be returned.

# Martix index
## `48. Rotate Image`
顺时针旋转矩阵，我记得我是直接找下标的规律，但是找的时间比较久。如何快速解决这些题目？Rotating the matrix clockwise, I remember I was looking directly for the rule of index, but it took longer to find.How to solve these problems quickly?
方案1 通过转置矩阵 Use Transpose matrix
可以看到，转置之后行反转和列反转就能分别得到逆时针和顺时针的结果。It can be seen that after the transposition, the row inversion and column inversion can obtain the results of counterclockwise and clockwise, respectively.

```
a =                       | a.T                      |Counterclockwise rot90(a,1)|
array([[ 0,  1,  2,  3],  |array([[ 0,  4,  8, 12],  |array([[ 3,  7, 11, 15],   |
       [ 4,  5,  6,  7],  |       [ 1,  5,  9, 13],  |       [ 2,  6, 10, 14],   |
       [ 8,  9, 10, 11],  |       [ 2,  6, 10, 14],  |       [ 1,  5,  9, 13],   |
       [12, 13, 14, 15]]) |       [ 3,  7, 11, 15]]) |       [ 0,  4,  8, 12]])  |

                          |clockwise rot90(a,-1)
                          |array([[12,  8,  4,  0],
                          |       [13,  9,  5,  1],
                          |       [14, 10,  6,  2],
                          |       [15, 11,  7,  3]])
```
方案2 如前序所述As mentioned in the preface
类似的题目还有一个什么螺旋打印矩阵。There is a spiral printing matrix for a similar problem.

# Others
## `670. Maximum Swap`
最多一次交换。所以要尽可能将最大值放在最高位。At most one exchange.Therefore, the maximum value should be placed as high as possible.
我用的方法和题解第二个类似The method I used is similar to the second item.
- 首先一次遍历记录最大值，及其位置。First traverse the record maximum value and its position
- 然后二次遍历，从高往低，找到比该位最大值小的位，交换。Then traverse twice, from high to low, find the bit smaller than the maximum value of the bit, and exchange.
```
idx  0 1 2 3 
v    2 7 3 6
                <- get max
max  7 7 6 6
     |-> exchange 1 and idx 0
maid 1 1 3 3
```



# Sliding Windows

## `209. Minimum Size Subarray Sum`
这个题限定了是正整数，目标和**范围**，求最小连续子数组。已经很明显是滑动窗口了。This question is limited to positive integers, range of target sums, and finding the minimal length of continuous sub-array.It is clearly a sliding window.

# Sort

[324. 摆动排序 II](https://leetcode-cn.com/problems/wiggle-sort-ii/)看到**快速选择算法**，了解了一下，快速选择算法的时间复杂度近似为`O(n)`但最坏任然是`O(n^2)`，因此每次最好随机选取一个基准。

`Time complexity`:

```python
# 第一次 数组长度n 全部跑一遍， 假设出现一般情况找到第k个位置，数组被分为了[0,k - 1],[k + 1,n - 1]
# 第二次 假设目标在大的那边需要在跑一遍k长度的数组
# ...
# 因为一般情况都是折半的，因此cost是：n -> n/2 -> n/4 -> ... -> 2 -> 1 等差数列，但是可以看出，后一次结果不会大于第一次遍历长度(n/i > n/2i)因此，极限收敛至O(2n)。
```

## 3-ways-patition

上面那题，还有一个荷兰国旗题都是关于这个`3-ways-patiton`算法的。



## Merge Sort

[315. 计算右侧小于当前元素的个数](https://leetcode-cn.com/problems/count-of-smaller-numbers-after-self/) & [剑指 Offer 51. 数组中的逆序对](https://leetcode-cn.com/problems/shu-zu-zhong-de-ni-xu-dui-lcof/)

本质还是并归排序，看看递归和非递归咋写的。

#### [148. 排序链表](https://leetcode-cn.com/problems/sort-list/) 链表并归 

`Time complexity: O(nlogn), space complexity: O(1)`

```c++
class Solution {
    ListNode* merge2(ListNode* l1, ListNode* l2){
        ListNode* dm = new ListNode(-1);
        ListNode* pre = dm;
        while(l1 && l2){
            if(l1->val > l2->val){
                pre->next = l2;
                l2 = l2->next;
            }
            else{
                pre->next = l1;
                l1 = l1->next;
            }
            pre = pre->next;
        }
        pre->next = l1?l1:l2;
        pre = dm->next;
        return pre;
    }
public:
    ListNode* sortList(ListNode* head) {
        int n = 0;
        ListNode* t = head;
        for(;t;t = t->next) ++n;
        
        ListNode *dm = new ListNode(-1), *dpre = dm;
        for(int i = 1; i < n; i *= 2){
            int c = i;
            t = head;
            dpre = dm;
            while(t){
                ListNode * first = t, *pre = nullptr;
                c = i;
                while(t && c--) {
                    pre = t;
                    t = t->next;
                }
                pre->next = nullptr;
                c = i;
                ListNode* second = t;
                while(t && c--){
                    pre = t;
                    t = t->next;
                }
                pre->next = nullptr;
                dpre->next = merge2(first,second);
                dpre = t;
            }
        }
        head = dm->next;
        delete dm; dm = nullptr;
        return head;
    }
};
```



# Stack
## `20. Valid Parentheses`
`Error 2` 写得不优雅就算了，上次被空串坑，这次又被`"["` 难倒了。哎
Even if it is not elegant, the last time I was pitted by an empty string, this time I was stumped by `"["`.
`Error 3` 用栈可以很优雅。Using the stack can be very elegant.但是也被坑了一次But also got pitted once `"]"` Be careful when pop from a stack!!


# String
[`151. Reverse Words in a String`](https://leetcode-cn.com/problems/reverse-words-in-a-string/)
这个流的运用还蛮有用的，细节可参考[stringstream的用法](https://zhuanlan.zhihu.com/p/44435521)：

```c++
istringstream ss(s);
string w;
while(ss >> w){ }

/*分隔逗号*/
std::string input ="abc,def,ghi";
std::istringstream ss(input);
std::string token;

while(std::getline(ss, token, ',')) {
 std::cout << token << 'n';
}
```

`String`头文件中还提供了多种`string to integer/folat/double/long`的接口函数：

> [C++字符串转换（stoi；stol；stoul；stoll；stoull；stof；stod；stold）](<https://blog.csdn.net/baidu_34884208/article/details/88342844>) 支持各种进制的`string`转换成`int`
>
> `ul`: `unsigned long`

# Tree

## `235. Lowest Common Ancestor of a Binary Search Tree`
二叉搜索树的LCA，第一次将两个数值分开的节点就是了。For the LCA of the binary search tree, the first time is to separate the two values. 考虑到边界，其实就是只要不是同时严格大于或者严格小于的节点。Considering the boundary, in fact, as long as it is not a node that is strictly greater than or strictly less than is the LCA.
以下，非递归，我觉得写的挺好的：The following, non-recursive, I think it is written very well

```cpp
TreeNode* lowestCommonAncestor(TreeNode* root, TreeNode* p, TreeNode* q) {
        if (root == nullptr || p == nullptr || q == nullptr) return nullptr;
	
	TreeNode* ptemp = root;
	
	while (ptemp)
	{
		if (ptemp->val > p->val && ptemp->val > q->val) ptemp = ptemp->left;
		else if (ptemp->val < p->val && ptemp->val < q->val) ptemp = ptemp->right;
		else return ptemp;
	}

	return nullptr;
}
```

## `236. Lowest Common Ancestor of a Binary Tree`
经典LCA，我好像只会用带vector记录路径的方法。Classic LCA, I seem to only use the method of recording paths with vector.

**others**
参考图解[Reference illustration](https://leetcode-cn.com/problems/lowest-common-ancestor-of-a-binary-tree/solution/236-er-cha-shu-de-zui-jin-gong-gong-zu-xian-hou-xu/)

```cpp
class Solution {
public:
    TreeNode* lowestCommonAncestor(TreeNode* root, TreeNode* p, TreeNode* q) {
        if(root == NULL)
            return NULL;
        if(root == p || root == q) //1. Found! return the node
            return root;
            
        TreeNode* left =  lowestCommonAncestor(root->left, p, q);
        TreeNode* right = lowestCommonAncestor(root->right, p, q);//2. receive the node
       
        if(left == NULL) //3. if left empty, return right
            return right;
        if(right == NULL)
            return left;      
        if(left && right) // p和q在两侧
            return root;
        
        return NULL; // 必须有返回值
    }
};
```

## `98. Validate Binary Search Tree`
还是中序遍历好，记得设置记录前值的`pre`为`long long`。It is better to traverse in order, remember to set the `pre` value of the record to `long long`.

## `617. Merge Two Binary Trees`
```cpp
TreeNode* mergeTrees(TreeNode* t1, TreeNode* t2) {
    if(!t1) return t2;
    if(!t2) return t1;
    t1->val += t2->val;
    t1->left = mergeTrees(t1->left,t2->left);
    t1->right = mergeTrees(t1->right,t2->right);
    return t1;
}
```
看别人写的就很精简。It is very simple to read what others have written.

## 二叉树的遍历
[迭代方法](https://leetcode-cn.com/problems/binary-tree-postorder-traversal/solution/mo-fang-di-gui-zhi-bian-yi-xing-by-sonp/)
```cpp
class Solution {
public:
    vector<int> postorderTraversal(TreeNode* root) {
        vector<int> res;
        stack<TreeNode*> call;
        if(root!=nullptr) call.push(root);
        while(!call.empty()){
            TreeNode *t = call.top();
            call.pop();
            if(t!=nullptr){
                call.push(t);  //在右节点之前重新插入该节点，以便在最后处理（访问值）
                call.push(nullptr); //nullptr跟随t插入，标识已经访问过，还没有被处理
                if(t->right) call.push(t->right);
                if(t->left) call.push(t->left);
            }else{
                res.push_back(call.top()->val);
                call.pop();
            }
        }
        return res;   
    }
};
```
## 线段树

[Vedio ](<https://www.bilibili.com/video/BV1ep4y197JE>)

[线段树详解 （原理，实现与应用）](https://www.cnblogs.com/AC-King/p/7789013.html)

> 

# Trouble

这里是一些暴力模拟的题目，虽说是暴力模拟，但是能有清晰的思路也很重要！

[面试题 16.18. 模式匹配](https://leetcode-cn.com/problems/pattern-matching-lcci/)



# Two pointers

