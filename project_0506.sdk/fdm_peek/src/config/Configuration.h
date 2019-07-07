/*
 * Configuration.h
 *
 *  Created on: 2019��5��6��
 *      Author: aisl
 */

 /**
 * Configuration.h
 *
 * Basic settings such as:
 *
 * - Type of electronics			// ��������
 * - Type of temperature sensor		// �¶ȴ���������
 * - Printer geometry				// ��ӡ���ṹ
 * - Endstop configuration			// ��λ����
 * - LCD controller					// LCD������
 * - Extra features					// �����һЩ��������
 *
 * Advanced settings can be found in Configuration_adv.h // �߼�������Configuration_adv.h��
 *
 */

#ifndef CONFIGURATION_H_
#define CONFIGURATION_H_

#define CONFIGURATION_H_VERSION 010100   // �����ļ��İ汾

//===========================================================================
// @section ��Ϣ��ʾ--����
//===========================================================================

// ��������ʱ��,�Զ���İ汾��Ϣ������ʾ��[Pronterface��] ��λ����,����������ȷ�鿴�Լ����޸��Ƿ��Ѿ���Ч,���ɹ����ص���������
#define STRING_CONFIG_H_AUTHOR "(none, default config)" // Who made the changes.
#define SHOW_BOOTSCREEN							// ������԰�������ε�,��lcd_start_screen�����е���ʾ����
#define STRING_SPLASH_LINE1 SHORT_BUILD_VERSION // will be shown during bootup in line 1
#define STRING_SPLASH_LINE2 WEBSITE_URL         // will be shown during bootup in line 2


//===========================================================================
// @section ����������
//===========================================================================

#define SERIAL_PORT 0

 // ������: 250000 most cases; :[2400, 9600, 19200, 38400, 57600, 115200, 250000, 500000, 1000000]
 // �������õ�1000000 ���� SD�ļ�����; �����жϴ����򽵵Ͳ�����
#define BAUDRATE 115200 //250000

// ������ӵ�����,
#ifndef MOTHERBOARD
  #define MOTHERBOARD BOARD_RAMPS_13_EEB // �����Զ���İ�������  //BOARD_LHC_CSU_FDM  MOTHERBOARD BOARD_RAMPS_14_EFB BOARD_RAMPS_13_EEB
#endif

// option �Զ������ƣ����Լ��Ļ�����LCD������ʾ����������Ϣ
#define CUSTOM_MACHINE_NAME "SMT ��ӡ��"//"3D Printer"



//===========================================================================
// @section ����ͷ���ֵ�����
//===========================================================================

// ���強��ͷ���� -- ��˫ͷ
// :[1, 2, 3, 4, 5]
#define EXTRUDERS 2

// ��������ƫ����(������ö��������--ȡ��ע�ͣ����ڸ���ʱ�����̼�ȥ��λ)��
// ����õ�ͷ��ӡ,�Ǽ�������ƫ��������ΪX=0, Y=0; �����˫ͷ, x��y�����������һ������ͷ�ľ���
#define HOTEND_OFFSET_X {0.0, 50.00} // (in mm) for each extruder, offset of the hotend on the X axis
#define HOTEND_OFFSET_Y {0.0, 0.00}  // (in mm) for each extruder, offset of the hotend on the Y axis



//===========================================================================
// @section ����ص�����
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
 *    13 : 100k Hisens 3950  1% up to 300��C for hotend "Simple ONE " & "Hotend "All In ONE"
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
 *   998 : Dummy Table that ALWAYS reads 25��C or the temperature defined below.
 *   999 : Dummy Table that ALWAYS reads 100��C or the temperature defined below.
 *
 * :{ '0': "Not used", '1':"100k / 4.7k - EPCOS", '2':"200k / 4.7k - ATC Semitec 204GT-2", '3':"Mendel-parts / 4.7k", '4':"10k !! do not use for a hotend. Bad resolution at high temp. !!", '5':"100K / 4.7k - ATC Semitec 104GT-2 (Used in ParCan & J-Head)", '6':"100k / 4.7k EPCOS - Not as accurate as Table 1", '7':"100k / 4.7k Honeywell 135-104LAG-J01", '8':"100k / 4.7k 0603 SMD Vishay NTCS0603E3104FXT", '9':"100k / 4.7k GE Sensing AL03006-58.2K-97-G1", '10':"100k / 4.7k RS 198-961", '11':"100k / 4.7k beta 3950 1%", '12':"100k / 4.7k 0603 SMD Vishay NTCS0603E3104FXT (calibrated for Makibox hot bed)", '13':"100k Hisens 3950  1% up to 300��C for hotend 'Simple ONE ' & hotend 'All In ONE'", '20':"PT100 (Ultimainboard V2.x)", '51':"100k / 1k - EPCOS", '52':"200k / 1k - ATC Semitec 204GT-2", '55':"100k / 1k - ATC Semitec 104GT-2 (Used in ParCan & J-Head)", '60':"100k Maker's Tool Works Kapton Bed Thermistor beta=3950", '66':"Dyze Design 4.7M High Temperature thermistor", '70':"the 100K thermistor found in the bq Hephestos 2", '71':"100k / 4.7k Honeywell 135-104LAF-J01", '147':"Pt100 / 4.7k", '1047':"Pt1000 / 4.7k", '110':"Pt100 / 1k (non-standard)", '1010':"Pt1000 / 1k (non standard)", '-3':"Thermocouple + MAX31855 (only for sensor 0)", '-2':"Thermocouple + MAX6675 (only for sensor 0)", '-1':"Thermocouple + AD595",'998':"Dummy 1", '999':"Dummy 2" }
 */
