/*
 * macro.h
 *
 *  Created on: 2019年6月8日
 *      Author: W530
 */

#ifndef SRC_CORE_MACROS_H_
#define SRC_CORE_MACROS_H_

//#include <math.h>  		// 包含数学宏
#include "../fdm_main.h"  // 包含了几个主要的头文件定义

#define NUM_AXIS 5  	// 4   180921
#define XYZE 	 5      // 4   180921 在Conditionals_LCD.h中将XYZ定义为XYZE
#define ABC      3
#define XYZ 	 3

// GNU C 的一大特色就是__attribute__ 机制
//__attribute__ 可以设置函数属性（Function Attribute）、变量属性（Variable Attribute）和类型属性（Type Attribute）。
//__attribute__((always_inline))意思是强制内联,所有加了__attribute__((always_inline))的函数再被调用时不会被编译成函数调用而是直接扩展到调用函数体内
#define FORCE_INLINE __attribute__((always_inline)) inline
#define _UNUSED      __attribute__((unused))

// 编译优化   Os O2都是优化选项的集合, 前者倾向于基于速度的优化，后者倾向于基于size更小的优化。
// man gcc能看出来，从O0到O1，O2，O3，是一个开启的优化选项逐步加大的过程；
#define _O0          __attribute__((optimize("O0")))
#define _Os          __attribute__((optimize("Os")))
#define _O1          __attribute__((optimize("O1")))
#define _O2          __attribute__((optimize("O2")))
#define _O3          __attribute__((optimize("O3")))


// 不应该被中断的括号(bracket)代码, 涉及到了中断操作, 根据后面实际使用位置替换成z7的
#ifndef CRITICAL_SECTION_SRART
	#define CRITICAL_SECTION_SRART unsigned char _sreg = SREG; cli(); //cli()是avr的disable中断函数,在interrupt.h中
	#define CRITICAL_SECTION_END    SREG = _sreg;
#endif



// 时钟speed相关factor, F_CPU是
// PS的时钟输入源为：33.333MHZ
#define F_CPU 33333000 // 33333333??  /1M
#define CYCLES_PER_MICROSECOND (F_CPU / 1000000L)  // 1us 的循环次数  33.333次???
// 16 or 20   // 1us 16或20个周期  16M 20Mhz
#define INT0_PRESCALER 8  // 分频器

 
/***********step pulses的高粒度延迟宏定义
 * (Highly granular delays for step pulses, etc)***********/
//NOOP 
#define NOOP do{} while(0)  // 空操作
#define DELAY_0_NOP NOOP
#define DELAY_1_NOP __asm__("nop\n\t")  // 内联汇编 写法：等一个机器周期. 需要确认写法是否可以
// 汇编代码之间用“\n\t”间隔，并且每条汇编代码单独占用一行,共有4个nop指令，
// 每个指令后的“\n\t”表示换行，然后加上TAB行首空，因为每个汇编指令必须在单独一行，需要换行，
//加上制表符是为了适应某些编译器的要求。

// 做空指令延时
// 明确Z7的时钟周期,机器周期！
#define DELAY_2_NOP DELAY_1_NOP; DELAY_1_NOP
#define DELAY_3_NOP DELAY_1_NOP; DELAY_2_NOP
#define DELAY_4_NOP DELAY_1_NOP; DELAY_3_NOP
#define DELAY_5_NOP DELAY_1_NOP; DELAY_4_NOP 
#define DELAY_10_NOP DELAY_5_NOP;  DELAY_5_NOP
#define DELAY_20_NOP DELAY_10_NOP; DELAY_10_NOP

#define DELAY_NOPS(X) \
  switch (X) { \
    case 20: DELAY_1_NOP; case 19: DELAY_1_NOP; \
    case 18: DELAY_1_NOP; case 17: DELAY_1_NOP; \
    case 16: DELAY_1_NOP; case 15: DELAY_1_NOP; \
    case 14: DELAY_1_NOP; case 13: DELAY_1_NOP; \
    case 12: DELAY_1_NOP; case 11: DELAY_1_NOP; \
    case 10: DELAY_1_NOP; case 9:  DELAY_1_NOP; \
    case 8:  DELAY_1_NOP; case 7:  DELAY_1_NOP; \
    case 6:  DELAY_1_NOP; case 5:  DELAY_1_NOP; \
    case 4:  DELAY_1_NOP; case 3:  DELAY_1_NOP; \
    case 2:  DELAY_1_NOP; case 1:  DELAY_1_NOP; \
  }

// 定义1us的延时时间，需要知道一个nop的执行时间
#if CYCLES_PER_MICROSECOND == 16    // 1us的循环次数
  #define DELAY_1US DELAY_10_NOP; DELAY_5_NOP; DELAY_1_NOP
