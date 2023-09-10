# 力扣算法
## 十大排序算法
- 代码详情[冒泡排序](./sort/bubble.cpp)

    1）比较相邻的元素。如果第一个比第二个大，就交换他们两个

    2）对每一对相邻元素作相同的工作，从开始第一对到结尾的最后一对，这样在最后的原始应该会是最大的数
    
    3）针对所有的元素重复以上的步骤，除了最后一个
    
    4）重复步骤1~3，直至排序完成
- 代码详情[插入排序](./sort/insert.cpp)
    
    1）分为已排序和未排序，初始已排序区间只有一个元素，就是数组第一个，遍历未排序的每一个元素在已排序区间里找到合适的位置插入并保证数据一直有序
- 代码详情[选择排序](./sort/select.cpp)

    1）分为已排序区和未排序区。每次从未排序区间找到最小的元素，将其放到排序区间末尾
- 代码详情[快速排序](./sort/quicksort.cpp)

    1）先找到一个枢纽，在原来的元素里根据这个枢纽划分，比这个枢纽小的元素排在前面；比这个枢纽大的排在后面；两部分数据一次递归排序下去，直到最终有序

- 代码详情[归并排序](./sort/mergesort.cpp)

    1）使用两个游标i,j，分别指向a[p...q]和a[q+1...r]的第一个元素。比较这两个元素A[i]和A[j]，如果A[i] <= A[j]，我们就把A[i]放到临时数组temp中，并且i向后移动一位，否则将A[j]放入到temp，j后移一位

- 代码详情[堆排序](./sort/heapsort.cpp)：利用堆这种数据结构所设计的一种排序算法。堆积是一个近似完全二叉树的结构，并同时满足堆积的性质：即子节点的键值或索引总是小于（大于）它的父节点。堆排序可以利用到上一次的排序结果，所以不像其它一般排序方法一样，每次都要进行n-1次比较，复杂度为O(logn)

    1）利用一个给定数组创建一个堆H[0...n-1],输出堆顶元素

    2）以最后一个元素代替堆顶，调整成堆，输出堆顶元素
    
    3）把堆的尺寸缩小1
    
    4）重复步骤2，直到堆的尺寸为1
    
    建堆：将数组原地建成一个堆，不需要额外的空间，采用从上往下的堆化（对于完全二叉树来说，下标是n/2+1到n的节点都是叶子结点，不需要堆化）

    排序：“删除堆顶元素”：当堆顶元素移除之后，把下标为n的元素放到堆顶，然后通过堆化的方法，将剩下的n-1个元素重新构建成堆，堆化完成后，再取堆顶元素，放在下标为n-1的位置，一直重复这个过程，直到最后堆栈中只剩下标为1的一个元素

- 代码详情[桶排序](./sort/bucket.cpp)：将数组分到有限数量的桶中。再对每个桶个别排序（有可能再使用别的排序算法或者是以递归方式继续使用桶排序进行排序）

- 代码详情[计数排序](./sort/countsort.cpp)：前提条件，待排序的数一定要满足一定范围的整数，而且计数排序需要比较多的辅助空间。其基本思想是，用待排序的数作为计数数组的下标，统计每个数字的个数。然后依次输出可得到有序序列

- 代码详情[基数排序](./sort/radixsort.cpp)：基数排序对要排序的数据是有要求的，需要可以分割出独立的“位”来比较，而且位之间有递进的关系，如果a数据的高位比b数据大，那剩下的低位就不用比较了。除此之外，每一位的数据范围不能太大，要可以用线性排序算法来排序，否则，基数排序的时间复杂度无法做到O(n)了。基数排序相当于循环做了多次桶排序

- 代码详情[希尔排序](./sort/shellsort.cpp)：通过将比较的全部元素分为几个区域来提升插入排序的性能。这样可以让一个元素可以一次性地朝最终位置前进一大步。然后算法再取越来越小的步长进行排序，算法的最后一步就是普通的插入排序，但是到了这一步，需要排序的数据几乎是已经排序好的了

## 数组
- 27 [删除元素](./array/27/removeElement.cpp)
- 977 [有序数组的平方](./array/977/sortedSquares.cpp)
- 209 [长度最小的子数组](./array/209/minSubArrayLen.cpp)
- 59 [螺旋矩阵II](./array/59/generateMatrix.cpp)
- 54 [螺旋矩阵](./array/54/spiralOrder.cpp)
- 560 [和为K的子数组](./array/560/subarraySum.cpp)
- 239 [滑动窗口最大值](./array/239/maxSlidingWindow.cpp)
- 189 [轮转数组](./array/189/rotate.cpp)
- 238 [除自身以外数组的乘积](./array/238/productExceptSelf.cpp)
- 48 [旋转图像](./array/48/rotate.cpp)

## 链表
- 24 [两两交换链表中的节点](./link_list/24/swapPairs.cpp)
- 142 [环形链表](./link_list/142/detectCycle.cpp)
- 160 [相交链表](./link_list/160/getIntersectionNode.cpp)
- 203 [移除链表元素](./link_list/203/removeElements.cpp)
- 206 [反转链表](./link_list/206/reverseList.cpp)
- 707 [设计链表](./link_list/707/MyLinkdList.cpp)
- 61 [旋转链表](./link_list/61/rotateRight.cpp)

## 哈希表
- 1 [两数之和](./hash/1/twoSum.cpp)
- 128 [最长连续序列](./hash/128/longestConsecutive.cpp)


