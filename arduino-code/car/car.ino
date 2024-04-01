#include <NewPing.h> // 초음파 라이브러리
#include "TFLidar.h"  // 라이더 라이브러리

// 모터 핀 설정
#define PWMA 12    // A 모터 속도
#define DIRA1 34 
#define DIRA2 35  // A 모터 방향
#define PWMB 8    // B 모터 속도
#define DIRB1 37 
#define DIRB2 36  // B 모터 방향
#define PWMC 6   // C 모터 속도 9를 6으로 변경
#define DIRC1 43 
#define DIRC2 42  // C 모터 방향
#define PWMD 5    // D 모터 속도
#define DIRD1 A4  //26  
#define DIRD2 A5  //27  // D 모터 방향

// 라이더 설정
#define LIDAR_SERIAL Serial2 
TFLidar lidar;  // TFLidar 클래스의 LIDAR_SERIAL 객체 생성
int dist;  // 라이더 거리 저장 변수

// 초음파 핀 설정
#define TRIGPIN1 32 //F-L PC5
#define ECHOPIN1 33 //F-L PC4

#define TRIGPIN2 25 //F-R PA3
#define ECHOPIN2 28 //F-R PA6

#define TRIGPIN3 47 //B PL2
#define ECHOPIN3 48 //B PL1

#define MAX_DISTANCE 200 // 초음파 최대 감지 거리 
NewPing sonar1(TRIGPIN1, ECHOPIN1, MAX_DISTANCE); // f-l 초음파 센서 초기화
NewPing sonar2(TRIGPIN2, ECHOPIN2, MAX_DISTANCE); // f-r 초음파 센서 초기화
NewPing sonar3(TRIGPIN3, ECHOPIN3, MAX_DISTANCE); // b 초음파 센서 초기화

// 초음파 거리 저장 변수
long leftDistance;
long rightDistance;
long backDistance;

int rssi;
float distance;
int robotMove = 0;  // 로봇을 움직임 플래그 변수
int previousRssi = 0;  // 이전 rssi를 저장하는 변수
int currentRssi = 0;  // 현재 rssi를 저장하는 변수
int previousDirection = 0;  // 이전 방향을 저장하는 함수
bool previousDirectionSaved = false;  // 이전 방향을 저장했는지 여부를 나타내는 변수  

void (* resetFunc) (void) = 0;

#define MOTORA_FORWARD(pwm)    do{digitalWrite(DIRA1,HIGH);digitalWrite(DIRA2,LOW); analogWrite(PWMA,pwm);}while(0)  // A 모터를 지정된 속도로 전진하는 매크로 
#define MOTORA_STOP(x)         do{digitalWrite(DIRA1,LOW); digitalWrite(DIRA2,LOW); analogWrite(PWMA,0);}while(0)  // A 모터를 정지시키는 매크로
#define MOTORA_BACKOFF(pwm)    do{digitalWrite(DIRA1,LOW); digitalWrite(DIRA2,HIGH);analogWrite(PWMA,pwm);}while(0)  // A 모터를 지정된 속도로 후진하는 매크로

#define MOTORB_FORWARD(pwm)    do{digitalWrite(DIRB1,LOW);digitalWrite(DIRB2,HIGH); analogWrite(PWMB,pwm);}while(0)  // B 모터를 지정된 속도로 전진하는 매크로 
#define MOTORB_STOP(x)         do{digitalWrite(DIRB1,LOW); digitalWrite(DIRB2,LOW); analogWrite(PWMB,0);}while(0)  // B 모터를 정지시키는 매크로
#define MOTORB_BACKOFF(pwm)    do{digitalWrite(DIRB1,HIGH); digitalWrite(DIRB2,LOW);analogWrite(PWMB,pwm);}while(0)  // B 모터를 지정된 속도로 후진하는 매크로

#define MOTORC_FORWARD(pwm)    do{digitalWrite(DIRC1,HIGH);digitalWrite(DIRC2,LOW); analogWrite(PWMC,pwm);}while(0)  // C 모터를 지정된 속도로 전진하는 매크로 
#define MOTORC_STOP(x)         do{digitalWrite(DIRC1,LOW); digitalWrite(DIRC2,LOW); analogWrite(PWMC,0);}while(0)  // C 모터를 정지시키는 매크로
#define MOTORC_BACKOFF(pwm)    do{digitalWrite(DIRC1,LOW); digitalWrite(DIRC2,HIGH);analogWrite(PWMC,pwm);}while(0)  // C 모터를 지정된 속도로 후진하는 매크로

