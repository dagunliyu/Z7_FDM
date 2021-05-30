///*
// * stopwatch.h
// *
// *  Created on: 2019��6��8��
// *      Author: W530
// */
//
//#ifndef SRC_LIBS_STOPWATCH_H_
//#define SRC_LIBS_STOPWATCH_H_
//
//#include "../core/macros.h"   // ����ENABLE DISABLE�Ȱ�װ��
//
//// Print debug messages with M111 S2 (Uses 156 bytes of PROGMEM)
////#define DEBUG_STOPWATCH
//
//
//class Stopwatch{
//
//private:
//	enum State{
//		STOPPED,
//		RUNNING,
//		PAUSED
//	};
//	Stopwatch::State state; // ����ö�ٶ���
//	millis_t accumulator;
//	millis_t startTimestamp;
//	millis_t stopTimestamp;
//
//public:
//
//	/*
//	 * @brief �๹�캯��StopWatch
//	 */
//	Stopwatch();
//
//	/*
//	 * @brief stops stopwatch
//	 * @details: ֹͣ�������еļ�ʱ���������ǰû�м�ʱ���������У���silently��������
//	 * @return ����true��ʾ�����ɹ�ִ��
//	 */
//	bool stop();
//
//    /**
//     * @brief Pause   stopwatch
//     * @details ��ͣ���е�timer�������ǰû�м�ʱ���������У���silently��������
//     * @return ����true��ʾ�����ɹ�ִ��
//     */
//    bool pause();
//
//    /**
//     * @brief Starts the stopwatch
//     * @details ����timer�������ǰû�м�ʱ���������У���silently��������
//     * @return ����true��ʾ�����ɹ�ִ��
//     */
//    bool start();
//
//	/*
//	 * @brief ��λ stopwatch
//	 * @details: ���������ø�λ����Ĭ��ֵ.
//	 */
//	void reset();
//
//    /**
//     * @brief ���timer�Ƿ���������
//     * @details ����true��ʾtimer��������,false��֮
//     * @return ����true��ʾstopwatch��������
//     */
//    bool isRunning();
//
//    /**
//     * @brief ���timer�Ƿ���ͣ
//     * @details ����true��ʾtimer��ǰ�Ѿ�����ͣ,false��֮
//     * @return ����true��ʾstopwatch����ͣ
//     */
//    bool isPaused();
//
//    /**
//     * @brief ��ȡ���е�ʱ��running time
//     * @details ����timer�Ѿ����е�ʱ��(s) total number of seconds the timer has been running.
//     * @return ������stopwatch��ʼ����ǰ��ʱ����
//     */
//    millis_t duration();
//
//
//	#if ENABLED(DEBUG_STOPWATCH)
//
//      /**
//       * @brief Prints debug��Ϣ
//       * @details printһ���򵥵ĵ�����Ϣ�� "Stopwatch::function"
//       */
//      static void debug(const char func[]);
//
//    #endif
//
//
//};
//
//#endif /* SRC_LIBS_STOPWATCH_H_ */
