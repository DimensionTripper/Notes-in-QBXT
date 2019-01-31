# Day4 数学

## BSGS

给定质数 $p$ ，给定 $a, b$ ，$gcd(a, p) = 1$ ，求最小的非负整数 $x$ ，使 $a^x \equiv b\pmod p$ 

* 由欧拉定理， $a^{\varphi(p)} \equiv 1 \pmod p$ ，则有解时最小非负整数解必定在 $[0, \varphi(p))$ 中
* 记 $m= \lfloor \sqrt{\varphi(p)} \rfloor$ ，任意 $x \in [0, \varphi(p))$ 都可以表示为 $x = im + j$ 
* 枚举 $i$ 的值， $a^i \equiv b\pmod p \Leftrightarrow a^j \equiv a^{-im}b \pmod p$ 
* 将 $a^0, a^1, a^2, ...... , a^{m-1}$ 压入 Hash-Table ，在 Hash-Table 中询问就行了

思想：分块
复杂度： $O(\sqrt{\varphi(p)})$ 
缺陷： $p$ 必须是指数

---

## Miller-Rabin

给定 $n$ ，判断 $n$ 是否为素数

* 进行该测试前先筛去所有偶数
* 对于素数 $p$ 而言，任意整数 $x \in [1, p - 1]$ 都有 $x^p \equiv x \pmod p$ ，而对于合数则不一定成立。因此若 $\exists x_0 \in [1, n - 1]$ 使 $x^n \not \equiv x \pmod n$ ，则 $n$ 一定为合数
* 考虑 $x^2 \equiv 1 \pmod n$ 的根，若 $n$ 为奇素数，则只有 1 和 $n-1$ 两根；若 $n$ 为奇合数，则必定存在其他根
* 设 $n - 1 = 2^r \times d$ ，若存在 $k \in [0, r)$ ，使 $a^{2^k \times d} \not \equiv 1 \pmod n$ ，但是 $a^{2^{k + 1} \times d} \equiv 1,-1 \pmod n$ ，可以推断 $n$ 一定是合数
* 任选一个 $a$ ，若 $a$ 为素数，一定能通过二次探查和费马定理测试，若为合数，矛盾的概率为 $\frac{1}{2}$ 
* 选取 $k$ 组 $a$ ，则判断错误的概率为 $2^{-k}$ 

---

## Pollard's-Rho

给定 $n$ ，要求对 $n$ 进行质因数分解。

* 若 Miller-Rabin 测试为素数则停止分解
* 随机基底 $a$ 和 $c$ ，生成序列 $x_0 = a, x_i = (x_{i - 1}^2 + c) \bmod n$ ，可以认为 ${x_i}$ 是随机序列
* 若出现 $gcd(x_i - x_{2i + 1}, n) \not = 1$ ，此时停止算法，令 $d = gcd(x_i - x{2i + 1}, n)$ ，若 $d \not = n$ ，则 $d$ 为 $n$ 的一个非平凡因子， $n$ 被分为 $d$ 与 $n / d$ 之积，递归下去继续分解
* 若 $d = n$ ，那么换一组基底重新进行分解
* 复杂度 $O(n^{\frac{1}{4}}poly(n))$ 

---

## Linear-Shaker（线性筛）

要求筛出所有小于 $n$ 的素数

* 传统筛法是用 $i$ 筛去所有 $i$ 的倍数，复杂度 $O(nlnn)$ 
* 线性筛是用 $i$ 筛掉 $i$ 的部分倍数，设 $i$ 的最小素因子为 $p_0$ ，小于等于 $p_0$ 的所有素因子为 $p_1, p_2, ... , p_j$ ，线性筛的过程中仅筛去了 $ip_1, i_p2, ... , ip_j$ 。注意到 $i$ 的最小素因子为 $p$ ， $i$ 仅会被 $i / p$ 筛去，复杂度 $O(n)$ 

原理并不需要明白，会打就行了（

```cpp
il void Linear_Shaker(int n)
{
	for (ri i = 2; i <= n; i++)
	{
		if (!vis[i])
			prime[++cnt] = i;
		for (ri j = 1; j <= cnt && prime[j] * i <= n; j++)
		{
			vis[prime[j] * i] = 1;
			if (!(i % prime[j]))
				break;
		}
	}
}
```

---

## Chinese Remainder Rheory（CRT 中国剩余定理）

