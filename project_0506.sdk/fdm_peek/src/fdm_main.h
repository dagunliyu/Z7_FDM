/*
 * fdm_main.h
 * 存放main.cc中使用的大多数函数, 看时间考虑和marlin2.0兼容......
 *  Created on: 2019年6月8日
 *      Author: W530
 */

#ifndef SRC_FDM_MAIN_H_
#define SRC_FDM_MAIN_H_

#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>  // 应该包含了memset和memcpy
#include <inttypes.h>

// 平台未实现项
//#include <util/delay.h>
//#include <avr/pgmspace.h>
//#include <avr/eeprom.h>
//#include <avr/interrupt.h>

#include "fdm_config.h"   // 替换MarlinConfig.h

#ifdef DEBUG_GCODE_PARSER
  #include "gcode/gcode.h"
#endif

#include "core/enum.h"
#include "core/types.h"
//#include "HAL/HAL_AVR/fastio.h"
#include "core/utility.h"
//#include "core/serial.h"


/*

#if ENABLED(PRINTCOUNTER)

#else

#endif
*/

#endif /* SRC_FDM_MAIN_H_ */
