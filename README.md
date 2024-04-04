<img src="https://capsule-render.vercel.app/api?type=waving&color=auto&height=200&section=header&text=호출%20가능한%20인공지능%20쓰레기통%20로봇%20call-T&fontSize=40" />

<h2>🛠 기술 스택</h2>
<table>
  <tr>
    <th colspan="2">구분</th>
    <th>상세내용</th>
  </tr>
  <tr>
    <td rowspan="4">S/W 개발환경</td>
    <td>OS</td>
    <td>
      <img src="https://img.shields.io/badge/Windows 10-0078D6?style=flat&logo=windows10&logoColor=white" />
      <img src="https://img.shields.io/badge/Linux-FCC624?style=flat&logo=linux&logoColor=black" />
      <img src="https://img.shields.io/badge/Ubuntu 20.04-E95420?style=flat&logo=ubuntu&logoColor=white" />
    </td>
  </tr>
  <tr>
    <td>개발환경(IDE)</td>
    <td>
      <img src="https://img.shields.io/badge/Visual Studio Code-007ACC?style=flat&logo=visualstudiocode&logoColor=white" />
      <img src="https://img.shields.io/badge/Arduino IDE-00878F?style=flat&logo=arduino&logoColor=white" />
    </td>
  </tr>
  <tr>
    <td>개발도구</td>
    <td>
      <img src="https://img.shields.io/badge/ROS-22314E?style=flat&logo=ros&logoColor=white" />
      <img src="https://img.shields.io/badge/React-61DAFB?style=flat&logo=React&logoColor=black" />
      <img src="https://img.shields.io/badge/OpenCV-5C3EE8?style=flat&logo=opencv&logoColor=white" />
    </td>
  </tr>
  <tr>
    <td>개발언어</td>
    <td>
      <img src="https://img.shields.io/badge/HTML5-E34F26?style=flat&logo=html5&logoColor=white" />
      <img src="https://img.shields.io/badge/CSS3-1572B6?style=flat&logo=css3&logoColor=white" />
      <img src="https://img.shields.io/badge/JavaScript-F7DF1E?style=flat&logo=javascript&logoColor=black" />
      <img src="https://img.shields.io/badge/Python-3776AB?style=flat&logo=python&logoColor=white" />
      <img src="https://img.shields.io/badge/C++-00599C?style=flat&logo=cplusplus&logoColor=white" />
    </td>
  </tr>
  <tr>
    <td rowspan="4">H/W 구성장비</td>
    <td>디바이스</td>
    <td>Arduino Mega 2560, 아두이노 우노+WIFI D1 R2 보드(ESP8266), RaspberryPi4, L298N 모터 드라이버</td>
  </tr>
  <tr>
    <td>센서</td>
    <td>LIDAR(IP65), 초음파 센서(HC-SR04)</td>
  </tr>
  <tr>
    <td>통신</td>
    <td>BLE(Bluetooth Low Energy) 통신, Serial 통신</td>
  </tr>
</table>

<h2>📱 하드웨어/센서 회로도</h2>
<h3>1) 압축 기능 설계도</h3>
<img src="https://github.com/jihyeon-1010/call-T/assets/119498515/864f9cd5-2d07-4643-814a-34e6ec3e1004" height="300px" />
<img src="https://github.com/jihyeon-1010/call-T/assets/119498515/5959e015-48bc-4af6-9db9-5759d11123b7" height="300px"/>
<h4>[D1 R2 보드 & DC 모터 드라이버 & 리니어 액추에이터 연결]</h4>

|WIFI D1 R2 보드(ESP8266)|L298N 모터 드라이버|리니어 액추에이터|초음파 센서
|:----:|:----:|:----:|:----:
|GND|GND|-|GND
|5V|5V|-|-
|3.3V|-|-|Vcc
|D7|-|-|Echo
|D6|-|-|Trig
|D5|ENA|-|-
|D4|IN1|-|-
|D3|IN2|-|-
|D3|IN2|-|-
|12V 아답터|12V, GND|-|-
|-|OUT1|양극(+)|-
|-|OUT2|음극(-)|-

