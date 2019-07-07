/*
 * board.h
 *
 *  Created on: 2019年6月8日
 *      Author: W530
 */

#ifndef SRC_CORE_BOARDS_H_
#define SRC_CORE_BOARDS_H_

#define BOARD_UNKNOWN     -1
#define BOARD_LHC_CSU_FDM 1111

#define MB(board) (MOTHERBOARD==BOARD_##board)   // 获得板子的名称, MOTHERBOARD在configuration.h中定义
// # 是把参数字符串化，## 是将两个参数连为一个整体。

#endif /* SRC_CORE_BOARDS_H_ */
