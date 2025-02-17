#ifndef CONTROLLER_H
#define CONTROLLER_H

// void controller_setup();

#include <cstdint>



class Controller{
private:
    float KD[3] = {1,1,1};
    // float KDI[4] = {0,-0.01,-0.11,-0.04}; This was a test doesn't really work
    float TC[4] = {0,7,54,19}; // Get's rid of the controller biases (messy startup data)
    float TRIM[4] = {0,0.1,0.1,0}; // Front Right, Back Right, Back Left, Front Left
    //Trim for the actuall motors themselves (In order to get it to hover properly)
    
    float c_delf;
	float c_delm0;
	float c_delm1;
	float c_delm2;
    // float delftrim = 0.01;
public:
    float thr_pwm;
    float roll_pwm;
    float pitch_pwm;
    float yaw_pwm;
    float pwmout_0;
    float pwmout_1;
    float pwmout_2;
    float pwmout_3;
    void controller_loop();
    void print();
    void mixer();
};


#endif
