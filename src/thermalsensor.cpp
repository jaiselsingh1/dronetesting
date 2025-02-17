
#include "../include/thermalsensor.h"

Adafruit_MLX90640 mlx;
float frame[32*24]; // buffer for full frame of temperatures

void thermal_setup() {
    Wire.begin(); 

    if (!mlx.begin(MLX90640_I2CADDR_DEFAULT, &Wire)) {
    Serial.println("MLX90640 not found! Check your wiring:"); }

    Serial.println("MLX90640 initialized successfully!");
  
    // Set basic configuration
    mlx.setMode(MLX90640_CHESS);
    mlx.setResolution(MLX90640_ADC_18BIT);
    mlx.setRefreshRate(MLX90640_2_HZ);
}; 

long frameTime = 0; // variable to track the last frame time 

void thermal_loop() {
    long currentTime = millis();
    
    // Only try to get a new frame if 500ms has passed
    if (currentTime - frameTime >= 500) {  // 500ms = 2Hz
        if (mlx.getFrame(frame) != 0) {
            Serial.println("failed to get frame data");
            return;
        }
        frameTime = currentTime;  
        
        // Print temperature values
        for (int h = 0; h < 24; h++) {
            for (int w = 0; w < 32; w++) {
                float t = frame[h * 32 + w];
                Serial.print(t, 1);
                Serial.print(" ");
            }
            Serial.println();
        }
    }


}; 