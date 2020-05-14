**A summary with Algorithm**
旨在通过归纳总结做过的习题以及遇到的问题，抽象提炼以完善自身思维和代码能力。
It aims at summarizing the exercises and problems encountered, and abstracting them to improve my thoughts and coding skills.

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

# Dynamic Programming
## `53. Maximum Subarray`
没想到动态规划这么快就来了，连续子数组。Unexpectedly, dynamic programming came so fast, continuous sub-arrays.
记得一开始是没想到动态规划的，一开始是想既然是连续子数组，那前缀和加双指针能解决。I remember that I didn't expect dynamic programming at the beginning. At the beginning, I thought that since it is a continuous subarray, the prefix and double pointers can be solved.
为什么可以用动态规划，这个思想是最重要的。Why dynamic programming can be used is the most important idea.



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

# Stack
## `20. Valid Parentheses`
`Error 2` 写得不优雅就算了，上次被空串坑，这次又被`"["` 难倒了。哎
Even if it is not elegant, the last time I was pitted by an empty string, this time I was stumped by `"["`.
`Error 3` 用栈可以很优雅。Using the stack can be very elegant.但是也被坑了一次But also got pitted once `"]"` Be careful when pop from a stack!!

# Link
## `21. Merge Two Sorted Lists`
这个是基础，太重要了，必须快速、准确的写出代码。This is the foundation, which is too important. The code must be written quickly and accurately.

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
