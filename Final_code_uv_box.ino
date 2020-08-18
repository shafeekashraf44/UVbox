#include "Countimer.h"
#include <TM1637Display.h>

////Constants//////////////////////////
const uint8_t OFF[] = {0, 0, 0, 0};
//const uint8_t PLAY[] = {B01110011, B00111110, B01101101, B01110110}; //PUSH
const uint8_t PLAY[] = {B00111111, B00111111, B00111111, B00111111};  //0000

//TM1637Display display(23,22);  ///(clk,data)
TM1637Display display(2, 3);

int mins, secs;
int countr;

Countimer tDown;
int pressCount = 0, value, reed, releaseCount = 0, k = 0, set, set2;
int reedcount, reedcount2, rcount;
///////////push
const int button = A1;

void setup()
{
  Serial.begin(9600);
  ///////////push
  pinMode(button, INPUT);
  pinMode(A0, INPUT);
  pinMode(5, OUTPUT);
  /////////////display
  display.setBrightness(0x0c);
  display.setSegments (OFF);
  ////////////////
  tDown.setCounter(0, 4, 0, tDown.COUNT_DOWN, tDownComplete);
  // Call print_time2() method every 1s.
  tDown.setInterval(print_time2, 1000);
  pinMode(4, OUTPUT);
  display.setSegments (PLAY);
}

void loop()
{
  tDown.run();
  value =  analogRead(button);
  reed = digitalRead(A0);
  //////////////////////////////////////////////
  if ((value == 0) && (pressCount == 0) && (reed == LOW))
  {
    releaseCount = releaseCount + 1;
    pressCount = 1;
    digitalWrite(5, HIGH);
    delay(50);
    digitalWrite(5, LOW);
  }
  if (value > 0)
  {
    set = set + 1;
  }
  if (set > 1000)
  {
    pressCount = 0;
    set = 0;
  }
  if ((reed == HIGH) && (rcount == 1))
  {
    digitalWrite(4, LOW);
    tDown.pause();
    /////////////////////////////////
    rcount = 2;
    digitalWrite(5, HIGH);
    delay(500);
    digitalWrite(5, LOW);
    delay(500);
    digitalWrite(5, HIGH);
    delay(500);
    digitalWrite(5, LOW);
    delay(500);

  }
  if ((reed == LOW) && (rcount == 2))
  {
    digitalWrite(5, HIGH);
    delay(50);
    digitalWrite(5, LOW);
    digitalWrite(4, HIGH);
    tDown.start();
    rcount = 1;
  }
  if ((releaseCount == 1) && (rcount == 0))
  {
    digitalWrite(4, HIGH);
    tDown.start();
    rcount = 1;
  }
  if (releaseCount == 2)
  {
    digitalWrite(4, LOW);
    tDown.pause();
    releaseCount = 0;
    k = 1;
    rcount = 0;
  }
  if ((value == 0) && (k == 1))
  {
    set2 = set2 + 1;
  }
  if (set2 > 30000)
  {
    tDown.restart();
    display.setSegments (PLAY);
    digitalWrite(4, LOW);
    tDown.pause();
    set2 = 0;
    pressCount = 1;
    releaseCount = 0;
    set = 0;
    Serial.print("Reset");
    rcount = 0;
  }

}

void print_time2()
{
  //Serial.print("Timer: ");
  //Serial.println(tDown.getCurrentTime());
  mins = tDown.getCurrentMinutes();
  secs = tDown.getCurrentSeconds();
  Serial.println(mins);
  Serial.println(secs);
  display.showNumberDecEx(secs, 0, true, 2, 2);
  display.showNumberDecEx(mins, 0x80 >> 3, true, 2, 0);
}

void tDownComplete()
{
  digitalWrite(4, LOW);
  tDown.pause();
  display.setSegments (PLAY);
  pressCount = 0;
  releaseCount = 0;
  set = 0;
  set2 = 0;
  rcount = 0;
  digitalWrite(5, HIGH);
  delay(500);
  digitalWrite(5, LOW);
  delay(500);
  digitalWrite(5, HIGH);
  delay(500);
  digitalWrite(5, LOW);
  delay(500);
  digitalWrite(5, HIGH);
  delay(500);
  digitalWrite(5, LOW);
  delay(500);
  digitalWrite(5, HIGH);
  delay(500);
  digitalWrite(5, LOW);
  delay(500);
  digitalWrite(5, HIGH);
  delay(500);
  digitalWrite(5, LOW);
  delay(500);
}
