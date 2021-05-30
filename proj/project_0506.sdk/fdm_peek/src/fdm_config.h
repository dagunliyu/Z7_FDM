
// 190608
// 包含一些宏定义的头文件,以便在其他需要调用的地方,进行fdm_config.h的引用
#ifndef FDM_CONFIG_H
#define FDM_CONFIG_H


#include "HAL/HAL_AVR/fastio.h"
#include "core/macros.h"
#include "core/boards.h"
#include "inc/Version.h"
#include "config/Configuration.h"
//#include "config/Conditionals_LCD.h"
#include "config/Configuration_adv.h"
//#include "pins/pins.h"  	// pins的东西主要都在vivado的约束文件中了

#ifndef USBCON
  #define HardwareSerial_h 	// trick to disable the standard HWserial
#endif

//#include "Arduino.h"
#include "config/Conditionals_post.h"
#include "inc/SanityCheck.h"      // 辅助做语法检测,避免配置出错

#endif // FDM_CONFIG_H
