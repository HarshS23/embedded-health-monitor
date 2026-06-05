#include "HeartRate.hpp"
#include "initSensor.hpp"
// Global Declaration of this Particle Sensor 
// MAX30105 ParticleSensor;

// ---------------------------------------------------------
static const int AVERAGE_COUNT = 4;
int Heartbeat_Array[AVERAGE_COUNT];
int FirstBeat = 0;
unsigned long LastBeat = 0;
int RateSpot = 0;
float BPM = 0;
unsigned int BPM_AVG = 0;


void HeartRate(){
    long IRValue = ParticleSensor.getIR();

    if(checkForBeat(IRValue) == true){

        // heart beat detected 
        long delta = millis() - LastBeat;
        LastBeat = millis();
        BPM = 60 / (delta / 1000.0f);

        if(BPM < 255 && BPM > 20){
            Heartbeat_Array[RateSpot++] = BPM;
            RateSpot %= AVERAGE_COUNT;


            //taking the average 
            BPM_AVG = 0;
            for(unsigned int i = 0; i < AVERAGE_COUNT; i++){
                BPM_AVG += Heartbeat_Array[i];
            }
            BPM_AVG /= AVERAGE_COUNT;
        }

    }
    Serial.print("IR = ");
    Serial.print(IRValue);

    Serial.print(" , BPM = ");
    Serial.print(BPM);

    Serial.print(" , Average BPM = ");
    Serial.print(BPM_AVG);

    // Reset the IR values if no finger is detected 
    if(IRValue < 20000){
        BPM = 0;
        BPM_AVG = 0;
        RateSpot = 0;

        //clear the array; 

        for(uint i = 0; i < AVERAGE_COUNT; i++){
            Heartbeat_Array[i] = 0;
        }

        Serial.print("\nNo finger detected\n");
    }

    Serial.println();

}