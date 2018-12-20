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

#include "LED_master_slave.h"

/******************* SETUP *******************/

LED_slave::LED_slave(int pin)
{
    Pin = pin;
    pinMode(Pin, OUTPUT);
}

/******************* SET *******************/

void LED_slave::SetFadeFromMaster(byte value,int speedValue,unsigned long startingTime)
{
    master_Speed = speedValue;
    //LED_slave::SetSpeed(speedValue);
    //LED_slave::SetFade(value);

    Last_value = Current_value;
    master_Future_value = value;

    starting_time = startingTime;
    FollowMaster = true;
}

void LED_slave::SetFade(byte value,int speedValue)
{
    LED_slave::SetSpeed(speedValue);
    LED_slave::SetFade(value);
    FollowMaster = false;
}

void LED_slave::SetFade(byte value)
{
    FollowMaster = false;
    Last_value = Current_value;
    Future_value = value;
    starting_time = millis();
}

void LED_slave::SetSpeed(int speedValue)
{
    FollowMaster = false;
   /* Last_value = Current_value;
    master_Future_value = value;
    master_starting_time = millis() - master_starting_time;*/
    //fix problem here with different speeds

    Speed = speedValue;
}

void LED_slave::SetValue(byte value)
{
    FollowMaster = false;
    Last_value = value;
    Current_value = value;
    Future_value = value;
    writeOutput();
}

void LED_slave::Setinverted(bool inverted)
{
    invertedPin = inverted;
}

void LED_slave::SetTimeDelay(long delay)
{
    TimeDelay = delay;
}



bool LED_slave::isFinished()
{
    if(FollowMaster == false)
    {
        if(millis()>starting_time+Speed) return true;
    }
    else
    {
        if(millis()>starting_time+master_Speed) return true;
    }
    return false;
}


/******************* COMMANDS *******************/

void LED_slave::run()
{

    if(FollowMaster == false)// || starting_time+Speed > master_starting_time+master_Speed)
    {
        unsigned long diff = millis()-starting_time;
        float PercentFade = double(diff)/double(Speed);
        if(PercentFade>1)
        {
            //FollowMaster = true;
            PercentFade=1;
        }

        Current_value = ((Future_value - Last_value)* PercentFade)+Last_value;
    }
    else
    {
        unsigned long diff = millis()-starting_time;
        float PercentFade = double(diff)/double(master_Speed);
        if(PercentFade>1)
        {
            PercentFade=1;
        }

        Current_value = ((master_Future_value - Last_value)* PercentFade)+Last_value;
    }
    
    writeOutput();
}

void LED_slave::runFor(unsigned long delayValue)
{
    unsigned long currentLocalTime = millis();
    while(currentLocalTime+delayValue>millis())
    {
        LED_slave::run();
    }
}




/******************* FUNCTIONS *******************/

void LED_slave::writeOutput()
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
