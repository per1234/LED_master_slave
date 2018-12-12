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
}


Func_LED::Func_LED(Func_LED *master)
{
    Master = master;
    *Master->Slave = this;
}


Func_LED::Func_LED(byte pin,Func_LED *master)
{
    Func_LED::Func_LED(pin);
    Func_LED::Func_LED(master);
}


/******************* SET SLAVE *******************/

void Func_LED::SetSlavesFade(byte value,int speedValue,unsigned long startingTime)
{
    master_Speed = speedValue;
    Last_value = Current_value;
    master_Future_value = value;
    master_starting_time = startingTime;
    FollowMaster = false;
    if(Slave != NULL) Slave->SetSlavesFade(value,Speed,master_starting_time);
}

void Func_LED::SetSlavesFade(byte value,int speedValue)
{
    master_Speed = speedValue;
    Last_value = Current_value;
    master_Future_value = value;
    master_starting_time = millis();
    FollowMaster = true;
    if(Slave != NULL) Slave->SetSlavesFade(value,Speed,master_starting_time);
}

void Func_LED::SetSlavesFade(byte value)
{
    Last_value = Current_value;
    master_Future_value = value;
    master_starting_time = millis();
    FollowMaster = true;
    if(Slave != NULL) Slave->SetSlavesFade(value,Speed,master_starting_time);
}

void Func_LED::SetSlavesSpeed(int speedValue)
{
   /* Last_value = Current_value;
    master_Future_value = value;
    master_starting_time = millis() - master_starting_time;*/
    //fix problem here with different speeds

    master_Speed = speedValue;
    if(Slave != NULL) Slave->SetSlavesSpeed(speedValue);
}

void Func_LED::SetSlavesValue(byte value)
{
    Last_value = value;
    Current_value = value;
    master_Future_value = value;
    writeOutput();
    FollowMaster = true;
    if(Slave != NULL) Slave->SetSlavesValue(value);
}

void Func_LED::SetSlavesinverted(bool inverted)
{
    invertedPin = inverted;
    if(Slave != NULL) Slave->SetSlavesinverted(inverted);
}

void Func_LED::SetSlavesTimeDelay(long delay)
{
    TimeDelay = delay;
    if(Slave != NULL) Slave->SetSlavesTimeDelay(delay);
}



/******************* SET SLAVE *******************/

void Func_LED::SetFade(byte value,int speedValue,unsigned long startingTime)
{
    Func_LED::SetSpeed(speedValue);
    Func_LED::SetFade(value);
    starting_time = startingTime;
}

void Func_LED::SetFade(byte value,int speedValue)
{
    Func_LED::SetSpeed(speedValue);
    Func_LED::SetFade(value);
}

void Func_LED::SetFade(byte value)
{
    Last_value = Current_value;
    Future_value = value;
    starting_time = millis();
}

void Func_LED::SetSpeed(int speedValue)
{
   /* Last_value = Current_value;
    master_Future_value = value;
    master_starting_time = millis() - master_starting_time;*/
    //fix problem here with different speeds

    Speed = speedValue;
}

void Func_LED::SetValue(byte value)
{
    Last_value = value;
    Current_value = value;
    Future_value = value;
    writeOutput();
}

void Func_LED::Setinverted(bool inverted)
{
    invertedPin = inverted;
}

void Func_LED::SetTimeDelay(long delay)
{
    TimeDelay = delay;
}


/******************* COMMANDS *******************/

void Func_LED::run()
{
    if(Master == NULL || FollowMaster == false || starting_time+Speed > master_starting_time+master_Speed)
    {
        unsigned long diff = millis()-starting_time;
        float PercentFade = double(diff)/double(Speed);
        if(PercentFade>1)
        {
            FollowMaster = true;
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
            PercentFade=0;
        }
        Current_value = ((master_Future_value - Last_value)* PercentFade)+Last_value;
    }
    
    writeOutput();
    if(Slave != NULL) Slave->run();
}

void Func_LED::runFor(unsigned long delayValue)
{
    unsigned long currentLocalTime = millis();
    while(currentLocalTime+delayValue>millis())
    {
        Func_LED::run();
    }
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
