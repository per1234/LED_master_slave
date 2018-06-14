#include <Func_LED.h>

Func_LED LED(8,B10000000+B11111111);

void setup() 
{
}

void loop() 
{
   LED.run();
}