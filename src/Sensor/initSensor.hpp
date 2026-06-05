#pragma once  
#ifndef _INIT_SENSOR_
#define  _INIT_SENSOR_

#include <Wire.h>
#include <MAX30105.h>
#include <heartRate.h>

extern MAX30105 ParticleSensor;


void StartSensor();


#endif