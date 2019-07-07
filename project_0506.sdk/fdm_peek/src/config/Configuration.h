/*
 * Configuration.h
 *
 *  Created on: 2019年5月6日
 *      Author: aisl
 */

 /**
 * Configuration.h
 *
 * Basic settings such as:
 *
 * - Type of electronics			// 电子类型
 * - Type of temperature sensor		// 温度传感器类型
 * - Printer geometry				// 打印机结构
 * - Endstop configuration			// 限位配置
 * - LCD controller					// LCD控制器
 * - Extra features					// 额外的一些特性配置
 *
 * Advanced settings can be found in Configuration_adv.h // 高级设置在Configuration_adv.h中
 *
 */

#ifndef CONFIGURATION_H_
#define CONFIGURATION_H_

#define CONFIGURATION_H_VERSION 010100   // 配置文件的版本

//===========================================================================
// @section 信息提示--设置
//===========================================================================

// 在启动的时候,自定义的版本信息可以显示在[Pronterface等] 上位机中,这样可以明确查看自己的修改是否已经生效,并成功下载到板子里了
#define STRING_CONFIG_H_AUTHOR "(none, default config)" // Who made the changes.
#define SHOW_BOOTSCREEN							// 后面可以把这个屏蔽掉,打开lcd_start_screen函数中的显示操作
#define STRING_SPLASH_LINE1 SHORT_BUILD_VERSION // will be shown during bootup in line 1
#define STRING_SPLASH_LINE2 WEBSITE_URL         // will be shown during bootup in line 2


//===========================================================================
// @section 机器的设置
//===========================================================================

#define SERIAL_PORT 0

 // 波特率: 250000 most cases; :[2400, 9600, 19200, 38400, 57600, 115200, 250000, 500000, 1000000]
 // 可以设置到1000000 加速 SD文件传输; 容易中断传输则降低波特率
#define BAUDRATE 115200 //250000

// 定义板子的类型,
#ifndef MOTHERBOARD
  #define MOTHERBOARD BOARD_RAMPS_13_EEB // 加入自定义的板子类型  //BOARD_LHC_CSU_FDM  MOTHERBOARD BOARD_RAMPS_14_EFB BOARD_RAMPS_13_EEB
#endif

// option 自定义名称，在自己的机器的LCD后面显示“就绪”消息
#define CUSTOM_MACHINE_NAME "SMT 打印机"//"3D Printer"



//===========================================================================
// @section 挤出头部分的设置
//===========================================================================

// 定义挤出头数量 -- 用双头
// :[1, 2, 3, 4, 5]
#define EXTRUDERS 2

// 挤出机的偏移量(如果是用多个挤出机--取消注释，并在更改时依赖固件去定位)。
// 如果用单头打印,那挤出机的偏移量必须为X=0, Y=0; 如果用双头, x和y就是相对于另一个挤出头的距离
#define HOTEND_OFFSET_X {0.0, 50.00} // (in mm) for each extruder, offset of the hotend on the X axis
#define HOTEND_OFFSET_Y {0.0, 0.00}  // (in mm) for each extruder, offset of the hotend on the Y axis



//===========================================================================
// @section 热相关的设置
//===========================================================================


