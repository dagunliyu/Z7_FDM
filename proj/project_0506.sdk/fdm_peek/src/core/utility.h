/*
 * utility.h
 *
 *  Created on: 2019年6月30日
 *      Author: W530
 */

#ifndef SRC_CORE_UTILITY_H_
#define SRC_CORE_UTILITY_H_

// 实现若干工具，int,float到str的转换等
//constexpr char axis_codes[XYZE] = {'X', 'Y', 'Z', 'E'}; // marlin2 写法 190401
//  “请大胆地将我看成编译时就能得出常量值的表达式去优化我”


// Delay ： 确保 heaters 和 watchdog 都保持 alive
void safe_delay(millis_t ms);



#endif /* SRC_CORE_UTILITY_H_ */
