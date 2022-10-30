nanoCH32V203
-----------
[中文](./README_cn.md) [English](./README.md)

* [Introduce](#Introduce)
* [Feature](#feature)
* [Chip Resources](#chip-resources)
* [How To Use](#how-to-use)
* [Product Link](#product-link)
* [Reference](#reference)


# Introduce
nanoCH32V203 is a development board made by MuseLab based on WCH CH32V203C8T6. Dual TYPE-C USB interfaces, LCD interface and SD card interface onboard, can be downloaded and burned through the USB port, which is convenient for prototype verification and development.

<div align=center>
<img src="https://github.com/wuxx/nanoCH32V203/blob/master/doc/nanoESP32-C3-1.jpg" width = "500" alt="" align=center />
</div>

# Feature
- Dual USB interface, USB1 supports Device, USB2 supports Host/Device
- Can be downloaded directly via USB without additional downloader
- Onboard 8MHz and 32.768K crystal oscillator
- FPC-12P cable interface, can support common LCD (such as ili9341, st7789, etc.)
- SD card slot, support SD card reading and writing (SPI protocol)

# Chip Resources
![CH32V203C8T6](https://github.com/wuxx/nanoCH32V203/blob/master/doc/CH32V203C8T6.png)

# How To Use
## MounRiver Studio IDE
WCH officially provides MounRiver Studio IDE development environment, which supports Windows/Linux/Mac. The instructions are as follows
 
### MounRiver Studio Download
download the MounRiver Studio IDE from the official website [MounRiver Studio](http://www.mounriver.com), and just select the latest version to download.

### Compile
Take the GPIO project as an example, double-click GPIO_Toggle.wvproj to open the project
![MRS-1](https://github.com/wuxx/nanoCH32V203/blob/master/doc/MRS-1.png)
![MRS-2](https://github.com/wuxx/nanoCH32V203/blob/master/doc/MRS-2.png)  
Click Project -> Build Project to compile the project  
![MRS-3](https://github.com/wuxx/nanoCH32V203/blob/master/doc/MRS-3.png)


## Program
If use WCH's official downloader WCHLink, click Flash -> Download to program the flash. If you use the USB1 port for program, the operation instructions are as follows
Note: The compiled binary file is located in the obj directory of the factory, such as EVT\EXAM\GPIO\GPIO_Toggle\obj\GPIO_Toggle.hex

### WCHISPTool Download
download WCHISPTool at [WCH Official Website](https://www.wch.cn/downloads/WCHISPTool_Setup_exe.html)

### WCHISPTool Config
![ISP-1](https://github.com/wuxx/nanoCH32V203/blob/master/doc/ISP-1.png)

The chip series select CH32Vx series, the chip model select CH32V203, and the download method select USB.
Keep pressing the BOOT button on the development board, then press and release the RST button, and finally release the BOOT button to make the chip enter the bootloader. If the bootloader is successfully entered, the target can be detected in the USB device list in the WCHISPTool.
Then select the bin or hex file to be programmed, and click Download to burn the firmware.

## Open Source Toolchain
### Toolchain Download

Download the RISC-V toolchain https://github.com/xpack-dev-tools/riscv-none-embed-gcc-xpack/releases to the local, then modify ~/.bashrc and import it into environment variables, for example as follows
```
export PATH=${PATH}:/home/pi/tool/xpack-riscv-none-embed-gcc-10.2.0-1.2/bin
```

### Compile
```
$git clone https://github.com/wuxx/CH32V203-makefile-example
$cd CH32V203-makefile-example
$make
```

### Program
use the open source download tool wchisp to program the flash, the operation is as follows
wchisp is a tool written in rust, first update rustc
```
$rustc -V
$rustup update
```

install wchisp
```
$cargo install wchisp --git https://github.com/ch32-rs/wchisp
```

Press and hold the BOOT button on the development board, then press the RST button and release, and finally release the BOOT button to make the chip enter the bootloader, and then call wchisp to program
```
$sudo /home/pi/.cargo/bin/wchisp info
$sudo /home/pi/.cargo/bin/wchisp flash ./build/app.bin
```

# Product Link
[nanoCH32V203 Board](https://item.taobao.com/item.htm?spm=a1z10.5-c.w4002-21349689069.14.146848aeEGVAz9&id=652515479052)

# Reference
### WCH
https://www.wch.cn/