有以下一组方程：
$$
x \bmod n_1 = x_1\\x \bmod n_2 = x_2\\ ... \\ x \bmod n_k = x_k
$$
其中 $n_1, n_2, ... , n_k$ 两两互质，求 $x$ 的一个合法解

解法如下：

令 $N = \prod\limits_{i = 1}^kn_i$ ，$m_i = N / n_i$ ， $t_i = m_i^{-1} \pmod {n_i}$ ，则有

$$
x = \sum\limits_i x_i m_i t_i\pmod N
$$
当 $j = i$ 时， $m_i t_i \equiv 1 \pmod {n_j}$ ；当 $j \not = i$ 时， $m_i t_i \equiv 0 \pmod {n_j}$  ，则 $x$ 一定为原方程的解

---

## Quadratic Sesidue（二次剩余）

给定 $y$ 和奇质数 $p$ ，求 $x^2 \equiv y \pmod p$ 的解

### 欧拉判别法

* 若 $y^{\frac{p - 1}{2}} \equiv 1 \pmod p$ ，则 $y$ 在模奇素数 $p$ 下有二次剩余
* 若 $y^{\frac{p - 1}{2}} \equiv -1 \pmod p$ ，则 $y$ 在模奇素数 $p$ 下没有二次剩余
* 勒让德符号 $(\frac{a}{p}) \equiv a^{\frac{p - 1}{2}}$ 
*  $[1, p - 1]$ 中有 $\dfrac{p - 1}{2}$ 个数的勒让德符号为 1 ，另外 $\dfrac{p - 1}{2}$ 个数的勒让德符号为 -1 

### Cipolla's Algorithm

* 不断随机 $a$ ，使得 $(\dfrac{a ^ 2 - y}{p}) = -1$ 
* 令 $\omega = \sqrt{a^2 - y}$ ， $x = (a + \omega)^{\frac{p + 1}{2}}$ 
*  $x^2 \equiv (a + \omega)^p \times (a + \omega) \equiv (a + \omega) \sum\limits_j\binom{p}{j}a^j \omega^{p - j} \equiv (a + \omega)(a - \omega) \equiv a^2 - \omega^2 \equiv y \pmod p$  

### 例题

#### T1

##### 题意

给定长度为 $n$ 的高精度数字 $a$ ，判断 $a$ 是不是完全平方数

##### 思路

~~高精度开方！~~

* 随机一些素数，判断对应模意义下是否有二次剩余
* 若 $a$ 为完全平方数则一定有解，反之则有 $\dfrac{1}{2}$ 的概率的概率有解
* 可以不用欧拉判别法，直接预处理所有的 $x \in [1, p], k \equiv x^2 \pmod p$ 即可

---

## Multiplicative Function（积性函数）

略

---

## Primitive Root（原根）

给定 $n$ ，若 $a$ 满足 $gcd(a, n) = 1$ 且 $1, a, a^2, ... , a^{\varphi(n) - 1}$ 在模 $n$ 意义下互不相同，则称 $a$ 是 $n$ 的一个原根

性质：

*  $2, 4, p^n, 2p^n$ 有原根（ $p$ 为奇素数
* 若 $n$ 有原根，则原根数量为 $\varphi(\varphi(n))$ 

### 阶

对于整数 $a$ ，存在 $x$ 使 $a^x \equiv 1 \pmod n$ ，最小的 $x$ 就称为 $a$ 在模 $n$ 意义下的阶，写作 $<a>$ 

* 若 $a^i \equiv a^j\pmod n, (i > j)$ ，则 $x \leq i - j$ 

* 若 $a^x \equiv 1\pmod n$ ，则 $<a> | x$ 

  证明：若 $<a> \not | x$ ，设 $<a> = r$ ，则 $x = pr + q$ ，变形得 $a^q \equiv a^{-pr} \equiv (a^{-r})^p \equiv 1 \pmod n$ ，和假设矛盾。

### 如何计算原根

由于原根的个数为 $\varphi(\varphi(n))$ ，所以随机一个都有 $O(\dfrac{1}{logn})$ 的概率取到，所以直接随机就完了（

### 如何判断原根

根据阶的性质 2 ，验证 $n$ 是否满足原根的定义即可

