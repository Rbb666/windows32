#ifndef __DRV_G2D_H__
#define __DRV_G2D_H__

#include <rtthread.h>
#include "hal_data.h"

void LCDCONF_DrawJPEG(int32_t      x,
                      int32_t      y,
                      const void *p,
                      int32_t      xSize,
                      int32_t      ySize);

#ifdef PKG_USING_LVGL
#include "lvgl.h"
void lv_port_gpu_blit(int32_t      x,
                      int32_t      y,
                      const void  *p,
                      const lv_area_t *area);
#endif
#endif
