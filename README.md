# 如何使用Mac和CLion学习江协STM32课程

这个项目分享如何使用MAC和CLion学习B站江协科技的STM32课程，环境配置主要参考CLion官方帮助文档
[Embedded development /
STM32CubeMX projects
](https://www.jetbrains.com/help/clion/2024.3/embedded-development.html?top&keymap=macOS#0)
## 安装需要的软件
* [CLion](https://www.jetbrains.com/clion/)
* [STM32CubeMX](https://www.st.com/en/development-tools/stm32cubemx.html)
* [ST-LINK-SERVER](https://www.st.com/en/development-tools/st-link-server.html)
* [GNU ARM toolchain](https://developer.arm.com/open-source/gnu-toolchain/gnu-rm)
  > 配置安装路径到环境变量 
  > 
  > ``` echo 'export PATH="$PATH:/Applications/ArmGNUToolchain/14.2.rel1/arm-none-eabi/bin"' >> ~/.zprofile```
* [OpenOCD](https://openocd.org/pages/getting-openocd.html)
  > 需先安装Homebrew,使用[科大源](https://mirrors.ustc.edu.cn/help/brew.git.html)安装Homebrew

  > 安装OpenOCD
  > 
  > ```brew install openocd```

## 配置CLion
Setting->Embedded Development
  > OpenOCD Location : /opt/homebrew/bin/openocd
  > 
  > Stm32CubeMX Location : /Applications/STMicroelectronics/STM32CubeMX.app/Contents/Resources/STM32CubeMX

## 生成点灯项目
* 打开STM32CubeMX，选择MCU型号
* Pinout&Configuration
  > System Core
  > 
  > SYS->Debug: Seral Wire  
  > GPIO->PC13: GPIO_Output

* Project Manager
  > Project
  > 
  > Project Name: Project （方便复制项目使用通用名称）   
  > Toolchain/IDE : STM32CubeIDE ✅Generate Under Root
* GENERATE CODE
* 使用CLion打开生成的项目
* Select Board Config File 
  >stm32f103c8t6_blue_pill.cfg->Copy to Project&Use
* 修改`.cfg`文件
  > 添加内容`source [find interface/stlink.cfg]`到正文第一行
* 修改`Main.c`文件
  > 添加LED闪烁代码
  > ```C
  > while (1){
  >     HAL_Delay(500);
  >     HAL_GPIO_TogglePin(GPIOC, GPIO_PIN_13);
  > }
  > ```
* 运行项目将看到LED闪烁
  > 运行日志如果有Error（日志是红字，注意区分Info和Error），尝试开发版Boot0跳线帽切换到1再次运行之后再切回到0
