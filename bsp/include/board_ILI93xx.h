/*
 * This file is subject to the terms of the GFX License. If a copy of
 * the license was not distributed with this file, you can obtain one at:
 *
 *              http://ugfx.org/license.html
 */

#ifndef GDISP_LLD_BOARD_H
#define GDISP_LLD_BOARD_H

#include <bsp/display.h>
#include "bsp/display.h"

static GFXINLINE void init_board(GDisplay *g)
{
	(void) g;
}

static GFXINLINE void post_init_board(GDisplay *g)
{
	(void) g;
}

static GFXINLINE void setpin_reset(GDisplay *g, bool_t state)
{
	(void) g;
	(void) state;
}

static GFXINLINE void set_backlight(GDisplay *g, uint8_t percent)
{
	(void) g;
	(void) percent;
}

static GFXINLINE void acquire_bus(GDisplay *g)
{
	(void) g;
}

static GFXINLINE void release_bus(GDisplay *g)
{
	(void) g;
}

static GFXINLINE void write_index(GDisplay *g, uint16_t index)
{
	(void) g;
	(void) index;
	((LCD_TypeDef *) LCD_BASE)->LCD_REG = index;
}

static GFXINLINE void write_data(GDisplay *g, uint16_t data)
{
	(void) g;
	(void) data;
	((LCD_TypeDef *) LCD_BASE)->LCD_RAM = data;
}

static GFXINLINE void setreadmode(GDisplay *g)
{
	(void) g;
}

static GFXINLINE void setwritemode(GDisplay *g)
{
	(void) g;
}

static GFXINLINE uint16_t read_data(GDisplay *g)
{
	(void) g;
	
	return ((LCD_TypeDef *) LCD_BASE)->LCD_RAM;
}

#endif /* GDISP_LLD_BOARD_H */
