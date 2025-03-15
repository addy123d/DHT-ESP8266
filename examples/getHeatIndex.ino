/* 
 * DHT Library For ESP32
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

#include "DHT.h"

#define DHTPIN 2     // Digital pin connected to the DHT sensor

#define DHTTYPE DHT11   // DHT 11


DHT dht(DHTPIN, DHTTYPE);

void setup() {
  // put your setup code here, to runonce:
  Serial.begin(9600);

//  dht.init(55,true,13);
  dht.init();
}

void loop() {
  
  //put your main code here, to run repeatedly:
  float tempIn_Celsius = dht.getTemperature();

  float humidity = dht.getHumidity();   
  float heatIndex = dht.heatIndex(tempIn_Celsius, humidity, false);  


  String HeatIndex_inC = "Heat Index in Celsius: ";
         HeatIndex_inC += heatIndex;
         HeatIndex_inC += " C";
  Serial.println(HeatIndex_inC);

  Serial.println("**********************************************************");
  

  
}