#define MOTORD_FORWARD(pwm)    do{digitalWrite(DIRD1,LOW);digitalWrite(DIRD2,HIGH); analogWrite(PWMD,pwm);}while(0)  // D 모터를 지정된 속도로 전진하는 매크로 
#define MOTORD_STOP(x)         do{digitalWrite(DIRD1,LOW); digitalWrite(DIRD2,LOW); analogWrite(PWMD,0);}while(0)  // D 모터를 정지시키는 매크로
#define MOTORD_BACKOFF(pwm)    do{digitalWrite(DIRD1,HIGH); digitalWrite(DIRD2,LOW);analogWrite(PWMD,pwm);}while(0)  // D 모터를 지정된 속도로 후진하는 매크로

#define SERIAL  Serial

#define LOG_DEBUG

#ifdef LOG_DEBUG
#define M_LOG SERIAL.print
#else
#define M_LOG 
#endif

/*
#define MAX_PWM   200
#define MIN_PWM   130
int Motor_PWM = 130;
*/

#define MAX_PWM   150
#define MIN_PWM   100
int Motor_PWM = 100;

// 전진
void ADVANCE()
{
  MOTORA_FORWARD(Motor_PWM); MOTORB_FORWARD(Motor_PWM);
  MOTORC_FORWARD(Motor_PWM); MOTORD_FORWARD(Motor_PWM);
}

// 후진
void BACK()
{
  MOTORA_BACKOFF(Motor_PWM); MOTORB_BACKOFF(Motor_PWM);
  MOTORC_BACKOFF(Motor_PWM); MOTORD_BACKOFF(Motor_PWM);
}

// 좌상향
void LEFT_1()
{
  MOTORA_STOP(Motor_PWM); MOTORB_FORWARD(Motor_PWM);
  MOTORC_FORWARD(Motor_PWM); MOTORD_STOP(Motor_PWM);
}

// 좌측(좌회전 아님)
void LEFT_2()
{
  MOTORA_BACKOFF(Motor_PWM); MOTORB_FORWARD(Motor_PWM);
  MOTORC_FORWARD(Motor_PWM); MOTORD_BACKOFF(Motor_PWM);
}

// 좌하향
void LEFT_3()
{
  MOTORA_BACKOFF(Motor_PWM); MOTORB_STOP(Motor_PWM);
  MOTORC_STOP(Motor_PWM); MOTORD_BACKOFF(Motor_PWM);
}

// 우상향
void RIGHT_1()
{
  MOTORA_FORWARD(Motor_PWM); MOTORB_STOP(Motor_PWM);
  MOTORC_STOP(Motor_PWM); MOTORD_FORWARD(Motor_PWM);
}

// 우회전(우회전 아님)
void RIGHT_2()
{
  MOTORA_FORWARD(Motor_PWM); MOTORB_BACKOFF(Motor_PWM);
  MOTORC_BACKOFF(Motor_PWM); MOTORD_FORWARD(Motor_PWM);
}

// 우하향
void RIGHT_3()
{
  MOTORA_STOP(Motor_PWM); MOTORB_BACKOFF(Motor_PWM);
  MOTORC_BACKOFF(Motor_PWM); MOTORD_STOP(Motor_PWM);
}

// 좌회전
void TURN_LEFT()
{
  MOTORA_BACKOFF(Motor_PWM); MOTORB_FORWARD(Motor_PWM);
  MOTORC_BACKOFF(Motor_PWM); MOTORD_FORWARD(Motor_PWM);
}

// 우회전
void TURN_RIGHT()
{
  MOTORA_FORWARD(Motor_PWM); MOTORB_BACKOFF(Motor_PWM);
  MOTORC_FORWARD(Motor_PWM); MOTORD_BACKOFF(Motor_PWM);
}

