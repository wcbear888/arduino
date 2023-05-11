
int apin = 8;
int bpin = 9;
int cpin = 10;
int dpin = 11;
int delaytime = 10;
int buttonpin =12;
int fanpin =7;
int buttonState =0;
bool GotInitPosition = false;
int updownDistince =55;
int fanrate =5;
void setup() {
  // put your setup code here, to run once:
  pinMode(apin, OUTPUT);
  pinMode(bpin, OUTPUT);
  pinMode(cpin, OUTPUT);
  pinMode(dpin, OUTPUT);
  pinMode(buttonpin,INPUT);
  pinMode (fanpin,OUTPUT);
   
}
void MotorDown()
{    digitalWrite(apin, HIGH);
    delay(delaytime);
    digitalWrite(apin, LOW);
    digitalWrite(bpin, HIGH);
    delay(delaytime);
    digitalWrite(bpin, LOW);
    digitalWrite(cpin, HIGH);
    delay(delaytime);
    digitalWrite(cpin, LOW);
    digitalWrite(dpin, HIGH);
    delay(delaytime);
    digitalWrite(dpin, LOW);
    }
void MotorUp()
{   


    digitalWrite(dpin, HIGH);
    delay(delaytime);
    digitalWrite(dpin, LOW);
        digitalWrite(cpin, HIGH);
    delay(delaytime);
    digitalWrite(cpin, LOW);
    digitalWrite(bpin, HIGH);
    delay(delaytime);
    digitalWrite(bpin, LOW);
       digitalWrite(apin, HIGH);
    delay(delaytime);
    digitalWrite(apin, LOW);

    }
void FanRun()
{
  for (int i=0;i<200;i++)
  {
    digitalWrite(fanpin, HIGH);
    delay(fanrate);
    digitalWrite(fanpin, LOW);
    delay(11-fanrate);
  }
  digitalWrite(fanpin, LOW);
  delay (100);
}
void loop() {
  // put your main code here, to run repeatedly:
  buttonState = digitalRead(buttonpin);
  if (buttonState == LOW && GotInitPosition == false)
  {
   
    MotorDown();
  }else
  {
   GotInitPosition = true;
   delaytime =3;
    for (int i=0;i<10;i++)
      {
        MotorUp();
      }
  delay(2000);
  }

  if (GotInitPosition ==true)
  {
    while  (true)
    {
      for (int i=0;i<updownDistince;i++)
      {
        MotorUp();
      }
        delay(100);
        FanRun();
      for (int i=0;i<updownDistince;i++)
      {
        MotorDown();
      }
      delay(500);
        buttonState = digitalRead(buttonpin);
        if (buttonState == HIGH)
        {
          delaytime =20;
          break;
        }
    }

  }
}
