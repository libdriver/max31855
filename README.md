[English](/README.md) | [ 简体中文](/README_zh-Hans.md) | [繁體中文](/README_zh-Hant.md) | [日本語](/README_ja.md) | [Deutsch](/README_de.md) | [한국어](/README_ko.md)

<div align=center>
<img src="/doc/image/logo.svg" width="400" height="150"/>
</div>

## LibDriver MAX31855

[![MISRA](https://img.shields.io/badge/misra-compliant-brightgreen.svg)](/misra/README.md) [![API](https://img.shields.io/badge/api-reference-blue.svg)](https://www.libdriver.com/docs/max31855/index.html) [![License](https://img.shields.io/badge/license-MIT-brightgreen.svg)](/LICENSE)

The MAX31855 performs cold-junction compensation and digitizes the signal from a K-, J-, N-, T-, S-, R-, or E-type thermocouple. The data is output in a signed 14-bit, SPI-compatible, read-only format. This converter resolves temperatures to 0.25°C, allows readings as high as +1800°C and as low as -270°C, and exhibits thermocouple accuracy of ±2°C for temperatures ranging from -200°C to +700°C for K-type thermocouples.

LibDriver MAX31855 is a full-featured driver for MAX31855, launched by LibDriver.It provides temperature reading and additional features. LibDriver is MISRA compliant.

### Table of Contents

  - [Instruction](#Instruction)
  - [Install](#Install)
  - [Usage](#Usage)
    - [example basic](#example-basic)
  - [Document](#Document)
  - [Contributing](#Contributing)
  - [License](#License)
  - [Contact Us](#Contact-Us)

### Instruction

/src includes LibDriver MAX31855 source files.

/interface includes LibDriver MAX31855 SPI platform independent template.

/test includes LibDriver MAX31855 driver test code and this code can test the chip necessary function simply.

/example includes LibDriver MAX31855 sample code.

/doc includes LibDriver MAX31855 offline document.

/datasheet includes MAX31855 datasheet.

/project includes the common Linux and MCU development board sample code. All projects use the shell script to debug the driver and the detail instruction can be found in each project's README.md.

/misra includes the LibDriver MISRA code scanning results.

### Install

Reference /interface SPI platform independent template and finish your platform SPI driver.

Add the /src directory, the interface driver for your platform, and your own drivers to your project, if you want to use the default example drivers, add the /example directory to your project.

### Usage

You can refer to the examples in the /example directory to complete your own driver. If you want to use the default programming examples, here's how to use them.

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

### Document

Online documents: [https://www.libdriver.com/docs/max31855/index.html](https://www.libdriver.com/docs/max31855/index.html).

Offline documents: /doc/html/index.html.

### Contributing

Please refer to CONTRIBUTING.md.

### License

Copyright (c) 2015 - present LibDriver All rights reserved



The MIT License (MIT) 



Permission is hereby granted, free of charge, to any person obtaining a copy

of this software and associated documentation files (the "Software"), to deal

in the Software without restriction, including without limitation the rights

to use, copy, modify, merge, publish, distribute, sublicense, and/or sell

copies of the Software, and to permit persons to whom the Software is

furnished to do so, subject to the following conditions: 



The above copyright notice and this permission notice shall be included in all

copies or substantial portions of the Software. 



THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR

IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,

FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE

AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER

LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,

OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE

SOFTWARE. 

### Contact Us

Please send an e-mail to lishifenging@outlook.com.