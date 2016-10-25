#include "PotentiometerController.h"
void PotentiometerController::setup(){
  int numReady = 0;

  //set up pots
  for(int i = 0; i < NUMPOTS; i++){
    potValues[i] = 0.0;
    if(pots[i].setup(i))
      numReady++;
  }

  // assert all pots are ready
  // if(numReady == NUMPOTS)
  //   startThread();
  // else
  //   cout << "ONLY " << numReady << " POTS READY.  NOT STARTING THREAD." << endl;

}


void PotentiometerController::threadedFunction(){
    while (isThreadRunning()){
      update();
      ofSleepMillis(100);
    }
}

void PotentiometerController::update(){
    hasNewValue = false;

    for(int i = 0; i < NUMPOTS; i++ ){
      pots[i].update();
      //store and flag if change value found
      if(pots[i].didPotChange){
        hasNewValue = true;
        potValues[i] = ofMap( (float)pots[i].lastPotValue, 3.0, 1021.0, 1.0, 0.0, true );
      }
    }

    // if(hasNewValue){
    //   for(int i = 0; i < NUMPOTS; i++)
    //     cout << potValues[i] << "\t";
    //   cout << endl;
    // }

}
