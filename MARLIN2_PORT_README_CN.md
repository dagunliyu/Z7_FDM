# Marlin 2 移植到 Xilinx Zynq-7000 平台

## 概述

本仓库包含了将 [Marlin 2.x 固件](https://github.com/MarlinFirmware/Marlin) 移植到 Xilinx Zynq-7000 平台的实现。Zynq-7000 是一款片上系统 (SoC)，结合了双核 ARM Cortex-A9 处理器和 FPGA 结构，使其非常适合用于高级3D打印机控制应用。

## 已完成的工作

### 1. Marlin 2 核心集成 (✅ 已完成)
- **源代码**：已将 Marlin 2.x 官方仓库的所有源文件复制到 `proj/project_0506.sdk/fdm_peek/src/`
- **目录结构**：保持了 Marlin 2 的组织结构：
  - `core/` - 核心数据类型和实用工具
  - `gcode/` - G代码解析器和命令
  - `module/` - 运动控制、温度管理等
  - `lcd/` - 显示和用户界面支持
  - `feature/` - 可选功能
  - `sd/` - SD卡支持
  - `HAL/` - 硬件抽象层
  - `pins/` - 板级引脚定义
  - `inc/` - 配置头文件

### 2. ZYNQ7 硬件抽象层 (✅ 已完成)
在 `proj/project_0506.sdk/fdm_peek/src/HAL/ZYNQ7/` 创建了新的 HAL：
- **HAL.h/HAL.cpp**：核心HAL函数，包括初始化、ADC和内存管理
- **fastio.h**：快速GPIO操作（READ、WRITE、SET_OUTPUT等）
- **timers.h/timers.cpp**：用于步进控制和温度调节的定时器管理
- **spi_pins.h**：SD卡和外设的SPI引脚定义
- **inc/**：平台特定的条件和合理性检查
  - `Conditionals_LCD.h`
  - `Conditionals_post.h`
  - `Conditionals_adv.h`
  - `SanityCheck.h`

### 3. 板级配置 (✅ 已完成)
- **板级定义**：在 `core/boards.h` 中添加了 `BOARD_ZYNQ7` (7200)
- **平台支持**：在 `HAL/platforms.h` 中添加了 ARM Cortex-A9 检测 (`__ARM_ARCH_7A__`)
- **引脚定义**：创建了 `pins/zynq7/pins_ZYNQ7.h`，包含默认引脚分配
- **配置**：更新了 `config/Configuration.h`，使用 `BOARD_ZYNQ7` 作为默认主板

### 4. 应用程序入口点 (✅ 已完成)
- 更新了 `main.cc` 以调用 Marlin 的 `setup()` 和 `loop()` 函数
- 提供了标准的嵌入式固件执行模型

## 待完成的工作

### 1. 硬件驱动实现 (❌ 待完成)
当前的HAL提供了占位符函数，这些需要连接到实际的Xilinx驱动程序：

#### GPIO (fastio.h)
```cpp
// 当前：占位符函数
// 待完成：使用 Xilinx GPIO 驱动实现 (xgpio.h)
void pinMode(int pin, int mode);
void digitalWrite(int pin, int value);
int digitalRead(int pin);
```

#### 定时器 (timers.cpp)
```cpp
// 当前：软件模拟
// 待完成：使用 Xilinx TTC (三重定时器计数器) 实现
// - 步进电机定时（需要高精度）
// - 温度传感器轮询
// - 加热器的PWM生成
```

#### ADC (HAL.cpp)
```cpp
// 当前：返回虚拟值
// 待完成：使用 XADC (Xilinx 模数转换器) 实现
// - 温度传感器读数
// - 模拟限位开关支持
```

#### UART (缺失)
```cpp
// 待完成：使用 Xilinx UART 驱动创建 MarlinSerial.h/cpp
// - G代码命令的串行通信
// - 调试输出
```

### 2. 构建系统集成 (❌ 待完成)

#### Xilinx SDK 项目配置
代码需要正确集成到 Xilinx SDK 构建系统中：

1. **更新 .cproject**：将所有新源文件添加到构建中
2. **包含路径**：确保所有 Marlin 2 目录在包含路径中
3. **编译器标志**：
   - 添加 `-D__ARM_ARCH_7A__` 以定义平台
   - 配置优化标志
   - 启用 C++11 或更高版本的功能

4. **链接器脚本**：验证 `lscript.ld` 中的内存布局能容纳更大的固件

#### 构建步骤示例
```bash
# 在 Xilinx SDK 中：
1. 右键点击 fdm_peek 项目 → Properties
2. C/C++ Build → Settings
3. 添加包含路径：
   - src/
   - src/HAL/ZYNQ7
   - src/core
   - src/module
   - 等等
4. 添加预处理器定义：
   - __ARM_ARCH_7A__
   - F_CPU=666666666UL
```

### 3. 硬件特定配置 (❌ 待完成)

#### 引脚映射 (pins/zynq7/pins_ZYNQ7.h)
当前的引脚定义是占位符。根据您的硬件更新：
```cpp
// 示例：更新以匹配您的实际硬件连接
#define X_STEP_PIN         /* 您的 GPIO 引脚 */
#define X_DIR_PIN          /* 您的 GPIO 引脚 */
#define HEATER_0_PIN       /* 您的支持PWM的引脚 */
// 等等
```

#### 时钟配置
更新 `HAL/ZYNQ7/inc/Conditionals_post.h`：
```cpp
#ifndef F_CPU
  #define F_CPU 666666666UL  // 调整为您的实际CPU频率
#endif
```

### 4. 测试和验证 (❌ 待完成)

1. **编译测试**：确保项目无错误地构建
2. **基本初始化**：验证 HAL_init() 正确执行
3. **定时器功能**：测试步进电机定时精度
4. **GPIO操作**：验证引脚控制正常工作
5. **串行通信**：测试G代码命令接收
6. **运动控制**：验证步进电机运动
7. **温度控制**：测试加热器和传感器功能

### 5. 可选增强功能 (⚠️ 未来)

- **FPGA 集成**：利用 FPGA 结构实现：
  - 硬件加速的步进脉冲生成
  - 并行传感器读取
  - 高级运动规划
  
- **性能优化**：
  - 使用双核功能进行并行处理
  - 实现实时操作系统 (RTOS) 支持

- **额外功能**：
  - 网络连接（以太网）
  - 高级LCD支持
  - 相机集成

## 目录结构

```
proj/project_0506.sdk/fdm_peek/src/
├── HAL/                    # 硬件抽象层
│   ├── ZYNQ7/             # Zynq-7 特定 HAL (新增)
│   ├── AVR/               # 其他平台（参考）
│   ├── STM32/
│   └── ...
├── pins/
│   ├── zynq7/             # Zynq-7 引脚定义 (新增)
│   └── ...
├── core/                   # 核心类型和实用工具
├── gcode/                  # G代码解析器
├── module/                 # 运动、温度等
├── lcd/                    # 显示支持
├── feature/                # 可选功能
├── sd/                     # SD卡支持
├── inc/                    # 配置头文件
├── config/                 # 用户配置文件
│   ├── Configuration.h
│   └── Configuration_adv.h
├── MarlinCore.cpp         # 主固件核心
├── MarlinCore.h
└── main.cc                # 应用程序入口点 (已更新)
```

## 构建和部署

### 前提条件
- Xilinx Vivado（用于FPGA设计）
- Xilinx SDK（用于软件开发）
- ARM 交叉编译器工具链
- Zynq-7000 开发板

### 构建步骤
1. 在 Xilinx SDK 中打开项目
2. 配置构建设置（见上文"构建系统集成"）
3. 构建项目
4. 使用硬件设计对 FPGA 进行编程
5. 部署和调试固件

## 配置

固件可以通过编辑以下文件进行配置：
- `config/Configuration.h` - 基本打印机配置
- `config/Configuration_adv.h` - 高级功能
- `pins/zynq7/pins_ZYNQ7.h` - 硬件引脚分配

## 已知限制

1. **HAL 函数**：当前为占位符，需要硬件驱动实现
2. **构建系统**：尚未与 Xilinx SDK 项目文件集成
3. **测试**：尚未在实际硬件上进行验证
4. **文档**：需要创建硬件设置指南

## 贡献

在实现待办事项时，请：
1. 在实际硬件上进行彻底测试
2. 记录任何硬件特定的问题
3. 更新此 README 以记录您的发现
4. 考虑将改进提交回社区

## 参考资料

- [Marlin 固件官方仓库](https://github.com/MarlinFirmware/Marlin)
- [Xilinx Zynq-7000 文档](https://www.xilinx.com/products/silicon-devices/soc/zynq-7000.html)
- [Marlin HAL 开发指南](https://marlinfw.org/docs/development/hardware.html)

## 许可证

本移植版本与 Marlin 的 GPL 3.0 许可证保持兼容。详见 LICENSE 文件。

---

## 快速开始检查清单

- [x] 克隆 Marlin 2 源代码
- [x] 创建 ZYNQ7 HAL 框架
- [x] 配置构建系统（板级定义）
- [x] 更新主入口点
- [ ] 实现 GPIO 驱动
- [ ] 实现定时器驱动
- [ ] 实现 ADC 驱动
- [ ] 实现 UART 驱动
- [ ] 配置构建系统（SDK 项目）
- [ ] 测试编译
- [ ] 硬件测试
- [ ] 验证基本运动控制
- [ ] 验证温度控制
- [ ] 完整系统集成测试

---

*最后更新：2026-01-12*
*基于 Marlin 2.1.x 分支的移植*
