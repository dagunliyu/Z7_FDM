/*
 * utility.h
 *
 *  Created on: 2019��6��30��
 *      Author: W530
 */

#ifndef SRC_CORE_UTILITY_H_
#define SRC_CORE_UTILITY_H_

// ʵ�����ɹ��ߣ�int,float��str��ת����
//constexpr char axis_codes[XYZE] = {'X', 'Y', 'Z', 'E'}; // marlin2 д�� 190401
//  ����󵨵ؽ��ҿ��ɱ���ʱ���ܵó�����ֵ�ı��ʽȥ�Ż��ҡ�


// Delay �� ȷ�� heaters �� watchdog ������ alive
void safe_delay(millis_t ms);



#endif /* SRC_CORE_UTILITY_H_ */
