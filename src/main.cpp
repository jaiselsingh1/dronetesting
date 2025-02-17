#include <Arduino.h>


#include "../include/rc_pilot_reading.h"
#include "../include/motors.h"
#include "../include/rc_pilot.h"
#include "../include/sensor_prelim.h"
#include "../include/controller.h"

Motors motors;
extern RC_PILOT rc;
Controller cntrl;

unsigned long previousMillis = 0;
const long interval = 500;


uint16_t pwm[4] = {MIN_PWM_OUT,MIN_PWM_OUT,MIN_PWM_OUT,MIN_PWM_OUT};
uint16_t MotorDataGCS[4] = {MIN_PWM_OUT,MIN_PWM_OUT,MIN_PWM_OUT,MIN_PWM_OUT};

void setup()
{

    rc_setup();

    pozyx_setup();

    motors.init();

    // thermal_setup();

    pinMode(LED_BUILTIN, OUTPUT);

}


void loop()
{

    digitalWrite(LED_BUILTIN, !digitalRead(LED_BUILTIN));

    rc_reciever_loop();
    // delay(1000);

    if(rc.rc_in.AUX2 > 1500)
    {
      // pwm[0] = rc.rc_in.THR;
      // pwm[1] = rc.rc_in.THR;
      // pwm[2] = rc.rc_in.THR;
      // pwm[3] = rc.rc_in.THR;

      pwm[0] = cntrl.pwmout_3;
      pwm[1] = cntrl.pwmout_0;
      pwm[2] = cntrl.pwmout_2;
      pwm[3] = cntrl.pwmout_1;
    }
    else{
      pwm[0] = MIN_PWM_OUT;
      pwm[1] = MIN_PWM_OUT; 
      pwm[2] = MIN_PWM_OUT;
      pwm[3] = MIN_PWM_OUT;
    } 

    // Serial.print("Pozyx\n");
    pozyx_loop();
    // Serial.print("\n");
    // delay(1000);

    cntrl.controller_loop();

    motors.update(pwm);

    

    unsigned long currentMillis = millis();
    if (currentMillis - previousMillis >= interval) {
        previousMillis = currentMillis;
        cntrl.print();
    }


    // Serial.print("Thermal Camera\n");
    // thermal_loop();
    // Serial.print("\n");
    delay(10);

    
}