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

LED_slave_Master::LED_slave_Master(LED_slave *slaves,int slavescount) : Slaves(slaves) 
{
    count = slavescount;
}

LED_slave_Master::LED_slave_Master(LED_slave &slaves,int slavescount) : Slaves(&slaves) 
{
    count = slavescount;
}

/******************* SET *******************/


void LED_slave_Master::SetFade(byte value,int speedValue)
{
    lastValue = value;
    lastSpeedValue = speedValue;
    startingTime = millis();
    for(int i = 0;i < count;i++)
    {
        Slaves[i].SetFadeFromMaster(value,speedValue,startingTime);
    }
}

void LED_slave_Master::SetFade(byte value)
{
    LED_slave_Master::SetFade(value,lastSpeedValue);
}

void LED_slave_Master::SetSpeed(int speedValue)
{
    LED_slave_Master::SetFade(lastValue,speedValue);
}

void LED_slave_Master::SetValue(byte value)
{
    for(int i = 0;i < count;i++)
    {
        Slaves[i].SetValue(value);
    }
}

void LED_slave_Master::Setinverted(bool inverted)
{
    for(int i = 0;i < count;i++)
    {
        Slaves[i].Setinverted(inverted);
    }
}

void LED_slave_Master::SetTimeDelay(long delay)
{
    for(int i = 0;i < count;i++)
    {
        Slaves[i].SetTimeDelay(delay);
    }
}



bool LED_slave_Master::isFinished()
{
    if(millis()>startingTime+lastSpeedValue) return true;
    return false;
}


/******************* COMMANDS *******************/

void LED_slave_Master::run()
{
    for(int i = 0;i < count;i++)
    {
        Slaves[i].run();
    }
}

void LED_slave_Master::runFor(unsigned long delayValue)
{
    unsigned long currentLocalTime = millis();
    while(currentLocalTime+delayValue>millis())
    {
        LED_slave_Master::run();
    }
}
