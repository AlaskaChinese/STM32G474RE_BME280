#ifndef __OLED_H
#define __OLED_H
 
#include "stdlib.h"
#include "stdio.h" 
#include "main.h"
#include "i2c.h"
#include "u8g2.h"

#define OLED_ADDRESS 0x78
uint8_t u8x8_byte_hw_i2c(u8x8_t *u8x8, uint8_t msg, uint8_t arg_int, void *arg_ptr);
extern uint8_t u8x8_gpio_and_delay(u8x8_t *u8x8, uint8_t msg, uint8_t arg_int, void *arg_ptr);
extern void u8g2Init(u8g2_t *u8g2);
void PrintVarFormat(u8g2_t *u8g2, u8g2_uint_t x, u8g2_uint_t y, const uint8_t *font, short var);

#endif