/**
 * --NORMAL IS 4.7kohm PULLUP!-- 1kohm pullup can be used on hotend sensor, using correct resistor and table
 *
 * Temperature sensors available:
 *
 *    -3 : thermocouple with MAX31855 (only for sensor 0)
 *    -2 : thermocouple with MAX6675 (only for sensor 0)
 *    -1 : thermocouple with AD595
 *     0 : not used
 *     1 : 100k thermistor - best choice for EPCOS 100k (4.7k pullup)
 *     2 : 200k thermistor - ATC Semitec 204GT-2 (4.7k pullup)
 *     3 : Mendel-parts thermistor (4.7k pullup)
 *     4 : 10k thermistor !! do not use it for a hotend. It gives bad resolution at high temp. !!
 *     5 : 100K thermistor - ATC Semitec 104GT-2 (Used in ParCan & J-Head) (4.7k pullup)
 *     6 : 100k EPCOS - Not as accurate as table 1 (created using a fluke thermocouple) (4.7k pullup)
 *     7 : 100k Honeywell thermistor 135-104LAG-J01 (4.7k pullup)
 *    71 : 100k Honeywell thermistor 135-104LAF-J01 (4.7k pullup)
 *     8 : 100k 0603 SMD Vishay NTCS0603E3104FXT (4.7k pullup)
 *     9 : 100k GE Sensing AL03006-58.2K-97-G1 (4.7k pullup)
 *    10 : 100k RS thermistor 198-961 (4.7k pullup)
 *    11 : 100k beta 3950 1% thermistor (4.7k pullup)
 *    12 : 100k 0603 SMD Vishay NTCS0603E3104FXT (4.7k pullup) (calibrated for Makibox hot bed)
 *    13 : 100k Hisens 3950  1% up to 300°C for hotend "Simple ONE " & "Hotend "All In ONE"
 *    20 : the PT100 circuit found in the Ultimainboard V2.x
 *    60 : 100k Maker's Tool Works Kapton Bed Thermistor beta=3950
 *    66 : 4.7M High Temperature thermistor from Dyze Design
 *    70 : the 100K thermistor found in the bq Hephestos 2
 *    75 : 100k Generic Silicon Heat Pad with NTC 100K MGB18-104F39050L32 thermistor
 *
 *       1k ohm pullup tables - This is atypical, and requires changing out the 4.7k pullup for 1k.
 *                              (but gives greater accuracy and more stable PID)
 *    51 : 100k thermistor - EPCOS (1k pullup)
 *    52 : 200k thermistor - ATC Semitec 204GT-2 (1k pullup)
 *    55 : 100k thermistor - ATC Semitec 104GT-2 (Used in ParCan & J-Head) (1k pullup)
 *
 *  1047 : Pt1000 with 4k7 pullup
 *  1010 : Pt1000 with 1k pullup (non standard)
 *   147 : Pt100 with 4k7 pullup
 *   110 : Pt100 with 1k pullup (non standard)
 *
 *         Use these for Testing or Development purposes. NEVER for production machine.
 *   998 : Dummy Table that ALWAYS reads 25°C or the temperature defined below.
 *   999 : Dummy Table that ALWAYS reads 100°C or the temperature defined below.
 *
 * :{ '0': "Not used", '1':"100k / 4.7k - EPCOS", '2':"200k / 4.7k - ATC Semitec 204GT-2", '3':"Mendel-parts / 4.7k", '4':"10k !! do not use for a hotend. Bad resolution at high temp. !!", '5':"100K / 4.7k - ATC Semitec 104GT-2 (Used in ParCan & J-Head)", '6':"100k / 4.7k EPCOS - Not as accurate as Table 1", '7':"100k / 4.7k Honeywell 135-104LAG-J01", '8':"100k / 4.7k 0603 SMD Vishay NTCS0603E3104FXT", '9':"100k / 4.7k GE Sensing AL03006-58.2K-97-G1", '10':"100k / 4.7k RS 198-961", '11':"100k / 4.7k beta 3950 1%", '12':"100k / 4.7k 0603 SMD Vishay NTCS0603E3104FXT (calibrated for Makibox hot bed)", '13':"100k Hisens 3950  1% up to 300°C for hotend 'Simple ONE ' & hotend 'All In ONE'", '20':"PT100 (Ultimainboard V2.x)", '51':"100k / 1k - EPCOS", '52':"200k / 1k - ATC Semitec 204GT-2", '55':"100k / 1k - ATC Semitec 104GT-2 (Used in ParCan & J-Head)", '60':"100k Maker's Tool Works Kapton Bed Thermistor beta=3950", '66':"Dyze Design 4.7M High Temperature thermistor", '70':"the 100K thermistor found in the bq Hephestos 2", '71':"100k / 4.7k Honeywell 135-104LAF-J01", '147':"Pt100 / 4.7k", '1047':"Pt1000 / 4.7k", '110':"Pt100 / 1k (non-standard)", '1010':"Pt1000 / 1k (non standard)", '-3':"Thermocouple + MAX31855 (only for sensor 0)", '-2':"Thermocouple + MAX6675 (only for sensor 0)", '-1':"Thermocouple + AD595",'998':"Dummy 1", '999':"Dummy 2" }
 */
#define TEMP_SENSOR_0 20 //1//20    //  PT100 用的是100k的热敏电阻
#define TEMP_SENSOR_1 1//20    // 用双头
#define TEMP_SENSOR_2 0
#define TEMP_SENSOR_3 0
#define TEMP_SENSOR_4 0
#define TEMP_SENSOR_BED 1  // 0 ？？

// 模拟(Dummy)热敏电阻恒温读数，用于998和999
#define DUMMY_THERMISTOR_998_VALUE 25
#define DUMMY_THERMISTOR_999_VALUE 100

// 使用温度传感器1作为传感器0的冗余传感器。如果两个传感器读出来的数据相差太大，打印将中止。
//#define TEMP_SENSOR_1_AS_REDUNDANT
#define MAX_REDUNDANT_TEMP_SENSOR_DIFF 10

