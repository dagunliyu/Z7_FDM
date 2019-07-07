/*
 * fdm_main.h
 * ���main.cc��ʹ�õĴ��������, ��ʱ�俼�Ǻ�marlin2.0����......
 *  Created on: 2019��6��8��
 *      Author: W530
 */

#ifndef SRC_FDM_MAIN_H_
#define SRC_FDM_MAIN_H_

#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>  // Ӧ�ð�����memset��memcpy
#include <inttypes.h>

// ƽ̨δʵ����
//#include <util/delay.h>
//#include <avr/pgmspace.h>
//#include <avr/eeprom.h>
//#include <avr/interrupt.h>

#include "fdm_config.h"   // �滻MarlinConfig.h

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