---
title: "CS:APP 数据实验笔记"
date: 2021-03-30T20:25:52+08:00
lastmod: 2021-03-30T20:25:52+08:00
draft: false
keywords: ["CS:APP"]
description: ""
tags: ["技术", "CS:APP", "CS:APP数据实验"]
categories: ["笔记"]
author: "Detachment"

# You can also close(false) or open(true) something for this content.
# P.S. comment can only be closed
comment: false
toc: false
autoCollapseToc: false
postMetaInFooter: false
hiddenFromHomePage: false
# You can also define another contentCopyright. e.g. contentCopyright: "This is another copyright."
contentCopyright: false
reward: false
mathjax: false
mathjaxEnableSingleDollar: false
mathjaxEnableAutoNumber: false

# You unlisted posts you might want not want the header or footer to show
hideHeaderAndFooter: false

# You can enable or disable out-of-date content warning for individual post.
# Comment this out to use the global config.
#enableOutdatedInfoWarning: false

flowchartDiagrams:
  enable: false
  options: ""

sequenceDiagrams: 
  enable: false
  options: ""

---
## 实验网站
* http://csapp.cs.cmu.edu/3e/labs.html
* 下载Self-Study Handout
## 一些思考
* c语言中所有非零的数（包括浮点数）被认为是布尔真，只有零被认为是布尔假
* 补码操作为取反加一`-x = ~x + 1`
* 补码与自身相等的数有两个`1000 0000 0000 0000 0000 0000 0000 0000`和`0000 0000 0000 0000 0000 0000 0000 0000`
* 1可用于掩码，掩码x对目标数相与（&），目标数对应x中为1的位置会被保留，其余的位置会变为0
* 对于非浮点数来说，乘2相当于左移一位，除2相当于右移一位
## 实验结果（仅供参考）
```c
/* 
 * CS:APP Data Lab 
 * 
 * <Please put your name and userid here>
 * 
 * bits.c - Source file with your solutions to the Lab.
 *          This is the file you will hand in to your instructor.
 *
 * WARNING: Do not include the <stdio.h> header; it confuses the dlc
 * compiler. You can still use printf for debugging without including
 * <stdio.h>, although you might get a compiler warning. In general,
 * it's not good practice to ignore compiler warnings, but in this
 * case it's OK.  
 */

#if 0
/*
 * Instructions to Students:
 *
 * STEP 1: Read the following instructions carefully.
 */

You will provide your solution to the Data Lab by
editing the collection of functions in this source file.

INTEGER CODING RULES:
 
  Replace the "return" statement in each function with one
  or more lines of C code that implements the function. Your code 
  must conform to the following style:
 
  int Funct(arg1, arg2, ...) {
      /* brief description of how your implementation works */
      int var1 = Expr1;
      ...
      int varM = ExprM;

      varJ = ExprJ;
      ...
      varN = ExprN;
      return ExprR;
  }

  Each "Expr" is an expression using ONLY the following:
  1. Integer constants 0 through 255 (0xFF), inclusive. You are
      not allowed to use big constants such as 0xffffffff.
  2. Function arguments and local variables (no global variables).
  3. Unary integer operations ! ~
  4. Binary integer operations & ^ | + << >>
    
  Some of the problems restrict the set of allowed operators even further.
  Each "Expr" may consist of multiple operators. You are not restricted to
  one operator per line.

  You are expressly forbidden to:
  1. Use any control constructs such as if, do, while, for, switch, etc.
  2. Define or use any macros.
  3. Define any additional functions in this file.
  4. Call any functions.
  5. Use any other operations, such as &&, ||, -, or ?:
  6. Use any form of casting.
  7. Use any data type other than int.  This implies that you
     cannot use arrays, structs, or unions.

 
  You may assume that your machine:
  1. Uses 2s complement, 32-bit representations of integers.
  2. Performs right shifts arithmetically.
  3. Has unpredictable behavior when shifting if the shift amount
     is less than 0 or greater than 31.


EXAMPLES OF ACCEPTABLE CODING STYLE:
  /*
   * pow2plus1 - returns 2^x + 1, where 0 <= x <= 31
   */
  int pow2plus1(int x) {
     /* exploit ability of shifts to compute powers of 2 */
     return (1 << x) + 1;
  }

  /*
   * pow2plus4 - returns 2^x + 4, where 0 <= x <= 31
   */
  int pow2plus4(int x) {
     /* exploit ability of shifts to compute powers of 2 */
     int result = (1 << x);
     result += 4;
     return result;
  }

FLOATING POINT CODING RULES

For the problems that require you to implement floating-point operations,
the coding rules are less strict.  You are allowed to use looping and
conditional control.  You are allowed to use both ints and unsigneds.
You can use arbitrary integer and unsigned constants. You can use any arithmetic,
logical, or comparison operations on int or unsigned data.

You are expressly forbidden to:
  1. Define or use any macros.
  2. Define any additional functions in this file.
  3. Call any functions.
  4. Use any form of casting.
  5. Use any data type other than int or unsigned.  This means that you
     cannot use arrays, structs, or unions.
  6. Use any floating point data types, operations, or constants.


NOTES:
  1. Use the dlc (data lab checker) compiler (described in the handout) to 
     check the legality of your solutions.
  2. Each function has a maximum number of operations (integer, logical,
     or comparison) that you are allowed to use for your implementation
     of the function.  The max operator count is checked by dlc.
     Note that assignment ('=') is not counted; you may use as many of
     these as you want without penalty.
  3. Use the btest test harness to check your functions for correctness.
  4. Use the BDD checker to formally verify your functions
  5. The maximum number of ops for each function is given in the
     header comment for each function. If there are any inconsistencies 
     between the maximum ops in the writeup and in this file, consider
     this file the authoritative source.

/*
 * STEP 2: Modify the following functions according the coding rules.
 * 
 *   IMPORTANT. TO AVOID GRADING SURPRISES:
 *   1. Use the dlc compiler to check that your solutions conform
 *      to the coding rules.
 *   2. Use the BDD checker to formally verify that your solutions produce 
 *      the correct answers.
 */


#endif
//1
/* 
 * bitXor - x^y using only ~ and & 
 *   Example: bitXor(4, 5) = 1
 *   Legal ops: ~ &
 *   Max ops: 14
 *   Rating: 1
 */
int bitXor(int x, int y) {
  return ~(~(~x & y) & ~(x & ~y));
}
/* 
 * tmin - return minimum two's complement integer 
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 4
 *   Rating: 1
 */
int tmin(void) {
  int a = 0;
  return (~ (a ^ a)) << 31;
}
//2
/*
 * isTmax - returns 1 if x is the maximum, two's complement number,
 *     and 0 otherwise 
 *   Legal ops: ! ~ & ^ | +
 *   Max ops: 10
 *   Rating: 1
 */
int isTmax(int x) {
  int a = x + 1;
  int c = !!a;
  int b = (~a) + 1;
  return (!!!(a ^ b)) & c;
}
/* 
 * allOddBits - return 1 if all odd-numbered bits in word set to 1
 *   where bits are numbered from 0 (least significant) to 31 (most significant)
 *   Examples allOddBits(0xFFFFFFFD) = 0, allOddBits(0xAAAAAAAA) = 1
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 12
 *   Rating: 2
 */
int allOddBits(int x) {
  int n = 0xAA;
  n = n + (n << 8);
  n = n + (n << 16);
  x = (x & n)^n;
  return !!!x;
}
/* 
 * negate - return -x 
 *   Example: negate(1) = -1.
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 5
 *   Rating: 2
 */
int negate(int x) {
  x = (~ x) + 1;
  return x;
}
//3
/* 
 * isAsciiDigit - return 1 if 0x30 <= x <= 0x39 (ASCII codes for characters '0' to '9')
 *   Example: isAsciiDigit(0x35) = 1.
 *            isAsciiDigit(0x3a) = 0.
 *            isAsciiDigit(0x05) = 0.
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 15
 *   Rating: 3
 */
int isAsciiDigit(int x) {
  int buffer = (~ x) + 1;
  int p = (~ 48) + 1;
  int q = 57;
  int a = p + x;
  int b = q + buffer;
  int m = !((a) >> 31);
  int n = !((b) >> 31);
  return (m & n)&(!(x >> 31));
}
/* 
 * conditional - same as x ? y : z 
 *   Example: conditional(2,4,5) = 4
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 16
 *   Rating: 3
 */
int conditional(int x, int y, int z) {
  int m = ~(!!x) + 1;
  int buffer = (~z) + 1 + y;
  int re = z + (buffer & m);
  return re;
}
/* 
 * isLessOrEqual - if x <= y  then return 1, else return 0 
 *   Example: isLessOrEqual(4,5) = 1.
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 24
 *   Rating: 3
 */
int isLessOrEqual(int x, int y) {
  int sy = !(y >> 31);
  int sx = !(x >> 31);
  int re = ((~x) + y + 1) >> 31;
  return ((!re) | (sy & (!sx))) & !((!sy) & sx);
}
//4
/* 
 * logicalNeg - implement the ! operator, using all of 
 *              the legal operators except !
 *   Examples: logicalNeg(3) = 0, logicalNeg(0) = 1
 *   Legal ops: ~ & ^ | + << >>
 *   Max ops: 12
 *   Rating: 4 
 */
int logicalNeg(int x) {
  return ((x >> 31) + 1) & ((((~x) + 1) >> 31) + 1);
}
/* howManyBits - return the minimum number of bits required to represent x in
 *             two's complement
 *  Examples: howManyBits(12) = 5
 *            howManyBits(298) = 10
 *            howManyBits(-5) = 4
 *            howManyBits(0)  = 1
 *            howManyBits(-1) = 1
 *            howManyBits(0x80000000) = 32
 *  Legal ops: ! ~ & ^ | + << >>
 *  Max ops: 90
 *  Rating: 4
 */
 //对于正数寻找第一个为1的位置
 //对于复数寻找第一个为0的位置
int howManyBits(int x1) {
  int y1 = ~x1;
  int sign = ~(x1 >> 31);
  int x = (x1 & sign) + (y1 & (~sign));
  int ret = !!x;
  int m = !!(x&(((0xFF << 8) + 0xFF) << 16))<<4;
  x>>=m;
  ret = ret + m;
  m=!!(x&(0xFF << 8))<<3;
  x>>=m;
  ret = ret + m;
  m=!!(x&0xF0)<<2;
  x>>=m;
  ret = ret + m;
  m=!!(x&0xC)<<1;
  x>>=m;
  ret = ret + m;
  ret = ret + !!(x&0x2);
  return ret + 1;
}
//float
/* 
 * floatScale2 - Return bit-level equivalent of expression 2*f for
 *   floating point argument f.
 *   Both the argument and result are passed as unsigned int's, but
 *   they are to be interpreted as the bit-level representation of
 *   single-precision floating point values.
 *   When argument is NaN, return argument
 *   Legal ops: Any integer/unsigned operations incl. ||, &&. also if, while
 *   Max ops: 30
 *   Rating: 4
 */
unsigned floatScale2(unsigned uf) {
  //unsigned x = uf >> 23;
  unsigned sign_m = 1 << 31;
  unsigned exp_m = 0xFF << 23;
  unsigned frac_m = (~(exp_m) << 1) >> 1;
  unsigned sign = sign_m & uf;
  unsigned exp = exp_m & uf;
  unsigned frac = frac_m & uf;
  if (!exp)
  {
    return (uf << 1) + sign;
    //一个很神奇的性质，当阶码为0的时候，x*2直接左移一位就可以得到
    //（和非浮点数一样）
  }
  else if ((!(exp ^ exp_m)) && frac){
    return uf;
    //输入Nan的时候返回Nan
  }
  else if (!((exp - (0xFE << 23))>>31))
  {
    return sign + exp_m;
    //结果溢出，返回无限大
  }
  else
  {
    return sign + (exp + (1 << 23)) + frac;
    //一般情况阶码+1
  }
}
/* 
 * floatFloat2Int - Return bit-level equivalent of expression (int) f
 *   for floating point argument f.
 *   Argument is passed as unsigned int, but
 *   it is to be interpreted as the bit-level representation of a
 *   single-precision floating point value.
 *   Anything out of range (including NaN and infinity) should return
 *   0x80000000u.
 *   Legal ops: Any integer/unsigned operations incl. ||, &&. also if, while
 *   Max ops: 30
 *   Rating: 4
 */
int floatFloat2Int(unsigned uf) {
  unsigned sign_m = 1 << 31;
  unsigned exp_m = 0xFF << 23;
  unsigned frac_m = (~(exp_m) << 1) >> 1;
  unsigned sign = sign_m & uf;
  unsigned exp = exp_m & uf;
  unsigned frac = frac_m & uf;
  unsigned witoutsign = uf & (~sign_m);
  //取绝对值
  unsigned buffer = (0x7F << 23) - (exp & (~ sign_m));
  if (((0x9D << 23) + frac_m - witoutsign) >> 31)
  {
    return (1 << 31);
    //过大溢出，返回0x80000000
  }
  else if (!(buffer >> 31)){
    //阶码最终值小于0的情况，如果阶码等于0，返回1或-1，如果阶码不等于0返回0（相当于0.12舍入为0这种情况）
    if (buffer){
      return 0;
    }
    else
    {
      int re = 1;
      if (sign){
        return (~re) + 1;
      }
      else
      {
        return re;
      }
    }
  }
  else
  {
    //一般情况
    int re = frac >> (22 - (exp >> 23));
    if (sign){
      return (~re) + 1;
    }
    else
    {
      return re;
    }
    
  }
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
 *   Legal ops: Any integer/unsigned operations incl. ||, &&. Also if, while 
 *   Max ops: 30 
 *   Rating: 4
 */
unsigned floatPower2(int x) 
{
  /*
  本函数在virtualbox中的Linux环境中会出现time out的情况，  
  可以用-T [Time]设置超时阈值。  
  本函数可以通过测试用例，具体超时原因还不清楚
  */
  int sign = x >> 31;
  int witoutsign = 0;
  if (sign)
  {
    witoutsign = (~x) + 1;
  }
  else
  {
    witoutsign = x;
  }
  //取绝对值
  if ((127 - witoutsign) >> 31)
  {
    //过大溢出，返回无穷大
    if (sign)
    {
      return 0;
    }
    else
    {
      return (0xFF << 23);
    }
  }
  else
  {
    //正常情况
    return ((x + 127) << 23);
  }
}

```

