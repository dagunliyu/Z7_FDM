# Z7_FDM

## Marlin 2.x Firmware for Xilinx Zynq-7 Platform

本仓库包含了Marlin 2.x 3D打印机固件到Xilinx Zynq-7平台的移植。

This repository contains a port of Marlin 2.x 3D printer firmware to the Xilinx Zynq-7 platform.

## 项目历史 / Project History

- **原始项目**: 由ATmega2560移植到Zynq7平台之上，代码继承自Marlin 1.1.6
- **当前版本**: 已升级到Marlin 2.x，采用完整的Marlin 2代码库和文件组织结构

---

- **Original**: Ported from ATmega2560 to Zynq-7, based on Marlin 1.1.6
- **Current**: Upgraded to Marlin 2.x with full Marlin 2 codebase and file organization

## 文档 / Documentation

详细的移植说明和实现指南请参阅：[MARLIN2_PORT_README.md](MARLIN2_PORT_README.md)

For detailed porting documentation and implementation guide, see: [MARLIN2_PORT_README.md](MARLIN2_PORT_README.md)

## 主要特性 / Key Features

- ✅ 完整的Marlin 2.x核心代码
- ✅ Zynq-7硬件抽象层 (HAL) 框架
- ✅ 标准的Marlin配置系统
- ⚠️ 硬件驱动实现待完成（GPIO, 定时器, ADC, UART）

---

- ✅ Complete Marlin 2.x core codebase
- ✅ Zynq-7 Hardware Abstraction Layer (HAL) framework
- ✅ Standard Marlin configuration system
- ⚠️ Hardware driver implementation pending (GPIO, timers, ADC, UART)

## 快速开始 / Quick Start

1. 打开Xilinx SDK项目 / Open in Xilinx SDK
2. 配置硬件驱动 / Configure hardware drivers (see MARLIN2_PORT_README.md)
3. 编译并部署 / Build and deploy

## 许可证 / License

GPL 3.0 (与Marlin固件保持一致 / Compatible with Marlin firmware)

