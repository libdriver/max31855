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
 * @file      driver_max31855_basic.c
 * @brief     driver max31855 basic source file
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

#include "driver_max31855_basic.h"

static max31855_handle_t gs_handle;        /**< max31855 handle */

/**
 * @brief  basic example init
 * @return status code
 *         - 0 success
 *         - 1 init failed
 * @note   none
 */
uint8_t max31855_basic_init(void)
{
    uint8_t res;

    /* link functions */
    DRIVER_MAX31855_LINK_INIT(&gs_handle, max31855_handle_t);
    DRIVER_MAX31855_LINK_SPI_INIT(&gs_handle, max31855_interface_spi_init);
    DRIVER_MAX31855_LINK_SPI_DEINIT(&gs_handle, max31855_interface_spi_deinit);
    DRIVER_MAX31855_LINK_SPI_READ_COMMAND(&gs_handle, max31855_interface_spi_read_cmd);
    DRIVER_MAX31855_LINK_DELAY_MS(&gs_handle, max31855_interface_delay_ms);
    DRIVER_MAX31855_LINK_DEBUG_PRINT(&gs_handle, max31855_interface_debug_print);
    
    /* max31855 init */
    res = max31855_init(&gs_handle);
    if (res != 0)
    {
        max31855_interface_debug_print("max31855: init failed.\n");
        
        return 1;
    }
    
    return 0;
}

/**
 * @brief  basic example deinit
 * @return status code
 *         - 0 success
 *         - 1 deinit failed
 * @note   none
 */
uint8_t max31855_basic_deinit(void)
{
    /* close max31855 */
    if (max31855_deinit(&gs_handle) != 0)
    {
        return 1;
    }
    
    return 0;
}

/**
 * @brief      basic example read the temperature
 * @param[out] *raw pointer to a raw temperature buffer
 * @param[out] *temp pointer to a converted temperature buffer
 * @param[out] *fault pointer to a fault buffer
 * @return     status code
 *             - 0 success
 *             - 1 read failed
 * @note       none
 */
uint8_t max31855_basic_read(int16_t *raw, float *temp, max31855_fault_t *fault)
{
    int16_t reference_junction_raw;
    float reference_junction_temp;
    
    /* read data */
    if (max31855_read(&gs_handle, raw, temp, 
                      &reference_junction_raw, &reference_junction_temp) != 0)
    {
        return 1;
    }
    
    /* get last fault */
    if (max31855_get_last_fault(&gs_handle, fault) != 0)
    {
        return 1;
    }
    
    return 0;
}
