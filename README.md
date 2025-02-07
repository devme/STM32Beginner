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

  >安装OpenOCD
  > 
  >```brew install openocd```

## 配置CLion
Setting->Embedded Development
  >OpenOCD Location : /opt/homebrew/bin/openocd
  > 
  >Stm32CubeMX Location : /Applications/STMicroelectronics/STM32CubeMX.app/Contents/Resources/STM32CubeMX
