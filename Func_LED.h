
#ifndef Func_LED_h
#define Func_LED_h

#if ARDUINO >= 100
#include <Arduino.h>
#else
#include <WProgram.h>
#include <wiring.h>
#endif


class Func_LED
{
    public:
        Func_LED *Master;
        Func_LED *Slave;

        // SETUP 
        Func_LED(byte pin);
        Func_LED(Func_LED *master);
        Func_LED(byte pin,Func_LED *master);

        // SET SLAVE 
        void SetSlavesFade(byte value,int speedValue,unsigned long startingTime);
        void SetSlavesFade(byte value,int speedValue);
        void SetSlavesFade(byte value);
        void SetSlavesSpeed(int speedValue);
        void SetSlavesValue(byte value);
        void SetSlavesinverted(bool inverted);
        void SetSlavesTimeDelay(long delay);

        // SET  
        void SetFade(byte value,int speedValue,unsigned long startingTime);
        void SetFade(byte value,int speedValue);
        void SetFade(byte value);
        void SetSpeed(int speedValue);
        void SetValue(byte value);
        void Setinverted(bool inverted);
        void SetTimeDelay(long delay);

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

#endif 
