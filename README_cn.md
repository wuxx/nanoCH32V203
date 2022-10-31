nanoCH32V203
-----------
[English](./README.md)

* [nanoCH32V203介绍](#nanoCH32V203介绍) 
* [特性](#特性)
* [芯片资源](#芯片资源)
* [使用教程](#使用教程)
* [产品链接](#产品链接)
* [参考](#参考)


# nanoCH32V203介绍
nanoCH32V203 是MuseLab基于沁恒CH32V203C8T6芯片推出的开发板，板载双TYPE-C USB接口，LCD接口，SD卡接口，可通过USB口下载烧录，方便客户进行快速的原型验证及开发。

![3](https://github.com/wuxx/nanoCH32V203/blob/master/doc/3.jpg)
![4](https://github.com/wuxx/nanoCH32V203/blob/master/doc/4.jpg)
![5](https://github.com/wuxx/nanoCH32V203/blob/master/doc/5.jpg)


# 特性
- 双USB接口，其中USB1支持Device，USB2支持Host/Device
- 可直接通过USB下载，无需额外下载器
- 板载8MHz与32.768K晶振
- 引出FPC-12P排线接口，可支持常见LCD （如ili9341、st7789等）
- 引出SD卡座，支持SD卡读写（SPI协议）

# 芯片资源
![CH32V203C8T6](https://github.com/wuxx/nanoCH32V203/blob/master/doc/CH32V203C8T6.png)

# 使用教程
## MounRiver Studio IDE
沁恒官方提供MounRiver Studio IDE开发环境，支持Windows/Linux/Mac，具体使用说明如下
 
### MounRiver Studio 下载
可在官网[MounRiver Studio](http://www.mounriver.com)下载IDE，选择最新版本下载即可。

### 编译
以GPIO工程为例，双击GPIO_Toggle.wvproj打开工程  
![MRS-1](https://github.com/wuxx/nanoCH32V203/blob/master/doc/MRS-1.png)
![MRS-2](https://github.com/wuxx/nanoCH32V203/blob/master/doc/MRS-2.png)  
点击 Project -> Build Project 对工程进行编译  
![MRS-3](https://github.com/wuxx/nanoCH32V203/blob/master/doc/MRS-3.png)


## 烧录
若使用沁恒官方的下载器WCHLink，则点击 Flash -> Download 即可完成烧录，若使用自带的USB口进行烧录，则操作说明如下
注：编译生成的二进制文件位于工厂的obj目录下，如EVT\EXAM\GPIO\GPIO_Toggle\obj\GPIO_Toggle.hex

### WCHISPTool 下载
可在[沁恒官网](https://www.wch.cn/downloads/WCHISPTool_Setup_exe.html)下载WCHISPTool工具

### WCHISPTool 配置
![ISP-1](https://github.com/wuxx/nanoCH32V203/blob/master/doc/ISP-1.png)

芯片系列选择CH32Vx系列，芯片型号选择CH32V203，下载方式选择USB。
持续按住开发板上的BOOT按键，然后按下RST按键并松开，最后再松开BOOT按键，令芯片进入bootloader，若成功进入bootloader，则在ISP工具中的USB设备列表中可检测到目标芯片。
然后在下方选择需要烧录的bin或者hex文件，点击下载即可烧录固件。

## 开源工具链开发
### 工具链下载

将RISC-V工具链 https://github.com/xpack-dev-tools/riscv-none-embed-gcc-xpack/releases 下载到本地，然后修改~/.bashrc，将其导入环境变量，举例如下
```
export PATH=${PATH}:/home/pi/tool/xpack-riscv-none-embed-gcc-10.2.0-1.2/bin
```

### 编译
```
$git clone https://github.com/wuxx/CH32V203-makefile-example
$cd CH32V203-makefile-example
$make
```

### 烧录
可使用开源的下载工具wchisp进行烧录，具体操作如下
wchisp是rust编写的工具，首先更新rustc
```
$rustc -V
$rustup update
```

安装wchisp
```
$cargo install wchisp --git https://github.com/ch32-rs/wchisp
```

按住开发板上的BOOT按键，然后按下RST按键并松开，最后再松开BOOT按键，令芯片进入bootloader，然后即可调用wchisp进行烧录
```
$sudo /home/pi/.cargo/bin/wchisp info
$sudo /home/pi/.cargo/bin/wchisp flash ./build/app.bin
```

# 产品链接
[nanoCH32V203 Board](https://item.taobao.com/item.htm?spm=a1z10.3-c.w4002-21349689064.10.6f55773dXd3CDz&id=689934001629)

# 参考
### WCH
https://www.wch.cn/
