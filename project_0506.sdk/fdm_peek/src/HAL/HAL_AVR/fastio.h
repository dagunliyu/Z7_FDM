/*
 * fastio.h
 *
 *  Created on: 2019年6月30日
 *      Author: W530
 */

#ifndef SRC_HAL_HAL_AVR_FASTIO_H_
#define SRC_HAL_HAL_AVR_FASTIO_H_

//#include <avr/io.h>
#include "../../core/macros.h"


#ifndef _BV
  #define _BV(PIN) (1UL << PIN)   // 1ul 表示无符号长整形; 
  //1ul 的二进制向左移动PIN个单位
#endif

/**
 * Magic I/O routines
 *
 * Now you can simply SET_OUTPUT(PIN); WRITE(PIN, HIGH); WRITE(PIN, LOW);
 *
 * Why double up on these macros? see http://gcc.gnu.org/onlinedocs/cpp/Stringification.html
 */


#endif /* SRC_HAL_HAL_AVR_FASTIO_H_ */