<h3>2) 분리수거 기능 설계도</h3>
<img src="https://github.com/jihyeon-1010/call-T/assets/119498515/89349bfd-7728-4768-8df6-1da4ff14f99e" height="200px" />
<img src="https://github.com/jihyeon-1010/call-T/assets/119498515/51faa02a-9555-43a3-9fb2-b0f5b68332fe" height="200px"/>
<h4>[아두이노 메가 & 서보 모터1 & 서보 모터2 연결]</h4>

|아두이노 메가|서보 모터1|서보 모터2
|:----:|:----:|:----:
|GND|GND|GND
|5V|5V|5V
|PWM 9|데이터 핀|-
|PWM 8|-|데이터 핀

<h3>3) 주행 기능 설계도</h3>
<img src="https://github.com/jihyeon-1010/call-T/assets/119498515/ba3adb65-45ab-497c-9416-cac64ea50f96" height="250px"/>
<img src="https://github.com/jihyeon-1010/call-T/assets/119498515/404fb108-29b8-492b-b708-f6ee83645c06" height="250px" />
<h4>호출 버튼</h3>
<img src="https://github.com/jihyeon-1010/call-T/assets/119498515/12829d31-7138-4d72-a5e1-aa2f7d8ef7fb" height="150px"/>
<img src="https://github.com/jihyeon-1010/call-T/assets/119498515/284c0f13-40f9-46e3-85d1-7bbd08a7260d" height="150px" />
<h4>[아두이노 메가 & 모터 드라이버 보드 & 초음파 센서 & 라이더 센서 & 휠 모터 연결]</h4>

|아두이노 메가|모터 드라이버 보드|전면 좌측 초음파|전면 우측 초음파|후면 초음파|라이더 센서|전면 좌측 모터|전면 우측 모터|후면 좌측 모터|후면 우측 모터
|:----:|:----:|:----:|:----:|:----:|:----:|:----:|:----:|:----:|:----:
|D 32|PC5|Trig|-|-|-|-|-|-|-
|D 33|PC4|Echo|-|-|-|-|-|-|-
|D 25|PA3|-|Trig|-|-|-|-|-|-
|D 28|PA6|-|Echo|-|-|-|-|-|-
|D 47|PL2|-|-|Trig|-|-|-|-|-
|D 48|PL1|-|-|Echo|-|-|-|-|-
|D 17|PH0|-|-|-|RXD|-|-|-|-
|D 16|PH1|-|-|-|TXD|-|-|-|-
|-|M1(M+)|-|-|-|-|M+|-|-|-
|-|M1(5V)|-|-|-|-|Vcc|-|-|-
|-|M1(A)|-|-|-|-|A|-|-|-
|-|M1(B)|-|-|-|-|B|-|-|-
|-|M1(GND)|-|-|-|-|GND|-|-|-
|-|M1(M-)|-|-|-|-|M-|-|-|-
|-|M2(M+)|-|-|-|-|-|M+|-|-
|-|M2(5V)|-|-|-|-|-|Vcc|-|-
|-|M2(A)|-|-|-|-|-|A|-|-
|-|M2(B)|-|-|-|-|-|B|-|-
|-|M2(GND)|-|-|-|-|-|GND|-|-
|-|M2(M-)|-|-|-|-|-|M-|-|-
|-|M3(M+)|-|-|-|-|-|-|M+|-
|-|M3(5V)|-|-|-|-|-|-|Vcc|-
|-|M3(A)|-|-|-|-|-|-|A|-
|-|M3(B)|-|-|-|-|-|-|B|-
|-|M3(GND)|-|-|-|-|-|-|GND|-
|-|M3(M-)|-|-|-|-|-|-|M-|-
|-|M4(M+)|-|-|-|-|-|-|-|M+
|-|M4(5V)|-|-|-|-|-|-|-|Vcc
|-|M4(A)|-|-|-|-|-|-|-|A
|-|M4(B)|-|-|-|-|-|-|-|B
|-|M4(GND)|-|-|-|-|-|-|-|GND
|-|M4(M-)|-|-|-|-|-|-|-|M-
|GND|GND|GND|GND|GND|GND|-|-|-|-
|VCC|VCC|VCC|VCC|VCC|5V|-|-|-|-

<h2>↪ 코드 흐름도</h2>
