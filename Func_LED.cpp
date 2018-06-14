/**********************************************************************************************
 * Arduino LED Func Library - Version 1.0
 * by William Bailes <williambailes@gmail.com> http://tinkersprojects.com/
 *
 * This Library is licensed under a GPLv3 License
 **********************************************************************************************/

#if ARDUINO >= 100
  #include "Arduino.h"
#else
  #include "WProgram.h"
#endif

#include "Func_LED.h"

/******************* SETUP *******************/

Func_LED::Func_LED(byte pin)
{
    Pin = pin;
    pinMode(Pin, OUTPUT);
    SyncCount = &FunctionCount;
}


Func_LED::Func_LED(byte pin,byte *sync)
{
    Pin = pin;
    pinMode(Pin, OUTPUT);
    SyncCount = sync;
}
Func_LED::Func_LED(byte pin,String functionString)
{
    Pin = pin;
    pinMode(Pin, OUTPUT);
    SyncCount = &FunctionCount;
    FunctionString = functionString;
}


Func_LED::Func_LED(byte pin,byte *sync,String functionString)
{
    Pin = pin;
    pinMode(Pin, OUTPUT);
    SyncCount = sync;
    FunctionString = functionString;
}


/******************* SET *******************/
/*
void Func_LED::SetFade(byte value)
{
    Last_value = Current_value;
    Future_value = value;

    starting_time = millis();
}

void Func_LED::setValue(byte value)
{
    Last_value = value;
    Current_value = value;
    Future_value = value;
    writeOutput();
}*/

void Func_LED::setString(String functionString)
{
    FunctionString = functionString;
}

void Func_LED::setSpeed(byte speedValue)
{
    Speed = speedValue;
}

void Func_LED::setinverted(bool inverted)
{
    invertedPin = inverted;
}


/******************* COMMANDS *******************/

void Func_LED::run()
{
    if(*SyncCount != FunctionCount) Func_LED::function(*SyncCount);
    
    unsigned long diff = millis()-starting_time;
    float PercentFade = double(diff)/double(Speed);
    if(PercentFade>1)
    {
        PercentFade=0;
        Func_LED::function(FunctionCount+1);
    }
    if(fade) Current_value = ((Future_value - Last_value)* PercentFade)+Last_value;
    else Current_value = Future_value;

    writeOutput();
}

void Func_LED::delay(unsigned long delayValue)
{
    unsigned long currentLocalTime = millis();
    while(currentLocalTime+delayValue>millis())
    {
        Func_LED::run();
    }
}

void Func_LED::function(byte Count)
{
    if(FunctionString.length()<=Count)Count = 0;
    if(FunctionString.charAt(Count)>127)
    {
        Future_value = FunctionString.charAt(Count)-128;
        fade = true;
    }
    else
    {
        Future_value = FunctionString.charAt(Count);
        fade = false;
    }

    Last_value = Current_value;
    FunctionCount = Count;
    *SyncCount = Count;
}




/******************* FUNCTIONS *******************/

void Func_LED::writeOutput()
{
    if(invertedPin == true)
    {
        analogWrite(Pin,255-Current_value);
    }
    else
    {
        analogWrite(Pin,Current_value);
    }
}
