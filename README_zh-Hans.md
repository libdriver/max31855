[English](/README.md) | [ 简体中文](/README_zh-Hans.md) | [繁體中文](/README_zh-Hant.md) | [日本語](/README_ja.md) | [Deutsch](/README_de.md) | [한국어](/README_ko.md)

<div align=center>
<img src="/doc/image/logo.svg" width="400" height="150"/>
</div>

## LibDriver MAX31855

[![MISRA](https://img.shields.io/badge/misra-compliant-brightgreen.svg)](/misra/README.md) [![API](https://img.shields.io/badge/api-reference-blue.svg)](https://www.libdriver.com/docs/max31855/index.html) [![License](https://img.shields.io/badge/license-MIT-brightgreen.svg)](/LICENSE)

MAX31855具有冷端补偿，将K、J、N、T或E型热电偶信号转换成数字量(如果使用S和R型热电偶，请联系工厂)。器件输出14位带符号数据，通过SPI兼容接口、以只读格式输出。转换器的温度分辨率为0.25℃，最高温度读数为+1800℃，最低温度读数为-270℃，对于K型热电偶，温度范围为-200℃至+700℃，保持±2℃精度。

LibDriver MAX31855是LibDriver推出的MAX31855全功能驱动，该驱动提供温度读取等功能并且它符合MISRA标准。

### 目录

  - [说明](#说明)
  - [安装](#安装)
  - [使用](#使用)
    - [example basic](#example-basic)
  - [文档](#文档)
  - [贡献](#贡献)
  - [版权](#版权)
  - [联系我们](#联系我们)

### 说明

/src目录包含了LibDriver MAX31855的源文件。

/interface目录包含了LibDriver MAX31855与平台无关的SPI总线模板。

/test目录包含了LibDriver MAX31855驱动测试程序，该程序可以简单的测试芯片必要功能。

/example目录包含了LibDriver MAX31855编程范例。

/doc目录包含了LibDriver MAX31855离线文档。

/datasheet目录包含了MAX31855数据手册。

/project目录包含了常用Linux与单片机开发板的工程样例。所有工程均采用shell脚本作为调试方法，详细内容可参考每个工程里面的README.md。

/misra目录包含了LibDriver MISRA代码扫描结果。

### 安装

参考/interface目录下与平台无关的SPI总线模板，完成指定平台的SPI总线驱动。

将/src目录，您使用平台的接口驱动和您开发的驱动加入工程，如果您想要使用默认的范例驱动，可以将/example目录加入您的工程。

### 使用

您可以参考/example目录下的编程范例完成适合您的驱动，如果您想要使用默认的编程范例，以下是它们的使用方法。

#### example basic

```C
#include "driver_max31855_basic.h"

uint8_t res;
uint32_t i;
uint32_t times;

times = 3;
res = max31855_basic_init();
if (res != 0)
{
    return 1;
}

...
    
for (i = 0; i < times; i++)
{
    int16_t raw;
    float temp;
    max31855_fault_t fault;

    /* read data */
    res = max31855_basic_read(&raw, &temp, &fault);
    if (res != 0)
    {
        (void)max31855_basic_deinit();
        if (fault != MAX31855_FAULT_NONE)
        {
            if (fault == MAX31855_FAULT_OC)
            {
                max31855_interface_debug_print("max31855: fault is open, no connections.\n");
            }
            else if (fault == MAX31855_FAULT_SCG)
            {
                max31855_interface_debug_print("max31855: fault is short-circuited to gnd.\n");
            }
            else if (fault == MAX31855_FAULT_SCV)
            {
                max31855_interface_debug_print("max31855: fault is short-circuited to vcc.\n");
            }
            else
            {
                max31855_interface_debug_print("max31855: fault is unknown.\n");
            }
        }

        return 1;
     }

    /* output */
    max31855_interface_debug_print("%d/%d %0.2fC.\n", i + 1, times, temp);

    /* delay 1000ms */
    max31855_interface_delay_ms(1000);
    
    ...
}

...
    
/* deinit */
(void)max31855_basic_deinit();

return 0;
```

### 文档

在线文档: [https://www.libdriver.com/docs/max31855/index.html](https://www.libdriver.com/docs/max31855/index.html)。

离线文档: /doc/html/index.html。

### 贡献

请参考CONTRIBUTING.md。

### 版权

版权 (c) 2015 - 现在 LibDriver 版权所有

MIT 许可证（MIT）

特此免费授予任何获得本软件副本和相关文档文件（下称“软件”）的人不受限制地处置该软件的权利，包括不受限制地使用、复制、修改、合并、发布、分发、转授许可和/或出售该软件副本，以及再授权被配发了本软件的人如上的权利，须在下列条件下：

上述版权声明和本许可声明应包含在该软件的所有副本或实质成分中。

本软件是“如此”提供的，没有任何形式的明示或暗示的保证，包括但不限于对适销性、特定用途的适用性和不侵权的保证。在任何情况下，作者或版权持有人都不对任何索赔、损害或其他责任负责，无论这些追责来自合同、侵权或其它行为中，还是产生于、源于或有关于本软件以及本软件的使用或其它处置。

### 联系我们

请联系lishifenging@outlook.com。