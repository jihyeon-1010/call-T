#include <Servo.h>

Servo servo1; 
Servo servo2; 
int initialPosition = 90; // 초기 위치 
int targetPosition = initialPosition; 

void setup() {
    // 서보 모터 초기 위치 설정
    Serial.begin(9600); 
    servo1.attach(8); 
    servo2.attach(9); 
    servo1.write(initialPosition); 
    servo2.write(initialPosition);
}

void loop() {
    if (Serial.available() > 0) {
        String obj = Serial.readStringUntil('\n');
        Serial.println(obj);
        
        // 시리얼 모니터에 can, plastic, paperpack이 입력되면 
        if (obj == "can" || obj == "plastic" || obj == "paperpack") {
            servo1.write(0);
            servo2.write(180); 
            delay(1000); 
            servo1.write(initialPosition);
            servo2.write(initialPosition);
        } 
        // 시리얼 모니터에 paper, tissue, vinyl이 입력되면
        else if (obj == "paper" || obj == "tissue" || obj == "vinyl") {
            servo1.write(180);
            servo2.write(0); 
            delay(1000); 
            servo1.write(initialPosition);
            servo2.write(initialPosition); 
            
            // 시리얼 버퍼 비우기
            while (Serial.available() > 0) {
            Serial.read();
            }
        } 
    }
}