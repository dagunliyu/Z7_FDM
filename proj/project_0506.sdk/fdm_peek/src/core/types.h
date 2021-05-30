/*
 * types.h
 *
 *  Created on: 2019年6月30日
 *      Author: W530
 */

#ifndef SRC_CORE_TYPES_H_
#define SRC_CORE_TYPES_H_

//#pragma once // marlin 2.0的写法 190401
#include <stdint.h>  // marlin 2.0的写法 190401

typedef unsigned long millis_t;  // 无符号长整型

//marlin2.0版本 190401
//#define PENDING(NOW,SOON) ((int32_t)(NOW-(SOON))<0)
//#define ELAPSED(NOW,SOON) (!PENDING(NOW,SOON))

#endif /* SRC_CORE_TYPES_H_ */
