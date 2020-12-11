#include "PWMController.h"

// create instance on pin 3 (pwm)
PWMController pwm(3);

void setup() {

  // run in synchronous (blocking) mode
  pwm.setSynchronousMode(true);

  // turn pwm off
  pwm.off();

}

void loop() {

  // fade to maximum (255) in 500 ms
  pwm.fade(255, 500);

  // fade to 0 in 500 ms
  pwm.fade(0, 500);
  
}