#define TEMP_SENSOR_0 20 //1//20    //  PT100 �õ���100k����������
#define TEMP_SENSOR_1 1//20    // ��˫ͷ
#define TEMP_SENSOR_2 0
#define TEMP_SENSOR_3 0
#define TEMP_SENSOR_4 0
#define TEMP_SENSOR_BED 1  // 0 ����

// ģ��(Dummy)����������¶���������998��999
#define DUMMY_THERMISTOR_998_VALUE 25
#define DUMMY_THERMISTOR_999_VALUE 100

// ʹ���¶ȴ�����1��Ϊ������0�����ഫ����������������������������������̫�󣬴�ӡ����ֹ��
//#define TEMP_SENSOR_1_AS_REDUNDANT
#define MAX_REDUNDANT_TEMP_SENSOR_DIFF 10

// ��M109����success֮ǰ,�������¶������:TEMP_RESIDENCY_TIMEʱ���� ��Ҫ�ܽӽ�Ŀ���¶�
#define TEMP_RESIDENCY_TIME 10  // (seconds)
#define TEMP_HYSTERESIS 3       // (degC) ��+/-3�ȵķ�Χ �ʹ����ǱȽϽӽ�Ŀ���¶���
#define TEMP_WINDOW     1       // (degC) Window around target to start the residency timer x degC early.

// ��M190����success֮ǰ, �ȴ��¶������:TEMP_BED_RESIDENCY_TIMEʱ���� ��Ҫ�ܽӽ�Ŀ���¶�
#define TEMP_BED_RESIDENCY_TIME 10  // (seconds)
#define TEMP_BED_HYSTERESIS 3       // (degC) ��+/-3�ȵķ�Χ �ʹ����ǱȽϽӽ�Ŀ���¶���
#define TEMP_BED_WINDOW     1       // (degC) Window around target to start the residency timer x degC early.

// ����¶���ָ�������ڵ�������¶�ʱ ��ʹ�ܼ���mos��, ��Ҫ���������������Ľ����Ƿ�Ͽ���
// ����ᵼ��mos��һֱ������ȡ�
#define HEATER_0_MINTEMP 5
#define HEATER_1_MINTEMP 5
#define HEATER_2_MINTEMP 5
#define HEATER_3_MINTEMP 5
#define HEATER_4_MINTEMP 5
#define BED_MINTEMP 5

// ���¶ȳ�������¶�ʱ��ֹͣ����; ���������Ϊ�˷�ֹ��Դ�������,��������Ϊ����������ȵ��µĶ�·/����
// Ӧ��ʹ��MINTEMP, ������������ж�·/���ϱ�������
#define HEATER_0_MAXTEMP 500 //450  190402 LCD��ʾ���ֵ���趨��MAXTEMP��ҪС15��  //275
#define HEATER_1_MAXTEMP 500 //450  190402   //275
#define HEATER_2_MAXTEMP 300//275
#define HEATER_3_MAXTEMP 300//275
#define HEATER_4_MAXTEMP 300//275
#define BED_MAXTEMP 200


