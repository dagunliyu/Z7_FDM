 

## Junction Deviation Explained and Visualized

### The following will illustrate how **Junction Deviation** and **Acceleration** work together for smooth cornering.

节偏差和加速度如何一起影响角边缘平滑度的？

 \*  https://reprap.org/forum/read.php?1,739819

 \*  https://blog.kyneticcnc.com/2018/10/computing-junction-deviation-for-marlin.html

Improving Grbl: Cornering Algorithm：https://onehossshay.wordpress.com/2011/09/24/improving_grbl_cornering_algorithm/

![img](https://onehossshay.files.wordpress.com/2011/09/untitled-11.png?w=240&h=217)

```c++
/**
 * Junction Deviation Factor
 *
 * See:
 *   https://reprap.org/forum/read.php?1,739819
 *   https://blog.kyneticcnc.com/2018/10/computing-junction-deviation-for-marlin.html
 */
#if DISABLED(CLASSIC_JERK)
  #define JUNCTION_DEVIATION_MM 0.013 // (mm) Distance from real junction edge
  #define JD_HANDLE_SMALL_SEGMENTS    // Use curvature estimation instead of just the junction angle
                                      // for small segments (< 1mm) with large junction angles (> 135°).
#endif
```





------



# 有没有3D打印机主控板固件Marlin的详细资料可参考？

目前大多数是解析的文章，环境配置部分居多，其他逻辑这些很少有人去搞，目前我们工作室的主板是ARM的，代码花了8个月书写与调试，目前很稳定了。目前移植开源固件难度很大，国内没有人去搞，不如自己写一个固件出来，可以参见我们的网站www.3dxmy.com,专注于3D打印DIY



作者：谢信福
链接：https://www.zhihu.com/question/24160226/answer/29940555
来源：知乎
著作权归作者所有。商业转载请联系作者获得授权，非商业转载请注明出处。

# 3D打印机控制器固件程序marlin基本设置

https://zhuanlan.zhihu.com/p/262531508

1、固件信息
STRING_CONFIG_H_AUTHOR 设置固件作者信息，可在窗口通信的是候看到。
SHOW_BOOTSCREEN 如果注释掉这行的话开机就不会显示初始画面，直接进入主界面。
STRING_SPLASH_LINE1 设置开机屏幕初始画面的第一行的文字，一般设置版本号。
STRING_SPLASH_LINE2 设置开机屏幕初始画面的第二行的文字，一般设置网站地址。\

2、端口

\#define SERIAL_PORT 0

3、波特率

BAUDRATE 设置串口通信的波特率，一般默认是250000，如果使用Mac或者Linux系统，需要改成115200，因为系统原因波特率上不到250000。对应的切片或联机打印软件也需要给波特率改为设置的值，否则无法连接。

\#define BAUDRATE 250000
4、主板类型
现在最新版本的Marlin固件固件已经默认设置为Makeboard主板主板类型，无需再更改。如使用其他版本固件，需将 MOTHERBOARD 设置为 BOARD_RAMPS_14_EFB 类型，或者直接设置为类型编号 33。

\#ifndef MOTHERBOARD

\#define MOTHERBOARD 33

\#endif

5、打印机名称

去掉 CUSTOM_MACHINE_NAME 行的注释，设置其值为打印机的名称，比如设置为”Makeboard”，开机打印机就绪后，就会在液晶屏主界面显示 Makeboard ready. 信息。

//#define CUSTOM_MACHINE_NAME "3D Printer"


6、挤出头数量

EXTRUDERS 设置挤出机数量，Makeboard Pro主板最多支持2挤出机，Makeboard Mini仅支持1挤出机。

\#define EXTRUDERS 1


7、混色打印
去掉 SINGLENOZZLE 行的注释，可以开启多挤出机混色打印，就是有多个挤出机挤出不同的颜色，但只有一个打印头，可靠切片软件安排不同挤出机颜色的挤出量达到混色的彩色效果

//#define SINGLENOZZLE

8、温度传感器
TEMP_SENSOR_0 表示一号打印头的感温类型，TEMP_SENSOR_1 以此类推，设置为0表示不启用，其他设置为对应感温类型编号，具体查看下面代码的列表。现在的打印机一般使用的是100k感温电阻测温，所以类型编号选择1。
TEMP_SENSOR_BED 表示热床的感温类型，只需要在这里把热床的感温类型设置好，就可以开启热床功能，一般热床感温类型编号也是1，和打印头一样。

\#define TEMP_SENSOR_0 1

\#define TEMP_SENSOR_1 0

\#define TEMP_SENSOR_2 0

\#define TEMP_SENSOR_BED 1

9、最小最大温度

HEATER_0_MAXTEMP 表示一号打印头的最大温度，HEATER_1_MAXTEMP 以此类推。BED_MAXTEMP 表示热床的最大温度。
温度数值建议根据实际情况保守设置，以免设置过大损坏硬件，或造成安全隐患，推荐打印头250，热床100，足以使用。最小就默认。

\#define HEATER_0_MINTEMP 5

\#define HEATER_1_MINTEMP 5

\#define HEATER_2_MINTEMP 5

\#define BED_MINTEMP 5

\#define HEATER_0_MAXTEMP 245

\#define HEATER_1_MAXTEMP 275

\#define HEATER_2_MAXTEMP 275

\#define BED_MAXTEMP 100

10、挤出机保护
EXTRUDE_MINTEMP 设置挤出机工作的最小温度，只有达到指定温度，挤出机电机才会转动，以此保护送丝轮挤不动造成磨损。所以如果发现挤出机不工作，请先查看打印头是否加热到指定温度。
EXTRUDE_MAXLENGTH 设置挤出机挤出耗材的最大长度，防止误操作造成损失。

\#define EXTRUDE_MINTEMP 185

\#define EXTRUDE_MAXLENGTH (X_MAX_LENGTH+Y_MAX_LENGTH)

11、双轴联动结构
如使用两个电机协同带两个轴的机型，如COREXY，COREXZ，COREYZ，去掉对应机型前面的注释即可。

//#define COREXY

//#define COREXZ

//#define COREYZ

12、限位开关上拉
ENDSTOPPULLUPS 去掉注释的话表示所有限位开关上拉，上拉表示对应引脚悬空的情况下默认是高电平，即限位开关开路状态下是H电平状态。Makeboard系列主板必须开启此项。如注释掉此项的话，可在下面代码单独配置XYZ轴MAX和MIN限位开关上拉状态。如去掉 ENDSTOPPULLUP_XMAX 注释可单独开启X-MAX限位开关上拉。

\#define ENDSTOPPULLUPS // Comment this out (using // at the start of the line) to disable the endstop pullup resistors

\#if DISABLED(ENDSTOPPULLUPS)

// fine endstop settings: Individual pullups. will be ignored if ENDSTOPPULLUPS is defined

//#define ENDSTOPPULLUP_XMAX

//#define ENDSTOPPULLUP_YMAX

//#define ENDSTOPPULLUP_ZMAX

//#define ENDSTOPPULLUP_XMIN

//#define ENDSTOPPULLUP_YMIN

//#define ENDSTOPPULLUP_ZMIN

//#define ENDSTOPPULLUP_ZMIN_PROBE

\#endif

13、限位开关信号

X_MIN_ENDSTOP_INVERTING 等系列参数设置为 true 表示将限位开关的信号反转，针对限位开关的常开和常闭状态，如触发状态不符合预期，可在此处修正。
Z_MIN_PROBE_ENDSTOP_INVERTING 表示自动调平使用的探针电平状态，如不时触底时才触发，可在此反转。

\#define X_MIN_ENDSTOP_INVERTING true // set to true to invert the logic of the endstop.

\#define Y_MIN_ENDSTOP_INVERTING true // set to true to invert the logic of the endstop.

\#define Z_MIN_ENDSTOP_INVERTING true // set to true to invert the logic of the endstop.

\#define X_MAX_ENDSTOP_INVERTING true // set to true to invert the logic of the endstop.

\#define Y_MAX_ENDSTOP_INVERTING true // set to true to invert the logic of the endstop.

\#define Z_MAX_ENDSTOP_INVERTING true // set to true to invert the logic of the endstop.

\#define Z_MIN_PROBE_ENDSTOP_INVERTING false // set to true to invert the logic of the endstop.

14、电机使能信号

X_ENABLE_ON 等系列参数设置为 0 表示电机是低电平使能，1 表示高电平使能。Makeboard配套驱动芯片均为低电平使能，默认设置即可。如外接驱动器，如果电机不工作，不锁死，可将此参数设为 1 尝试。

\#define X_ENABLE_ON 0

\#define Y_ENABLE_ON 0

\#define Z_ENABLE_ON 0

\#define E_ENABLE_ON 0 // For all extruders

15、禁用电机

如特殊用途，如激光切割机一类，将指定轴，如 DISABLE_Z 设置为 ture 即可禁用Z轴电机。
\#define DISABLE_X false
\#define DISABLE_Y false
\#define DISABLE_Z false
16、电机运动方向
如果复位时候，打印头不是朝限位开关方向移动，可将对应轴，如 INVERT_X_DIR 设置为 true 即可反转X轴电机运动方向。
如果挤出机电机挤出和回抽动作是反，将对应挤出机，如 INVERT_E0_DIR 设置为 true 即可反转一号挤出机运动方向。

\#define INVERT_X_DIR false

\#define INVERT_Y_DIR false

\#define INVERT_Z_DIR true

\#define INVERT_E0_DIR false

\#define INVERT_E1_DIR false

17、复位限位开关

设置各轴复位时触发的限位开关，三角洲机型设置为 1，复位时最大值，三轴限位开关插在MAX接口。非三角洲机型一般设置为 -1，复位时为最小值，复位后坐标为 0,0,0，三轴限位开关插在MIN接口。

\#define X_HOME_DIR -1

\#define Y_HOME_DIR -1

\#define Z_HOME_DIR -1

18、软限位
min_software_endstops 设置为 true 开启的话会使打印头无法移动到副坐标，保护硬件不受损坏。实际三角洲机型此值无意义，非三角洲机型因为一般MIN方向有硬限位开关，也不会有问题，开不开启无所谓了。
max_software_endstops 设置为 true 开启的话会使打印头无法移动超过 X_MAX_POS，Y_MAX_POS,Z_MAX_POS 设置的坐标，保护硬件不受损坏，一般需要开启，防误操作。

\#define min_software_endstops true

\#define max_software_endstops true

19、复位坐标

设置打印机的打印范围，X_MIN_POS，Y_MIN_POS，Z_MIN_POS，为打印机最小值方向复位的坐标，一般默认设置为 0 即可。
X_MAX_POS，Y_MAX_POS，Z_MAX_POS 为打印机复位时的坐标值，在开启MAX软复位后，为打印机的最大打印范围。一般打印机在调试完后，通过G1指令移动打印头，M114查看当前坐标测得打印机最大打印范围。
三角洲机型需特别注意 Z_MAX_POS 参数，为复位后打印头到平台之间的距离，可将此值设置大些，G28复位后，通过G1指令，移动Z轴，使打印头接触平台后，通过M114查看当前坐标，即可知道距离是多少了。

\#define X_MIN_POS 0

\#define Y_MIN_POS 0

\#define Z_MIN_POS 0

\#define X_MAX_POS 200

\#define Y_MAX_POS 200

\#define Z_MAX_POS 200

20、缺料检测

FILAMENT_RUNOUT_SENSOR 去掉注释，即可开启缺料检测功能。一般使用光电限位开关装在送丝机耗材入口处，高电平表示正常送丝，低电平表示缺料。
FIL_RUNOUT_INVERTING 设置为 true 可反转限位开关信号。
ENDSTOPPULLUP_FIL_RUNOUT 去掉注释，表示缺料检测引脚默认上拉，一般默认开启。
FILAMENT_RUNOUT_SCRIPT 设置缺料检测激活时运行的脚本，一般为 M600，使打印机暂时打印，换好耗材后，可继续打印。

//#define FILAMENT_RUNOUT_SENSOR

\#if ENABLED(FILAMENT_RUNOUT_SENSOR)

const bool FIL_RUNOUT_INVERTING = false;

\#define ENDSTOPPULLUP_FIL_RUNOUT

\#define FILAMENT_RUNOUT_SCRIPT "M600"

\#endif

21、自动调平
AUTO_BED_LEVELING_FEATURE 去掉注释可开启自动调平功能，此处不做过多介绍，请看后续自动调平详细教程。

//#define AUTO_BED_LEVELING_FEATURE // Delete the comment to enable (remove // at the start of the line)

22、复位速度
HOMING_FEEDRATE_XY 设置复位时XY轴的移动速度。
HOMING_FEEDRATE_Z 设置复位时Z轴的移动速度，如果用丝杆的话，需要设置的比用皮带慢很多。

\#define HOMING_FEEDRATE_XY (50*60)

\#define HOMING_FEEDRATE_Z (4*60)

23、电机步数

DEFAULT_AXIS_STEPS_PER_UNIT 后面的四个数字 {80,80,4000,500} ，分别表示XYZ和挤出机电机的步进数。

\#define DEFAULT_AXIS_STEPS_PER_UNIT {80,80,4000,500}

XYZ电机步进公式为：360 / 电机布局角 * 细分数 ) / (同步带齿距 * 齿数)
一般现在3D打印机使用的42步进电机步距角为1.8度，细分数根据主板上跳帽的设置，一般设置成16，同步带齿距一般使用的是2mm的，齿数一般为16或者20齿，可以自己数数。如果Z轴使丝杠的话，直接除以丝杆的导程即可。这样默认情况下可以算得：
挤出机步进数没有很精确的计算公式，目前通常使用的近程挤出机设置为100，远程挤出机设置为150，然后根据实际打印的出丝多少微调，要出多点步进数就调大，出少点就调小。
24、电机最大移动速度
DEFAULT_MAX_FEEDRATE 后面的四个数字 {300, 300, 5, 25} ，分别表示XYZ和挤出机电机的最大移动速度。在实际测试不失步的情况下设置的越大越好，此值和电机步进数相关，步进数越大，对应的移动速度设置越小。所以使用大细分数或者丝杆需要减小此值才能保证电机不失步。

