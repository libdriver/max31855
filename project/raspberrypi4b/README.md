### 1. Board

#### 1.1 Board Info

Board Name: Raspberry Pi 4B.

SPI Pin: SCLK/MISO/CS GPIO11/GPIO9/GPIO8.

### 2. Install

#### 2.1 Dependencies

Install the necessary dependencies.

```shell
sudo apt-get install libgpiod-dev pkg-config cmake -y
```

#### 2.2 Makefile

Build the project.

```shell
make
```

Install the project and this is optional.

```shell
sudo make install
```

Uninstall the project and this is optional.

```shell
sudo make uninstall
```

#### 2.3 CMake

Build the project.

```shell
mkdir build && cd build 
cmake .. 
make
```

Install the project and this is optional.

```shell
sudo make install
```

Uninstall the project and this is optional.

```shell
sudo make uninstall
```

Test the project and this is optional.

```shell
make test
```

Find the compiled library in CMake. 

```cmake
find_package(max31855 REQUIRED)
```


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
./max31855 -i

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
./max31855 -p

max31855: SCK connected to GPIO11(BCM).
max31855: MISO connected to GPIO9(BCM).
max31855: CS connected to GPIO8(BCM).
```

```shell
./max31855 -t read --times=3

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
max31855: thermocouple raw is 110.
max31855: thermocouple is 27.50C.
max31855: reference junction raw is 463.
max31855: reference junction is 28.94C.
max31855: thermocouple raw is 110.
max31855: thermocouple is 27.50C.
max31855: reference junction raw is 463.
max31855: reference junction is 28.94C.
max31855: thermocouple raw is 110.
max31855: thermocouple is 27.50C.
max31855: reference junction raw is 463.
max31855: reference junction is 28.94C.
max31855: finish read test.
```

```shell
./max31855 -e read --times=3

1/3 31.75C.
2/3 31.50C.
3/3 31.50C.
```

```shell
./max31855 -h

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

