#include <Arduino.h>
#include "Sensor/initSensor.hpp"
#include "Sensor/HeartRate.hpp"
#include "Sensor/sp02.hpp"


MAX30105 ParticleSensor;

void setup(){
    
    StartSensor();
    Sp02_Setup();
}

void loop(){
    // this runs during the run time of the mc 
    // it will run until the power is turned off 
    HeartRate();
    RunSp02();


}