\#define DEFAULT_MAX_FEEDRATE {300, 300, 5, 25}

25、电机最大加速度
DEFAULT_MAX_ACCELERATION 后面的四个数字 {3000,3000,100,10000} ，分别表示XYZ和挤出机电机的最大加速度。三角洲机型的加速度可以设置的大些，其他机型小些，原则也是实际测试，在不失步的情况下设置的越大越好。

\#define DEFAULT_MAX_ACCELERATION {3000,3000,100,10000}

26、电机默认加速度
DEFAULT_ACCELERATION 设置X，Y，Z和E轴电机的默认移动加速度。
DEFAULT_RETRACT_ACCELERATION 设置E轴电机回抽时候的默认加速度。
DEFAULT_TRAVEL_ACCELERATION* 设置E轴电机挤出时候的默认加速度。

\#define DEFAULT_ACCELERATION 3000

\#define DEFAULT_RETRACT_ACCELERATION 3000

\#define DEFAULT_TRAVEL_ACCELERATION 3000

27、无需加速距离
DEFAULT_XYJERK，DEFAULT_ZJERK，DEFAULT_EJERK 分别设置X，Y，Z和E轴电机移动时，速度改变时无需加速过程的距离。如果使用三角洲机型，需要将 DEFAULT_ZJERK 值设置的和 DEFAULT_XYJERK 一样，要不容易失步。