#else
  #define DELAY_1US DELAY_20_NOP
#endif
#define DELAY_2US  DELAY_1US; DELAY_1US
#define DELAY_3US  DELAY_1US; DELAY_2US
#define DELAY_4US  DELAY_1US; DELAY_3US
#define DELAY_5US  DELAY_1US; DELAY_4US
#define DELAY_6US  DELAY_1US; DELAY_5US
#define DELAY_7US  DELAY_1US; DELAY_6US
#define DELAY_8US  DELAY_1US; DELAY_7US
#define DELAY_9US  DELAY_1US; DELAY_8US
#define DELAY_10US DELAY_1US; DELAY_9US

/******************************************************/




/*********************** 计算时间NOW & SOON ***************/
#define PENDING(NOW,SOON) ((long)(NOW-(SOON))<0) // ((int32_t)(NOW-(SOON))<0)
#define ELAPSED(NOW,SOON) (!PENDING(NOW,SOON))   // 时间消逝
/******************************************************/

#define PIN_EXISTS(PN) (defined(PN ##_PIN) && PN ##_PIN >= 0)

// 删除未使用变量上的编译器警告  
#define UNUSED(x) (void) (x)

// 从宏生成字符串, 使用#,把参数字符化
#define STRINGIFY_(M) #M
#define STRINGIFY(M) STRINGIFY_(M) 

 
/***********************支持选项测试的宏, 使能/禁止某些功能选项***************/
#define _CAT(a, ...) a ## __VA_ARGS__  // 使用可变参数宏... 和 __VA_ARGS__, __VA_ARGS__替换省略号 
#define SWITCH_ENABLED_false 0
#define SWITCH_ENABLED_true  1
#define SWITCH_ENABLED_0     0
#define SWITCH_ENABLED_1     1
#define SWITCH_ENABLED_      1
#define ENABLED(b)	_CAT(SWITCH_ENABLED_, b)       
#define DISABLED(b) (!_CAT(SWITCH_ENABLED_, b))  // ？？？？？

// SWITCH_ENABLED_ ## PIDTEMP  若PIDTEMP为1或者是true, 则拼起来的结果为SWITCH_ENABLED_1或者是SWITCH_ENABLED_true
// #define PIDTEMP  宏定义不以#开头,展开参数直接替换;如果以#为开头,不展开参数直接替换
// 展开过程#if ENABLED(PIDTEMP) --> ENABLED(1) --> _CAT(SWITCH_ENABLED_, 1) --> SWITCH_ENABLED_1 --> 1 

/******************************************************/


/***********************Macros for initializing arrays***************/ 
#define ARRAY_6(v1, v2, v3, v4, v5, v6, ...) { v1, v2, v3, v4, v5, v6 }
#define ARRAY_5(v1, v2, v3, v4, v5, ...)     { v1, v2, v3, v4, v5 }
#define ARRAY_4(v1, v2, v3, v4, ...)         { v1, v2, v3, v4 }
#define ARRAY_3(v1, v2, v3, ...)             { v1, v2, v3 }
#define ARRAY_2(v1, v2, ...)                 { v1, v2 }
#define ARRAY_1(v1, ...)                     { v1 }

#define _ARRAY_N(N, ...) ARRAY_ ##N(__VA_ARGS__)
#define ARRAY_N(N, ...) _ARRAY_N(N, __VA_ARGS__)
/******************************************************/


/***********************和数学操作相关的宏定义***************/
#define Math_Associate_Operation
#ifdef Math_Associate_Operation 


// 用于实现位掩码操作的宏定义 
#define TEST(n,b) 			( ((n) & _BV(b)) != 0 ) // n和1左移b位做与运算的结果不为0,返回true.否则为false
#define SBI(n,b)			(n | _BV(b))  			// n和1左移b位做或运算
#define CBI(n,b)			(n & ~_BV(b)) 			// n和取反后的(1左移b位)做与运算
#define SET_BIT(n,b,value)	(n) ^= ( ((-value)^(n)) & (_BV(b)) )// n和的结果做 异或运算后赋值给n:按位运算,相同取0,不同的取1

// 检查一个数是否是2的次幂
#define IS_POWER_OF_2(x) 	( (x) && !( (x) & ((x)-1) ) )

// maths shortcuts
#ifndef M_PI
  #define M_PI 3.14159265358979323846
#endif
#define RADIANS(d) 	( (d)*M_PI/180 ) // 角度转弧度
#define DEGREE(r)	( (r)*180/M_PI ) // 弧度转角度
#define HYPOT2(x,y) (sq(x)+sq(y))    // 考虑将sq换为sqrt
#define SIGN(a)     ((a>0)-(a<0))    // 符号函数, 若a>0, 则(a>0)=1,(a<0)=0,1-0=1;反之亦然

