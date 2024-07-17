#include"bme280_bsp.h"
#include"stdio.h"

u8g2_t u8g2;
/*
In file in bme280_defs.h
In case of the macro "BME280_FLOAT_ENABLE" enabled, The outputs are in double and the units are

- Celsius for temperature
- % relative humidity
- Pascal for pressure
In case if "BME280_FLOAT_ENABLE" is not enabled, then it is

- int32_t for temperature with the units 100 * Celsius
- uint32_t for humidity with the units 1024 * % relative humidity
- uint32_t for pressure
     If macro "BME280_64BIT_ENABLE" is enabled, which it is by default, the unit is 100 * Pascal
     If this macro is disabled, Then the unit is in Pascal
*/
void print_sensor_data(struct bme280_data *comp_data)
{
#ifdef BME280_FLOAT_ENABLE
	printf("temperature:%0.2f*C   pressure:%0.2fhPa   humidity:%0.2f%%\r\n",comp_data->temperature, comp_data->pressure/100, comp_data->humidity);
#else
	printf("temperature:%ld*C   pressure:%ldhPa   humidity:%ld%%\r\n",comp_data->temperature, comp_data->pressure/100, comp_data->humidity);
#endif
}




int8_t stream_sensor_data_normal_mode(struct bme280_dev *dev)
{
	//int8_t rslt;
	uint8_t settings_sel;
	struct bme280_data comp_data;

	/* Recommended mode of operation: Indoor navigation */
	dev->settings.osr_h = BME280_OVERSAMPLING_1X;
	dev->settings.osr_p = BME280_OVERSAMPLING_16X;
	dev->settings.osr_t = BME280_OVERSAMPLING_2X;
	dev->settings.filter = BME280_FILTER_COEFF_16;
	dev->settings.standby_time = BME280_STANDBY_TIME_62_5_MS;

	settings_sel = BME280_OSR_PRESS_SEL;
	settings_sel |= BME280_OSR_TEMP_SEL;
	settings_sel |= BME280_OSR_HUM_SEL;
	settings_sel |= BME280_STANDBY_SEL;
	settings_sel |= BME280_FILTER_SEL;
	//rslt = bme280_set_sensor_settings(settings_sel, dev);
	bme280_set_sensor_settings(settings_sel, dev);
	//rslt = bme280_set_sensor_mode(BME280_NORMAL_MODE, dev);
	bme280_set_sensor_mode(BME280_NORMAL_MODE, dev);

	printf("Temperature           Pressure             Humidity\r\n");
	while (1) {
		/* Delay while the sensor completes a measurement */
		dev->delay_ms(70);
		//rslt = bme280_get_sensor_data(BME280_ALL, &comp_data, dev);
		bme280_get_sensor_data(BME280_ALL, &comp_data, dev);
		print_sensor_data(&comp_data);
	}
	//return rslt;
}


int8_t stream_sensor_data_forced_mode(struct bme280_dev *dev)
{
    //int8_t rslt;
    uint8_t settings_sel;
    struct bme280_data comp_data;

    /* Recommended mode of operation: Indoor navigation */
    dev->settings.osr_h = BME280_OVERSAMPLING_1X;
    dev->settings.osr_p = BME280_OVERSAMPLING_16X;
    dev->settings.osr_t = BME280_OVERSAMPLING_2X;
    dev->settings.filter = BME280_FILTER_COEFF_16;

    settings_sel = BME280_OSR_PRESS_SEL | BME280_OSR_TEMP_SEL | BME280_OSR_HUM_SEL | BME280_FILTER_SEL;

    //rslt = bme280_set_sensor_settings(settings_sel, dev);
	bme280_set_sensor_settings(settings_sel, dev);

    printf("Temperature           Pressure             Humidity\r\n");
    /* Continuously stream sensor data */
    while (1) {
        //rslt = bme280_set_sensor_mode(BME280_FORCED_MODE, dev);
		bme280_set_sensor_mode(BME280_FORCED_MODE, dev);
        /* Wait for the measurement to complete and print data @25Hz */
        dev->delay_ms(40);
        //rslt = bme280_get_sensor_data(BME280_ALL, &comp_data, dev);
		bme280_get_sensor_data(BME280_ALL, &comp_data, dev);
        print_sensor_data(&comp_data);
    }
    //return rslt;
}

void oled_sensor_data_normal_mode(struct bme280_dev *dev, u8g2_t *u8g2)
{
	//int8_t rslt;
	uint8_t settings_sel;
	struct bme280_data comp_data;

	/* Recommended mode of operation: Indoor navigation */
	dev->settings.osr_h = BME280_OVERSAMPLING_1X;
	dev->settings.osr_p = BME280_OVERSAMPLING_16X;
	dev->settings.osr_t = BME280_OVERSAMPLING_2X;
	dev->settings.filter = BME280_FILTER_COEFF_16;
	dev->settings.standby_time = BME280_STANDBY_TIME_62_5_MS;

	settings_sel = BME280_OSR_PRESS_SEL;
	settings_sel |= BME280_OSR_TEMP_SEL;
	settings_sel |= BME280_OSR_HUM_SEL;
	settings_sel |= BME280_STANDBY_SEL;
	settings_sel |= BME280_FILTER_SEL;
	//rslt = bme280_set_sensor_settings(settings_sel, dev);
	bme280_set_sensor_settings(settings_sel, dev);
	//rslt = bme280_set_sensor_mode(BME280_NORMAL_MODE, dev);
	bme280_set_sensor_mode(BME280_NORMAL_MODE, dev);

	/* Delay while the sensor completes a measurement */
	dev->delay_ms(70);
	//rslt = bme280_get_sensor_data(BME280_ALL, &comp_data, dev);
	bme280_get_sensor_data(BME280_ALL, &comp_data, dev);

	print_sensor_data(&comp_data);
	u8g2_SetFont(u8g2,u8g2_font_ncenB08_tf);
    u8g2_DrawUTF8(u8g2,0,15, "Temp:       C");
    u8g2_DrawCircle(u8g2, 52, 8, 2, U8G2_DRAW_ALL);//¥Ú”°°Ê
    u8g2_DrawStr(u8g2,0,30, "Press:         Pa");
    u8g2_DrawUTF8(u8g2,0,45, "Hum:       %");
	PrintVarFormat(u8g2, 30, 15, u8g2_font_ncenB08_tf, comp_data.temperature);
	PrintVarFormat(u8g2, 33, 30, u8g2_font_ncenB08_tf, comp_data.pressure/100);
	PrintVarFormat(u8g2, 30, 45, u8g2_font_ncenB08_tf, comp_data.humidity);
    u8g2_SendBuffer(u8g2);
	//return rslt;
}
