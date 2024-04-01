#include <BLEDevice.h>
#include <BLEServer.h>
#include <BLEUtils.h>
#include <BLE2902.h>
#include <WiFi.h> 

BLEServer *pServer;  // BLE 서버 객체
BLEService *pService;  // BLE 서비스 객체
BLECharacteristic *pCharacteristic;  // BLE 캐릭터리스틱 객체
BLE2902 *pDescriptor;  // BLE 디스크립터 객체

const char *SERVICE_UUID = "4fafc201-1fb5-459e-8fcc-c5c9c331914b";  // 서비스 uuid
const char *CHARACTERISTIC_UUID = "beb5483e-36e1-4688-b7f5-ea07361b26a8";  // 캐릭터리스틱 uuid

class MyServerCallbacks : public BLEServerCallbacks {
    // 디바이스 장치 연결 이벤트 콜백
    void onConnect(BLEServer *pServer) {  
        Serial.println("디바이스 장치 연결 성공");
    }

    // 디바이스 장치 연결 끊김 이벤트 콜백
    void onDisconnect(BLEServer *pServer) {  
        Serial.println("디바이스 장치 연결 끊김");
    }
};

void setup() {
    Serial.begin(9600);
    BLEDevice::init("ESP32-CAM");

    // BLE 서버 생성
    pServer = BLEDevice::createServer();  
    pServer->setCallbacks(new MyServerCallbacks());  

    // 서비스 생성
    pService = pServer->createService(SERVICE_UUID);  

    pCharacteristic = pService->createCharacteristic(
        CHARACTERISTIC_UUID,
        BLECharacteristic::PROPERTY_READ |  // 캐릭터리스틱 속성 설정 (읽기, 알림)
            BLECharacteristic::PROPERTY_NOTIFY);

    // BLE 디스크립터 객체 생성
    pDescriptor = new BLE2902();  
    pCharacteristic->addDescriptor(pDescriptor); 

    // 서비스 시작
    pService->start();  
    // 광고에 서비스 UUID 추가
    pServer->getAdvertising()->addServiceUUID(SERVICE_UUID);  
    // BLE 서버 광고를 시작하여 주변 디바이스들에게 서비스의 존재를 알리고, 이에 대한 연결 요청 기다림
    pServer->getAdvertising()->start();  
}

void loop() {
  delay(1000);
}



