/**
 * Copyright (c) 2015 - present LibDriver All rights reserved
 * 
 * The MIT License (MIT)
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in all
 * copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 * SOFTWARE. 
 *
 * @file      main.c
 * @brief     main source file
 * @version   1.0.0
 * @author    Shifeng Li
 * @date      2025-01-08
 *
 * <h3>history</h3>
 * <table>
 * <tr><th>Date        <th>Version  <th>Author      <th>Description
 * <tr><td>2025/01/08  <td>1.0      <td>Shifeng Li  <td>first upload
 * </table>
 */

#include "driver_max31855_read_test.h"
#include "driver_max31855_basic.h"
#include "shell.h"
#include "clock.h"
#include "delay.h"
#include "uart.h"
#include "getopt.h"
#include <stdlib.h>

/**
 * @brief global var definition
 */
uint8_t g_buf[256];        /**< uart buffer */
volatile uint16_t g_len;   /**< uart buffer length */

/**
 * @brief     max31855 full function
 * @param[in] argc arg numbers
 * @param[in] **argv arg address
 * @return    status code
 *            - 0 success
 *            - 1 run failed
 *            - 5 param is invalid
 * @note      none
 */
uint8_t max31855(uint8_t argc, char **argv)
{
    int c;
    int longindex = 0;
    const char short_options[] = "hipe:t:";
    const struct option long_options[] =
    {
        {"help", no_argument, NULL, 'h'},
        {"information", no_argument, NULL, 'i'},
        {"port", no_argument, NULL, 'p'},
        {"example", required_argument, NULL, 'e'},
        {"test", required_argument, NULL, 't'},
        {"times", required_argument, NULL, 1},
        {NULL, 0, NULL, 0},
    };
    char type[33] = "unknown";
    uint32_t times = 3;
    
    /* if no params */
    if (argc == 1)
    {
        /* goto the help */
        goto help;
    }
    
    /* init 0 */
    optind = 0;
    
    /* parse */
    do
    {
        /* parse the args */
        c = getopt_long(argc, argv, short_options, long_options, &longindex);
        
        /* judge the result */
        switch (c)
        {
            /* help */
            case 'h' :
            {
                /* set the type */
                memset(type, 0, sizeof(char) * 33);
                snprintf(type, 32, "h");
                
                break;
            }
            
            /* information */
            case 'i' :
            {
                /* set the type */
                memset(type, 0, sizeof(char) * 33);
                snprintf(type, 32, "i");
                
                break;
            }
            
            /* port */
            case 'p' :
            {
                /* set the type */
                memset(type, 0, sizeof(char) * 33);
                snprintf(type, 32, "p");
                
                break;
            }
            
            /* example */
            case 'e' :
            {
                /* set the type */
                memset(type, 0, sizeof(char) * 33);
                snprintf(type, 32, "e_%s", optarg);
                
                break;
            }
            
            /* test */
            case 't' :
            {
                /* set the type */
                memset(type, 0, sizeof(char) * 33);
                snprintf(type, 32, "t_%s", optarg);
                
                break;
            }
            
            /* running times */
            case 1 :
            {
                /* set the times */
                times = atol(optarg);
                
                break;
            } 
            
            /* the end */
            case -1 :
            {
                break;
            }
            
            /* others */
            default :
            {
                return 5;
            }
        }
    } while (c != -1);

    /* run the function */
    if (strcmp("t_read", type) == 0)
    {
        uint8_t res;
        
        /* run the read test */
        res = max31855_read_test(times);
        if (res != 0)
        {
            return 1;
        }
        else
        {
            return 0;
        }
    }
    else if (strcmp("e_read", type) == 0)
    {
        uint8_t res;
        uint32_t i;
        
        /* init */
        res = max31855_basic_init();
        if (res != 0)
        {
            return 1;
        }
        
        /* loop */
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
        }
        
        /* deinit */
        (void)max31855_basic_deinit();
        
        return 0;
    }
    else if (strcmp("h", type) == 0)
    {
        help:
        max31855_interface_debug_print("Usage:\n");
        max31855_interface_debug_print("  max31855 (-i | --information)\n");
        max31855_interface_debug_print("  max31855 (-h | --help)\n");
        max31855_interface_debug_print("  max31855 (-p | --port)\n");
        max31855_interface_debug_print("  max31855 (-t read | --test=read) [--times=<num>]\n");
        max31855_interface_debug_print("  max31855 (-e read | --example=read) [--times=<num>]\n");
        max31855_interface_debug_print("\n");
        max31855_interface_debug_print("Options:\n");
        max31855_interface_debug_print("  -e <read>, --example=<read>        Run the driver example.\n");
        max31855_interface_debug_print("  -h, --help                         Show the help.\n");
        max31855_interface_debug_print("  -i, --information                  Show the chip information.\n");
        max31855_interface_debug_print("  -p, --port                         Display the pin connections of the current board.\n");
        max31855_interface_debug_print("  -t <read>, --test=<read>           Run the driver test.\n");
        max31855_interface_debug_print("      --times=<num>                  Set the running times.([default: 3])\n");

        return 0;
    }
    else if (strcmp("i", type) == 0)
    {
        max31855_info_t info;
        
        /* print max31855 info */
        max31855_info(&info);
        max31855_interface_debug_print("max31855: chip is %s.\n", info.chip_name);
        max31855_interface_debug_print("max31855: manufacturer is %s.\n", info.manufacturer_name);
        max31855_interface_debug_print("max31855: interface is %s.\n", info.interface);
        max31855_interface_debug_print("max31855: driver version is %d.%d.\n", info.driver_version / 1000, (info.driver_version % 1000) / 100);
        max31855_interface_debug_print("max31855: min supply voltage is %0.1fV.\n", info.supply_voltage_min_v);
        max31855_interface_debug_print("max31855: max supply voltage is %0.1fV.\n", info.supply_voltage_max_v);
        max31855_interface_debug_print("max31855: max current is %0.2fmA.\n", info.max_current_ma);
        max31855_interface_debug_print("max31855: max temperature is %0.1fC.\n", info.temperature_max);
        max31855_interface_debug_print("max31855: min temperature is %0.1fC.\n", info.temperature_min);
        
        return 0;
    }
    else if (strcmp("p", type) == 0)
    {
        /* print pin connection */
        max31855_interface_debug_print("max31855: SCK connected to GPIOA PIN5.\n");
        max31855_interface_debug_print("max31855: MISO connected to GPIOA PIN6.\n");
        max31855_interface_debug_print("max31855: CS connected to GPIOA PIN4.\n");
        
        return 0;
    }
    else
    {
        return 5;
    }
}

/**
 * @brief main function
 * @note  none
 */
int main(void)
{
    uint8_t res;
    
    /* stm32f407 clock init and hal init */
    clock_init();
    
    /* delay init */
    delay_init();
    
    /* uart init */
    uart_init(115200);
    
    /* shell init && register max31855 function */
    shell_init();
    shell_register("max31855", max31855);
    uart_print("max31855: welcome to libdriver max31855.\n");
    
    while (1)
    {
        /* read uart */
        g_len = uart_read(g_buf, 256);
        if (g_len != 0)
        {
            /* run shell */
            res = shell_parse((char *)g_buf, g_len);
            if (res == 0)
            {
                /* run success */
            }
            else if (res == 1)
            {
                uart_print("max31855: run failed.\n");
            }
            else if (res == 2)
            {
                uart_print("max31855: unknown command.\n");
            }
            else if (res == 3)
            {
                uart_print("max31855: length is too long.\n");
            }
            else if (res == 4)
            {
                uart_print("max31855: pretreat failed.\n");
            }
            else if (res == 5)
            {
                uart_print("max31855: param is invalid.\n");
            }
            else
            {
                uart_print("max31855: unknown status code.\n");
            }
            uart_flush();
        }
        delay_ms(100);
    }
}
