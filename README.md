# 如何使用Mac和CLion学习江协STM32课程

这个项目分享如何使用MAC和CLion学习B站江协科技的STM32课程，环境配置主要参考CLion官方帮助文档
[Embedded development /
STM32CubeMX projects
](https://www.jetbrains.com/help/clion/2024.3/embedded-development.html?top&keymap=macOS#0)。

## 安装需要的软件

* [CLion](https://www.jetbrains.com/clion/)

* [STM32CubeMX](https://www.st.com/en/development-tools/stm32cubemx.html)

* [ST-LINK-SERVER](https://www.st.com/en/development-tools/st-link-server.html)

* [GNU ARM toolchain](https://developer.arm.com/open-source/gnu-toolchain/gnu-rm)  

  配置安装路径到环境变量：

  ``` echo 'export PATH="$PATH:/Applications/ArmGNUToolchain/14.2.rel1/arm-none-eabi/bin"' >> ~/.zprofile```

* [OpenOCD](https://openocd.org/pages/getting-openocd.html)
  
  需先安装Homebrew,使用[科大源](https://mirrors.ustc.edu.cn/help/brew.git.html)安装Homebrew。

  安装OpenOCD```brew install openocd```。

## 配置CLion

Setting->Embedded Development：

```
OpenOCD Location : /opt/homebrew/bin/openocd

Stm32CubeMX Location : /Applications/STMicroelectronics/STM32CubeMX.app/Contents/Resources/STM32CubeMX
```

## 生成点灯项目

* 打开STM32CubeMX，选择MCU型

* Pinout&Configuration/System Core
  
  ```
  SYS->Debug: Seral Wire  
  
  GPIO->PC13: GPIO_Output
  ```

  **注意**：如果Debug设置为No Debug第二次运行的时候会报错:
  `Error: init mode failed (unable to connect to the target)`,
  尝试开发版Boot0跳线帽切换到1并断电重新上电，再次运行之后再切回到0。

* Project Manager/Project
  
  ```
  Project Name: Project （方便复制项目使用通用名称）  
  
  Toolchain/IDE : STM32CubeIDE ✅Generate Under Root
  ```
  
* GENERATE CODE

* 使用CLion打开生成的项目

* Select Board Config File 

  如果生成的代码项目完整且正确CLion会弹出Select Board Config File窗口，
  选择stm32f103c8t6_blue_pill.cfg点击Copy to Project&Use。

* 修改`.cfg`文件

  添加内容`source [find interface/stlink.cfg]`到正文第一行。

* 修改`Main.c`文件

  添加LED闪烁代码：
  
  ```C
  while (1){
    HAL_Delay(500);
    HAL_GPIO_TogglePin(GPIOC, GPIO_PIN_13);
  }
  ```
* 运行项目将看到LED闪烁

## 迁移标准库代码

* 复制老师给的源码2-1中 `Library`、`Start`、`User`文件夹到项目根目录

* `Start`文件夹下的`startup_`开头的文件全部删除，复制`Core/Startup/startup_stm32f103c8tx.s`到`Start`文件夹

* 复制`Core/Src/syscalls.c`文件到User目录（这个文件第9章`printf`函数要用到）

* 删除`Core Drivers .cproject .mxproject .osx.project .project CMakeLists_template.txt`等文件

* 修改`CMakeLists.txt`文件

  修改
  
  ```
  include_directories(Core/Inc Drivers/STM32F1xx_HAL_Driver/Inc/Legacy Drivers/STM32F1xx_HAL_Driver/Inc Drivers/CMSIS/Device/ST/STM32F1xx/Include Drivers/CMSIS/Include)
  add_definitions(-DDEBUG -DUSE_HAL_DRIVER -DSTM32F103xB)
  file(GLOB_RECURSE SOURCES "Core/*.*" "Drivers/*.*")
  ```

  为

  ```
  #后续添加所有文件夹都要在这里定义  
  include_directories(Library Start User)  
  add_definitions(-DDEBUG -DSTM32F10X_MD -DUSE_STDPERIPH_DRIVER)  
  #后续添加所有文件夹都要在这里定义  
  file(GLOB_RECURSE SOURCES "Library/*.*" "Start/*.*" "User/*.*")  
  ```
* 点击CMake刷新图标，Reload CMake Project

* 修改或删除`core_cm3.c`文件

  可修改736和753行`"=r"`为`"=&r"`或删除文件。  

* 代码迁移完成运行项目将看到LED点亮

Debug 需要的.svd文件可以从[官网](https://www.st.com/content/st_com/en/search.html#q=svd-t=resources-page=1)下载，如果安装了STM32CubeIDE也可以在包文件找到。

⚠️注意事项：
1. 新建.c.h文件时不要勾选`Add to targets`选项。
2. 新建文件之后需要点击 Reload Cmake Project 图标。
3. .h文件如果使用`uint8_t`等数据类型，可能需要添加`#include <stdint.h>`来引入标准库文件。

## 第九章串口和`printf`
* 串口插件

  安装串口插件`Serial Port Monitor`，链接`/dev/tty.usb....`的设备。 

  插件不能发送HEX数据包，9-3节课中发送字符代替。  
  串口发送@开头勾选结束符如：@ABCD  ✅Send EOL。  
  使用`if (RxData == 0x40)`判断@符号为开始，使用`if (RxData == 0x0d)`判断EOL符号为结束。

* printf  

  在9-1节`Hardware/Serial.c`文件修改老师重写的`int fputc(int ch, FILE *f)`为 `int __io_putchar(int ch) ` 。
  
  > 参考老师给的资料`固件库/Project/STM32F10x_StdPeriph_Examples/USART/Printf`示例项目。
  
  添加`add_link_options(-specs=nano.specs -specs=nosys.specs)`到`CMakeLists.txt`文件。


