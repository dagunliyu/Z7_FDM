/*
 * board.h
 *
 *  Created on: 2019��6��8��
 *      Author: W530
 */

#ifndef SRC_CORE_BOARDS_H_
#define SRC_CORE_BOARDS_H_

#define BOARD_UNKNOWN     -1
#define BOARD_LHC_CSU_FDM 1111

#define MB(board) (MOTHERBOARD==BOARD_##board)   // ��ð��ӵ�����, MOTHERBOARD��configuration.h�ж���
// # �ǰѲ����ַ�������## �ǽ�����������Ϊһ�����塣

#endif /* SRC_CORE_BOARDS_H_ */