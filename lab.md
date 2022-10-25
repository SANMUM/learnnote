# datalab

1. 仅使用~和&实现异或运算

   ```c++
   int bitXor(int x,int y){
       return ~(~x&~y)&~(x&y); //仅用~和&
       //return (a|b)&(~a|~b); //用~,&,|
       //return (a&~b)|(~a&b);
   }
   ```

2. 使用位运算获取对2补码的最小int值

   ```c++
   /* 
    * tmin - return minimum two's complement integer 
    *   Legal ops: ! ~ & ^ | + << >>
    *   Max ops: 4
    *   Rating: 1
    */
   int tmin(void) {
   
     return 0x1<<31;
     // return 2;
   
   }
   ```

   

3. 通过位运算计算是否是补码最大值

   ```c++
   /*
    * isTmax - returns 1 if x is the maximum, two's complement number,
    *     and 0 otherwise 
    *   Legal ops: ! ~ & ^ | +
    *   Max ops: 10
    *   Rating: 1
    */
   int isTmax(int x) {
     int i = x+1;//Tmin,1000...
     x=x+i;//-1,1111...
     x=~x;//0,0000...
     i=!i;//exclude x=0xffff...
     x=x+i;//exclude x=0xffff...
     return !x;
   }
   ```

   - 通过将最大值变成0，然后用逻辑！

4. 判断所有的偶数位是否为1

   ```c++
   /* 
    * allOddBits - return 1 if all odd-numbered bits in word set to 1
    *   where bits are numbered from 0 (least significant) to 31 (most significant)
    *   Examples allOddBits(0xFFFFFFFD) = 0, allOddBits(0xAAAAAAAA) = 1
    *   Legal ops: ! ~ & ^ | + << >>
    *   Max ops: 12
    *   Rating: 2
    */
   int allOddBits(int x) {
     int mask = 0xAAAAAAAA;
     return !((mask&x)^mask);
     // return !(x^mask);
     
   }
   ```

   构造掩码将其他位清零，mask&x，再与mask异或取非

5. 求相反数

   ```c++
   /* 
    * negate - return -x 
    *   Example: negate(1) = -1.
    *   Legal ops: ! ~ & ^ | + << >>
    *   Max ops: 5
    *   Rating: 2
    */
   int negate(int x) {
     return ~x + 1;
   }
   ```

   常识：取反加1

6. 计算输入值是否是数字 0-9 的 `ASCII` 值

   ```c++
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
     int sign = 0x1<<31;
     int upperBound = ~(sign|0x39);
     int lowerBound = ~0x30;
     upperBound = sign&(upperBound+x)>>31;
     lowerBound = sign&(lowerBound+1+x)>>31;
     return !(upperBound|lowerBound);
   }
   ```

   使用两个数，一个数是加上比0x39大的数后符号由正变负，另一个数是加上比0x30小的值时是负数。这两个数是代码中初始化的 `upperBound` 和 `lowerBound`，然后加法之后获取其符号位判断即可

7. 三目运算符

   ```c++
   /* 
    * conditional - same as x ? y : z 
    *   Example: conditional(2,4,5) = 4
    *   Legal ops: ! ~ & ^ | + << >>
    *   Max ops: 16
    *   Rating: 3
    */
   int conditional(int x, int y, int z) {
     x = !!x;
     x = ~x+1;
     return (x&y)|(~x&z);
   }
   ```

   根据 `x` 的布尔值转换为全0或全1是不是更容易解决了，即 `x==0` 时位表示是全0的， `x!=0` 时位表示是全1的。这就是1-2行代码，通过获取其布尔值0或1，然后求其补码（0的补码是本身，位表示全0；1的补码是-1，位表示全1）得到想要的结果。然后通过位运算获取最终值。

