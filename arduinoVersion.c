#define rs 22
#define Rrw 23
#define enable 24

#define LCDDATA PORTD
#define LCDCOMMAND PORTD
#define RS_COMMAND 0
#define RS_DATA 1
#define WRITE 0
#define READ 1

#define d0 30
#define d1 31
#define d2 32
#define d3 33
#define d4 34
#define d5 35
#define d6 36
#define d7 37

#include <LiquidCrystal.h>

  
  LiquidCrystal lcd(rs, rw, enable, d0,d1,d2,d3,d4,d5,d6,d7);
  
void setup() {
  // put your setup code here, to run once:
  lcd.begin(20, 4);
  //lcd.setCursor(0,1);
  lcd.print("hello world!");
}

void loop() {
  // put your main code here, to run repeatedly:

}