// 정지
void STOP()
{
  MOTORA_STOP(Motor_PWM);MOTORB_STOP(Motor_PWM);
  MOTORC_STOP(Motor_PWM);MOTORD_STOP(Motor_PWM);
}

void IO_init()
{
  pinMode(PWMA, OUTPUT);
  pinMode(DIRA1, OUTPUT);
  pinMode(DIRA2, OUTPUT);
  pinMode(PWMB, OUTPUT);
  pinMode(DIRB1, OUTPUT);
  pinMode(DIRB2, OUTPUT);
  pinMode(PWMC, OUTPUT);
  pinMode(DIRC1, OUTPUT);
  pinMode(DIRC2, OUTPUT);
  pinMode(PWMD, OUTPUT);
  pinMode(DIRD1, OUTPUT);
  pinMode(DIRD2, OUTPUT);
  STOP();
}

// 라이더 센서 거리 측정 후 반환
int ladarDistance() 
{
  lidar.getData(dist);  
  Serial.print("라이더 센서 거리(cm): ");
  Serial.println(dist);
  Serial.println();
  return dist;
}

// 라이더 감지 거리를 파라미터로 받아 회피 동작 수행 (라이더는 무조건 헤딩값만 보기 위한 용도임. 초음파 회피 함수랑 헷길리지 X)
bool avoidObstacle(int LidarSensorDistance) 
{
  if (LidarSensorDistance >= 60) {
    return true;
  } else{
    return false;
  }
}

// F-L 초음파 감지
void F_L_movePattern() 
{
  Motor_PWM = 120;
  BACK();
  delay(500);

  TURN_LEFT();
  delay(1000); 
  
  Motor_PWM = 120;
  ADVANCE();
}

// F-R 초음파 감지
void F_R_movePattern()
{
  Motor_PWM = 120;
  BACK();
  delay(500);

  TURN_LEFT();
  delay(1000); 

  Motor_PWM = 120;
  ADVANCE();
}

// B 초음파 감지
void B_movePattern()
{
  STOP();
  delay(500);
  
  Motor_PWM = 120;
  ADVANCE();
}

// 입력받은 rssi값과 distance를 각각 정수형과 실수형으로 변환
int parseData(String data, int &rssi, float &distance) 
{
  int commaIndex = data.indexOf(',');
  if (commaIndex == -1) {
    return -1;  // 데이터 파싱에 실패할 시 -1 반환
  }

  String rssiStr = data.substring(0, commaIndex);
  String distanceStr = data.substring(commaIndex + 1);

  rssi = rssiStr.toInt();
  distance = distanceStr.toFloat();

  return rssi;  // 데이터 파싱에 성공하면 rssi값 반환
}

// 이동 전 rssi 측정
void setPreviousRssi() 
{
  int totalRssi = 0;
  int validReadings = 0;

  // 시리얼 버퍼에 데이터가 들어오면 rssi를 3번 파싱하여 유효한 rssi만 축적
  if (Serial.available() > 0) {
    while (validReadings < 3) {
      String data = Serial.readStringUntil('\n');

      // 데이터 파싱 결과를 변수 previousRssi에 대입
      previousRssi = parseData(data, rssi, distance);

      // 정수형으로 파싱된 rssi가 return되면 totalRssi에 previousRssi 축적
      if (previousRssi != -1) {
      totalRssi += previousRssi;
      ++validReadings;
      }
    }
    delay(100); 
  }

  // 유효한 rssi가 3번 축적되면 평균값으로 변환 후 previousRssi에 대입
  if (validReadings == 3) {
    previousRssi = totalRssi / 3;
    // rssi를 평균값으로 변환하는 과정이 끝나면 로봇을 움직일지 여부를 나타내는 플래그 변수에 1 할당
    robotMove = 1;
  } else {
    robotMove = 0;
  }

  Serial.print("이동 전 rssi 값: ");
  Serial.println(previousRssi);
}

