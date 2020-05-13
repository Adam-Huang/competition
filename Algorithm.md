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

# hash
## `two sum`
[*13 May 2020*]
这是一个基础题，但是解题思想很常用。This is a basic question, but the idea of solving the problem is very common
1. 通过排序`O(N logN)` 降低时间复杂度。Reduce time complexity by sorting with `O (N logN)`.
2. 利用`hash`的特点，用空间换时间。将查找组合问题换成了固定一个数在`hash`中找另一个数的问题。Use the features of `hash` to trade space for time.Replace the search combination problem with the problem of fixing one number to find another number in `hash`.

