/*
 * macro.h
 *
 *  Created on: 2019��6��8��
 *      Author: W530
 */

#ifndef SRC_CORE_MACROS_H_
#define SRC_CORE_MACROS_H_

//#include <math.h>  		// ������ѧ��
#include "../fdm_main.h"  // �����˼�����Ҫ��ͷ�ļ�����

#define NUM_AXIS 5  	// 4   180921
#define XYZE 	 5      // 4   180921 ��Conditionals_LCD.h�н�XYZ����ΪXYZE
#define ABC      3
#define XYZ 	 3

// GNU C ��һ����ɫ����__attribute__ ����
//__attribute__ �������ú������ԣ�Function Attribute�����������ԣ�Variable Attribute�����������ԣ�Type Attribute����
//__attribute__((always_inline))��˼��ǿ������,���м���__attribute__((always_inline))�ĺ����ٱ�����ʱ���ᱻ����ɺ������ö���ֱ����չ�����ú�������
#define FORCE_INLINE __attribute__((always_inline)) inline
#define _UNUSED      __attribute__((unused))

// �����Ż�   Os O2�����Ż�ѡ��ļ���, ǰ�������ڻ����ٶȵ��Ż������������ڻ���size��С���Ż���
// man gcc�ܿ���������O0��O1��O2��O3����һ���������Ż�ѡ���𲽼Ӵ�Ĺ��̣�
#define _O0          __attribute__((optimize("O0")))
#define _Os          __attribute__((optimize("Os")))
#define _O1          __attribute__((optimize("O1")))
#define _O2          __attribute__((optimize("O2")))
#define _O3          __attribute__((optimize("O3")))


// ��Ӧ�ñ��жϵ�����(bracket)����, �漰�����жϲ���, ���ݺ���ʵ��ʹ��λ���滻��z7��
#ifndef CRITICAL_SECTION_SRART
	#define CRITICAL_SECTION_SRART unsigned char _sreg = SREG; cli(); //cli()��avr��disable�жϺ���,��interrupt.h��
	#define CRITICAL_SECTION_END    SREG = _sreg;
#endif



// ʱ��speed���factor, F_CPU��
// PS��ʱ������ԴΪ��33.333MHZ
#define F_CPU 33333000 // 33333333??  /1M
#define CYCLES_PER_MICROSECOND (F_CPU / 1000000L)  // 1us ��ѭ������  33.333��???
// 16 or 20   // 1us 16��20������  16M 20Mhz
#define INT0_PRESCALER 8  // ��Ƶ��

 
/***********step pulses�ĸ������ӳٺ궨��
 * (Highly granular delays for step pulses, etc)***********/
//NOOP 
#define NOOP do{} while(0)  // �ղ���
#define DELAY_0_NOP NOOP
#define DELAY_1_NOP __asm__("nop\n\t")  // ������� д������һ����������. ��Ҫȷ��д���Ƿ����
// ������֮���á�\n\t�����������ÿ�������뵥��ռ��һ��,����4��nopָ�
// ÿ��ָ���ġ�\n\t����ʾ���У�Ȼ�����TAB���׿գ���Ϊÿ�����ָ������ڵ���һ�У���Ҫ���У�
//�����Ʊ����Ϊ����ӦĳЩ��������Ҫ��

// ����ָ����ʱ
// ��ȷZ7��ʱ������,�������ڣ�
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

// ����1us����ʱʱ�䣬��Ҫ֪��һ��nop��ִ��ʱ��
#if CYCLES_PER_MICROSECOND == 16    // 1us��ѭ������
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




/*********************** ����ʱ��NOW & SOON ***************/
#define PENDING(NOW,SOON) ((long)(NOW-(SOON))<0) // ((int32_t)(NOW-(SOON))<0)
#define ELAPSED(NOW,SOON) (!PENDING(NOW,SOON))   // ʱ������
/******************************************************/

#define PIN_EXISTS(PN) (defined(PN ##_PIN) && PN ##_PIN >= 0)

// ɾ��δʹ�ñ����ϵı���������  
#define UNUSED(x) (void) (x)

// �Ӻ������ַ���, ʹ��#,�Ѳ����ַ���
#define STRINGIFY_(M) #M
#define STRINGIFY(M) STRINGIFY_(M) 

 
/***********************֧��ѡ����Եĺ�, ʹ��/��ֹĳЩ����ѡ��***************/
#define _CAT(a, ...) a ## __VA_ARGS__  // ʹ�ÿɱ������... �� __VA_ARGS__, __VA_ARGS__�滻ʡ�Ժ� 
#define SWITCH_ENABLED_false 0
#define SWITCH_ENABLED_true  1
#define SWITCH_ENABLED_0     0
#define SWITCH_ENABLED_1     1
#define SWITCH_ENABLED_      1
#define ENABLED(b)	_CAT(SWITCH_ENABLED_, b)       
#define DISABLED(b) (!_CAT(SWITCH_ENABLED_, b))  // ����������

// SWITCH_ENABLED_ ## PIDTEMP  ��PIDTEMPΪ1������true, ��ƴ�����Ľ��ΪSWITCH_ENABLED_1������SWITCH_ENABLED_true
// #define PIDTEMP  �궨�岻��#��ͷ,չ������ֱ���滻;�����#Ϊ��ͷ,��չ������ֱ���滻
// չ������#if ENABLED(PIDTEMP) --> ENABLED(1) --> _CAT(SWITCH_ENABLED_, 1) --> SWITCH_ENABLED_1 --> 1 

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


