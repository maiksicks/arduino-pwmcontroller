#ifndef PWM_CONTROLLER_H
#define PWM_CONTROLLER_H

#include <Arduino.h>

class PWMController {

  public:
  
    /**
     * Constructor.
     * 
     * @param _pin  Arduino-based pin (with pwm support).
     */
    PWMController(uint8_t _pin);

    /**
     * Setter: Synchronous (blocking) mode. (default: false)
     * When enabled, 'fade' will act as delay until fading has finished.
     * Method 'execute()' not required.
     */
    void setSynchronousMode(bool _synchronous);

    /**
     * Setter: Invert pwm output. (default: false)
     */
    void setInvert(bool _invert);

    /**
     * Setter: Set timing multiplier. (default: 1)
     * Change multiplier, if you adjusted TIMER 0.
     */
    void setTimingMultiplier(uint16_t _timing_multiplier);

    /**
     * Setter: Set pwm bit width. (default: 8)
     * Change bit width, if you adjusted pwm bit width.
     */
    void setBitWidth(uint8_t _bit_width);

    /**
     * Turn pwm output high.
     */
    void on();

    /**
     * Turn pwm output low.
     */
    void off();

    /**
     * Set pwm to a specified value.
     */
    void set(uint16_t _value);

    /**
     * Fade pwm output to a specified value in a specified duration.
     */
    void fade(uint16_t _value, uint32_t _duration);

    /**
     * Stop all animations (e.g. fading).
     */
    void stop();

    /**
     * Calculate current pwm output from animation state.
     * Only required, if synchronous mode disabled.
     * 
     * Put this inside your loop().
     */
    void execute();

  private:

    bool synchronous = false;
    uint8_t pin = 0;
    bool invert = false;
    uint16_t timing_multiplier = 1;
    
    uint8_t bit_width = 8;
    uint16_t max_value = 255;

    uint16_t value = 0;

    bool animation_running = false;
    
    uint32_t animation_time_start = 0;
    uint32_t animation_time_current = 0;
    uint32_t animation_time_total = 0;
    
    uint16_t animation_value_start = 0;
    int32_t animation_value_diff = 0;
    uint16_t animation_value_end = 0;

    uint32_t getCurrentTime();
    void setPin(uint16_t _value);
};


#endif
