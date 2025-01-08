### 1. Chip

#### 1.1 Chip Info

Chip Name: STM32F407ZGT6.

Extern Oscillator: 8MHz.

UART Pin: TX/RX PA9/PA10.

SPI Pin: SCK/MISO/CS  PA5/PA6/PA4.

### 2. Development and Debugging

#### 2.1 Integrated Development Environment

LibDriver provides both Keil and IAR integrated development environment projects.

MDK is the Keil ARM project and your Keil version must be 5 or higher.Keil ARM project needs STMicroelectronics STM32F4 Series Device Family Pack and you can download from https://www.keil.com/dd2/stmicroelectronics/stm32f407zgtx.

EW is the IAR ARM project and your IAR version must be 9 or higher.

#### 2.2 Serial Port Parameter

Baud Rate: 115200.

Data Bits : 8.

Stop Bits: 1.

Parity: None.

Flow Control: None.

#### 2.3 Serial Port Assistant

We use '\n' to wrap lines.If your serial port assistant displays exceptions (e.g. the displayed content does not divide lines), please modify the configuration of your serial port assistant or replace one that supports '\n' parsing.

### 3. MAX31855

#### 3.1 Command Instruction

1. Show max31855 chip and driver information.

   ```shell
   max31855 (-i | --information)
   ```

2. Show max31855 help.

   ```shell
   max31855 (-h | --help)
   ```

3. Show max31855 pin connections of the current board.

   ```shell
   max31855 (-p | --port)
   ```

4. Run max31855 read test, num is the test times. 

   ```shell
   max31855 (-t read | --test=read) [--times=<num>]
   ```

5. Run max31855 read function, num is the read times. 

   ```shell
   max31855 (-e read | --example=read) [--times=<num>]
   ```

#### 3.2 Command Example

```shell
max31855 -i

max31855: chip is Maxim Integrated max31855.
max31855: manufacturer is Maxim Integrated.
max31855: interface is SPI.
max31855: driver version is 1.0.
max31855: min supply voltage is 3.0V.
max31855: max supply voltage is 3.6V.
max31855: max current is 1.50mA.
max31855: max temperature is 125.0C.
max31855: min temperature is -20.0C.
```

```shell
max31855 -p

max31855: SCK connected to GPIOA PIN5.
max31855: MISO connected to GPIOA PIN6.
max31855: CS connected to GPIOA PIN4.
```

```shell
max31855 -t read --times=3

max31855: chip is Maxim Integrated max31855.
max31855: manufacturer is Maxim Integrated.
max31855: interface is SPI.
max31855: driver version is 1.0.
max31855: min supply voltage is 3.0V.
max31855: max supply voltage is 3.6V.
max31855: max current is 1.50mA.
max31855: max temperature is 125.0C.
max31855: min temperature is -20.0C.
max31855: start read test.
max31855: thermocouple raw is 116.
max31855: thermocouple is 29.00C.
max31855: reference junction raw is 437.
max31855: reference junction is 27.31C.
max31855: thermocouple raw is 116.
max31855: thermocouple is 29.00C.
max31855: reference junction raw is 437.
max31855: reference junction is 27.31C.
max31855: thermocouple raw is 115.
max31855: thermocouple is 28.75C.
max31855: reference junction raw is 437.
max31855: reference junction is 27.31C.
max31855: finish read test.
```

```shell
max31855 -e read --times=3

1/3 28.25C.
2/3 28.50C.
3/3 28.25C.
```

```shell
max31855 -h

Usage:
  max31855 (-i | --information)
  max31855 (-h | --help)
  max31855 (-p | --port)
  max31855 (-t read | --test=read) [--times=<num>]
  max31855 (-e read | --example=read) [--times=<num>]

Options:
  -e <read>, --example=<read>        Run the driver example.
  -h, --help                         Show the help.
  -i, --information                  Show the chip information.
  -p, --port                         Display the pin connections of the current board.
  -t <read>, --test=<read>           Run the driver test.
      --times=<num>                  Set the running times.([default: 3])
```

