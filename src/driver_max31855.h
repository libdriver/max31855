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
 * @file      driver_max31855.h
 * @brief     driver max31855 header file
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

#ifndef DRIVER_MAX31855_H
#define DRIVER_MAX31855_H

#include <stdio.h>
#include <stdint.h>
#include <string.h>

#ifdef __cplusplus
extern "C"{
#endif

/**
 * @defgroup max31855_driver max31855 driver function
 * @brief    max31855 driver modules
 * @{
 */

/**
 * @addtogroup max31855_base_driver
 * @{
 */

/**
 * @brief max31855 fault enumeration definition
 */
typedef enum
{
    MAX31855_FAULT_NONE = 0x00,           /**< none */
    MAX31855_FAULT_OC  = (1 << 0),        /**< open, no connections */
    MAX31855_FAULT_SCG = (1 << 1),        /**< short-circuited to gnd */
    MAX31855_FAULT_SCV = (1 << 2),        /**< short-circuited to vcc */
} max31855_fault_t;

/**
 * @brief max31855 handle structure definition
 */
typedef struct max31855_handle_s
{
    uint8_t (*spi_init)(void);                                  /**< point to a spi_init function address */
    uint8_t (*spi_deinit)(void);                                /**< point to a spi_deinit function address */
    uint8_t (*spi_read_cmd)(uint8_t *buf, uint16_t len);        /**< point to a spi_read_cmd function address */
    void (*delay_ms)(uint32_t ms);                              /**< point to a delay_ms function address */
    void (*debug_print)(const char *const fmt, ...);            /**< point to a debug_print function address */
    uint8_t inited;                                             /**< inited flag */
    uint8_t fault;                                              /**< fault */
} max31855_handle_t;

/**
 * @brief max31855 information structure definition
 */
typedef struct max31855_info_s
{
    char chip_name[32];                /**< chip name */
    char manufacturer_name[32];        /**< manufacturer name */
    char interface[8];                 /**< chip interface name */
    float supply_voltage_min_v;        /**< chip min supply voltage */
    float supply_voltage_max_v;        /**< chip max supply voltage */
    float max_current_ma;              /**< chip max current */
    float temperature_min;             /**< chip min operating temperature */
    float temperature_max;             /**< chip max operating temperature */
    uint32_t driver_version;           /**< driver version */
} max31855_info_t;

/**
 * @}
 */

/**
 * @defgroup max31855_link_driver max31855 link driver function
 * @brief    max31855 link driver modules
 * @ingroup  max31855_driver
 * @{
 */

/**
 * @brief     initialize max31855_handle_t structure
 * @param[in] HANDLE pointer to a max31855 handle structure
 * @param[in] STRUCTURE max31855_handle_t
 * @note      none
 */
#define DRIVER_MAX31855_LINK_INIT(HANDLE, STRUCTURE)               memset(HANDLE, 0, sizeof(STRUCTURE))

/**
 * @brief     link spi_init function
 * @param[in] HANDLE pointer to a max31855 handle structure
 * @param[in] FUC pointer to a spi_init function address
 * @note      none
 */
#define DRIVER_MAX31855_LINK_SPI_INIT(HANDLE, FUC)                (HANDLE)->spi_init = FUC

/**
 * @brief     link spi_deinit function
 * @param[in] HANDLE pointer to a max31855 handle structure
 * @param[in] FUC pointer to a spi_deinit function address
 * @note      none
 */
#define DRIVER_MAX31855_LINK_SPI_DEINIT(HANDLE, FUC)              (HANDLE)->spi_deinit = FUC

/**
 * @brief     link spi_read_cmd function
 * @param[in] HANDLE pointer to a max31855 handle structure
 * @param[in] FUC pointer to a spi_read_cmd function address
 * @note      none
 */
#define DRIVER_MAX31855_LINK_SPI_READ_COMMAND(HANDLE, FUC)        (HANDLE)->spi_read_cmd = FUC

/**
 * @brief     link delay_ms function
 * @param[in] HANDLE pointer to a max31855 handle structure
 * @param[in] FUC pointer to a delay_ms function address
 * @note      none
 */
#define DRIVER_MAX31855_LINK_DELAY_MS(HANDLE, FUC)                (HANDLE)->delay_ms = FUC

/**
 * @brief     link debug_print function
 * @param[in] HANDLE pointer to a max31855 handle structure
 * @param[in] FUC pointer to a debug_print function address
 * @note      none
 */
#define DRIVER_MAX31855_LINK_DEBUG_PRINT(HANDLE, FUC)             (HANDLE)->debug_print = FUC

/**
 * @}
 */

/**
 * @defgroup max31855_base_driver max31855 base driver function
 * @brief    max31855 base driver modules
 * @ingroup  max31855_driver
 * @{
 */

/**
 * @brief      get chip's information
 * @param[out] *info pointer to a max31855 info structure
 * @return     status code
 *             - 0 success
 *             - 2 handle is NULL
 * @note       none
 */
uint8_t max31855_info(max31855_info_t *info);

/**
 * @brief     initialize the chip
 * @param[in] *handle pointer to a max31855 handle structure
 * @return    status code
 *            - 0 success
 *            - 1 spi initialization failed
 *            - 2 handle is NULL
 *            - 3 linked functions is NULL
 * @note      none
 */
uint8_t max31855_init(max31855_handle_t *handle);

/**
 * @brief     close the chip
 * @param[in] *handle pointer to a max31855 handle structure
 * @return    status code
 *            - 0 success
 *            - 1 deinit failed
 *            - 2 handle is NULL
 *            - 3 handle is not initialized
 * @note      none
 */
uint8_t max31855_deinit(max31855_handle_t *handle);

/**
 * @brief      read the temperature
 * @param[in]  *handle pointer to a max31855 handle structure
 * @param[out] *thermocouple_raw pointer to a thermocouple raw data buffer
 * @param[out] *thermocouple_temp pointer to a thermocouple converted temperature buffer
 * @param[out] *reference_junction_raw pointer to a reference junction raw data buffer
 * @param[out] *reference_junction_temp pointer to a reference junction converted temperature buffer
 * @return     status code
 *             - 0 success
 *             - 1 read failed
 *             - 2 handle is NULL
 *             - 3 handle is not initialized
 *             - 4 find fault
 * @note       none
 */
uint8_t max31855_read(max31855_handle_t *handle, int16_t *thermocouple_raw, float *thermocouple_temp,
                      int16_t *reference_junction_raw, float *reference_junction_temp);

/**
 * @brief      get the last fault
 * @param[in]  *handle pointer to a max31855 handle structure
 * @param[out] *fault pointer to a fault buffer
 * @return     status code
 *             - 0 success
 *             - 2 handle is NULL
 *             - 3 handle is not initialized
 * @note       none
 */
uint8_t max31855_get_last_fault(max31855_handle_t *handle, max31855_fault_t *fault);

/**
 * @}
 */

/**
 * @defgroup max31855_extern_driver max31855 extern driver function
 * @brief    max31855 extern driver modules
 * @ingroup  max31855_driver
 * @{
 */

/**
 * @brief      get the chip register
 * @param[in]  *handle pointer to a max31855 handle structure
 * @param[out] *data pointer to a data buffer
 * @return     status code
 *             - 0 success
 *             - 1 read failed
 *             - 2 handle is NULL
 *             - 3 handle is not initialized
 * @note       none
 */
uint8_t max31855_get_reg(max31855_handle_t *handle, uint32_t *data);

/**
 * @}
 */

/**
 * @}
 */

#ifdef __cplusplus
}
#endif

#endif
