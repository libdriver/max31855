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
 * @file      driver_max31855.c
 * @brief     driver max31855 source file
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

#include "driver_max31855.h"

/**
 * @brief chip information definition
 */
#define CHIP_NAME                 "Maxim Integrated max31855"       /**< chip name */
#define MANUFACTURER_NAME         "Maxim Integrated"                /**< manufacturer name */
#define SUPPLY_VOLTAGE_MIN        3.0f                              /**< chip min supply voltage */
#define SUPPLY_VOLTAGE_MAX        3.6f                              /**< chip max supply voltage */
#define MAX_CURRENT               1.5f                              /**< chip max current */
#define TEMPERATURE_MIN           -20.0f                            /**< chip min operating temperature */
#define TEMPERATURE_MAX           125.0f                            /**< chip max operating temperature */
#define DRIVER_VERSION            1000                              /**< driver version */

/**
 * @brief      read bytes
 * @param[in]  *handle pointer to a max31855 handle structure
 * @param[out] *data pointer to a data buffer
 * @return     status code
 *             - 0 success
 *             - 1 spi read failed
 * @note       none
 */
static uint8_t a_max31855_spi_read(max31855_handle_t *handle, uint32_t *data)
{
    uint8_t buf[4];
    
    if (handle->spi_read_cmd(buf, 4) != 0)          /* spi read */
    {
        return 1;                                   /* return error */
    }
    else
    {
        *data = (((uint32_t)buf[0]) << 24) |
                (((uint32_t)buf[1]) << 16) | 
                (((uint32_t)buf[2]) << 8) |
                (((uint32_t)buf[3]) << 0);          /* get the data */
        
        return 0;                                   /* success return 0 */
    }
}

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
uint8_t max31855_init(max31855_handle_t *handle)
{
    uint32_t data;
    
    if (handle == NULL)                                                 /* check handle */
    {
        return 2;                                                       /* return error */
    }
    if (handle->debug_print == NULL)                                    /* check debug_print */
    {
        return 3;                                                       /* return error */
    }
    if (handle->spi_init == NULL)                                       /* check spi_init */
    {
        handle->debug_print("max31855: spi_init is null.\n");           /* spi_init is null */
       
        return 3;                                                       /* return error */
    }
    if (handle->spi_deinit == NULL)                                     /* check spi_deinit */
    {
        handle->debug_print("max31855: spi_deinit is null.\n");         /* spi_deinit is null */
       
        return 3;                                                       /* return error */
    }
    if (handle->spi_read_cmd == NULL)                                   /* check spi_read_cmd */
    {
        handle->debug_print("max31855: spi_read_cmd is null.\n");       /* spi_read_cmd is null */
       
        return 3;                                                       /* return error */
    }
    if (handle->delay_ms == NULL)                                       /* check delay_ms */
    {
        handle->debug_print("max31855: delay_ms is null.\n");           /* delay_ms is null */
       
        return 3;                                                       /* return error */
    }
    
    if (handle->spi_init() != 0)                                        /* spi init */
    {
        handle->debug_print("max31855: spi init failed.\n");            /* spi init failed */
        
        return 1;                                                       /* return error */
    }
    if (a_max31855_spi_read(handle, &data) != 0)                        /* read data */
    {
        handle->debug_print("max31855: read data failed.\n");           /* read data failed */
       
        return 1;                                                       /* return error */
    }
    
    handle->fault = 0x00;                                               /* init none */
    handle->inited = 1;                                                 /* flag finish initialization */
    
    return 0;                                                           /* success return 0 */
}

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
uint8_t max31855_deinit(max31855_handle_t *handle)
{
    uint8_t res;
    
    if (handle == NULL)                                              /* check handle */
    {
        return 2;                                                    /* return error */
    }
    if (handle->inited != 1)                                         /* check handle initialization */
    {
        return 3;                                                    /* return error */
    }
    
    res = handle->spi_deinit();                                      /* spi deinit */
    if (res != 0)                                                    /* check result */
    {
        handle->debug_print("max31855: spi deinit failed.\n");       /* spi deinit failed */
       
        return 1;                                                    /* return error */
    }
    handle->inited = 0;                                              /* flag close */
    
    return 0;                                                        /* success return 0 */
}

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
uint8_t max31855_get_last_fault(max31855_handle_t *handle, max31855_fault_t *fault)
{
    if (handle == NULL)                                /* check handle */
    {
        return 2;                                      /* return error */
    }
    if (handle->inited != 1)                           /* check handle initialization */
    {
        return 3;                                      /* return error */
    }
    
    *fault = (max31855_fault_t)(handle->fault);        /* set last fault */
    
    return 0;                                          /* success return 0 */
}

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
                      int16_t *reference_junction_raw, float *reference_junction_temp)
{
    uint8_t res;
    uint32_t data;
    uint16_t d1;
    uint16_t d0;
    
    if (handle == NULL)                                                       /* check handle */
    {
        return 2;                                                             /* return error */
    }
    if (handle->inited != 1)                                                  /* check handle initialization */
    {
        return 3;                                                             /* return error */
    }
    
    res = a_max31855_spi_read(handle, &data);                                 /* read data */
    if (res != 0)                                                             /* check result */
    {
        handle->debug_print("max31855: read data failed.\n");                 /* read data failed */
       
        return 1;                                                             /* return error */
    }
    d1 = (data >> 16) & 0xFFFFU;                                              /* get d1 */
    d0 = (data >> 0) & 0xFFFFU;                                               /* get d0 */
    if ((d1 & 0x01) != 0)                                                     /* check fault */
    {
        handle->debug_print("max31855: find fault.\n");                       /* find fault */
        handle->fault = d0 & 0x07;                                            /* save fault */
        
        return 4;                                                             /* return error */
    }
    if ((d1 >> 15) != 0)                                                      /* check sign bit */
    {
        *thermocouple_raw = (int16_t)((d1 >> 2) | 0xC000U);                   /* set raw data */
    }
    else
    {
        *thermocouple_raw = (int16_t)(d1 >> 2);                               /* set raw data */
    }
    *thermocouple_temp = (float)(*thermocouple_raw) * 0.25f;                  /* convert data */
    if ((d0 >> 15) != 0)                                                      /* check sign bit */
    {
        *reference_junction_raw = (int16_t)((d1 >> 4) | 0xF000U);             /* set raw data */
    }
    else
    {
        *reference_junction_raw = (int16_t)(d0 >> 4);                         /* set raw data */
    }
    *reference_junction_temp = (float)(*reference_junction_raw) * 0.0625f;    /* convert data */
    
    return 0;                                                                 /* success return 0 */
}

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
uint8_t max31855_get_reg(max31855_handle_t *handle, uint32_t *data)
{
    if (handle == NULL)                            /* check handle */
    {
        return 2;                                  /* return error */
    }
    if (handle->inited != 1)                       /* check handle initialization */
    {
        return 3;                                  /* return error */
    }
    
    return a_max31855_spi_read(handle, data);      /* read data */
}

