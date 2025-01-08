[English](/README.md) | [ 简体中文](/README_zh-Hans.md) | [繁體中文](/README_zh-Hant.md) | [日本語](/README_ja.md) | [Deutsch](/README_de.md) | [한국어](/README_ko.md)

<div align=center>
<img src="/doc/image/logo.svg" width="400" height="150"/>
</div>

## LibDriver MAX31855

[![MISRA](https://img.shields.io/badge/misra-compliant-brightgreen.svg)](/misra/README.md) [![API](https://img.shields.io/badge/api-reference-blue.svg)](https://www.libdriver.com/docs/max31855/index.html) [![License](https://img.shields.io/badge/license-MIT-brightgreen.svg)](/LICENSE)

MAX31855具有冷端補償，將K、J、N、T或E型熱電偶訊號轉換成數位量（如果使用S和R型熱電偶，請聯系工廠）。 器件輸出14比特帶符號數據，通過SPI相容介面、以只讀格式輸出。 轉換器的溫度分辯率為0.25℃，最高溫度讀數為+1800℃，最低溫度讀數為-270℃，對於K型熱電偶，溫度範圍為-200℃至+700℃，保持±2℃精度。

LibDriver MAX31855是LibDriver推出的MAX31855全功能驅動，該驅動提供溫度讀取等功能並且它符合MISRA標準。

### 目錄

  - [說明](#說明)
  - [安裝](#安裝)
  - [使用](#使用)
    - [example basic](#example-basic)
  - [文檔](#文檔)
  - [貢獻](#貢獻)
  - [版權](#版權)
  - [聯繫我們](#聯繫我們)

### 說明

/src目錄包含了LibDriver MAX31855的源文件。

/interface目錄包含了LibDriver MAX31855與平台無關的SPI總線模板。

/test目錄包含了LibDriver MAX31855驅動測試程序，該程序可以簡單的測試芯片必要功能。

/example目錄包含了LibDriver MAX31855編程範例。

/doc目錄包含了LibDriver MAX31855離線文檔。

/datasheet目錄包含了MAX31855數據手冊。

/project目錄包含了常用Linux與單片機開發板的工程樣例。所有工程均採用shell腳本作為調試方法，詳細內容可參考每個工程裡面的README.md。

/misra目錄包含了LibDriver MISRA程式碼掃描結果。

### 安裝

參考/interface目錄下與平台無關的SPI總線模板，完成指定平台的SPI總線驅動。

將/src目錄，您使用平臺的介面驅動和您開發的驅動加入工程，如果您想要使用默認的範例驅動，可以將/example目錄加入您的工程。

### 使用

您可以參考/example目錄下的程式設計範例完成適合您的驅動，如果您想要使用默認的程式設計範例，以下是它們的使用方法。

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

### 文檔

在線文檔: [https://www.libdriver.com/docs/max31855/index.html](https://www.libdriver.com/docs/max31855/index.html)。

離線文檔: /doc/html/index.html。

### 貢獻

請參攷CONTRIBUTING.md。

### 版權

版權 (c) 2015 - 現在 LibDriver 版權所有

MIT 許可證（MIT）

特此免費授予任何獲得本軟件副本和相關文檔文件（下稱“軟件”）的人不受限制地處置該軟件的權利，包括不受限制地使用、複製、修改、合併、發布、分發、轉授許可和/或出售該軟件副本，以及再授權被配發了本軟件的人如上的權利，須在下列條件下：

上述版權聲明和本許可聲明應包含在該軟件的所有副本或實質成分中。

本軟件是“如此”提供的，沒有任何形式的明示或暗示的保證，包括但不限於對適銷性、特定用途的適用性和不侵權的保證。在任何情況下，作者或版權持有人都不對任何索賠、損害或其他責任負責，無論這些追責來自合同、侵權或其它行為中，還是產生於、源於或有關於本軟件以及本軟件的使用或其它處置。

### 聯繫我們

請聯繫lishifenging@outlook.com。
