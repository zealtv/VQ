#include "Pui.h"

//--------------------------------------------------------------
void Pui::setup()
{

	
	//SET UP WIRINGPI
	if( wiringPiSetup() == -1 ) cout << "WiringPiSetup Failed!" << endl;
	else cout << "WiringPiSetup() Succeeded!" << endl;

	//SETUP POTENTIOMETERS
	for( int i = 0; i < 8; i++ )
	{
		potController[i].setup( i );  
	}


	//SETUP LED
	pinMode( 0,OUTPUT );
	pinMode( 2,OUTPUT );
	pinMode( 3,OUTPUT );

	boolLedR = false;
	boolLedG = false;
	boolLedB = false;

	//turn off LED
	digitalWrite( 0, 1 );
	digitalWrite( 2, 1 );
	digitalWrite( 3, 1 );



	//SETUP BUTTONS
	pinMode( 4, INPUT );
	pullUpDnControl( 4, PUD_UP ); //switch on internal pull up resistor
	pinMode( 5, INPUT );
	pullUpDnControl( 5, PUD_UP ); //switch on internal pull up resistor
	pinMode( 6, INPUT );
	pullUpDnControl( 6, PUD_UP ); //switch on internal pull up resistor  
	pinMode( 7, INPUT );
	pullUpDnControl( 7, PUD_UP ); //switch on internal pull up resistor
	pinMode( 8, INPUT );  // has built in pull up resistor
	pinMode( 9, INPUT );  // has built in pull up resistor
    

	for( int i = 0; i < 6; i++ )
	{
		buttonLastState[i] = false;
		buttonTimePressed[i] = 0.0;
		buttonTimeReleased[i] = 0.0;
		buttonCheckLongPress[i] = true;
	}
	
}

//--------------------------------------------------------------
void Pui::update()
{
	updateButtons();
}

//--------------------------------------------------------------
void Pui::close()
{
	setLed( 0, 0, 0 );
}


//--------------------------------------------------------------
void Pui::getParams(float params[])
{
	for( int i = 0; i < 8; i++ )
	{
		if( potController[i].didFilteredPotChange ) 
		{

			float currentValue = ofMap( (float)potController[i].lastPotValue, 3.0, 1021.0, 0.0, 1.0, true );
			if( doInvertPots ) currentValue = 1.0 - currentValue;

			params[i] = currentValue;
		}
	}
}


//--------------------------------------------------------------
void Pui::updateButtons(){


	//read buttons
	for( int i = 0; i < 6; i++ )
	{
		buttonCurrentState[i] = digitalRead( i + 4 );
	}


	//check for long presses
	for( int i = 0; i < 6; i++ )
	{

		if( buttonLastState[i] == 0 && buttonCurrentState[i] == 0 && buttonCheckLongPress[i] )
		{
			//compare current time and previous time
		    if( ofGetElapsedTimeMillis() - buttonTimePressed[i] > 1000.0 )
		    {
		    	controllable->buttonLongPress( i );
		    	masterControllable->buttonLongPress( i );
				buttonCheckLongPress[i] = false;
		    }
		}


		//check for press and releases
		if( buttonCurrentState[i] != buttonLastState[i] )    
		{ 
			//press 
			if( buttonCurrentState[i] == 0 )
			{
				controllable->buttonPress( i );
				masterControllable->buttonPress( i );				

				//start timer
				buttonTimePressed[i] = ofGetElapsedTimeMillis();

			}

			//release
			else 
			{
				controllable->buttonRelease( i );
				masterControllable->buttonRelease( i );				
				buttonCheckLongPress[i] = true;
			}

			//save current state into last state
			buttonLastState[i] = buttonCurrentState[i];
		}


	}

}


//--------------------------------------------------------------
void Pui::setLed( bool r, bool g, bool b)
{
	digitalWrite(0, !r);
    digitalWrite(2, !g);
    digitalWrite(3, !b);

}


//--------------------------------------------------------------
void Pui::setControllable( Controllable *c )
{
	controllable = c;
}

void Pui::setMasterControllable( Controllable *c )
{
	masterControllable = c;
}