//============== ��Ĥ���� - δ��֤ ================
#define SlidingModeTemp
#if ENABLED(SlidingModeTemp)
	#define K_slide 5.2   // �Ŵ���? X(s)/U(s) = (K * exp(-t0*s))/(tau*s + 1)
	#define t0_slide 0.25 // ���ͺ�ʱ��
	#define tau_slide 44  // ϵͳ��ʱ�䳣��
	#define a1_slide	( 1/(t0_slide*tau_slide) )  // ֻ�����򵥵��滻������һ��Ҫ��������
	#define a2_slide  ( (t0_slide+tau_slide)/(t0_slide*tau_slide) )
	#define b1_slide  (K_slide/(t0_slide*tau_slide))

	#define lambda1 ((t0_slide+tau_slide)/(t0_slide*tau_slide))
	#define lambda0 (lambda1*lambda1/4)

	#define epsilon 1  // st = delta(e(t)) + lambda0 * e(t) + lambda11 *
	#define k_slide		1  // epsilon * sgn(s(t))
#endif


//===========================================================================
//============================= PID ���� ====================================
//===========================================================================
// PID Tuning Guide here: http://reprap.org/wiki/PID_Tuning

// ���������PIDTEMP,ʹ��bang-bang����    Comment the following line to disable PID and enable bang-bang.
#define PIDTEMP
#define BANG_MAX 255		// limits current to nozzle while in bang-bang mode; 255=full current
#define PID_MAX BANG_MAX	// limits current to nozzle while PID is active (see PID_FUNCTIONAL_RANGE below); 255=full current
#if ENABLED(PIDTEMP)
  //#define PID_AUTOTUNE_MENU		// Add PID Autotune to the LCD "Temperature" menu to run M303 and apply the result.
  //#define PID_DEBUG				// Sends debug data to the serial port.
  //#define PID_OPENLOOP 1			// Puts PID in open loop. M104/M140 sets the output power from 0 to PID_MAX
  //#define SLOW_PWM_HEATERS		// �ܵ�Ƶ�ʵ�PWM (roughly 0.125Hz=8s) and (�ɼ̵��������ļ����������״̬ʱ��ԼΪ1��) minimum state time of approximately 1s useful for heaters driven by a relay
  //#define PID_PARAMS_PER_HOTEND	// ÿ������ͷʹ�ò�ͬ��PID�������Բ�ƥ���ͷ�Ƚ�����  ( Uses separate PID parameters for each extruder (useful for mismatched extruders)
									// Set/get with gcode: M301 E[extruder number, 0-2]
  #define PID_FUNCTIONAL_RANGE 10	// ���target��current֮���²����PID_FUNCTIONAL_RANGE, ��ص�PID�������ն˻ᱻ����Ϊmin��max  If the temperature difference between the target temperature and the actual temperature is more than PID_FUNCTIONAL_RANGE
									// then the PID will be shut off and the heater will be set to min/max.
  #define K1 0.95		// PID�е�ƽ������ smoothing factor(smoothing factor within the PID)

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
//============================= PID > �ȴ��¶ȿ��� ==========================
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
//======================== �����¶����Ƽ������˶� ===========================
//===========================================================================

// ����¶ȵ���EXTRUDE_MINTEMP, ��ô���˶�e�ἷ��˿��,��Ϊ�¶Ȳ���
// ����ʹ�� M302 ָ��ȥ������С�ļ����¶�, ���߲���hotend�¶�����moving the extruder.
// *** IT IS HIGHLY RECOMMENDED TO LEAVE THIS OPTION ENABLED! ***
#define PREVENT_COLD_EXTRUSION
#define EXTRUDE_MINTEMP 0	//190305���� //170   // ����������¶�����,���ڴ��¶�,�ڴ�ӡ�����м�����������

// ��ѡ���ֹsingle������ EXTRUDE_MAXLENGTH ����;   ע�⣺����Bowden�����������������õ�ֵ̫С���ܻ�prevent loading.
#define PREVENT_LENGTHY_EXTRUDE
#define EXTRUDE_MAXLENGTH 200

//===========================================================================
//======================== Thermal �ܷɱ��� =================================
//===========================================================================

/**
 * �¶��ܷɱ�������ֹ�𻵻����������Ż��¶ȴ�������Ϊĳ��ԭ��ʧЧ���»��ڼ��ȣ�
 * ���¶ȴ�����ʧЧ,���޷���׼ȷ�����¶ȡ������⵽����,������ڳ������ּ��ȣ�������������.
 * "Thermal Runaway" ���� "Heating failed" ����, ��Configuration_adv.h ����е���
 */

#define THERMAL_PROTECTION_HOTENDS // ʹ�����м���ͷ���ȱ���
#define THERMAL_PROTECTION_BED     // ʹ���ȴ����ȱ���





#endif /* CONFIGURATION_H_ */
