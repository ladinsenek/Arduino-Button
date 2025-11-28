# Arduino Button Library
Simple library for managing buttons on Arduino platforms. Buttons can have either pin as input or boolean value for software buttons. Standart debounce is set to 50ms and is non-blocking. Library is capable of detecting short and long presses.

## Basic Usage
```cpp
#include <Button.h>

void trigger();
void triggerLong();
Button btn(
  BUTTON_PIN,             //Pin for the button
  INPUT_PULLUP,           //Pin mode: INPUT, INPUT_PULLUP  
  Button::FALLING,        //Trigger mode: LOW, HIGH, RISING, FALLING, CHANGE
  trigger,                //Short press callback
  triggerLong,            //Long press callback
  true                    //If long press callback should be called in loop or only triggered once
);

void setup() {
  btn.setDebounce(50);    //Set debound to 50ms (default value is 50 ms)
  btn.setLongTime(1000);  //Set interval for long press detection (default value is 1000 ms)
}

void loop() {
  btn.update();           //Update each tick
}
```
