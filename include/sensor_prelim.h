// This file is to make sure that the bootup and setup for any and all sensors is done sequentially,
// does not conflict, and are on separate bauds:

#ifndef SENSOR_PRELIM_h
#define SENSOR_PRELIM_h

void pozyx_setup();
void pozyx_loop();
void thermal_setup();
void thermal_loop();


#endif