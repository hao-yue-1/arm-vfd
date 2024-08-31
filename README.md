# 基于ARM的低压交直交变频器的开发设计

- 基于ARM：使用STM32F103C8T6作为主控芯片
- 低压：理论36V，只测试过12V
- 交直交：变频器主流架构

# 开发环境

- 硬件：嘉立创EDA专业版
- 软件：CLion + STM32CubeMX + OpenOCD + MinGW + arm-none-eabi-gcc
- 调试工具：DAPlink

# 注意

- 该项目只是一个简单的输出可调频率正弦波的工具，并未做过任何驱动电机的测试，只是一个玩具，切勿做任何危险的操作！！！

# 实物图

<img src="./image/30.7Hz.jpg" alt="image-20240901004223542"  />