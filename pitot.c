/*
 * pitot.c
 *
 *  Created on: 19 oct. 2018
 *      Author: alex
 */
#include "pitot.h"
#include "stm32f4xx_hal.h"
#include <math.h>

#ifndef fmax
	#define fmax( a, b ) ( ((a) > (b)) ? (a) : (b) )
#endif

#define POLL_TIMEOUT 10
#define ADC_5V_VALUE 6206.0f //5V equivalent
#define PITOT_OFFSET 0.13f //kPa
#define DENSITY 1.293f //air density kg/m3
/**
 * @brief adc used for pitot sensor
 * 		  Defined in main.c
 */
extern ADC_HandleTypeDef hadc1;

void Pitot_init()
{
	HAL_ADC_Start (&hadc1);
}

float Pitot_getDiffPressure()
{
	uint32_t value;
	float diff_pressure;
	HAL_ADC_PollForConversion (&hadc1, POLL_TIMEOUT);
	value = HAL_ADC_GetValue (&hadc1);
	//using transfer function form datasheet
	diff_pressure = (value/ADC_5V_VALUE - 0.2)/0.2;//6206 is the 5V equivalent
	return diff_pressure;
}

float Pitot_getDiffPressureWithAutoZero()
{
	float diff_pressure;
	diff_pressure = Pitot_getDiffPressure() - PITOT_OFFSET;
	return diff_pressure;
}

float Pitot_getWindSpeed()
{
	float windspeed, diff_pressure;
	diff_pressure = Pitot_getDiffPressureWithAutoZero();
	windspeed = sqrt ( (2.0 * fmax(diff_pressure, 0) * 1000.0)/DENSITY);
	return windspeed;
}
