# Day2 分治与分块

## 树分治

树分治是用来解决一类树上路径问题的高效算法

### 点分治

[点分治学习笔记](https://dimensiontripper.github.io/2019/01/05/NBDC/)

#### 例题

##### T1 Race（IOI 2011）

###### 题意

给定一棵 $n$ 个节点的有边权的树，求一条路径使权值和为 $k$ 且边的数量最小。

###### 思路

分治下去后只需记录权值为 $x$ 的路径的最短长度即可

### 边分治

在树中选择一条边，统计与这条边有关的信息

然后递归处理将这条边删掉后得到的两棵子树

与点分治相同，选择的边要保证将其删去后最大的子树最小

#### 关于菊花图

菊花图朴素的边分会退化到 $O(n)$ 级，所以需要将树重构后再边分

具体参见KS神仙的 [边分治原理及实现](https://ksmeow.moe/edge_based_divide_and_conquer/) ，由于我太菜，这里就不讲了。

### 链分治

树链剖分

略

## CDQ分治 & 整体二分

### CDQ分治

#### CDQ分治与普通分治的差别

* 普通分治的流程：对于区间 $[L, R]$ ，递归解决 $[L, M], [M + 1, R]$ 后将两个区间的答案合并即得到答案。
* CDQ分治的流程：对于区间 $[L, R]$ ，递归解决 $[L, M], [M + 1, R]$ 后将两个区间的答案合并再加上 $[L, M]$ 对 $[M + 1, R]$ 的贡献即得到答案。

#### 例题

##### T1 二维偏序

###### 题意

给定 $n$ 个有序对 $(a, b)$ ，求对于每个 $(a, b)$ ，满足 $a_2 < a$ 且 $b_2 < b$ 的有序对 $(a_2 , b_2)$ 有多少个。

###### 思路

* 首先将这 $n$ 个有序对按 $a$ 为第一关键字从小到大， $b$ 为第二关键字从大到小排序。
* 对应上述的流程，将 $[L, R]$ 的问题分为 $[L, M], [M + 1, R]$ 的问题解决，直到区间大小为1。
* 重点在于如何计算 $[L, M]$ 对 $[M + 1, R]$ 的贡献。
* 由于子区间内部的贡献已经计算完毕，我们不妨对这两个区间都按 $b$ 权值从小到大排序。考虑到我们最初的排序方式，因此在 $[L, M]$ 中的 $(u, v)$ 如果对 $[M + 1, R]$ 中的 $(a, b)$ 产生贡献，等价于 $v < b$ 。因此使用双指针扫一遍即可。
* 然后我们考虑这个子区间内按照 $b$ 排序的过程，实际上不必在每一层递归的时候都排序，而是将两个子区间排完序的有序对组归并即可。

### 整体二分

使用整体二分的题要满足以下性质：

* 询问的答案具有可二分性。
* 修改对询问的贡献是独立的，相互之间不影响。
* 不同的修改的贡献是可叠加的，不必重复计算。
* 贡献满足交换律、结合律、有可加性。
* 题目允许离线。

具体实现如下：

* 顾名思义，对所有的询问一起二分。
* 通常而言，这类题的询问是类似乎第几次修改后满足条件，因此二分的就是修改序列，至多二分 $O(logm)$ 层。

#### 例题

##### T1 Meteors

###### 题意

有 $n$ 个国家和 $m$ 个空间站，每个空间站都属于一个国家，一个国家可以有多个空间站，所有空间站按照顺序形成一个环，也就是说 $m$ 号空间站和 1 号空间站相邻。现在，将会有 $k$ 场流星雨降临，每一场流星雨都会给区间 $[l_i , r_i]$ 内的每个空间站带来 $a_i$ 单位的陨石，每个国家都有一个收集陨石的目标 $p_i$ ，即第 $i$ 个国家需要收集 $p_i$ 单位的陨石。
询问：每个国家最早完成陨石收集目标是在第几场流星雨过后。

###### 思路

* 二分答案，假设当前二分的区间是 $[L, R]$ ，答案在 $[L, R]$ 区间中的询问是 $A_1 , ...... , A_l$ 。
* 用线段树模拟 $[L, M]$ 区间中的修改。
* 枚举每一个询问，达到 $p_i$ 要求的答案应在 $[L, M]$ 区间中，否则在 $[M + 1, R]$ 中，继续二分下去。
* 当二分的区间长度为 1 时结束递归。

## 三分

* 回想二分是用来解决一类单调的问题的，而三分则是用来解决凸函数上最值的问题。
* 例如，具体来讲，给定一个严格下凸函数 $f(x)$ ，如何求 $[L, R]$ 区间中的最小值?
* 将区间三等分为 $[L, M_1], [M_1 , M_2], [M_2 , R]$ 。如果 $f(M_1) \leq f(M_2)$ ，由下凸函数的性质，我们知道 $[M_2 , R]$ 这段区间上的函数值一定大于 $f(M_2)$ ，因此不会取到最小值，因此答案区间缩小为 $[L, M_2]$ ，长度变为原来的 $\frac{2}{3}$ 。
* 当 $f(M_1) > f(M_2)$ 同理。
* 这样在 $O(logC)$ 的时间内就能达到题目所需要的精度要求。

~~（当然也可以求导~~

## 分块

略（lxl的第一到第十几分块就先留坑待填）

## 块状链表

* 数组定位的复杂度为 $O(1)$ ，插入删除的复杂度是 $O(n)$ 。
* 链表定位的复杂度是 $O(n)$ ，插入删除的复杂度是 $O(1)$ 。
* 块状数组结合了链表和数组的优点，使得所有操作的复杂度均为 $O(\sqrt{n})$ 。
* 块状链表从宏观上看是链表，而链表中的每个节点又是一个数组。
* 注意插入删除后要及时合并小的块。

### 例题

#### T1 ORZJRY I（BZOJ 3337）

##### 题意

兹磁 11 种操作的数据结构

##### 思路

维护两个块状链表 & ODT