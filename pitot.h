/*
 * pitot.h
 *
 *  Created on: 19 oct. 2018
 *      Author: alex
 */

#ifndef PITOT_H_
#define PITOT_H_

/**
 * @brief Init the pitot sensor
 * 		  It will start the ADC used to collect data
 */
extern void Pitot_init();

/**
 * @brief calculate the differential pressure
 * @warn getting the value from ADC requires a conversion that can take time
 * @warn The result can have up to 2.5% of error
 * @return the differential pressure in kPa
 */
extern float Pitot_getDiffPressure();

/**
 * @brief calculate the differential pressure with an auto-zero
 * @warn getting the value from ADC requires a conversion that can take time
 * @warn the result may be different if you're using a different sensor (due to factory calibration)
 * @return the differential pressure in kPa
 */
extern float Pitot_getDiffPressureWithAutoZero();

/**
 * @brief calculate the windspeed thanks to differential pressure
 * @warn Conversion from ADC will take a short amount of time
 * @warn The result can have up to 2.5% of error
 * @return the windspeed in m/s
 */
extern float Pitot_getWindSpeed();

#endif /* PITOT_H_ */
