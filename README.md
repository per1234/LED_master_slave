# LED_master_slave (not tested, working progress)
[https://tinkersprojects.com/](https://tinkersprojects.com/)

This is a LED Fadding control library for Arduino. Each LED can be controlled individually or by its master LED.   

This library has not been tested, there will be a few bugs thoughout it. If you wish to use this library, it will be tested and complete soon.


## Master Functions
### SETUP
#### LED_slave_Master(LED_slave *slaves,int slavescount)

### SET 
#### void SetFade(byte value,int speedValue)
This function is used to fade from the current set value to a different value. Value is used to set the fade. The value Byte variable are the value between 0 and 255. 0 is the LED completely off, 255 is the LED Completely on and all values between is a PWM percent. The speedValue is in milliseconds and is used from the start to the finish of the fade.

#### void SetFade(byte value)
This function is used to fade from the current set value to a different value. Value is used to set the fade. The value Byte variable are the value between 0 and 255. 0 is the LED completely off, 255 is the LED Completely on and all values between is a PWM percent.

#### void SetSpeed(int speedValue)
This Functions sets the speed of fades and the speed of colour functions. The speedValue is in milliseconds and is used from the start to the finish of the fade.

#### void SetValue(byte value)
#### void Setinverted(bool inverted)
#### void SetTimeDelay(long delay)

### SET 
#### bool isFinished()
#### void run()
#### void runFor(unsigned long delayValue)
  
  
## Slave Functions
### SETUP
#### LED_slave(int pin)

### SET 
#### void SetFadeFromMaster(byte value,int speedValue,unsigned long startingTime)
#### void SetFade(byte value,int speedValue)
#### void SetFade(byte value)
#### void SetSpeed(int speedValue)
#### void SetValue(byte value)
#### void Setinverted(bool inverted)
#### void SetTimeDelay(long delay)

### SET 
#### bool isFinished()
#### void run()
#### void runFor(unsigned long delayValue)
### void writeOutput()
  



## Example
### Example 1:  3 LED fade

```c++
#include <LED_master_slave.h>

LED_slave LEDs[] = {
   LED_slave(4),
   LED_slave(9),
   LED_slave(10)
};

LED_slave_Master LEDMaster(LEDs,3);

void setup() 
{
   LEDMaster.SetFade(255,10000);
}

void loop() 
{
   LEDMaster.run();
}
```

### Example 2: 3 LED Different Fade

```c++
include <LED_master_slave.h>

LED_slave LEDs[] = {
   LED_slave(4),
   LED_slave(9),
   LED_slave(10)
};

LED_slave_Master LEDMaster(LEDs,3);

void setup() 
{
   LEDMaster.SetFade(255,10000);
   LEDs[1].SetFade(255,2000);
}

void loop() 
{
   LEDMaster.run();
   if(LEDs[1].isFinished())
   {
      LEDs[1].SetFade(0,2000);
   }
}
```

### Example 3: Slave control

```c++
#include <LED_master_slave.h>

LED_slave LED(4);

void setup() 
{
   LED.SetFade(255,2000);
}

void loop() 
{
   LED.run();
}
```

## To Do list
- 
