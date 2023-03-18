#include <Arduino.h>
#line 1 "C:\\Users\\rotem\\Desktop\\Programming\\Arduino C++\\ArduinoLCD_I2C\\ArduinoLCD_I2C.ino"
#include<Wire.h>
#include <LiquidCrystal_I2C.h>

LiquidCrystal_I2C lcd(0x27,16,2);

byte smiley[8] = {
  0b00000,
  0b00000,
  0b01010,
  0b00000,
  0b00000,
  0b10001,
  0b01110,
  0b00000
};
byte frownie[8] = {
    0b00000,
  0b00000,
  0b01010,
  0b00000,
  0b00000,
  0b01110,
  0b10001,
  0b00000
};

#line 27 "C:\\Users\\rotem\\Desktop\\Programming\\Arduino C++\\ArduinoLCD_I2C\\ArduinoLCD_I2C.ino"
void setup();
#line 39 "C:\\Users\\rotem\\Desktop\\Programming\\Arduino C++\\ArduinoLCD_I2C\\ArduinoLCD_I2C.ino"
void loop();
#line 94 "C:\\Users\\rotem\\Desktop\\Programming\\Arduino C++\\ArduinoLCD_I2C\\ArduinoLCD_I2C.ino"
void ClearLine(int lineNum);
#line 27 "C:\\Users\\rotem\\Desktop\\Programming\\Arduino C++\\ArduinoLCD_I2C\\ArduinoLCD_I2C.ino"
void setup()
{
    lcd.init();
	lcd.begin(16,2);
    lcd.backlight();
    lcd.createChar(0, smiley);
    lcd.createChar(1, frownie);
}

int rowNumber = 0;
bool growing = true;

void loop() {
    if(growing){
        ClearLine(0);
        lcd.setCursor(8-rowNumber,0);
        int firstLineLength = 1 + 2 * rowNumber;
        for (int i = 0; i < firstLineLength; i++)
        {
            lcd.write(byte(i%2 == 0 ? 0 : 1));
        }

        ClearLine(1);
        lcd.setCursor(7-rowNumber,1);
        for (int i = 0; i < firstLineLength + 2; i++)
        {
            lcd.write(byte(i%2 == 0 ? 0 : 1));
        }

        if (rowNumber < 6)
        {
            rowNumber += 1;
        }
        else
        {
            growing = false;
            rowNumber = 0;
        }
    }
    else{
        ClearLine(0);
        lcd.setCursor(rowNumber + 1,0);
        int firstLineLength = 15 - 2 * rowNumber;
        for (int i = 0; i < firstLineLength; i++)
        {
            lcd.write(byte(i%2 == 0 ? 0 : 1));
        }

        ClearLine(1);
        lcd.setCursor(rowNumber+2, 1);
        for (int i = 0; i < firstLineLength - 2; i++)
        {
            lcd.write(byte(i%2 == 0 ? 0 : 1));
        }
        
        if (rowNumber < 6)
        {
            rowNumber += 1;
        }
        else{
            growing = true;
            rowNumber = 0;
        }
    }
    delay(700);
}

void ClearLine(int lineNum){
    lcd.setCursor(0,lineNum);
    lcd.print("                ");
}

