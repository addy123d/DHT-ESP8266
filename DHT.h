/* 
 * DHT Library
 */

/*
 * The MIT License (MIT)
 * Copyright (c) 2022 Aditya Chaudhary and contributors
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 * The above copyright notice and this permission notice shall be included in all
 * copies or substantial portions of the Software.
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, 
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE
*/

#ifndef DHT_H
#define DHT_H

#include "Arduino.h"

/*
 * Sensors this library will cover :
 * DHT11
 * DHT12
 * DHT21
 * DHT22
 * AM2301
 */

static const uint8_t DHT11{11}; /*DHT-11*/
static const uint8_t DHT12{12}; /*DHT-12*/
static const uint8_t DHT21{21}; /*DHT-21*/
static const uint8_t DHT22{22}; /*DHT-22*/
static const uint8_t AM2301{21}; /*AM2301*/

#ifndef microseconds_to_clockcycles
	/*
	 * Formula: clock_cycles = ( (time_in_microseconds) * (SystemCoreClock / 1000000L) )
	 */
	#define microseconds_to_clockcycles(param) ((param) * (SystemCoreClock / 1000000L))
#endif

/*
 * Class which will have all methods, and all data which will store and sensor definition
 */
class DHT{
                
	public:
		DHT(uint8_t pin, uint8_t type);
		void init(uint8_t pulltime_in_usec = 55, bool test=false, uint8_t alert_pin=13);
		void sensor_test(uint8_t alert_pin);
		void indicator(uint8_t alert_pin, int count);

		double getTemperature(bool fahrenheit=false);
		double getKelvin_temperature();

		double getHumidity();

		double heatIndex(double temperature, double humidity);
		double dewPoint();

		double read_sensor(bool temp);
                

	private:
		/*
		 * data[5]: array which will store sensor data
		 * _pin: store the mcu digital pin
		 * _type: sensor number
		 */
		uint8_t data[5], _pin, _type;

		#ifdef __AVR
			/*
			 * Direct IO access for 8 bit AVR.
			 * Directly get access of the port.
			 * Use Bitmasking for digital pin.
			 */
			uint8_t _bit, _port;	
		#endif
		

};

#endif