\#define DEFAULT_XYJERK 20.0 // (mm/sec)

\#define DEFAULT_ZJERK 0.4 // (mm/sec)

\#define DEFAULT_EJERK 5.0

28、EEPROM
EEPROM_SETTINGS 去掉注释，可开启EEPROM功能，打印机部分配置参数将保存在打印机中，可通过液晶屏实时调节，无需重刷固件。配置固件阶段推荐关闭，调试好机器后再开启，要不很可能有参数给代码中调节后不会生效，造成误判断。

//#define EEPROM_SETTINGS

29、预加热
分别设置液晶屏菜单选择预加热PLA和ABS的打印头，热床温度，及冷却风扇转速。

\#define PREHEAT_1_TEMP_HOTEND 180

\#define PREHEAT_1_TEMP_BED 70

\#define PREHEAT_1_FAN_SPEED 0 // Value from 0 to 255

\#define PREHEAT_2_TEMP_HOTEND 240

\#define PREHEAT_2_TEMP_BED 110

\#define PREHEAT_2_FAN_SPEED 0 // Value from 0 to 255

30、挤出头温度调控

\#define DEFAULT_Kp 22.2

\#define DEFAULT_Ki 1.08

\#define DEFAULT_Kd 114

31、热床温度调控

\#define DEFAULT_bedKp 10.00