8. 使用位级运算符实现<=

   ```c++
   /* 
    * isLessOrEqual - if x <= y  then return 1, else return 0 
    *   Example: isLessOrEqual(4,5) = 1.
    *   Legal ops: ! ~ & ^ | + << >>
    *   Max ops: 24
    *   Rating: 3
    */
   int isLessOrEqual(int x, int y) {
     int negX=~x+1;//-x
     int addX=negX+y;//y-x
     int checkSign = addX>>31&1; //y-x的符号
     int leftBit = 1<<31;//最大位为1的32位有符号数
     int xLeft = x&leftBit;//x的符号
     int yLeft = y&leftBit;//y的符号
     int bitXor = xLeft ^ yLeft;//x和y符号相同标志位，相同为0不同为1
     bitXor = (bitXor>>31)&1;//符号相同标志位格式化为0或1
     return ((!bitXor)&(!checkSign))|(bitXor&(xLeft>>31));//返回1有两种情况：符号相同标志位为0（相同）位与 y-x 的符号为0（y-x>=0）结果为1；符号相同标志位为1（不同）位与x的符号位为1（x<0）
   }
   ```

   一是符号不同正数为大，二是符号相同看差值符号。

   

9. 使用位级运算实现逻辑非！

   ```c++
   /* 
    * logicalNeg - implement the ! operator, using all of 
    *              the legal operators except !
    *   Examples: logicalNeg(3) = 0, logicalNeg(0) = 1
    *   Legal ops: ~ & ^ | + << >>
    *   Max ops: 12
    *   Rating: 4 
    */
   
   int logicalNeg(int x) {
   
     return ((x|(~x+1))>>31)+1;
   }
   ```

10. 一个数用补码表示最少需要多少位

    ```c
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
    int howManyBits(int x) {
      int b16,b8,b4,b2,b1,b0;
      int sign=x>>31;
      x = (sign&~x)|(~sign&x);//如果x为正则不变，否则按位取反（这样好找最高位为1的，原来是最高位为0的，这样也将符号位去掉了）
    
    
    // 不断缩小范围
      b16 = !!(x>>16)<<4;//高十六位是否有1
      x = x>>b16;//如果有（至少需要16位），则将原数右移16位
      b8 = !!(x>>8)<<3;//剩余位高8位是否有1
      x = x>>b8;//如果有（至少需要16+8=24位），则右移8位
      b4 = !!(x>>4)<<2;//同理
      x = x>>b4;
      b2 = !!(x>>2)<<1;
      x = x>>b2;
      b1 = !!(x>>1);
      x = x>>b1;
      b0 = x;
      return b16+b8+b4+b2+b1+b0+1;//+1表示加上符号位
    }
    ```

11. 求2乘以一个浮点数

    ```c
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
      int exp = (uf&0x7f800000)>>23;
      int sign = uf&(1<<31);
      if(exp==0) return uf<<1|sign;
      if(exp==255) return uf;
      exp++;
      if(exp==255) return 0x7f800000|sign;
      return (exp<<23)|(uf&0x807fffff);
    }
    ```

12. 将浮点数转换为整数

    ```c
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
      int s_    = uf>>31;
      int exp_  = ((uf&0x7f800000)>>23)-127;
      int frac_ = (uf&0x007fffff)|0x00800000;
      if(!(uf&0x7fffffff)) return 0;
    
      if(exp_ > 31) return 0x80000000;
      if(exp_ < 0) return 0;
    
      if(exp_ > 23) frac_ <<= (exp_-23);
      else frac_ >>= (23-exp_);
    
      if(!((frac_>>31)^s_)) return frac_;
      else if(frac_>>31) return 0x80000000;
      else return ~frac_+1;
    }
    ```

13. 求$2.0^x$

    ```c++
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
     *   Max ops: 31 
     *   Rating: 4
     */
    unsigned floatPower2(int x) {
    
      int INF = 0xff<<23;
      int exp = x + 127;
      if(exp <= 0) return 0;
      if(exp >= 255) return INF;
      return exp << 23;
    }
    ```

    
