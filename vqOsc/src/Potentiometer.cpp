#include "Potentiometer.h"
Potentiometer::Potentiometer(){
    isReady = false;
    didPotChange = false;
    lastPotValue = 0;
    potValue = 0;
    //10k trim pot connected to adc #0
    potentiometerInput = 0;
    currentAverageIndex = 0;

    for(int i = 0; i < avgSize; i++)
        lastPotValues[i] = 0;

    lastPotAverageValue = 0;
}



bool Potentiometer::setup( int i ){
    int status = wiringPiSPISetup(0, 1000000);
    if (status != -1){
        ofLogVerbose() << "wiringPiSetup PASS";
        isReady = true;
    }else
        ofLogError() << "wiringPiSetup FAIL status: " << status;

    potentiometerInput = i;
    return isReady;
}

void Potentiometer::update(){
        didPotChange = false;

        //dummy read to stabalize reading
        readAnalogDigitalConvertor();
        readAnalogDigitalConvertor();
        potValue = readAnalogDigitalConvertor();

        //only read if no change
        if( potValue != lastPotValue ){
          didPotChange = true;

          //wrap index to store value
          if( ++currentAverageIndex >= avgSize )
              currentAverageIndex = 0;

          lastPotValues[currentAverageIndex] = lastPotValue;

          int lastValuesTotal = 0;
          int tMin = lastPotValues[0];
          int tMax = lastPotValues[0];
          for( int i = 0; i < avgSize; i++ ){
              lastValuesTotal += lastPotValues[i];

              if(lastPotValues[i] < tMin)
                tMin = lastPotValues[i];
              if(lastPotValues[i] > tMax)
                tMax = lastPotValues[i];
          }

          //remove highest and lowest value from average
          lastPotAverageValue = (lastValuesTotal - (tMin + tMax)) / avgSize;
          lastPotValue = potValue;
        }
}



int  Potentiometer::readAnalogDigitalConvertor(){
    uint8_t buffer[3];

    buffer[0] = 1;
    buffer[1] = (8+potentiometerInput)<<4;
    buffer[2] = 0;

    wiringPiSPIDataRW(0, buffer, 3);

    return ((buffer[1]&3) << 8) + buffer[2];
}
