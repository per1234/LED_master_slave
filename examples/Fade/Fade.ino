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