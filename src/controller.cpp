#include "../include/controller.h"
#include "../include/rc_pilot.h"
#include "../include/sensors.h"

#define MIN_PWM 900
#define MAX_PWM 1900
#define LIMIT(x,xl,xu) ((x)>=(xu)?(xu):((x)<(xl)?(xl):(x)))

extern RC_PILOT rc;
extern Sensors sens;



// void controller_setup(){

// }

void Controller::controller_loop() {
    // Normalize the input values to [-1, 1]
    // c_delf  = (rc.rc_in.THR - 1500) / 500.0 - delftrim;
    // c_delm0 = (rc.rc_in.ROLL - 1500) / 500.0 - KD[0] * sens.data.gyr[1];
    // c_delm1 = (rc.rc_in.PITCH - 1500) / 500.0 - KD[1] * sens.data.gyr[2];
    // c_delm2 = (rc.rc_in.YAW - 1500) / 500.0 - KD[2] * sens.data.gyr[3];

    c_delf  = ((static_cast<int>(rc.rc_in.THR) + TC[0] - 1500) / 500.0 - KD[0]) + TRIM[0];
    c_delm0 = ((static_cast<int>(rc.rc_in.ROLL) + TC[1] - 1500) / 500.0 - KD[1] * sens.data.gyr[1]) + TRIM[1];
    c_delm1 = ((static_cast<int>(rc.rc_in.PITCH) + TC[2] - 1500) / 500.0 - KD[2] * sens.data.gyr[2]) + TRIM[2];
    c_delm2 = ((static_cast<int>(rc.rc_in.YAW) + TC[3] - 1500) / 500.0 - KD[3] * sens.data.gyr[3]) + TRIM[3] ;


    // c_delf  = rc.rc_in.THR;
    // c_delm0 = rc.rc_in.ROLL - KD[0] * sens.data.gyr[1];
    // c_delm1 = rc.rc_in.PITCH - KD[1] * sens.data.gyr[2];
    // c_delm2 = rc.rc_in.YAW - KD[2] * sens.data.gyr[3];
    mixer();
}

void Controller::print(){
    Serial.print(rc.rc_in.THR);
    Serial.print(", ");
    Serial.print(rc.rc_in.ROLL);
    Serial.print(", ");
    Serial.print(rc.rc_in.PITCH);
    Serial.print(", ");
    Serial.print(rc.rc_in.YAW); 
    Serial.print("\n");

    Serial.print(c_delf);
    Serial.print(", ");
    Serial.print(c_delm0);
    Serial.print(", ");
    Serial.print(c_delm1);
    Serial.print(", ");
    Serial.print(c_delm2); 
    Serial.print("\n");

    Serial.print(thr_pwm);
    Serial.print(", ");
    Serial.print(roll_pwm);
    Serial.print(", ");
    Serial.print(pitch_pwm);
    Serial.print(", ");
    Serial.print(yaw_pwm); 
    Serial.print("\n");

    Serial.print(pwmout_0);
    Serial.print(", ");
    Serial.print(pwmout_1);
    Serial.print(", ");
    Serial.print(pwmout_2);
    Serial.print(", ");
    Serial.print(pwmout_3);
    Serial.print("\n");

}

void Controller::mixer(){
    		// only throttle and roll
		thr_pwm = ( c_delf - ( -1 ) ) * ( 2000 - 1000 ) / ( 1 - ( -1 ) ) + 1000; // from [-1,1] to [1000,2000]
		roll_pwm = ( c_delm0 - ( -1 ) ) * ( 500 - ( -500 ) ) / ( 1 - ( -1 ) ) + ( -500 ); // from [-1,1] to [-500,500]
		pitch_pwm = ( c_delm1 - ( -1 ) ) * ( 500 - ( -500 ) ) / ( 1 - ( -1 ) ) + ( -500 ); // from [-1,1] to [-500,500]
		yaw_pwm = ( c_delm2 - ( -1 ) ) * ( 500 - ( -500 ) ) / ( 1 - ( -1 ) ) + ( -500 ); // from [-1,1] to [-500,500]

        // float thr_pwm = c_delf;
		// float roll_pwm = c_delm0;
		// float pitch_pwm = c_delm1;
		// float yaw_pwm = c_delm2;

		pwmout_0 = ( unsigned short ) LIMIT( thr_pwm - roll_pwm - pitch_pwm + yaw_pwm, MIN_PWM, MAX_PWM ) - 100; // front-right CW
		pwmout_1 = ( unsigned short ) LIMIT( thr_pwm - roll_pwm + pitch_pwm - yaw_pwm, MIN_PWM, MAX_PWM ) - 100; // back-right  CCW
		pwmout_2 = ( unsigned short ) LIMIT( thr_pwm + roll_pwm + pitch_pwm + yaw_pwm, MIN_PWM, MAX_PWM ) - 100; // back-left   CW
		pwmout_3 = ( unsigned short ) LIMIT( thr_pwm + roll_pwm - pitch_pwm - yaw_pwm, MIN_PWM, MAX_PWM ) - 100; // front-left CCW


}