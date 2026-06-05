#include <Wire.h>
#include <MAX30105.h>

extern MAX30105 ParticleSensor;

void StartSensor(){
    delay(1000);           
    Serial.begin(115200); // this is baud rate or comunication speed 
    while(!Serial);        
    Serial.println("\n INITLIZING  MAX30105 SENSOR \n");
    Wire.begin(42,41);
    // This just checks if the sensor is found or not 
    if (!ParticleSensor.begin(Wire, I2C_SPEED_FAST)){ // use default I2C Bus, with 400kHz speed 
        Serial.println("ERROR: SENSOR NOT FOUND, CHECK WIRING\n");
       while(1);
    }

    Serial.println("\n SENSOR FOUND\n");

    ParticleSensor.setup(); // this is set to default settings 
    ParticleSensor.setPulseAmplitudeIR(0x0A); // setting IR LED to red 
    ParticleSensor.setPulseAmplitudeGreen(0);

    
}

