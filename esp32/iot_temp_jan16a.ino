#include "arduino_secrets.h"
#include "thingProperties.h"

#define RXD2 16
#define TXD2 17
#define SENSOR_BAUD 115200

String receivedData;
int16_t           // Biến lưu giá trị
AcceX = 0, 
AcceY = 0, 
AcceZ = 0, 
Temp  = 0,  
GyroX = 0, 
GyroY = 0, 
GyroZ = 0; 

HardwareSerial sensorSerial(2);

void setup() {
  Serial.begin(115200);
  delay(1500); // Delay to allow serial monitor to open
  sensorSerial.begin(SENSOR_BAUD, SERIAL_8N1, RXD2, TXD2);
  initProperties();
  ArduinoCloud.begin(ArduinoIoTPreferredConnection);
  setDebugMessageLevel(2);
  ArduinoCloud.printDebugInfo();
  xTaskCreatePinnedToCore(ReadData, 
                          "ReadData",  
                          4096, 
                          NULL, 
                          2, 
                          NULL, 
                          tskNO_AFFINITY);                       
}

void loop() {
  ArduinoCloud.update();
}

void ReadData(void *pvParameters) {
    (void) pvParameters;
    for (;;) {
        int32_t receivedValues[7]; 
        
        // Kiểm tra nếu có đủ dữ liệu
        if (sensorSerial.available() >= sizeof(receivedValues)) {
            // Đọc dữ liệu thô từ serial
            sensorSerial.readBytes((char *)receivedValues, sizeof(receivedValues));
            
            // Gán giá trị vào các biến
            AcceX = receivedValues[0];
            AcceY = receivedValues[1];
            AcceZ = receivedValues[2];
            Temp  = receivedValues[3];
            GyroX = receivedValues[4];
            GyroY = receivedValues[5];
            GyroZ = receivedValues[6];

            gyroX = GyroX;
            gyroY = GyroY;
            gyroZ = GyroZ;
            temp = Temp;
        } else {
            Serial.println("Waiting for data...");
        }
        vTaskDelay(10 / portTICK_PERIOD_MS);
    }
}




/*
  Since temp is a READ_WRITE variable, onTempChange() is
  executed every time a new value is received from IoT Cloud.
*/
void onTempChange()  {
  // Add your code here to act upon Temp change  
}

/*
  Since GyroX is READ_WRITE variable, onGyroXChange() is
  executed every time a new value is received from IoT Cloud.
*/
void onGyroXChange()  {
  // Add your code here to act upon GyroX change
}

/*
  Since GyroY is READ_WRITE variable, onGyroYChange() is
  executed every time a new value is received from IoT Cloud.
*/
void onGyroYChange()  {
  // Add your code here to act upon GyroY change
}

/*
  Since GyroZ is READ_WRITE variable, onGyroZChange() is
  executed every time a new value is received from IoT Cloud.
*/
void onGyroZChange()  {
  // Add your code here to act upon GyroZ change
}
