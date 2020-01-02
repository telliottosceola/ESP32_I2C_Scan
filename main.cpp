#include <Wire.h>
#include <Arduino.h>
unsigned long scanInterval = 10000;
unsigned long lastScan = 0;
void scan();

void setup() {
    //Set the speed of the I2C port on the Photon and start it.
    Serial.begin(115200);
    delay(2000);
    Serial.println("About to call Wire.begin");
    Wire.begin();
    Serial.println("Wire library initiated");
    scan();
}

void loop() {
    if(millis() > lastScan + scanInterval){
      scan();
    }
}

void scan(){
  Serial.println("Scanning");
    lastScan = millis();
    bool devicesFound = false;
    String newDevices = "Devices at: ";
    //Step through all 127 possible I2C addresses to scan for devices on the I2C bus.
    for(int i = 1; i < 128; i++){
        //Make a general call to device at the current address to see if anything responds.
        Wire.beginTransmission(i);
        uint8_t status = Wire.endTransmission();
        if(status == 0){
            //Device found so append it to our device list event string
            newDevices.concat(i);
            newDevices.concat(", ");
            devicesFound = true;
        }

    }
    if(devicesFound){
        Serial.println(newDevices);
    }else{
        Serial.println("No Devices Found");
    }
}