// 约束值
#define NOMORE(v,n)	do{ if(v > n) v = n; }while(0)
#define NOLESS(v,n)	do{ if(v < n) v = n; }while(0)

#define WITHIN(V,L,H) 		((V) >= (L) && (V) <= (H))
#define NUMERIC(a) 			WITHIN(a, '0', '9')   // 数字
#define DECIMAL(a) 			(NUMERIC(a) || a == '.')  // 小数
#define NUMERIC_SIGNED(a) 	(NUMERIC(a) || (a) == '-' || (a) == '+')
#define DECIMAL_SIGNED(a) 	(DECIMAL(a) || (a) == '-' || (a) == '+')
#define COUNT(a) 			(sizeof(a)/sizeof(*a))
#define ZERO(a) 			memset(a,0,sizeof(a))
#define COPY(a,b) 			memcpy(a, b, fmin(sizeof(a),sizeof(b))) 
// 解决min的问题!!!!,这里的math.h只有fmin
// memset memcpy都是gnu...的string.h函数
// The memset() function fills the first len bytes of the memory area pointed  to by dest with the constant byte val.

// The memcpy() function copies len bytes from memory area src to memory area
// dest.  The memory areas may not overlap.  Use memmove() if the memory areas do overlap.

// Macros for adding
#define INC_0 1
#define INC_1 2
#define INC_2 3
#define INC_3 4
#define INC_4 5
#define INC_5 6
#define INC_6 7
#define INC_7 8
#define INC_8 9
#define INCREMENT_(n) INC_ ##n
#define INCREMENT(n) INCREMENT_(n)

// Macros for subtracting
#define DEC_1 0
#define DEC_2 1
#define DEC_3 2
#define DEC_4 3
#define DEC_5 4
#define DEC_6 5
#define DEC_7 6
#define DEC_8 7
#define DEC_9 8
#define DECREMENT_(n) DEC_ ##n
#define DECREMENT(n) DECREMENT_(n)

// 上限?????
#define CEILING(x,y) (((x) + (y) - 1) / (y))

// 直接的min和max没有, gun-arm-none-eabi里的math.h是fmin fmax
#define MIN3(a, b, c)       fmin(fmin(a, b), c)			//min(min(a, b), c)
#define MIN4(a, b, c, d)    fmin(MIN3(a, b, c), d)		//min(MIN3(a, b, c), d)
#define MIN5(a, b, c, d, e) fmin(MIN4(a, b, c, d), e)	//min(MIN4(a, b, c, d), e)
#define MAX3(a, b, c)       fmax(fmax(a, b), c)			//max(max(a, b), c)
#define MAX4(a, b, c, d)    fmax(MAX3(a, b, c), d)		//max(MAX3(a, b, c), d)
#define MAX5(a, b, c, d, e) fmax(MAX4(a, b, c, d), e)  	//max(MAX4(a, b, c, d), e)

// 和0相关的判断
#define UNEAR_ZERO(x) 	((x) < 0.000001)
#define NEAR_ZERO(x) 	WITHIN(x, -0.000001, 0.000001)
#define NEAR(x,y) 		NEAR_ZERO((x)-(y))

//  reciprocal-互惠的；相互的
#define RECIPROCAL(x) 	(NEAR_ZERO(x) ? 0.0 : 1.0 / (x))  
// 定点
#define FIXFLOAT(f) 	(f + 0.00001)   

// 可以被HAL重写(overridden)的 运算宏定义 macros
#define ATAN2(y, x) atan2(y, x)   	// 	θ = ATan2(y, x)求出的θ取值范围是[-PI, PI]。 atan2() 是avr的math.h函数
									// θ = ATan(y / x)求出的θ取值范围是[-PI/2, PI/2]。
#define FABS(x)     fabs(x)			// 求一个实数的绝对值,输入和返回值都是double; abs是int
#define POW(x, y)   pow(x, y)       // 计算x的y次方. x、y及函数值都是double型
#define SQRT(x)     sqrt(x)			// 开平方根
#define CEIL(x)     ceil(x)			// 整数上限-返回大于等于表达式的最小整数, double型
#define FLOOR(x)    floor(x)		// 向下取整, 返回不大于x的最大整数值
#define LROUND(x)   lround(x)		// 和round类似, x的四舍五入整数值, 会有一定概率溢出??
#define FMOD(x, y)  fmod(x,y) // FMOD：返回x/y的浮点数余数

#endif
/******************************************************/



#endif /* SRC_CORE_MACROS_H_ */
