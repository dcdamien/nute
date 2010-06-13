#ifndef __COLORTABLE_H_
#define __COLORTABLE_H_

#include <avr/pgmspace.h>

#define COLOR_COUNT    15

prog_uint8_t ColorTable[][3] = {
{0x00, 0x00, 3},
{0x00, 0x00, 18},
{0x00, 0x00, 54},
{0x00, 0x00, 135},
{0x00, 0x00, 255},
{0, 3, 0},
{0, 18, 0},
{0, 54, 0},
{0, 135, 0},
{0, 255, 0},
{3, 0, 0},
{18, 0, 0},
{54, 0, 0},
{135, 0, 0},
{255, 0, 0}
};

#endif