void move(int moveDistance, int direction) 
{
  switch (direction) {
    case 1:  // 전진
      Serial.println("전진");
      ADVANCE();
      delay(moveDistance);
      STOP();
      delay(3000);
      break;  
    case 2:  // 좌회전 
      Serial.println("좌회전");
      TURN_LEFT();  
      delay(1000);

      ADVANCE();
      delay(moveDistance);
      STOP();
      delay(3000);
      break;  
    case 3:  // 우회전
      Serial.println("우회전");
      TURN_RIGHT();  
      delay(1000);

      ADVANCE();
      delay(moveDistance);
      STOP();
      delay(3000);
      break;
    case 4:  // 후진
      Serial.println("후진");
      BACK();
      delay(moveDistance);
      STOP();
      delay(3000);
      break;
    default:
      break;
  }

  // 거리값을 변수에 저장
  int distFL = sonar1.ping_cm();
  int distFR = sonar2.ping_cm();
  int distB = sonar3.ping_cm();

  // 장애물 감지
  if (distFL > 0 && distFL < 40) {
    F_L_movePattern();
  }
  if (distFR > 0 && distFR < 40) {
    F_R_movePattern();
  }
  if (distB > 0 && distB < 40) {
    B_movePattern();
  }

  delay(100);
}

// 이전 방향 저장
void setPreviousDirection(int direction) {
  previousDirection = direction;
  previousDirectionSaved = true;

  Serial.print("이전 방향 저장: ");
  Serial.println(direction);
}

// 이동 후 rssi값 저장
void setCurrentRssi() 
{
  int totalRssi = 0;
  int validReadings = 0;

  // 시리얼 버퍼에 데이터가 들어오면 rssi를 3번 파싱하여 유효한 rssi만 축적
  if (Serial.available() > 0) {
    while (validReadings < 3) {
      String data = Serial.readStringUntil('\n');

      // 데이터 파싱 결과를 변수 currentRssi에 대입
      currentRssi = parseData(data, rssi, distance);

      // 정수형으로 파싱된 rssi가 return되면 totalRssi에 previousRssi 축적
      if (currentRssi != -1) {
      totalRssi += currentRssi;
      ++validReadings;
      }
    }
    delay(100); 
  }

  // 유효한 rssi가 3번 축적되면 평균값으로 변환 후 previousRssi에 대입
  if (validReadings == 3) {
    currentRssi = totalRssi / 3;
    // rssi를 평균값으로 변환하는 과정이 끝나면 로봇을 움직일지 여부를 나타내는 플래그 변수에 1 할당
    robotMove = 1;
  } else {
    robotMove = 0;
  }

  Serial.print("이동 후 rssi 값: ");
  Serial.println(currentRssi);
}

void changeDirection()
{
  if (currentRssi >= previousRssi) { // 이동 후 rssi값이 커지거나 같은 경우
    dist = ladarDistance();
    // 라이더 센서를 이용해 측정한 전방의 거리가 60cm 이상일 때만 실행
    if (avoidObstacle(dist)) {
      move(6000, previousDirection); 
    }
  } else {  // 이동 후 rssi값이 작아진 경우
    move(6000, 3); 
  }
}

void setup()
{
   SERIAL.begin(9600);
  while (!Serial); 
  Serial.print("Serial init OK\r\n");
  LIDAR_SERIAL.begin(115200);  // LIDAR와의 통신 속도
  lidar.begin(&LIDAR_SERIAL);    
  IO_init();
}

void loop()
{
  // 1) 시리어 모니터에 rssi가 입력될 때만 이동 전 RSSI 값 저장 후 로봇의 움직임 여부를 결정하는 플래그에 1 할당 
  setPreviousRssi(); 

  // robotMove가 1인 경우에만 실행
  if (robotMove == 1) {
    dist = ladarDistance();
    // 2) 라이더 센서를 이용해 측정한 전방의 거리가 60cm 이상일 때만 실행
    if (avoidObstacle(dist)) {
      // 3) 이동거리, 방향
      move(6000, 1);  
      Serial.println("move 끝!");
      setPreviousDirection(1);  // 방향 저장
      // 4) 이동 후의 rssi값 저장
      setCurrentRssi(); 
      // 5) 이동 방향 결정
      changeDirection();
    } else {
      // 라이더 센서를 이용해 측정한 전방의 거리가 60cm 이하일 때 오른쪽으로 턴한 후 다시 loop()문 반복
      move(6000, 3);  
    }
  } else {
    // 시리얼 모니터에 rssi가 입력되지 않으면 차량은 멈춤
    STOP();
  }
}