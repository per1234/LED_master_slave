
#ifndef Func_LED_h
#define Func_LED_h

#if ARDUINO >= 100
#include <Arduino.h>
#include <String.h>
#else
#include <WProgram.h>
#include <wiring.h>
#include <String.h>
#endif


class Func_LED
{
    public:
        // SETUP 
        Func_LED(byte pin,String functionString);
        Func_LED(byte pin,byte *sync,String functionString);
        Func_LED(byte pin);
        Func_LED(byte pin,byte *sync);
        void setString(String functionString);
        void setSpeed(byte value);
        void run();
        void delay(unsigned long delayValue);
        void function(byte Count);
        void writeOutput();
        void setinverted(bool inverted);

    private:
        byte Sync;
        byte *SyncCount;
        byte FunctionCount;


        byte Pin;
        byte Last_value;
        byte Current_value;
        byte Future_value;
        String FunctionString;

        unsigned long Speed = 2000;
        unsigned long starting_time;
        bool fade=0;
        bool invertedPin;
};

#endif 
