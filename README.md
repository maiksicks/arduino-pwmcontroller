# arduino-pwmcontroller
This library can fade PWM pins without blocking your code. No watchdog timers are used.

## Usage
First, include the library in your sketch:
```
#include "PWMController.h"
```

Next, create instances for the pins you want to control:
```
PWMController pwm(3);
```

Now, you need to choose between synchronous or non-blocking mode:

**synchronous mode**
```
void setup() {
  pwm.setSynchronousMode(true);
}

void loop() {
  // pwm.execute(); // do not use this in syncronous mode, it does nothing
}
```

**non-blocking mode**
```
void setup() {
  pwm.setSynchronousMode(false); // optional, false is default
}

void loop() {
  pwm.execute(); // required! execute this as much as possible
}
```

Now you can use the following methods to control your pins:
```
// turn pin high
pwm.on();

// turn pin off
pwm.off();

// set pin to specific value
pwm.set(255);

// fade pin to 50 in 2000 ms
pwm.fade(50, 2000);

// stop current fading
pwm.stop();
```

## Special features

In case you changed the internal TIMER 0 multiplier for higher PWM frequency, millis() and delay() are not working as expected.
In the example below, TIMER 0's multiplier is changed from 64 to 1 and `delay(64 * 1000)` will delay for 1 second.
```
void setup() {
  // ...

  // ATmega328p compatible
  TCCR0B = TCCR0B & B11111000 | B00000001; // pins 5 and 6  => ~64 kHz
  TCCR1B = TCCR1B & B11111000 | B00000001; // pins 9 and 10 => ~32 kHz
  TCCR2B = TCCR2B & B11111000 | B00000001; // pins 3 and 11 => ~32 kHz
  
  // this will fade for 1/64 second
  pwm.fade(255, 1000);
  
  // multiply all durations given by 'fade' with 64
  pwm.setTimingMultiplier(64);
  
  // this will fade for 1 second
  pwm.fade(255, 1000);
  
}
```

In case you changed pwm resolution to 10 bits:
```
void setup() {
  // ...
  
  analogWriteResolution(10);
  pwm.setBitWidth(10);
  
  // now you can specify pwm values in range 0 to 1023
  led.set(1023);
}
```