// 在M109返回success之前,挤出机温度在这个:TEMP_RESIDENCY_TIME时间内 需要很接近目标温度
#define TEMP_RESIDENCY_TIME 10  // (seconds)
#define TEMP_HYSTERESIS 3       // (degC) 有+/-3度的范围 就代表是比较接近目标温度了
#define TEMP_WINDOW     1       // (degC) Window around target to start the residency timer x degC early.

// 在M190返回success之前, 热床温度在这个:TEMP_BED_RESIDENCY_TIME时间内 需要很接近目标温度
#define TEMP_BED_RESIDENCY_TIME 10  // (seconds)
#define TEMP_BED_HYSTERESIS 3       // (degC) 有+/-3度的范围 就代表是比较接近目标温度了
#define TEMP_BED_WINDOW     1       // (degC) Window around target to start the residency timer x degC early.

// 最低温度是指加热器在低于最低温度时 不使能加热mos管, 主要用来检查热敏电阻的接线是否断开。
// 否则会导致mos管一直开起加热。
#define HEATER_0_MINTEMP 5
#define HEATER_1_MINTEMP 5
#define HEATER_2_MINTEMP 5
#define HEATER_3_MINTEMP 5
#define HEATER_4_MINTEMP 5
#define BED_MINTEMP 5

// 当温度超过最高温度时，停止加热; 这个功能是为了防止热源意外过热,而不是因为热敏电阻过热导致的短路/故障
// 应该使用MINTEMP, 对热敏电阻进行短路/故障保护，。
#define HEATER_0_MAXTEMP 500 //450  190402 LCD显示最高值比设定的MAXTEMP还要小15度  //275
#define HEATER_1_MAXTEMP 500 //450  190402   //275
#define HEATER_2_MAXTEMP 300//275
#define HEATER_3_MAXTEMP 300//275
#define HEATER_4_MAXTEMP 300//275
#define BED_MAXTEMP 200


//============== 滑膜控制 - 未验证 ================
#define SlidingModeTemp
#if ENABLED(SlidingModeTemp)
	#define K_slide 5.2   // 放大倍数? X(s)/U(s) = (K * exp(-t0*s))/(tau*s + 1)
	#define t0_slide 0.25 // 纯滞后时间
	#define tau_slide 44  // 系统的时间常数
	#define a1_slide	( 1/(t0_slide*tau_slide) )  // 只会做简单的替换，运算一定要加上括号
	#define a2_slide  ( (t0_slide+tau_slide)/(t0_slide*tau_slide) )
	#define b1_slide  (K_slide/(t0_slide*tau_slide))

	#define lambda1 ((t0_slide+tau_slide)/(t0_slide*tau_slide))
	#define lambda0 (lambda1*lambda1/4)

	#define epsilon 1  // st = delta(e(t)) + lambda0 * e(t) + lambda11 *
	#define k_slide		1  // epsilon * sgn(s(t))
#endif


//===========================================================================
//============================= PID 设置 ====================================
//===========================================================================
// PID Tuning Guide here: http://reprap.org/wiki/PID_Tuning

// 屏蔽下面的PIDTEMP,使能bang-bang控制    Comment the following line to disable PID and enable bang-bang.
#define PIDTEMP
#define BANG_MAX 255		// limits current to nozzle while in bang-bang mode; 255=full current
#define PID_MAX BANG_MAX	// limits current to nozzle while PID is active (see PID_FUNCTIONAL_RANGE below); 255=full current
#if ENABLED(PIDTEMP)
  //#define PID_AUTOTUNE_MENU		// Add PID Autotune to the LCD "Temperature" menu to run M303 and apply the result.
  //#define PID_DEBUG				// Sends debug data to the serial port.
  //#define PID_OPENLOOP 1			// Puts PID in open loop. M104/M140 sets the output power from 0 to PID_MAX
  //#define SLOW_PWM_HEATERS		// 很低频率的PWM (roughly 0.125Hz=8s) and (由继电器驱动的加热器的最低状态时间约为1秒) minimum state time of approximately 1s useful for heaters driven by a relay
  //#define PID_PARAMS_PER_HOTEND	// 每个挤出头使用不同的PID参数，对不匹配的头比较有用  ( Uses separate PID parameters for each extruder (useful for mismatched extruders)
									// Set/get with gcode: M301 E[extruder number, 0-2]
  #define PID_FUNCTIONAL_RANGE 10	// 如果target和current之间温差大于PID_FUNCTIONAL_RANGE, 会关掉PID；加热终端会被设置为min或max  If the temperature difference between the target temperature and the actual temperature is more than PID_FUNCTIONAL_RANGE
									// then the PID will be shut off and the heater will be set to min/max.
  #define K1 0.95		// PID中的平滑因子 smoothing factor(smoothing factor within the PID)

  // If you are using a pre-configured hotend then you can use one of the value sets by uncommenting it

  // Ultimaker
  #define  DEFAULT_Kp 30      // 22.2
  #define  DEFAULT_Ki 1.08    // 1.08
  #define  DEFAULT_Kd 120     // 114

  // MakerGear
  //#define  DEFAULT_Kp 7.0
  //#define  DEFAULT_Ki 0.1
  //#define  DEFAULT_Kd 12

  // Mendel Parts V9 on 12V
  //#define  DEFAULT_Kp 63.0
  //#define  DEFAULT_Ki 2.25
  //#define  DEFAULT_Kd 440