具体来说，若存在 $x \in [1, \varphi(n) - 1]$ ，使得 $a^x \equiv 1 \pmod n$ ，则 $x$ 一定为 $\varphi(n)$ 的因子，并且若 $a^x \equiv 1 \pmod n$ ，则有 $a^{xb} \equiv 1 \pmod n$ 。 因此将 $\varphi(n)$ 分解成 $\varphi(n) = \prod p_i^{r_i}$ ，分别验证 $a^{\frac{\varphi(n)}{n}} \not \equiv 1 \pmod n$ 是否成立，若不成立则 $a$ 不为原根，反之则为原根

---

## Combination（组合数学）

$\dbinom{n}{m}$ 表示从 $n$ 个有区别的物品中无顺序的选出 $m$ 个的方法数

$$
\dbinom{n}{m} = \dfrac{n!}{m!(n-m)!}
$$

### 求法

* 杨辉三角（递推）
* 预处理阶乘及逆元
*  $n, m$ 比较大时根据模数是否为质数选择 $Lucas$ 或 $ExLucas$ 求解

---

## Recurrence Relation（线性递推：矩阵加速）

在一些只需要用较少的状态刻画的问题中，巧妙构造矩阵后利用矩阵快速幂可以极大的优化线性递推。

### 例题

#### 题意

给出一张 $n$ 个点， $m$ 条边的有向图， $q$ 次询问，每次询问图中从每个点出发的长度为 $k$ 的路径的条数

#### 思路

- 如果直接每次询问矩阵快速幂，复杂度 $O(q\cdot n^3logk)$ 。
- 如果预处理所有询问，复杂度 $O(n^3k)$ 。
- 运用分块思想，预处理 $k=1,2...9,k=10,20...100$ 的矩阵。复杂度 $O(n^3(\sqrt k + q))$ 。

---

## Principle of Inclusion-Exclusion（容斥原理）

略（感性理解即可）

---

## Binomial Inversion（二项式反演）

$$
f_n = \sum\limits_{i = 0}^{n}(-1)^i\dbinom{n}{i}g_i \Leftrightarrow g_n = \sum\limits_{i  = 0}^{n} (-1)^i\dbinom{n}{i}f_i\\
f_n = \sum\limits_{i = 0}^{n}\dbinom{n}{i}g_i \Leftrightarrow g_n = \sum\limits_{i = 0}^{n}(-1)^{n - i}\dbinom{n}{i}f_i
$$

### 例题

#### T1 集合计数（BZOJ 2839）

##### 题意

 $n$ 个元素的集合，从其所有子集中选出若干子集，求有多少种方法使得选出集合的交集数为 $k$ ，答案对 $10^9 + 7$ 取模

##### 思路

- 令 $f_k$ 表示 $n$ 个元素选择出若干子集交的大小大于等于 $k$ 的方案数，则 $f_k=\dbinom{n}{k}\times (2^{2^{n-k}}-1)$ 。
- 令 $g_k$ 表示 $n$ 个元素选择出若干子集交的大小等于k的方案数， $f_i=\sum\limits_{j=i}^n\dbinom{j}{i}g_j$ 。
- 为了便于反演，变形为 $f_i=\sum\limits_{j=0}^{n-i}\binom{j+i}{i}g_{j+i}$ 。
- 反演即可（

#### T2 染色问题（JSOI 2015）

##### 题意

有 $n\times m$ 的矩阵， $c$ 种染料，每个格子可以不染色或被染成任意颜色，求有多少种方案使得每一行和每一列都至少有一个格子被染了色且每种颜色至少出现过一次

##### 思路

待填坑

---

## Probability Thereom（概率论）

期望公式： $E(x) = \sum P(x = a_i) \times a_i$ （ $a_i$ 为价值）

### 期望的线性性

对任意两个随机事件 $A, B$ （**不要求相互独立**），都满足 $E(A + B) = E(A) + E(B)$ 

### 例题

#### T1 Clear The Room（JSK1483G）

##### 题意

给定 $n\times m$ 的矩阵， $(i, j)$ 中的价值为 $w_{ij}$ 每次随机选择两个格子，将两个格子确定的矩形中还没被拿走的价值全部拿走，求 $k$ 次后拿走的物品价值和的期望。

##### 思路

-  $E(x)=\sum\sum P((x,y)被盖住)\times a_{x,y}$ 
- 考虑 $(x,y)$ 被拿走的概率 $P=P(x\in [x_1,x_2])\times P(y\in[y_1,y_2])$ 

---

## Gaussian（高斯消元）

略

---

## Determinant（行列式）

留坑待填

---

## Matrix-Tree（矩阵树）

留坑待填

---

## Burnside & Polya

留坑待填

---

## SG

留坑待填