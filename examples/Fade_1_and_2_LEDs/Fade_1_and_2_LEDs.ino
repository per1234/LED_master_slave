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