#include <Servo.h>
#include <BluetoothSerial.h>
#include <EEPROM.h>
BluetoothSerial SerialBT;
TaskHandle_t Task1;
Servo myservo;
int servoPin = 16;//GPIO 16 (RX2)
int motorPin =23;
int pos = 0;  // 定義舵機轉動位置
byte delaytime = 10;


void Task1_senddata(void* pvParameters) {
  //無窮迴圈
  for (;;) {
    delay(10);
    //BT
    if (Serial.available()) {
      SerialBT.write(Serial.read());
    }
    if (SerialBT.available()) {
      auto str = SerialBT.readString();
      if (str.c_str()[0] == '1')
        //delaytime = atoi(SerialBT.readString().c_str());
        //if (delaytime > 1000)
        delaytime += 1 * str.length();
      else if (str.c_str()[0] == '2')
        delaytime -= 1 * str.length();
      if (delaytime < 2)
        delaytime = 2;
      if (delaytime > 10)
        delaytime = 10;
      Serial.println(delaytime);
      EEPROM.write(0, delaytime);
      EEPROM.commit();
     
    }
  }
}
void setup() {
  pinMode(motorPin, OUTPUT);
    digitalWrite(motorPin, LOW); 
  EEPROM.begin(1);  delaytime = EEPROM.read(0);
  if (delaytime < 2)
    delaytime = 2;
  if (delaytime > 10)
    delaytime = 10;
    myservo.attach(servoPin);  // 設置舵機控制腳位
      myservo.write(0);
     
    delay(200);
    myservo.write(60);
   
    delay(200);  
    myservo.write(0);
   
    delay(200);  
 myservo.write(60);
 
    delay(2000);  
  Serial.begin(9600);
  SerialBT.begin("BEAR_BT");  //藍牙顯示名稱，可自行更改，需避免與他人重複命名
   digitalWrite(motorPin, HIGH); 

  //在核心0啟動任務1
  xTaskCreatePinnedToCore(
    Task1_senddata, /*任務實際對應的Function*/
    "Task1",        /*任務名稱*/
    10000,          /*堆疊空間*/
    NULL,           /*無輸入值*/
    0,              /*優先序0*/
    &Task1,         /*對應的任務變數位址*/
    0);             /*指定在核心0執行 */
}

void loop() {
    digitalWrite(motorPin, HIGH); 
     Serial.print("delay:");
        Serial.println(delaytime);
  myservo.write(60);
  delay(delaytime * 1000);
  
  digitalWrite(motorPin, LOW); 
  myservo.write(0);
  delay(200);
}