## 字符串
- 49 [字母异位词分组](./string_type/49/groupAnagrams.cpp)
- 3 [无重复字符的最长子串](./string_type/3/lengthOfLongestSubstring.cpp)
- 438 [找到字符串中所有字母的异位词](./string_type/438/findAnagrams.cpp)
- 76 [最小覆盖子串](./string_type/76/minWindow.cpp)
## 二叉树
- 144&94&145 [二叉树的迭代遍历](./tree/144/Traversal.cpp)
- 226 [翻转二叉树](./tree/226/invertTree.cpp)
- 110 [平衡二叉树](./tree/110/isBalanced.cpp)
- 257 [二叉树的所有路径](./tree/257/binaryTreePaths.cpp)
- 104 [二叉树的最大深度](./tree/104/maxDepth.cpp)
- 111 [二叉树的最小深度](./tree/111/minDepth.cpp)
- 404 [左叶子之和](./tree/404/sumOfLeftLeaves.cpp)
- 106 [从中序与后序遍历序列构造二叉树](./tree/106/buildTree.cpp)
- 513 [找树左下角的值](./tree/513/findBottomLeftValue.cpp)
- 112 [路径总和](./tree/112/hasPathSum.cpp)
- 113 [路径总和II](./tree/113/pathSum.cpp)
- 96 [不同的二叉搜索树](./tree/96/numTrees.cpp)
- 654 [最大二叉树](./tree/654/constructMaximumBinaryTree.cpp)
- 617 [合并二叉树](./tree/617/mergeTrees.cpp)
- 700 [二叉搜索树中的搜索](./tree/700/searchBST.cpp)
- 98 [验证二叉搜索树](./tree/98/isValidBST.cpp)
- 530 [BST的最小绝对差](./tree/530/getMinimumDifference.cpp)
- 501 [二叉搜索树中的众数](./tree/501/findMode.cpp)
- 236 [二叉树的最低公共祖先](./tree/236/lowestCommonAncestor.cpp)
- 235 [二叉搜索树的最近公共祖先](./tree/235/lowestCommonAncestor.cpp)
- 701 [插入二叉搜索树](./tree/701/insertIntoBST.cpp)
- 450 [删除二叉搜索树中的节点](./tree/450/deleteNode.cpp)
- 669 [修剪二叉树搜索树](./tree/669/trimBST.cpp)
- 108 [将排序数组转换为二叉搜索树](./tree/108/sortedArrayToBST.cpp)
- 538 [将BST转换为更大的树](./tree/538/convertBST.cpp)
## 回溯法
- 131 [分隔字符串](./backtracking/131/partition.cpp)
- 93 [复原IP地址](./backtracking/93/restoreIpAddresses.cpp)
- 78 [子集](./backtracking/78/subsets.cpp)
- 90 [子集II](./backtracking/90/subsetsWithDup.cpp)
- 491 [递增子序列](./backtracking/491/findSubsequences.cpp)
- 46 [全排列](./backtracking/46/permute.cpp)
- 47 [全排列II](./backtracking/47/permuteUnique.cpp)
- 332 [重新安排行程](./backtracking/332/findItinerary.cpp)
- 51 [N皇后](./backtracking/51/solveNQueens.cpp)
- 37 [解数独](./backtracking/37/solveSudoku.cpp)

## 双指针算法
- 15 [三数之和](./double_pointer/15/threeSum.cpp)
- 151 [翻转字符串中的单词](./double_pointer/151/reverseWords.cpp)
- 283 [移动零](./double_pointer/283/moveZeroes.cpp)
- 11 [盛水最多的容器](./double_pointer/11/maxArea.cpp)


## 贪心算法
- 680 [验证回文串](./greed/680/validPalindrome.cpp)
- 455 [分发饼干](./greed/455/findContentChildren.cpp)
- 376 [摆动序列](./greed/376/wiggleMaxLength.cpp)
- 53 [最大子数组和](./greed/53/maxSubArray.cpp)
- 122 [买卖股票的最佳时机](./greed/122/maxProfit.cpp)
- 55 [跳跃游戏](./greed/55/canJump.cpp)
- 45 [跳跃游戏II](./greed/45/jump.cpp)
- 1005 [K次取反后最大化的数组和](./greed/1005/largestSumAfterKNegations.cpp)
- 134 [加油站](./greed/134/canCompleteCircuit.cpp)
- 135 [分发糖果](./greed/135/candy.cpp)
- 860 [柠檬水找零](./greed/860/lemonadeChange.cpp)
- 406 [根据身高重建队列](./greed/406/reconstructQueue.cpp)
- 452 [用最少数量的箭引爆气球](./greed/452/findMinArrowShots.cpp)
- 435 [无重叠区间](./greed/435/eraseOverlapIntervals.cpp)
- 763 [划分字母区间](./greed/763/partitionLabels.cpp)
- 56 [合并区间](./greed/56/merge.cpp)
- 738 [单调递增的数字](./greed/738/monotoneIncreasingDigits.cpp)
## 动态规划
动态规划五部曲
    
    1）确定dp数组以及下标的含义
    2）确定递推公式
    3）dp数组如何初始化
    4）确定遍历顺序
    5）举例推导dp数组
- 509 [斐波那契数](./dp/509/fib.cpp)
- 70 [爬楼梯](./dp/70/climbStairs.cpp)
- 746 [使用最小花费爬楼梯](./dp/746/minCostClimbingStairs.cpp)
- 62 [不同路径](./dp/62/uniquePaths.cpp)
- 63 [不同路径II](./dp/63/uniquePathsWithObstacles.cpp)
- 343 [整数拆分](./dp//343/integerBreak.cpp)

## 图论

- 509 [岛屿数量](./grapth/200/numIslands.cpp)

## 单调栈
- 42 [接雨水](./double_pointer/42/trap.cpp)
