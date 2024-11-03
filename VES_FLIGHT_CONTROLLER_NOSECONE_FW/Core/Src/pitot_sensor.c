/*
 * PitotSensor.c
 *
 *  Created on: Apr 6, 2024
 *      Author: tommaso
 */

#ifndef PITOTSENSOR_H
#include "pitot_sensor.h"
#endif

uint8_t init_pitot_sensor(pitot_sensor_t *dev, ADC_HandleTypeDef *ADC_handler) {

	uint8_t result = HAL_ERROR;

	if (dev != NULL && ADC_handler != NULL) {
		result = HAL_OK;

		dev -> hadc = ADC_handler;
	}

	return result;
}

uint8_t read_diff_pressure(pitot_sensor_t *dev) {

	uint8_t result = HAL_ERROR;

	HAL_ADC_Start(dev -> hadc);

	if (HAL_ADC_PollForConversion(dev -> hadc, PITOT_SENSOR_TIMEOUT_MS) == HAL_OK) {

		result = HAL_OK;

		dev -> adc_value = HAL_ADC_GetValue(dev -> hadc);

		dev -> diff_pressure = (MAX_DIFF_PRESSURE / 0xFFF) * dev -> adc_value;

	}

	return result;
}
