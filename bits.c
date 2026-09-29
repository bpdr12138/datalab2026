/* WARNING: Do not include any other libraries here,
 * otherwise you will get an error while running test.py
 * You can still use printf for debugging without including
 * <stdio.h>, although you might get a compiler warning. In general,
 * it's not good practice to ignore compiler warnings, but in this
 * case it's OK.
 *
 * Using printf will interfere with our script capturing the execution results.
 * At this point, you can only test correctness with ./btest.
 * After confirming everything is correct in ./btest, remove the printf
 * and run the complete tests with test.py.
 */

 /*
 * bitAnd - x & y using only ~ and |
 * Example: bitAnd(4, 5) = 4
 * Legal ops: ~ |
 * Max ops: 7
 * Difficulty: 1
 */
int bitAnd(int x, int y) {
    return ~(~x | ~y);
}

/*
 * bitXor - x ^ y using only ~ and &
 *   Example: bitXor(4, 5) = 1
 *   Legal ops: ~ &
 *   Max ops: 7
 *   Difficulty: 1
 */
int bitXor(int x, int y) {
    // 抽象: 使用与非门构造或门
    // 异或: 属于两者其中一个，但不属于两者之和
    return ~(x&y) & ~(~x&~y);
}

/*
 * samesign - Determines if two integers have the same sign.
 *   0 is not positive, nor negative
 *   Example: samesign(0, 1) = 0, samesign(0, 0) = 1
 *            samesign(-4, -5) = 1, samesign(-4, 5) = 0
 *   Legal ops: >> << ! ^ && if else &
 *   Max ops: 12
 *   Difficulty: 2
 *
 * Parameters:
 *   x - The first integer.
 *   y - The second integer.
 *
 * Returns:
 *   1 if x and y have the same sign , 0 otherwise.
 */
int samesign(int x, int y) {
    // 分类讨论，拆成相互独立情况，不断筛掉                          1
    if ((x >> 31) ^ (y >> 31))
    {
        return 0;
    }

    if (!x && !y)
    {
        return 1;
    }

    if (!(x && y))
    {
        return 0;
    }

    return 1;
}

/*
 * logtwo - Calculate the base-2 logarithm of a positive integer using bit
 *   shifting. (Think about bitCount)
 *   Note: You may assume that v > 0
 *   Example: logtwo(32) = 5
 *   Legal ops: > < >> << |
 *   Max ops: 25
 *   Difficulty: 4
 */
int logtwo(int v) {

    int b4, b3, b2, b1, b0;
    int a4, a3, a2, a1;

    // 探测阶有没有达到16
    b4 = (v >> 16) > 0;
    v = v >> (a4 = (b4 << 4)); // 若存在，v 右移 16 位. 若不存在则不移动

    // 探测剩余阶有没有达到8
    b3 = (v >> 8) > 0;
    v = v >> (a3 = (b3 << 3)); // 若存在，v 右移 8 位. 若不存在则不移动

    // 探测剩余阶有没有达到4 
    b2 = (v >> 4) > 0;
    v = v >> (a2 = (b2 << 2)); // 若存在，v 右移 4 位. 若不存在则不移动

    // 探测剩余阶有没有达到2
    b1 = (v >> 2) > 0;
    v = v >> (a1 = (b1 << 1)); // 若存在，v 右移 2 位. 若不存在则不移动

    // 探测剩余阶有没有达到1
    b0 = (v >> 1) > 0;

    // 用或 模拟 二进制转十进制
    return a4 | a3 | a2 | a1 | b0;
}

/*
 *  byteSwap - swaps the nth byte and the mth byte
 *    Examples: byteSwap(0x12345678, 1, 3) = 0x56341278
 *              byteSwap(0xDEADBEEF, 0, 2) = 0xDEEFBEAD
 *    Note: You may assume that 0 <= n <= 3, 0 <= m <= 3
 *    Legal ops: ! ~ & ^ | + << >>
 *    Max ops: 17
 *    Difficulty: 2
 */