\#define DEFAULT_bedKi .023

\#define DEFAULT_bedKd 305.4

32、液晶屏语言
Marlin固件现在的最新版本直接官方支持中文，LCD_LANGUAGE 设置为 cn 即可，前提是需要使用12864液晶屏。

\#define LCD_LANGUAGE en

33、旋转编码器方向
REVERSE_ENCODER_DIRECTION 去掉注释，反转液晶屏上调节数值旋转编码器方向。
REVERSE_MENU_DIRECTION 去掉注释，反转液晶屏上选择菜单时旋转编码器方向。
有些液晶屏旋转编码器方向做反了，需要软件修正，Makeboard配套液晶屏不需要，默认即可。

//#define REVERSE_ENCODER_DIRECTION

//#define REVERSE_MENU_DIRECTION

34、独立轴复位菜单
INDIVIDUAL_AXIS_HOMING_MENU 去掉注释，可在液晶屏上增加单独的复位X，Y，Z轴的菜单，方便调试。

//#define INDIVIDUAL_AXIS_HOMING_MENU

35、液晶屏蜂鸣器
SPEAKER 去掉注释，可开始液晶屏上的蜂鸣器，旋转编码旋转或者按下时蜂鸣器会发声。

//#define SPEAKER

36、液晶屏2004
去掉 REPRAP_DISCOUNT_SMART_CONTROLLER 行的注释，可开启2004液晶屏功能。特别强调，如果使用非配套Makeboard液晶屏，液晶屏无法使用的话，可能时液晶屏牛角插座缺口方向是反的，EXP1和EXP2线的接头凸起处换个方向强行插入即可。

