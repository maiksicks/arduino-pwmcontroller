#include "PWMController.h"

PWMController::PWMController(uint8_t _pin) {
  pin = _pin;
  pinMode(pin, OUTPUT);
}

void PWMController::setSynchronousMode(bool _synchronous) {
  synchronous = _synchronous;
}

void PWMController::setInvert(bool _invert) {
  invert = _invert;
}

void PWMController::setTimingMultiplier(uint16_t _timing_multiplier) {
  timing_multiplier = _timing_multiplier;
}

void PWMController::setBitWidth(uint8_t _bit_width) {
  bit_width = _bit_width;
  max_value = pow(2, bit_width) - 1;
}

void PWMController::on() {
  set(max_value);
}

void PWMController::off() {
  set(0);
}

void PWMController::set(uint16_t _value) {

  animation_running = false;
  
  if (_value > max_value) {
    _value = max_value;
  }
  
  setPin(_value);
  
}

void PWMController::fade(uint16_t _value, uint32_t _duration) {
  if (_value > max_value) {
    _value = max_value;
  }

  if (_duration == 0) {
    set(_value);
    return;
  }

  animation_time_start = getCurrentTime();
  animation_time_current = 0;
  animation_time_total = _duration;

  animation_value_start = value;
  animation_value_diff = (int32_t) _value - (int32_t) value;
  animation_value_end = _value;
  
  animation_running = true;

  if (synchronous) {
    while (animation_running) {
      execute();
      delay(1 * timing_multiplier);
    }
  }
}

void PWMController::stop() {
  animation_running = false;
}

void PWMController::execute() {
  if (animation_running) {

    // get animation time elapsed
    animation_time_current = getCurrentTime() - animation_time_start;

    if (animation_time_current < animation_time_total) {

      // prevent float (=> slow) using factor 1000
      int32_t progress = (1000 * animation_time_current) / animation_time_total; 
  
      // calculate new value ()
      setPin(animation_value_start + ((animation_value_diff * progress) / 1000));

    } else {
      animation_running = false;
      setPin(animation_value_end);
    }

  }
}

uint32_t PWMController::getCurrentTime() {
  return (millis() / timing_multiplier);
}

void PWMController::setPin(uint16_t _value) {

  
  
  value = _value;
  if (invert) {
    analogWrite(pin, max_value - value);
  } else {
    analogWrite(pin, value);
  }
} 
