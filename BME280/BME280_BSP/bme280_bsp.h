#ifndef __BME280_BSP_H__
#define __BME280_BSP_H__

#include "stm32g4xx_hal.h"
#include "bme280.h"
#include "bme280_selftest.h"
#include "OLED_U8g2.h"


void print_sensor_data(struct bme280_data *comp_data);

int8_t stream_sensor_data_normal_mode(struct bme280_dev *dev);
	
int8_t stream_sensor_data_forced_mode(struct bme280_dev *dev);

void oled_sensor_data_normal_mode(struct bme280_dev *dev, u8g2_t *u8g2);


#endif
