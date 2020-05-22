**A summary with Algorithm**
旨在通过归纳总结做过的习题以及遇到的问题，抽象提炼以完善自身思维和代码能力。
It aims at summarizing the exercises and problems encountered, and abstracting them to improve my thoughts and coding skills.

# array
## Trapping Rain Water
- [`42. Trapping Rain Water`](https://leetcode-cn.com/problems/trapping-rain-water/)接雨水相关的，因为是短边决定的雨水量，因此每次只移动短边即可。It is related to rainwater, because it is the amount of rainwater determined by the short side, so you only need to move the short side each time.



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
```
n = 4, k = 2
     1       2       3        4
   / | \   / | \   / | \    / | \
   2 3 4   1 3 4   1 2 4    1 2 3
```
### `39. Combination Sum`
求组合和等于`target`的所有情况。Find all cases where the combined sum is equal to target. I draw the recursive tree again.
```
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

# bit manipulation
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

```python3
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
二分查找，不是左边就是右边。如果能在一个特定的条件下，确实是左边。那超出这个条件就是右边。（这话说着我有点心虚呀- -!）Binary search, either left or right.If it can be under a specific condition, it is indeed the left.That exceeds this condition is the right.(This is saying with a guilty conscience--!)


# Dynamic Programming
## `53. Maximum Subarray`
连续子数组。Unexpectedly, dynamic programming came so fast, continuous sub-arrays.
记得一开始是没想到动态规划的，一开始是想既然是连续子数组，那前缀和加双指针能解决。I remember that I didn't expect dynamic programming at the beginning. At the beginning, I thought that since it is a continuous subarray, the prefix and double pointers can be solved.
为什么可以用动态规划，这个思想是最重要的。Why dynamic programming can be used is the most important idea.

## `221. Maximal Square`
这道题就比较容易看出来是动态规划。而且递推方程也好写。This question is easier to see as dynamic programming.And recursive equations are also easy to write.

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

# Greedy
以跳跃游戏为例，是贪心算法。如何从题目中分离出是贪心算法才是关键。Take the jump game as an example, it is a greedy algorithm.How to separate from the problem is the greedy algorithm is the key. 此外还有一些细节需要考虑：There are also some details to consider:
1. 跳（动作）、在一个范围内搜索、选择下一次跳跃点（同时也会确定下一次搜索范围）是三个分开的过程。Jumping (the action), searching within a range, and selecting the next jump point (also determining the next search range) are three separate processes. 保险起见，一开始可以申请尽可能多的变量，以免死循环。For insurance purposes, you can apply for as many variables as possible to avoid endless loops.


# hash
## `two sum`
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


# Stack
## `20. Valid Parentheses`
`Error 2` 写得不优雅就算了，上次被空串坑，这次又被`"["` 难倒了。哎
Even if it is not elegant, the last time I was pitted by an empty string, this time I was stumped by `"["`.
`Error 3` 用栈可以很优雅。Using the stack can be very elegant.但是也被坑了一次But also got pitted once `"]"` Be careful when pop from a stack!!


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


# Two pointers