\#define REPRAP_DISCOUNT_SMART_CONTROLLER

35、液晶屏12864

去掉 REPRAP_DISCOUNT_FULL_GRAPHIC_SMART_CONTROLLER 行的注释，可开启12864液晶屏功能。需要u8glib库文件，否则编译无法通过，将网盘下载的 u8glib_arduino_v1.18.1.zip 文件解压到Arduino的 libraries 目录即可。

//#define REPRAP_DISCOUNT_FULL_GRAPHIC_SMART_CONTROLLER



------

**首先介绍下Marlin固件：**

- 固件配置都在Configuration.h 中
- Marlin固件的配置主要包含以下几个方面：

## **基本配置**

- Marlin固件的配置文件在`Configuration.h`中
- Marlin固件的配置主要包含以下几个方面：

1. 通讯波特率
2. 主板类型，所使用的主板类型
3. 温度传感器类型，包括挤出头温度传感器和加热床的温度传感器
4. 温度配置，包括喷头温度和加热床温度
5. PID 温控参数，包括喷头温度控制和加热床温度控制
6. 限位开关
7. 4 个轴步进电机方向
8. X/Y/Z 三个坐标轴的初始位置
9. 打印机运动范围
10. 自动调平
11. 运动速度
12. 各轴运动分辨率
13. 脱机控制器

### **一、串口介绍**

电脑和打印机通过串口进行通讯，要定义好端口和波特率，在此定义的是 3D 打印主板的端口和波特率，端口号使用默认的 0 就可以了。Marlin 固件默认的波特率是 250000，也可以修改为其他值，比如 115200，这是标准的 ANSI 波特率值。

```c
  #define SERIAL_PORT0
  #define BAUDRATE 250000
```

### **二、主板类型介绍**

Marlin 固件支持非常多种类的 3D 打印机主板，比如常见的RAMPS1.3/1.4、Melzi、Printrboard、Ultimainboard、Sanguinololu 等控制板。需要注意的是不同主板使用不同的引脚和数量，如果该定义和 Arduino IDE 中使用的主板不一致，肯定会导致编译不通过。笔者使用的是 RAMPS1.4 并且 D8、D9、D10 控制的是一个喷头加热、一个加热床加热和一个风扇输出，因此定义为 33。

```c
  #ifndef MOTHERBOARD
  #define MOTHERBOARD 33
  #endif
```

### **三、电源介绍**

电源有两种类型可以选择：

- 1 表示开关电源
- 2 表示 X-Box 360 203 伏电源
- 一般都使用的是开关电源，因此定义为 1。

```c
  #define EXTRUDERS1
  #define POWER_SUPPLY1
```

### **四、温度传感器介绍**