/***********************����ѧ������صĺ궨��***************/
#define Math_Associate_Operation
#ifdef Math_Associate_Operation 


// ����ʵ��λ��������ĺ궨�� 
#define TEST(n,b) 			( ((n) & _BV(b)) != 0 ) // n��1����bλ��������Ľ����Ϊ0,����true.����Ϊfalse
#define SBI(n,b)			(n | _BV(b))  			// n��1����bλ��������
#define CBI(n,b)			(n & ~_BV(b)) 			// n��ȡ�����(1����bλ)��������
#define SET_BIT(n,b,value)	(n) ^= ( ((-value)^(n)) & (_BV(b)) )// n�͵Ľ���� ��������ֵ��n:��λ����,��ͬȡ0,��ͬ��ȡ1

// ���һ�����Ƿ���2�Ĵ���
#define IS_POWER_OF_2(x) 	( (x) && !( (x) & ((x)-1) ) )

// maths shortcuts
#ifndef M_PI
  #define M_PI 3.14159265358979323846
#endif
#define RADIANS(d) 	( (d)*M_PI/180 ) // �Ƕ�ת����
#define DEGREE(r)	( (r)*180/M_PI ) // ����ת�Ƕ�
#define HYPOT2(x,y) (sq(x)+sq(y))    // ���ǽ�sq��Ϊsqrt
#define SIGN(a)     ((a>0)-(a<0))    // ���ź���, ��a>0, ��(a>0)=1,(a<0)=0,1-0=1;��֮��Ȼ

// Լ��ֵ
#define NOMORE(v,n)	do{ if(v > n) v = n; }while(0)
#define NOLESS(v,n)	do{ if(v < n) v = n; }while(0)

#define WITHIN(V,L,H) 		((V) >= (L) && (V) <= (H))
#define NUMERIC(a) 			WITHIN(a, '0', '9')   // ����
#define DECIMAL(a) 			(NUMERIC(a) || a == '.')  // С��
#define NUMERIC_SIGNED(a) 	(NUMERIC(a) || (a) == '-' || (a) == '+')
#define DECIMAL_SIGNED(a) 	(DECIMAL(a) || (a) == '-' || (a) == '+')
#define COUNT(a) 			(sizeof(a)/sizeof(*a))
#define ZERO(a) 			memset(a,0,sizeof(a))
#define COPY(a,b) 			memcpy(a, b, fmin(sizeof(a),sizeof(b))) 
// ���min������!!!!,�����math.hֻ��fmin
// memset memcpy����gnu...��string.h����
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

// ����?????
#define CEILING(x,y) (((x) + (y) - 1) / (y))

// ֱ�ӵ�min��maxû��, gun-arm-none-eabi���math.h��fmin fmax
#define MIN3(a, b, c)       fmin(fmin(a, b), c)			//min(min(a, b), c)
#define MIN4(a, b, c, d)    fmin(MIN3(a, b, c), d)		//min(MIN3(a, b, c), d)
#define MIN5(a, b, c, d, e) fmin(MIN4(a, b, c, d), e)	//min(MIN4(a, b, c, d), e)
#define MAX3(a, b, c)       fmax(fmax(a, b), c)			//max(max(a, b), c)
#define MAX4(a, b, c, d)    fmax(MAX3(a, b, c), d)		//max(MAX3(a, b, c), d)
#define MAX5(a, b, c, d, e) fmax(MAX4(a, b, c, d), e)  	//max(MAX4(a, b, c, d), e)

// ��0��ص��ж�
#define UNEAR_ZERO(x) 	((x) < 0.000001)
#define NEAR_ZERO(x) 	WITHIN(x, -0.000001, 0.000001)
#define NEAR(x,y) 		NEAR_ZERO((x)-(y))

//  reciprocal-���ݵģ��໥��
#define RECIPROCAL(x) 	(NEAR_ZERO(x) ? 0.0 : 1.0 / (x))  
// ����
#define FIXFLOAT(f) 	(f + 0.00001)   

// ���Ա�HAL��д(overridden)�� ����궨�� macros
#define ATAN2(y, x) atan2(y, x)   	// 	�� = ATan2(y, x)����Ħ�ȡֵ��Χ��[-PI, PI]�� atan2() ��avr��math.h����
									// �� = ATan(y / x)����Ħ�ȡֵ��Χ��[-PI/2, PI/2]��
#define FABS(x)     fabs(x)			// ��һ��ʵ���ľ���ֵ,����ͷ���ֵ����double; abs��int
#define POW(x, y)   pow(x, y)       // ����x��y�η�. x��y������ֵ����double��
#define SQRT(x)     sqrt(x)			// ��ƽ����
#define CEIL(x)     ceil(x)			// ��������-���ش��ڵ��ڱ��ʽ����С����, double��
#define FLOOR(x)    floor(x)		// ����ȡ��, ���ز�����x���������ֵ
#define LROUND(x)   lround(x)		// ��round����, x��������������ֵ, ����һ���������??
#define FMOD(x, y)  fmod(x,y) // FMOD������x/y�ĸ���������

#endif
/******************************************************/



#endif /* SRC_CORE_MACROS_H_ */