int byteSwap(int x, int n, int m) {
    // 模拟
    n = n << 3;
    m = m << 3;
    int a = (0xFF << n);
    int b = (0xFF << m);
    int c = ((x & a) >> n) & 0xFF;
    c = c << m;
    int d = ((x & b) >> m) & 0xFF;
    d = d << n;
    x = (x & ~(a|b)) | c | d;
    return x;
}

/*
 * reverse - Reverse the bit order of a 32-bit unsigned integer.
 *   Example: reverse(0xFFFF0000) = 0x0000FFFF reverse(0x80000000)=0x1 reverse(0xA0000000)=0x5
 *   Note: You may assume that an unsigned integer is 32 bits long.
 *   Legal ops: << | & - + >> for while ! ~ (You can define unsigned in this function)
 *   Max ops: 30
 *   Difficulty: 3
 */
unsigned reverse(unsigned v) {
    v = ((v >> 1) & 0x55555555) | ((v & 0x55555555) << 1);
    v = ((v >> 2) & 0x33333333) | ((v & 0x33333333) << 2);
    v = ((v >> 4) & 0x0F0F0F0F) | ((v & 0x0F0F0F0F) << 4);
    v = ((v >> 8) & 0x00FF00FF) | ((v & 0x00FF00FF) << 8);
    v = ((v >> 16) & 0x0000FFFF) | ((v & 0x0000FFFF) << 16);
    return v;
}

/*
 * logicalShift - shift x to the right by n, using a logical shift
 *   Examples: logicalShift(0x87654321,4) = 0x08765432
 *   Note: You can assume that 0 <= n <= 31
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 20
 *   Difficulty: 3
 */
int logicalShift(int x, int n) {
    int a = 0x80000000;
    a = a >> n << 1;
    x = x >> n;
    x = x & (~a);
    return x;
}

/*
 * leftBitCount - returns count of number of consective 1's in left-hand (most) end of word.
 *   Examples: leftBitCount(-1) = 32, leftBitCount(0xFFF0F0F0) = 12,
 *             leftBitCount(0xFE00FF0F) = 7
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 50
 *   Difficulty: 4
 */
int leftBitCount(int x) {

    // 0向右传播
    x = x & (x >> 1);
    x = x & (x >> 2);
    x = x & (x >> 4);
    x = x & (x >> 8);
    x = x & (x >> 16);
    // 高k位为 1，其余位全为 0

    // 1 的个数
    int m1 = 0x55555555;
    int m2 = 0x33333333;
    int m4 = 0x0F0F0F0F;
    int m8 = 0x00FF00FF;
    int m16 = 0x0000FFFF;

    x = (x & m1) + ((x >> 1) & m1);
    x = (x & m2) + ((x >> 2) & m2);
    x = (x & m4) + ((x >> 4) & m4);
    x = (x & m8) + ((x >> 8) & m8);
    x = (x & m16) + ((x >> 16) & m16);

    return x & 0x3F;
}

/*
 * float_i2f - Return bit-level equivalent of expression (float) x
 *   Result is returned as unsigned int, but it is to be interpreted as
 *   the bit-level representation of a single-precision floating point values.
 *   Legal ops: if else while for & | ~ + - >> << < > ! ==
 *   Max ops: 30
 *   Difficulty: 4
 */
unsigned float_i2f(int x) {
    int sign = x & 0x80000000;
    int exp = 158; // 31 + 127
    int frac;
    int round_part;

    if (x == 0) 
    {
        return 0;
    }

    // 负数取反
    if (sign) 
    {
        x = -x;
    }

    // 规格化，将最高位的 1 推到第 31 位
    while ((x & 0x80000000) == 0) 
    {
        x = x << 1;
        exp = exp - 1;
    }

    // 提取低 8 位以及尾数
    round_part = x & 0x000000FF;
    frac = (x >> 8) & 0x007FFFFF; // 提取纯粹的 23 位尾数

    // 舍入判定
    // 进位条件：> 0.5 或者 (== 0.5 且 保留位最低位为 1)
    if (round_part > 0x00000080) 
    {
        frac = frac + 1;
    }
    else if (round_part == 0x00000080)
    {
        if (frac & 1)
        {
            frac = frac + 1;
        }
    }

    // 组装
    return sign + (exp << 23) + frac;
}

