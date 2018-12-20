
#ifndef LED_master_slave_h
#define LED_master_slave_h

#if ARDUINO >= 100
#include <Arduino.h>
#else
#include <WProgram.h>
#include <wiring.h>
#endif


class LED_slave
{
    public:
        // SETUP 
        LED_slave(int pin);

        // SET  
        void SetFadeFromMaster(byte value,int speedValue,unsigned long startingTime);
        void SetFade(byte value,int speedValue);
        void SetFade(byte value);
        void SetSpeed(int speedValue);
        void SetValue(byte value);
        void Setinverted(bool inverted);
        void SetTimeDelay(long delay);

        bool isFinished();

        // COMMANDS 
        void run();
        void runFor(unsigned long delayValue);

        // FUNCTIONS
        void writeOutput();

    private:

        bool FollowMaster = true;
        int Pin = -1;
        bool invertedPin;

        byte Last_value;
        byte Current_value;
        byte Future_value;
        byte master_Future_value;
        unsigned long starting_time;
        unsigned long master_starting_time;

        long TimeDelay = 0;
        unsigned long Speed = 2000;
        unsigned long master_Speed = 2000;
};


class LED_slave_Master
{
    public:
        // SETUP 
        LED_slave_Master(LED_slave *slaves,int slavescount);
        LED_slave_Master(LED_slave &slaves,int slavescount);
        //LED_slave_Master(LED_slave *slaves,int countslaves);

        // SET  
        void SetFade(byte value,int speedValue);
        void SetFade(byte value);
        void SetSpeed(int speedValue);
        void SetValue(byte value);
        void Setinverted(bool inverted);
        void SetTimeDelay(long delay);

        bool isFinished();

        // COMMANDS 
        void run();
        void runFor(unsigned long delayValue);

    private:
        unsigned long startingTime;
        LED_slave *Slaves;
        int count = 0;
        byte lastValue = 0;
        int lastSpeedValue = 2000;
        
};



#endif 
