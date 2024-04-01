#include <ESP8266WiFi.h>
#include <ThingSpeak.h>
#include <Firebase_ESP_Client.h> 

#define echo D7  // 초음파 수신 핀
#define trig D6  // 초음파 발신 핀

const int ENABLE = D5;  // ENABLE 핀 (모터 동작 제어)
const int IN1 = D4;  // IN1 핀 (방향제어)
const int IN2 = D3;  // IN2 핀 (방향제어)

enum MOTOR_DIRECTION{FOWARD=0, BACKWARD=1};  // 모터의 전방, 후방 여부 확인을 위한 자료형 
enum MOTOR_DIRECTION Direction;  // 모터의 전방, 후방 여부 확인을 위한 자료형 생성

const char* firebaseHost =  FIREBASE_HOST // firebase URL
const char* firebaseAuth = FIREBASE_AUTH // firebase 비밀번호

const char* ssid = "WIFI_SSID";
const char* password = "WIFI_PASSWORD";
const char* thingSpeakApiKey = "THINGSPEAKAPIKEY";  // thingSpeak api 키

WiFiClient client;  // wifi 클라이언트 객체 생성
FirebaseData firebaseData; // FirebaseData 객체 생성

void setup() {
    Serial.begin(115200);
    pinMode(trig, OUTPUT); 
    pinMode(echo, INPUT);   

    pinMode(ENABLE, OUTPUT);
    pinMode(IN1, OUTPUT);  
    pinMode(IN2, OUTPUT); 
    digitalWrite(ENABLE, HIGH); 

    WiFi.begin(ssid, password);  // 와이파이 네트워크 연결

    while (WiFi.status() != WL_CONNECTED) {
        delay(1000);
        Serial.println("wifi에 연결중입니다.");
    }
    Serial.println("wifi에 연결되었습니다.");

    ThingSpeak.begin(client);  // ThingSpeak 라이브러리 초기화 
    Firebase.begin(FIREBASE_HOST, FIREBASE_AUTH);  // Firebase 연결 설정
    }

    unsigned long motorStartTime = 0;  // 모터 동작 시작 시간 기록을 위한 변수
    const unsigned long motorDuration = 6000;  // 모터 동작 시간 (6초)

    void loop() {
    digitalWrite(trig, HIGH);  // 초음파 발신
    delayMicroseconds(10);
    digitalWrite(trig, LOW);

    // 초음파 최대 측정 거리를 100cm로 지정 
    long duration = pulseIn(echo, HIGH, 5800); 
    long distance = duration * 17 / 1000;  

    Serial.print("Duration: ");  
    Serial.println(duration);
    Serial.print("Distance: "); 
    Serial.print(distance);
    Serial.println("cm");

    // 거리가 15cm 이하일 때 모터 전진
    if (distance > 0 && distance <= 15){ 
        Direction = FOWARD;  
        digitalWrite(ENABLE, HIGH);  
        motorStartTime = millis();  
    } 

    // 6초 후 모터 후진
    if (millis() - motorStartTime >= motorDuration && Direction == FOWARD) {
        Direction = BACKWARD;  
        digitalWrite(ENABLE, HIGH);  
        motorStartTime = millis(); 
    }
    
    // 모터 정지
    if (millis() - motorStartTime >= motorDuration && Direction == BACKWARD) {
        digitalWrite(ENABLE, LOW); // 모터 정지
    }

    Serial.print("Direction: "); 
    Serial.println(Direction);

    // 모터 방향이 전진이면
    if(Direction == FOWARD){  
        digitalWrite(IN1, LOW);  
        digitalWrite(IN2, HIGH); 
    } 
    //모터 방향이 후진이면 
    else {  
        digitalWrite(IN1, HIGH);  
        digitalWrite(IN2, LOW);  
    }

  ThingSpeak.writeField(2363439, 1, distance, thingSpeakApiKey); // ThingSpeak API로 센서 값 전송

  delay(1000);
}