/**
 * @brief      get chip's information
 * @param[out] *info pointer to a max31855 info structure
 * @return     status code
 *             - 0 success
 *             - 2 handle is NULL
 * @note       none
 */
uint8_t max31855_info(max31855_info_t *info)
{
    if (info == NULL)                                               /* check handle */
    {
        return 2;                                                   /* return error */
    }
    
    memset(info, 0, sizeof(max31855_info_t));                       /* initialize max31855 info structure */
    strncpy(info->chip_name, CHIP_NAME, 32);                        /* copy chip name */
    strncpy(info->manufacturer_name, MANUFACTURER_NAME, 32);        /* copy manufacturer name */
    strncpy(info->interface, "SPI", 8);                             /* copy interface name */
    info->supply_voltage_min_v = SUPPLY_VOLTAGE_MIN;                /* set minimal supply voltage */
    info->supply_voltage_max_v = SUPPLY_VOLTAGE_MAX;                /* set maximum supply voltage */
    info->max_current_ma = MAX_CURRENT;                             /* set maximum current */
    info->temperature_max = TEMPERATURE_MAX;                        /* set minimal temperature */
    info->temperature_min = TEMPERATURE_MIN;                        /* set maximum temperature */
    info->driver_version = DRIVER_VERSION;                          /* set driver version */
    
    return 0;                                                       /* success return 0 */
}