定义温度传感器类型，包括每个喷头使用的温度传感器（如果是多喷头）和加热床的温度传感器类型，常用的温度传感器有电热偶和热敏电阻两大类，热敏电阻又分为很多种。目前的 3D 打印机主要用的是热敏电阻，具体是哪种热敏电阻需要自己判断或询问卖家，不出意外的话，都是 100k ntc 热敏电阻，即 1。根据注释，1 要求 4.7k 的上拉电阻，而根据 RepRap wiki，几乎所有的 3D 打印机都使用了 4.7K 的热敏电阻上拉电阻。笔者观察了几种电路板的电路图，发现都使用了 4.7K 的上拉电阻，如图 一 所示。

![img](https://pic4.zhimg.com/80/v2-3b379ebb4398351aa38c70743b3e7843_720w.jpg)图一 4.7K 上拉电阻

本人打印机为单喷头，因此第一个喷头的温度传感器配置为 1，其他配置为 0（0 表示没有使用），加热床的温度传感器也配置为 1。

```c
  #define TEMP_SENSOR_0 1
  #define TEMP_SENSOR_1 0
  #define TEMP_SENSOR_2 0
  #define TEMP_SENSOR_BED 1
```



### **五、温度配置**

下面是温度检测的一些配置，包括双喷头温度差，M109 检测配置，安全温度配置。首先下面这个宏定义配置双喷头温差最大值，如果温度超过这个数值，那么打印机会终止工作，因此对于双喷头打印机玩家来说，这个参数需要注意。

```c
   #define MAX_REDUNDANT_TEMP_SENSOR_DIFF 10
```

下面这是配置 M109 指令完成的指标，我们知道，M109 指令设定喷头温度并等待，那么等待到什么时候呢？下面这三个参数控制这个时间。第一个参数表示温度“接近”目标温度必须持续 10 秒才算加热完成，第二个参数表示和目标温度相差不超过 3°为“接近”，第三个参数表示从温度与目标温度相差不超过 1 度开始计时，从此刻开始，温度和目标温度持续接近 10 秒钟，则完成加热。

```c
  #define TEMP_RESIDENCY_TIME 10
  #define TEMP_HYSTERESIS 3
  #define TEMP_WINDOW 1
```

下面是配置安全温度范围的下限和上限，包括各个喷头和加热床。如果温度超过下限，那么打印机会抛出 MINTEMP 的错误并终止工作，如果超过上限，那么打印机抛出 MAXTEMP 的错误并终止工作。Marlin 用这种方式保护 3D 打印机。下面的配置最小温度都是 5°，喷头的最大温度为 275°，热床的最大温度为 150°。

```c
  #define HEATER_0_MINTEMP 5
  #define HEATER_1_MINTEMP 5
  #define HEATER_2_MINTEMP 5
  #define BED_MINTEMP 5
  #define HEATER_0_MAXTEMP 275
  #define HEATER_1_MAXTEMP 275
  #define HEATER_2_MAXTEMP 275
  #define BED_MAXTEMP 150
```

如果希望 M105 指令在报告温度的时候，也报告喷头和加热床的功率，则可以将下面两句的前面的”//”去掉。具体的功率数值需要自己计算得到。

```c
  #define EXTRUDER_WATTS (12.0*12.0/6.7)
  #define BED_WATTS  (12.0*12.0/1.1)
```

### **六、PID温度配置**

PID温控配置，PID参数设置，需要根据系统情况设置，可以通过 M303 代码调用PID_autotune函数获得基本PID参数，然后参照修改下面的DEFAULT_Kp、DEFAULT_Ki、DEFAULT_Kd，例如：M303 E0 C8 S190，表示获取打印头0（第一个打印头）、目标温度190度、循环调用PID_autotune8次后的相应的PID参数。系统自动生成的PID参数相当不错，本人认为可以使用默认，这里就不多介绍。

### **七、挤出机介绍**

下边这两个宏是用来保护打印机不发生自燃的，例如热敏电阻或者温度传感器失效了或者坏了，打印机就没有办法感知真实的温度，就会一直加热，很容易导致自燃。

```c
  #define THERMAL_PROTECTION_HOTENDS
  #define THERMAL_PROTECTION_HOTENDS
```

### 详细说明，请点击下方~链接

[免费获取3D打印机制作资料mp.weixin.qq.com](https://link.zhihu.com/?target=https%3A//mp.weixin.qq.com/s/3ezAHCqBpZ-qMrku-pP-EQ)



编辑于 03-06