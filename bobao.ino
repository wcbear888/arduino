#include <Servo.h>
#include <BluetoothSerial.h>
#include <EEPROM.h>
BluetoothSerial SerialBT;
TaskHandle_t Task1;
Servo myservo;
int servoPin = 16;

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
      if (delaytime < 1)
        delaytime = 1;
      if (delaytime>100)
      delaytime =100;
      Serial.println(delaytime);
      EEPROM.write(0, delaytime);
      EEPROM.commit();
    }
  }
}
void setup() {
  EEPROM.begin(1);
  delaytime = EEPROM.read(0);
  if (delaytime < 1)
    delaytime = 1;
  if (delaytime >100)
  delaytime =100;
  myservo.attach(servoPin);  // 設置舵機控制腳位
  Serial.begin(9600);
  SerialBT.begin("BEAR_BT");  //藍牙顯示名稱，可自行更改，需避免與他人重複命名


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
  // 0到180旋轉舵機，每次延時15毫秒
  //for (pos = 0; pos < 180; pos += 10) {
  // myservo.write(pos);
  // delay(1);
  //}
  myservo.write(60);
  delay(delaytime*100);
  myservo.write(0);
  delay(250);
}
