///*
// * stopwatch.h
// *
// *  Created on: 2019年6月8日
// *      Author: W530
// */
//
//#ifndef SRC_LIBS_STOPWATCH_H_
//#define SRC_LIBS_STOPWATCH_H_
//
//#include "../core/macros.h"   // 定义ENABLE DISABLE等包装宏
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
//	Stopwatch::State state; // 构建枚举对象
//	millis_t accumulator;
//	millis_t startTimestamp;
//	millis_t stopTimestamp;
//
//public:
//
//	/*
//	 * @brief 类构造函数StopWatch
//	 */
//	Stopwatch();
//
//	/*
//	 * @brief stops stopwatch
//	 * @details: 停止正在运行的计时器，如果当前没有计时器正在运行，则silently忽略请求
//	 * @return 返回true表示方法成功执行
//	 */
//	bool stop();
//
//    /**
//     * @brief Pause   stopwatch
//     * @details 暂停运行的timer，如果当前没有计时器正在运行，则silently忽略请求
//     * @return 返回true表示方法成功执行
//     */
//    bool pause();
//
//    /**
//     * @brief Starts the stopwatch
//     * @details 开启timer，如果当前没有计时器正在运行，则silently忽略请求
//     * @return 返回true表示方法成功执行
//     */
//    bool start();
//
//	/*
//	 * @brief 复位 stopwatch
//	 * @details: 将所有设置复位到其默认值.
//	 */
//	void reset();
//
//    /**
//     * @brief 检查timer是否正在运行
//     * @details 返回true表示timer正在运行,false反之
//     * @return 返回true表示stopwatch正在运行
//     */
//    bool isRunning();
//
//    /**
//     * @brief 检查timer是否被暂停
//     * @details 返回true表示timer当前已经被暂停,false反之
//     * @return 返回true表示stopwatch已暂停
//     */
//    bool isPaused();
//
//    /**
//     * @brief 获取运行的时间running time
//     * @details 返回timer已经运行的时间(s) total number of seconds the timer has been running.
//     * @return 从启动stopwatch开始到当前的时间间隔
//     */
//    millis_t duration();
//
//
//	#if ENABLED(DEBUG_STOPWATCH)
//
//      /**
//       * @brief Prints debug信息
//       * @details print一个简单的调试信息： "Stopwatch::function"
//       */
//      static void debug(const char func[]);
//
//    #endif
//
//
//};
//
//#endif /* SRC_LIBS_STOPWATCH_H_ */
