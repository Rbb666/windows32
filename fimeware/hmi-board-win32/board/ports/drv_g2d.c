/*
 * Copyright (c) 2006-2023, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2022-12-10     Rbb666       the first version
 */
#include <rtthread.h>
#include <lcd_port.h>
#include <stdlib.h>

#include "drv_g2d.h"

#ifdef BSP_USING_G2D

static d2_device *_d2_handle;
static d2_renderbuffer *renderbuffer;

static uint32_t _GetD2Mode(void)
{
    uint32_t r;
    r = d2_mode_rgb565;

    return r;
}

int G2d_Drv_HWInit(void)
{
    d2_s32 d2_err;

    // Initialize D/AVE 2D driver
    //_d2_handle = (d2_device *)rt_malloc(sizeof(_d2_handle));
    _d2_handle = d2_opendevice(0);

    d2_err = d2_inithw(_d2_handle, 0);
    if (d2_err != D2_OK)
    {
        rt_kprintf("Could NOT d2_inithw\n");
        d2_closedevice(_d2_handle);
        return RT_ERROR;
    }

    // Clear both buffers
    d2_framebuffer(_d2_handle,
                   &fb_background[0],
                   480,
                   480,
                   272,
                   (d2_s32) _GetD2Mode());
    d2_clear(_d2_handle, 0x000000);

    // Set various D2 parameters
    d2_setalphablendmode(_d2_handle, d2_bm_one, d2_bm_one_minus_alpha);
    d2_setblendmode(_d2_handle, d2_bm_alpha, d2_bm_one_minus_alpha);

    d2_setalphamode(_d2_handle, d2_am_constant);
    d2_setalpha(_d2_handle, UINT8_MAX);
    d2_setantialiasing(_d2_handle, 1);
    d2_setlinecap(_d2_handle, d2_lc_butt);
    d2_setlinejoin(_d2_handle, d2_lj_miter);

    renderbuffer = d2_newrenderbuffer(_d2_handle, 20, 20);
    if (!renderbuffer)
    {
        rt_kprintf("NO renderbuffer\n");
        d2_closedevice(_d2_handle);
    }

    return RT_EOK;
}
INIT_DEVICE_EXPORT(G2d_Drv_HWInit);

void _GraphicsHWDeInit(void)
{
    // Stop graphics LCD controller
    while (FSP_SUCCESS != R_GLCDC_Stop(g_display0.p_ctrl))
    {
        /* Wait for GLCDC register update to complete before closing driver. */
    }

    R_GLCDC_Close(g_display0.p_ctrl);

    // Deinitialize D/AVE 2D driver
    d2_freerenderbuffer(_d2_handle, renderbuffer);
    d2_deinithw(_d2_handle);
    d2_closedevice(_d2_handle);
}

void LCDCONF_DrawJPEG(int32_t      x,
                      int32_t      y,
                      const void *p,
                      int32_t      xSize,
                      int32_t      ySize)
{
    uint32_t Mode;
    uint32_t ModeSrc;

    Mode    = _GetD2Mode();
    ModeSrc = d2_mode_rgb565;

    // Generate render operations
    d2_framebuffer(_d2_handle,
                   (uint16_t *)&fb_background[0],
                   LCD_WIDTH,
                   LCD_WIDTH,
                   LCD_HEIGHT,
                   (d2_s32) Mode);

    d2_selectrenderbuffer(_d2_handle, renderbuffer);
    d2_cliprect(_d2_handle, 0, 0, LCD_WIDTH, LCD_HEIGHT);
    d2_setblitsrc(_d2_handle, (void *) p, xSize, xSize, ySize, ModeSrc);
    d2_blitcopy(_d2_handle, xSize, ySize, 0, 0, (d2_width)(xSize << 4), (d2_width)(ySize << 4),
                (d2_point)(x << 4), (d2_point)(y << 4), 0);

    // Execute render operations
    d2_executerenderbuffer(_d2_handle, renderbuffer, 0);

    // In single-buffered mode always wait for DRW to finish before returning
    d2_flushframe(_d2_handle);
}
#endif
