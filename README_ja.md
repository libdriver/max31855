[English](/README.md) | [ 简体中文](/README_zh-Hans.md) | [繁體中文](/README_zh-Hant.md) | [日本語](/README_ja.md) | [Deutsch](/README_de.md) | [한국어](/README_ko.md)

<div align=center>
<img src="/doc/image/logo.svg" width="400" height="150"/>
</div>

## LibDriver MAX31855

[![MISRA](https://img.shields.io/badge/misra-compliant-brightgreen.svg)](/misra/README.md) [![API](https://img.shields.io/badge/api-reference-blue.svg)](https://www.libdriver.com/docs/max31855/index.html) [![License](https://img.shields.io/badge/license-MIT-brightgreen.svg)](/LICENSE)

MAX31855 は冷接点補償を実行し、K、J、N、T、S、R、または E タイプの熱電対からの信号をデジタル化します。データは、符号付き 14 ビット、SPI 互換、読み取り専用形式で出力されます。このコンバータは、温度を 0.25°C まで分解し、最高 +1800°C、最低 -270°C の読み取りが可能で、K タイプ熱電対の場合、-200°C ～ +700°C の温度範囲で ±2°C の熱電対精度を示します。

LibDriver MAX31855 は、LibDriver によって起動された MAX31855 のフル機能ドライバです。温度の読み取り機能などを提供します。 LibDriver は MISRA 準拠です。

### 目次

  - [説明](#説明)
  - [インストール](#インストール)
  - [使用](#使用)
    - [example basic](#example-basic)
  - [ドキュメント](#ドキュメント)
  - [貢献](#貢献)
  - [著作権](#著作権)
  - [連絡して](#連絡して)

### 説明

/ srcディレクトリには、LibDriver MAX31855のソースファイルが含まれています。

/ interfaceディレクトリには、LibDriver MAX31855用のプラットフォームに依存しないSPIバステンプレートが含まれています。

/ testディレクトリには、チップの必要な機能を簡単にテストできるLibDriver MAX31855ドライバーテストプログラムが含まれています。

/ exampleディレクトリには、LibDriver MAX31855プログラミング例が含まれています。

/ docディレクトリには、LibDriver MAX31855オフラインドキュメントが含まれています。

/ datasheetディレクトリには、MAX31855データシートが含まれています。

/ projectディレクトリには、一般的に使用されるLinuxおよびマイクロコントローラー開発ボードのプロジェクトサンプルが含まれています。 すべてのプロジェクトは、デバッグ方法としてシェルスクリプトを使用しています。詳細については、各プロジェクトのREADME.mdを参照してください。

/ misraはLibDriver misraコードスキャン結果を含む。

### インストール

/ interfaceディレクトリにあるプラットフォームに依存しないSPIバステンプレートを参照して、指定したプラットフォームのSPIバスドライバを完成させます。

/src ディレクトリ、プラットフォームのインターフェイス ドライバー、および独自のドライバーをプロジェクトに追加します。デフォルトのサンプル ドライバーを使用する場合は、/example ディレクトリをプロジェクトに追加します。

### 使用

/example ディレクトリ内のサンプルを参照して、独自のドライバーを完成させることができます。 デフォルトのプログラミング例を使用したい場合の使用方法は次のとおりです。

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

### ドキュメント

オンラインドキュメント: [https://www.libdriver.com/docs/max31855/index.html](https://www.libdriver.com/docs/max31855/index.html)。

オフラインドキュメント: /doc/html/index.html。

### 貢献

CONTRIBUTING.mdを参照してください。

### 著作権

著作権（c）2015-今 LibDriver 全著作権所有

MITライセンス（MIT）

このソフトウェアおよび関連するドキュメントファイル（「ソフトウェア」）のコピーを取得した人は、無制限の使用、複製、変更、組み込み、公開、配布、サブライセンスを含む、ソフトウェアを処分する権利を制限なく付与されます。ソフトウェアのライセンスおよび/またはコピーの販売、および上記のようにソフトウェアが配布された人の権利のサブライセンスは、次の条件に従うものとします。

上記の著作権表示およびこの許可通知は、このソフトウェアのすべてのコピーまたは実体に含まれるものとします。

このソフトウェアは「現状有姿」で提供され、商品性、特定目的への適合性、および非侵害の保証を含むがこれらに限定されない、明示または黙示を問わず、いかなる種類の保証もありません。 いかなる場合も、作者または著作権所有者は、契約、不法行為、またはその他の方法で、本ソフトウェアおよび本ソフトウェアの使用またはその他の廃棄に起因または関連して、請求、損害、またはその他の責任を負わないものとします。

### 連絡して

お問い合わせくださいlishifenging@outlook.com。