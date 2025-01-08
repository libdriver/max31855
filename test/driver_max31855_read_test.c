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
 * @file      driver_max31855_read_test.c
 * @brief     driver max31855 read test source file
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

static max31855_handle_t gs_handle;        /**< max31855 handle */

/**
 * @brief     read test
 * @param[in] times test times
 * @return    status code
 *            - 0 success
 *            - 1 test failed
 * @note      none
 */
uint8_t max31855_read_test(uint32_t times)
{
    uint8_t res;
    uint32_t i;
    max31855_info_t info;
    
    /* link functions */
    DRIVER_MAX31855_LINK_INIT(&gs_handle, max31855_handle_t);
    DRIVER_MAX31855_LINK_SPI_INIT(&gs_handle, max31855_interface_spi_init);
    DRIVER_MAX31855_LINK_SPI_DEINIT(&gs_handle, max31855_interface_spi_deinit);
    DRIVER_MAX31855_LINK_SPI_READ_COMMAND(&gs_handle, max31855_interface_spi_read_cmd);
    DRIVER_MAX31855_LINK_DELAY_MS(&gs_handle, max31855_interface_delay_ms);
    DRIVER_MAX31855_LINK_DEBUG_PRINT(&gs_handle, max31855_interface_debug_print);
    
    /* max31855 info */
    res = max31855_info(&info);
    if (res != 0)
    {
        max31855_interface_debug_print("max31855: get info failed.\n");
       
        return 1;
    }
    else
    {
        /* print chip information */
        max31855_interface_debug_print("max31855: chip is %s.\n", info.chip_name);
        max31855_interface_debug_print("max31855: manufacturer is %s.\n", info.manufacturer_name);
        max31855_interface_debug_print("max31855: interface is %s.\n", info.interface);
        max31855_interface_debug_print("max31855: driver version is %d.%d.\n", info.driver_version / 1000, (info.driver_version % 1000) / 100);
        max31855_interface_debug_print("max31855: min supply voltage is %0.1fV.\n", info.supply_voltage_min_v);
        max31855_interface_debug_print("max31855: max supply voltage is %0.1fV.\n", info.supply_voltage_max_v);
        max31855_interface_debug_print("max31855: max current is %0.2fmA.\n", info.max_current_ma);
        max31855_interface_debug_print("max31855: max temperature is %0.1fC.\n", info.temperature_max);
        max31855_interface_debug_print("max31855: min temperature is %0.1fC.\n", info.temperature_min);
    }
    
    /* max31855 init */
    res = max31855_init(&gs_handle);
    if (res != 0)
    {
        max31855_interface_debug_print("max31855: init failed.\n");
       
        return 1;
    }
    
    /* start read test */
    max31855_interface_debug_print("max31855: start read test.\n");
    
    for (i = 0; i < times; i++)
    {
        int16_t thermocouple_raw;
        float thermocouple_temp;
        int16_t reference_junction_raw;
        float reference_junction_temp;
        
        /* read data */
        res = max31855_read(&gs_handle, &thermocouple_raw, &thermocouple_temp,
                            &reference_junction_raw, &reference_junction_temp);
        if (res != 0)
        {
            max31855_interface_debug_print("max31855: read failed.\n");
            (void)max31855_deinit(&gs_handle);
            
            return 1;
        }
        
        /* output */
        max31855_interface_debug_print("max31855: thermocouple raw is %d.\n", thermocouple_raw);
        max31855_interface_debug_print("max31855: thermocouple is %0.2fC.\n", thermocouple_temp);
        max31855_interface_debug_print("max31855: reference junction raw is %d.\n", reference_junction_raw);
        max31855_interface_debug_print("max31855: reference junction is %0.2fC.\n", reference_junction_temp);
        
        /* delay 1000ms */
        max31855_interface_delay_ms(1000);
    }
    
    /* finish read test */
    max31855_interface_debug_print("max31855: finish read test.\n");  
    (void)max31855_deinit(&gs_handle);
    
    return 0;
}
