//공학설계입문(정원국 교수님) 5조 Smart Robot Car. 소스 코드

//약 560줄, 14페이지 분량

#include <Servo.h>
#include <SoftwareSerial.h>
SoftwareSerial BTSerial(0, 1);
int relayPin = 13;
int servoPin1 = 7; //몸통 회전 서보
int servoPin2 = 8; //거리 서보
int servoPin3 = 9; //높이 서보
int servoPin4 = 10; //집게 서보
int data; //임시
int T = 1;
int A,B;// 자동주행 내 변수
int sensorRef = 600; // 적외선 센서의 역치 : 읽은 값이 이 값 이상이면 인식한걸
로 간주.
int ECHO = 2;
int TRIG = 4; //초음파 센서 핀
int distance_cm = 100;
Servo servo1;
Servo servo2;
Servo servo3;
Servo servo4;
int V0,V1,V2,V3,V4,V5; //적외선 센서 변수
int angle1=90; //각 서보의 초기값
int angle2=90;
int angle3=90;
int angle4=90;
int servodelay=15; //서보 민감도. 높으면 느리게 동작, 낮으면 빠르게 동작.
int i = 0;
void setup()
{
servo1.attach(servoPin1);
servo2.attach(servoPin2);
servo3.attach(servoPin3);
servo4.attach(servoPin4);
Serial.begin(9600);
int mPin[] = {3,5,6,11}; //모터 제어 핀
for(i=0; i<4; i++)

{
pinMode(mPin[i],OUTPUT);
}
long echo_time_us; //초음파 센서 변수
double distance_cm;
pinMode(relayPin,OUTPUT);
digitalWrite(relayPin,HIGH) ;
pinMode(ECHO, INPUT);
pinMode(TRIG, OUTPUT);
} // void setup() 문장의 끝
void loop()
{

// 적외선 센서 입력 코드.
/*
V0 = analogRead(A0);
V1 = analogRead(A1);
V2 = analogRead(A2);
V3 = analogRead(A3);
V4 = analogRead(A4);
V5 = analogRead(A5); */
// --------------------------------
/* 적외선 센서 수치 피드백을 위한 serial출력 코드
Serial.print(V0);
Serial.print(" || ");
Serial.print(V1);
Serial.print(" || ");
Serial.print(V2);
Serial.print(" || ");
Serial.print(V3);
Serial.print(" || ");
Serial.print(V4);
Serial.print(" || ");
Serial.println(V5);
Serial.println(" ");
delay(1); */
// ---------------------------------

if(Serial.available())
{
char data = Serial.read();
if(data == 'i') //서보 버벅일때
{
angle2 = 90;
angle3 = 90;
servo2.write(angle2);
servo3.write(angle3);
}

// @@@@@@================ 자동 주행

=================@@@@@@
if(data == 'S') //자동 주행 조건문.
{
angle1 = 90;
angle2 = 90;
angle3 = 90;
angle4 = 90;
servo1.write(angle1);
servo2.write(angle2);
servo3.write(angle3);
servo4.write(angle4);
data = 0;
while(1) //무한 반복
{
V0 = analogRead(A0);
V1 = analogRead(A1);
V2 = analogRead(A2);
V3 = analogRead(A3);
V4 = analogRead(A4);
V5 = analogRead(A5);
// 적외선 센서 작동.
/*
Serial.print(V0);
Serial.print(" || ");
Serial.print(V1);
Serial.print(" || ");
Serial.print(V2);
Serial.print(" || ");
Serial.print(V3);
Serial.print(" || ");
Serial.print(V4);
Serial.print(" || ");

Serial.println(V5);
Serial.println(" ");
l
*/
// Serial.println("[Auto Mode]"); // 모드 확인 위하여.
if(Serial.available()>0); // serial통신으로 문자를 받았을 경우
{
data = Serial.read();
if(data == 'S') // 그 중 data가 S이면 자동주행 종료.
{
analogWrite(6, LOW);
analogWrite(11, 0); //이 두줄이 왼쪽 바퀴
analogWrite(3, LOW);
analogWrite(5, 0); //이 두줄이 오른쪽 바퀴
break;
}
}
if((V2 > sensorRef) && (V3 > sensorRef)) //중간 2개의 센서에 라인이 감지된 경
우(A2 A3)
{
analogWrite(6, LOW);
analogWrite(11, 55); //이 두줄이 왼쪽 바퀴
analogWrite(3, LOW);
analogWrite(5, 55); //이 두줄이 오른쪽 바퀴
Serial.println(" [ M I D ] ");
// ========== 직진 할 경우 에만 정면과의 거리 인식 ============
digitalWrite(TRIG, HIGH);
delayMicroseconds(10);
digitalWrite(TRIG, LOW);
distance_cm = pulseIn(ECHO, HIGH) * 17/1000;

//
==========================================================
// ----------------------------------
Serial.print("Distance =");
Serial.print(distance_cm);
Serial.println("cm");
// delay(100);
// 초음파 센서 거리 측정 코드
// ----------------------------------
}

else if(V0 > sensorRef) // 맨 왼쪽 센서(A0)에 라인이 감지된 경우
{
A = 0;
B = 210*T;
analogWrite(6, LOW);
analogWrite(11, A);
analogWrite(3, LOW);
analogWrite(5, B);
delay(1);
Serial.println(" << << << ");
}
else if(V5 > sensorRef) // 맨 오른쪽 센서(A5)에 라인이 감지된 경우
{
A = 210*T;
B = 0;
analogWrite(6, LOW);
analogWrite(11, A);
analogWrite(3, LOW);
analogWrite(5, B);
delay(1);
Serial.println(" >> >> >> ");
}
else if(V1 > sensorRef) // 왼쪽에서 두 번째 센서(A1)에 라인이 감지된 경우
{
A = 30;
B = 180*T;
analogWrite(6, LOW);
analogWrite(11, A); //이 두줄이 왼쪽 바퀴
analogWrite(3, LOW);
analogWrite(5, B); //이 두줄이 오른쪽 바퀴
delay(1);
Serial.println(" << << ");
}
else if(V4 > sensorRef) // 오른쪽에서 두 번째 센서(A4)에 라인이 감지된 경우
{
A = 180*T;
B = 30;
analogWrite(6, LOW);
analogWrite(11, A); //이 두줄이 왼쪽 바퀴
analogWrite(3, LOW);
analogWrite(5, B); //이 두줄이 오른쪽 바퀴
delay(1);
Serial.println(" >> >> ");

}
else if(V2 > sensorRef) // 왼쪽에서 세 번째 센서(A2)에 라인이 감지된 경우
{
A = 40;
B = 150*T;
analogWrite(6, LOW);
analogWrite(11,A); //이 두줄이 왼쪽 바퀴
analogWrite(3, LOW);
analogWrite(5, B); //이 두줄이 오른쪽 바퀴
delay(1);
Serial.println(" << ");
}
else if(V3 > sensorRef) // 오른쪽에서 세 번째 센서(A3)에 라인이 감지된 경우
{
A = 150*T;
B = 40;
analogWrite(6, LOW);
analogWrite(11, A); //이 두줄이 왼쪽 바퀴
analogWrite(3, LOW);
analogWrite(5, B); //이 두줄이 오른쪽 바퀴
delay(1);
Serial.println(" >> ");
}
else // 라인이 감지가 되지 않는다면 멈춤
{
Serial.println(" M I S S ");
analogWrite(6, LOW);
analogWrite(11, A);
analogWrite(3, LOW);
analogWrite(5, B);
delay(10);
A = 0;
B = 0;
analogWrite(6, LOW);
analogWrite(11, A);
analogWrite(3, LOW);
analogWrite(5, B);
}
delay(1);
// @@@@@@@@@@@========== 로봇팔 자동 작동 코드
==========@@@@@@@@@@@@@
if(distance_cm < 22) // 초음파 센서 10cm 이내 감지할 경우 발동.

{

Serial.println(" S T O P ");
analogWrite(6, LOW);
analogWrite(11, 0);
analogWrite(3, LOW);
analogWrite(5, 0);
delay(400);
// 로봇 팔 작동 #1
while(angle1 > 72) {
angle1 -= 3;
servo1.write(angle1);
delay(20);
}
while(angle2 < 171) {
angle2 += 3;
servo2.write(angle2);
delay(20);
}
while(angle3 > 27) {
angle3 -= 3;
servo3.write(angle3);
delay(20);
}
while(angle4 > 45) {
angle4 -= 3;
servo4.write(angle4);
delay(20);
}

analogWrite(6, LOW);
analogWrite(11, 255);
analogWrite(3, LOW);
analogWrite(5, 230);
delay(300);
analogWrite(6, LOW);
analogWrite(11, 0);
analogWrite(3, LOW);
analogWrite(5, 0);
delay(100);
while(angle4 < 135) {

angle4 += 3;
servo4.write(angle4);
delay(20);
}

// 로봇 팔 작동 #2
while(angle2 > 90) {
angle2 -= 3;
servo2.write(angle2);
delay(15);
}
while(angle3 < 90) {
angle3 += 3;
servo3.write(angle3);
delay(15);
}
// 로봇 팔 작동 #3
while(angle1 < 123) {
angle1 += 3;
servo1.write(angle1);
delay(15);
}
// 로봇 팔 작동 #4
while(angle2 < 171) {
angle2 += 3;
servo2.write(angle2);
delay(15);
}
while(angle3 > 51) {
angle3 -= 3;
servo3.write(angle3);
delay(15);
}
while(angle4 > 90) {
angle4 -= 3;
servo4.write(angle4);
delay(15);
}
// 로봇 팔 작동 #5
while(angle2 > 193) {
angle2 -= 3;

servo2.write(angle2);
delay(15);
}
while(angle3 < 150) {
angle3 += 3;
servo3.write(angle3);
delay(15);
}
while(angle2 < 171) {
angle2 += 3;
servo2.write(angle2);
delay(20);
}
while(angle3 > 9) {
angle3 -= 3;
servo3.write(angle3);
delay(20);
}
// digitalWrite(TRIG, HIGH);
// delayMicroseconds(10);
// digitalWrite(TRIG, LOW);
// distance_cm = pulseIn(ECHO, HIGH) * 17/1000;
// Serial.print(distance_cm);
// Serial.println(" cm");
distance_cm = 100;
Serial.println(" G O ");
analogWrite(6, LOW);
analogWrite(11, 210);
analogWrite(3, LOW);
analogWrite(5, 210);
delay(100);

// 로봇팔 자동 코드 삽입 부분

}
} // while 문 종료
} // if(data == 'S') 부분 코드 종료
//여기에다가 라인트레이서 + 자동임무수행 코드 삽입.

if(data == 'X') //여기부터 RC car 조종 소스
{

analogWrite(6, LOW);
analogWrite(11, 0);
analogWrite(3, LOW);
analogWrite(5, 0);
}
if(data == '1') // <<- 조이스틱 좌측 상단
{
analogWrite(6, LOW);
analogWrite(11, 100);
analogWrite(3, LOW);
analogWrite(5, 255);
}
if(data == '2') //조이스틱 중앙 상단
{
analogWrite(6, LOW);
analogWrite(11, 255);
analogWrite(3, LOW);
analogWrite(5, 230);
}
if(data == '3') //조이스틱 우측 상단
{
analogWrite(6, LOW);
analogWrite(11, 255);
analogWrite(3, LOW);
analogWrite(5, 100);
}
if(data == '4') //조이스틱 좌측 중단
{
analogWrite(6, LOW);
analogWrite(11, 0);
analogWrite(3, LOW);
analogWrite(5, 200);
}
if(data == '5') //조이스틱 기본
{
analogWrite(6, LOW);
analogWrite(11, 0);
analogWrite(3, LOW);
analogWrite(5, 0);
}
if(data == '6') //조이스틱 우측 중단
{
analogWrite(6, LOW);
analogWrite(11, 200);
analogWrite(3, LOW);

analogWrite(5, 0);
}
if(data == '7') //조이스틱 좌측 하단
{
analogWrite(6, LOW);
analogWrite(11, 0);
analogWrite(3, 160);
analogWrite(5, 0);
}
if(data == '8') //조이스틱 중앙 하단
{
analogWrite(6, 160);
analogWrite(11, 0);
analogWrite(3, 150);
analogWrite(5, 0);
}
if(data == '9') //조이스틱 우측 하단
{
analogWrite(6, 160);
analogWrite(11, 0);
analogWrite(3, LOW);
analogWrite(5, 0);
}
/* 여기까지 바퀴 제어 부분
아래부터 로봇팔 제어 부분 */

if(data=='a')
{
if(angle1<170)
{
angle1 = angle1+3;
servo1.write(angle1); delay(servodelay);
}
}
if(data=='b')
{
if(angle1>10)
{
angle1 = angle1-3;
servo1.write(angle1); delay(servodelay);

}
}

// a 와 b가 2핀에 연결된 서브모터 통제

if(data=='d')
{
if(angle2<170)
{
angle2 = angle2+3;
servo2.write(angle2); delay(servodelay);
}
}
if(data=='c')
{
if(angle2>65)
{
angle2 = angle2-3;
servo2.write(angle2); delay(servodelay);
}
}

// c 와 d가 3핀에 연결된 서브모터 통제

if(data=='f')
{
if(angle3<170)
{
angle3 = angle3+3;
servo3.write(angle3); delay(servodelay);
}
}
if(data=='e')
{
if(angle3>10)
{
angle3 = angle3-3;
servo3.write(angle3); delay(servodelay);
}
}

// e 와 f가 4핀에 연결된 서브모터 통제

if(data=='g')
{
if(angle4<160)
{
angle4 = angle4+3;
servo4.write(angle4); delay(servodelay);
}

}
if(data=='h')
{
if(angle4>60)
{
angle4 = angle4-3;
servo4.write(angle4); delay(servodelay);
}
}

// g 와 h가 5핀에 연결된 서브모터 통제

} // if(Serial.available()) 문장의 끝
/*
Serial.print("angle 1 : ");
Serial.print(angle1,DEC);
Serial.print(" | angle 2 : "); //서보의 각도 피드백 코드.
Serial.print(angle2,DEC);
Serial.print(" | angle 3 : ");
Serial.print(angle3,DEC);
Serial.print(" | angle 4 : ");
Serial.println(angle4,DEC);
Serial.println("---------------------------------------------"); */
} // void loop() 문장의 끝