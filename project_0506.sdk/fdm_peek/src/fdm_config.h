
// 190608
// ����һЩ�궨���ͷ�ļ�,�Ա���������Ҫ���õĵط�,����fdm_config.h������
#ifndef FDM_CONFIG_H
#define FDM_CONFIG_H


#include "HAL/HAL_AVR/fastio.h"
#include "core/macros.h"
#include "core/boards.h"
#include "inc/Version.h"
#include "config/Configuration.h"
//#include "config/Conditionals_LCD.h"
#include "config/Configuration_adv.h"
//#include "pins/pins.h"  	// pins�Ķ�����Ҫ����vivado��Լ���ļ�����

#ifndef USBCON
  #define HardwareSerial_h 	// trick to disable the standard HWserial
#endif

//#include "Arduino.h"
#include "config/Conditionals_post.h"
#include "inc/SanityCheck.h"      // �������﷨���,�������ó���

#endif // FDM_CONFIG_H
