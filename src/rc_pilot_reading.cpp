/***
 * Copyright 2022, The Pennsylvania State University, All Rights Reserved.
 * Unauthorized use and/or redistribution is disallowed.
 * This library is distributed without any warranty; without even
 * the implied warranty of fitness for a particular purpose.
 *
 * Pennsylvania State University Unmanned Aerial System Research Laboratory (PURL)
 * Department of Aerospace Engineering
 * 229 Hammond
 * The Pennsylvania State University
 * University Park, PA 16802
 * http://purl.psu.edu
 *
 * Contact Information:
 * Dr. Thanakorn Khamvilai Email: thanakorn.khamvilai@ttu.edu
 * Dr. Vitor Valente       Email: vitor.valente@psu.edu
 *
 * EndCopyright
 ***/

/*
 Receiver Wiring:
  - Roll     -> Pin A1
  - Pitch    -> Pin A2
  - Throttle -> Pin A3
  - Yaw      -> Pin 6
  - Aux1     -> Pin 8
  - Aux2     -> Pin 1
*/

// #include "wifi.h"
#include "rc_pilot.h"
// #include "datalink.h"
#include "rc_pilot_reading.h"

  RC_PILOT rc;

// unsigned long previousMillis = 0;
// const long interval = 500;

void rc_setup() {

  // initialize wifi
  //WifiSetup();

  // initialize rc
  rc.init();

  // initialize peripherals 
  Serial.begin(115200);
  while (!Serial) {
    ; // wait for serial port to connect. Needed for native USB port only
  }
  pinMode(LED_BUILTIN, OUTPUT);
}

void rc_reciever_loop() {
  digitalWrite(LED_BUILTIN, !digitalRead(LED_BUILTIN));
  
  rc.update();
  //rc.print();
  // unsigned long currentMillis = millis();
  // if (currentMillis - previousMillis >= interval) {
  //   previousMillis = currentMillis;
  //   rc.print(); // should be commented out for flight
  // }

  //readDatalink( &Udp );
  //writeAutopilotDels( &Udp );
  //writeRcChannels( &Udp , &rc );
}