/*
 * floatScale2 - Return bit-level equivalent of expression 2*f for
 *   floating point argument f.
 *   Both the argument and result are passed as unsigned int's, but
 *   they are to be interpreted as the bit-level representation of
 *   single-precision floating point values.
 *   When argument is NaN, return argument
 *   Legal ops: & >> << | if > < >= <= ! ~ else + ==
 *   Max ops: 30
 *   Difficulty: 4
 */
unsigned floatScale2(unsigned uf) {
    // 提符号位
    unsigned S = uf & 0x80000000;
    // 提阶码
    unsigned E = (uf >> 23) & 0x000000FF;

    // 非规格化值 且 NaN/Inf
    if (E == 0xFF) 
    {
        return uf;
    }

    // 非规格化数 或 0：阶码全 0 (0x00)
    if (E == 0x00) 
    {
        return S | (uf << 1);
    }

    // 规格化数：阶码加 1
    E = E + 1;
    // 阶码加 1 后可能变成 255，返回对应符号的无穷大
    if (E == 0xFF) 
    {
        return S | 0x7F800000;
    }

    // 规格化数：组装
    return (uf & 0x807FFFFF) | (E << 23);
}

/*
 * float64_f2i - Convert a 64-bit IEEE 754 floating-point number to a 32-bit signed integer.
 *   The conversion rounds towards zero.
 *   Note: Assumes IEEE 754 representation and standard two's complement integer format.
 *   Parameters:
 *     uf1 - The lower 32 bits of the 64-bit floating-point number.
 *     uf2 - The higher 32 bits of the 64-bit floating-point number.
 *   Returns:
 *     The converted integer value, or 0x80000000 on overflow, or 0 on underflow.
 *   Legal ops: >> << | & ~ ! + - > < >= <= if else
 *   Max ops: 60
 *   Difficulty: 3
 */
int float64_f2i(unsigned uf1, unsigned uf2) {
    // uf2: 1 11 20  uf1: 32
    int S = (uf2 >> 31) & 1; // 提符号位
    int exp = ((uf2 >> 20) & 0x000007FF) - 1023; // 提阶码,减bias = 1023得exp
    int frac_high = (uf2 & 0x000FFFFF) | 0x00100000; // 提取高 20 位尾数, 这里要补齐隐含位 1
    int val = 0;

    // 阶码<0 -> underflow -> 向零取整
    if (exp < 0) 
    {
        return 0;
    }

    // 上溢：指数超出32位
    if (exp > 31) 
    {
        return 0x80000000;
    }

    // 阶码，小数点移位
    // frac_high 包含隐含位共 21 位
    // 指数不足 20，小数点右移exp也不超出uf2右边，向0舍入，uf1 可全部忽略
    if (exp <= 20) 
    {
        val = frac_high >> (20 - exp);
    } 
    else 
    {
        // 指数大于 20，小数点右移exp跨到uf1了，需要拼接低 32 位 uf1 的高位数据
        // exp - 20 在 1 到 11 之间
        int t = exp - 20;
        val = (frac_high << t) | (uf1 >> (32 - t));
    }

    // 处理符号
    if (S) 
    {
        val = -val;
    } 
    else 
    {
        // 正溢出
        if (val < 0) 
        {
            return 0x80000000;
        }
    }

    return val;
}

/*
 * floatPower2 - Return bit-level equivalent of the expression 2.0^x
 *   (2.0 raised to the power x) for any 32-bit integer x.
 *
 *   The unsigned value that is returned should have the identical bit
 *   representation as the single-precision floating-point number 2.0^x.
 *   If the result is too small to be represented as a denorm, return
 *   0. If too large, return +INF.
 *
 *   Legal ops: < > <= >= << >> + - & | ~ ! if else &&
 *   Max ops: 30
 *   Difficulty: 4
 */
unsigned floatPower2(int x) {
    // 1 8 23
    // x > 127
    if (x > 127) // 上溢
    {
        return 0x7F800000;
    }

    // -126 <= x <= 127
    if (x >= -126) 
    {
        return (x + 127) << 23;
    }

    // -149 <= x < -126
    if (x >= -149) 
    {
        return 1 << (x + 149);
    }

    // x < -149
    return 0;
}
