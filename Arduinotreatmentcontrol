//uv dry contact relay is normally open conact--0
#include <Wire.h>
#include <Adafruit_RGBLCDShield.h>
#include <utility/Adafruit_MCP23017.h>
Adafruit_RGBLCDShield lcd = Adafruit_RGBLCDShield();
#define RED 0x1
#define YELLOW 0x3
#define GREEN 0x2
#define TEAL 0x6
#define BLUE 0x4
#define VIOLET 0x5
#define WHITE 0x7


void statuss() {
  delay(5);
 int washlevel = analogRead(A10);// *100/1023 percentage
  int graylevel = analogRead(A11);
  int blacklevel = analogRead(A12);
  washlevel = round ((washlevel-116)*2/5);
  graylevel= round ((graylevel-116)*2/5);
  blacklevel= round ((blacklevel-116)*2/5);      
  lcd.setCursor(0, 0);
  lcd.print("wash");lcd.print(washlevel);lcd.print("%"); 
  lcd.print(" gray");lcd.print(graylevel); lcd.print("%    ");
  lcd.setCursor(0, 1);
  lcd.print("    black:");lcd.print(blacklevel); lcd.print("%    ");
}

struct myStructure   //give it a better name ;-)
{
  byte LedPin;       //LED connects here, HIGH makes LED light
  byte ButtonPin;    //Switch connects here
  byte ButtonState;  //Last state of ButtonPin
  byte LedState;     //Current state of LED

  //Structure Functions
  void SwitchToggle()
  {
    byte val  = digitalRead(ButtonPin);
    delay(10);
    byte val2 = digitalRead(ButtonPin);

    if (val == val2)
    {
      if (val != ButtonState)
      {
        ButtonState = val;
        if (val == LOW)
        {
          if (LedState == LOW)
          {
            LedState = HIGH;
            digitalWrite(LedPin, HIGH);
          }
          else
          {
            LedState = LOW;
            digitalWrite(LedPin, LOW);
          }
        }
      }
    }
  } //END of switchtoggle()

  void begin()
  {
    pinMode(LedPin, OUTPUT);
    digitalWrite(LedPin, LOW);
    pinMode(ButtonPin, INPUT_PULLUP);
    ButtonState = digitalRead(ButtonPin);
  } //END of begin()

};  //END of myStructure
////////////////////8 auto / 9 manual  uv relay10 reads 1   back pressure11 reads 1
/////A10:Wash water    A11: Graywater   A12: Blackwater
//Create objects:
myStructure blacktank = //blackwater tank 35,34 black then red
{ 37, 2  //LED pin , Switch pin
};
myStructure washtank = //wash water tank 36, 39
{38, 14  //LED pin , Switch pin
};
myStructure graytank = //graywater tank 42,45
{44, 19  //LED pin , Switch pin
};
myStructure slowstart =//slow start 29,28
{31, 17  //LED pin , Switch pin
};
myStructure graymembrane =//greywater mmbrane 23,22 
{25, 6  //LED pin , Switch pin
};
myStructure blackmembrane =//blackwater membrane 24,27
{26, 15  //LED pin , Switch pin
};
myStructure washproduct =//product washwater 41,40
{43, 7   //LED pin , Switch pin
};
myStructure grayproduct =//product graywater 12,13
{49, 16  //LED pin , Switch pin
};
myStructure blackreject =//reject blackwater 47,46
{48, 4  //LED pin , Switch pin
};
myStructure grayreject =//reject graywater 30,33
{32, 5  //LED pin , Switch pin
};
myStructure pump =
{55, 18  //LED pin , Switch pin
};
myStructure uv =
{54, 3  //LED pin , Switch pin
};
// etc.

//**********************************************************************

void setup()
{
 blacktank.begin();
 washtank.begin();
 graytank.begin();
 slowstart.begin();
 graymembrane.begin();
 blackmembrane.begin();
 washproduct.begin();
 grayproduct.begin();
 blackreject.begin();
 grayreject.begin();
 pump.begin();
 uv.begin();
 
 lcd.begin(16, 2);
 lcd.print("Starting...");
 lcd.setBacklight(GREEN);
 delay(500);
} //End of setup()


void loop()
{statuss();
 blacktank.SwitchToggle();
 washtank.SwitchToggle();
 graytank.SwitchToggle();
 slowstart.SwitchToggle();
 graymembrane.SwitchToggle();
 blackmembrane.SwitchToggle();
 washproduct.SwitchToggle();
 grayproduct.SwitchToggle();
 blackreject.SwitchToggle();
 grayreject.SwitchToggle();
 pump.SwitchToggle();
 uv.SwitchToggle();
} //End of loop()