#endif // PIDTEMP

//===========================================================================
//============================= PID > 热床温度控制 ==========================
//===========================================================================
// Select PID or bang-bang with PIDTEMPBED. If bang-bang, BED_LIMIT_SWITCHING will enable hysteresis
//
// Uncomment this to enable PID on the bed. It uses the same frequency PWM as the extruder.
// If your PID_dT is the default, and correct for your hardware/configuration, that means 7.689Hz,
// which is fine for driving a square wave into a resistive load and does not significantly impact you FET heating.
// This also works fine on a Fotek SSR-10DA Solid State Relay into a 250W heater.
// If your configuration is significantly different than this and you don't understand the issues involved, you probably
// shouldn't use bed PID until someone else verifies your hardware works.
// If this is enabled, find your own PID constants below.
//#define PIDTEMPBED

//#define BED_LIMIT_SWITCHING

// This sets the max power delivered to the bed, and replaces the HEATER_BED_DUTY_CYCLE_DIVIDER option.
// all forms of bed control obey this (PID, bang-bang, bang-bang with hysteresis)
// setting this to anything other than 255 enables a form of PWM to the bed just like HEATER_BED_DUTY_CYCLE_DIVIDER did,
// so you shouldn't use it unless you are OK with PWM on your bed.  (see the comment on enabling PIDTEMPBED)
#define MAX_BED_POWER 255 // limits duty cycle to bed; 255=full current

#if ENABLED(PIDTEMPBED)

  //#define PID_BED_DEBUG // Sends debug data to the serial port.

  //120V 250W silicone heater into 4mm borosilicate (MendelMax 1.5+)
  //from FOPDT model - kp=.39 Tp=405 Tdead=66, Tc set to 79.2, aggressive factor of .15 (vs .1, 1, 10)
  #define  DEFAULT_bedKp 10.00
  #define  DEFAULT_bedKi .023
  #define  DEFAULT_bedKd 305.4

  //120V 250W silicone heater into 4mm borosilicate (MendelMax 1.5+)
  //from pidautotune
  //#define  DEFAULT_bedKp 97.1
  //#define  DEFAULT_bedKi 1.41
  //#define  DEFAULT_bedKd 1675.16

  // FIND YOUR OWN: "M303 E-1 C8 S90" to run autotune on the bed at 90 degreesC for 8 cycles.
#endif // PIDTEMPBED

// @section extruder

//===========================================================================
//======================== 根据温度限制挤出机运动 ===========================
//===========================================================================

// 如果温度低于EXTRUDE_MINTEMP, 那么不运动e轴挤出丝材,因为温度不够
// 可以使用 M302 指令去设置最小的挤出温度, 或者不管hotend温度允许moving the extruder.
// *** IT IS HIGHLY RECOMMENDED TO LEAVE THIS OPTION ENABLED! ***
#define PREVENT_COLD_EXTRUSION
#define EXTRUDE_MINTEMP 0	//190305调试 //170   // 挤出机最低温度设置,低于此温度,在打印加热中挤出机不工作

// 此选项防止single挤出比 EXTRUDE_MAXLENGTH 还长;   注意：对于Bowden挤出机，如果这个设置的值太小可能会prevent loading.
#define PREVENT_LENGTHY_EXTRUDE
#define EXTRUDE_MAXLENGTH 200

//===========================================================================
//======================== Thermal 跑飞保护 =================================
//===========================================================================

/**
 * 温度跑飞保护：防止损坏机器或者是着火（温度传感器因为某种原因失效导致还在加热）
 * 若温度传感器失效,则无法再准确测量温度。如果检测到低温,软件还在持续保持加热，则极易引发故障.
 * "Thermal Runaway" 或者 "Heating failed" 错误, 在Configuration_adv.h 里进行调整
 */

#define THERMAL_PROTECTION_HOTENDS // 使能所有挤出头的热保护
#define THERMAL_PROTECTION_BED     // 使能热床的热保护





#endif /* CONFIGURATION_H_ */
