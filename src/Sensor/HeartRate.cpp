#include "HeartRate.hpp"
// Global Declaration of this Particle Sensor 
// MAX30105 ParticleSensor;

// ---------------------------------------------------------
const  unsigned int Average_Count = 4;
unsigned int Heartbeat_Array[Average_Count];
unsigned int FirstBeat; 
unsigned int LastBeat;
unsigned int RateSpot = 0;
float BPM; 
unsigned int BPM_AVG; 



uint HeartRate(){
    long IRValue = ParticleSensor.getIR();

    if(checkForBeat(IRValue) == true){

        // heart beat detected 
        long delta = millis() - LastBeat;
        LastBeat = millis();
        BPM = 60 / (delta / 1000.0f);

        if(BPM < 255 && BPM > 20){
            Heartbeat_Array[RateSpot++] = BPM;
            RateSpot %= Average_Count;


            //taking the average 
            BPM_AVG = 0;
            for(uint i = 0; i < Average_Count; i++){
                BPM_AVG += Heartbeat_Array[i];
            BPM_AVG /= Average_Count;
            }
        }

    }


    Serial.print("IR = ");
    Serial.print(IRValue);

    Serial.print(" , BPM = ");
    Serial.print(BPM);

    Serial.print(" , Average BPM = ");
    Serial.print(BPM_AVG);

}