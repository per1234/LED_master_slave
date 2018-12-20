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