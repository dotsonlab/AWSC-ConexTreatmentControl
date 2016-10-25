//START --- add all defines of pins to variables
int WWbuttonPin = 19;
int INTbuttonPin = 2;
int FILTbuttonPin = 14;
int RRObuttonPin = 16;
int RNFbuttonPin = 15;
int SSbuttonPin = 17;
int SendbuttonPin = 6;

int SSswitchPin = 31;
int ITswitchPin = 44;
int ROswitchPin = 49;
int GWswitchPin = 37;
int NFswitchPin = 26;
int WWswitchPin = 38;
//END --- add all defines of pins to variables

int InUse = 0;

//START --- set initial button states
int SSbuttonState;
int SSbuttonAction = 0;

int WWbuttonState;
int WWbuttonAction = 0;

int INTbuttonState;
int INTbuttonAction = 0;

int FILTbuttonState;
int FILTbuttonAction = 0;

int SendbuttonState;
int SendbuttonAction = 0;

int RRObuttonState;
int RRObuttonAction = 0;

int RNFbuttonState;
int RNFbuttonAction = 0;
//END --- set initial button states

//START --- setup
void setup() {
  //Serial.begin(9600);

  //hand control of soft-start
  pinMode(SSbuttonPin, INPUT);       // Set the switch pin as input
  pinMode(SSswitchPin, OUTPUT);
  
  //operational configuration buttons
  pinMode(WWbuttonPin, INPUT);       // Set the switch pin as input
  pinMode(INTbuttonPin, INPUT);       // Set the switch pin as input
  pinMode(FILTbuttonPin, INPUT);       // Set the switch pin as input
  pinMode(RRObuttonPin, INPUT);       // Set the switch pin as input
  pinMode(RNFbuttonPin, INPUT);       // Set the switch pin as input

  //MWWvalve switches
  pinMode(ITswitchPin, OUTPUT);      // Set to control the actuator switch
  pinMode(ROswitchPin, OUTPUT);      // Set to control the actuator switch
  pinMode(GWswitchPin, OUTPUT);      // Set to control the actuator switch
  pinMode(NFswitchPin, OUTPUT);      // Set to control the actuator switch
  pinMode(WWswitchPin, OUTPUT);      // Set to control the actuator switch
  //buttonState = digitalRead(buttonPin);   // read the initial state
}
//END --- setup

//START --- loop
void loop() {
  MakeWashWater();
  MakeIntWater();
  FilterGW();
  RinseNF();
  RinseRO();
  SoftStart();
  SendBack();
  //delay(1000);
  //Serial.print(InUse); 
}
//END --- loop

//START --- functions
void MakeWashWater() {
  int MWWval = digitalRead(WWbuttonPin);      // read input MWWvalue and store it in MWWval
  delay(10);                         // 10 milliseconds is a good amount of time
  int MWWval2 = digitalRead(WWbuttonPin);     // read the input again to check for bounces
  if (MWWval == MWWval2) {                 // make sure we got 2 consistant readings!
    if (MWWval != WWbuttonState) {          // the button state has changed!
      if (MWWval == LOW) {                // check if the button is pressed
        if ((WWbuttonAction == 0 ) && (InUse == 0)) {          // is the light off?
          WWbuttonAction = 1;               // turn light on!
          InUse = 1;
          digitalWrite(ITswitchPin, HIGH);  //open intermediate tank
          digitalWrite(ROswitchPin, HIGH);  //open RO membrane
        } else if (WWbuttonAction == 1 ){
          WWbuttonAction = 0;               // turn light off!
          InUse = 0;
          digitalWrite(ITswitchPin, LOW);   //close intermediate tank
          digitalWrite(ROswitchPin, LOW);   //close RO membrane
        }
          //else{}
      }
    }
    WWbuttonState = MWWval;                 // save the new state in our variable
  }
}

void RinseRO() {
  int RROval = digitalRead(RRObuttonPin);      // read input value and store it in val
  delay(10);                         // 10 milliseconds is a good amount of time
  int RROval2 = digitalRead(RRObuttonPin);     // read the input again to check for bounces
  if (RROval == RROval2) {                 // make sure we got 2 consistant readings!
    if (RROval != RRObuttonState) {          // the button state has changed!
      if (RROval == LOW) {                // check if the button is pressed
        if ((RRObuttonAction == 0)  && (InUse == 0)) {          // is the light off?
          RRObuttonAction = 1;               // turn light on!
          InUse = 1;
          digitalWrite(WWswitchPin, HIGH);  //open intermediate tank
          digitalWrite(ROswitchPin, HIGH);  //open RO membrane
        } else if (RRObuttonAction == 1) {
          RRObuttonAction = 0;               // turn light off!
          InUse = 0;
          digitalWrite(WWswitchPin, LOW);   //close intermediate tank
          digitalWrite(ROswitchPin, LOW);   //close RO membrane
        }
          //else{}
      }
    }
    RRObuttonState = RROval;                 // save the new state in our variable
  }
}

void MakeIntWater() {
  int MIWval = digitalRead(INTbuttonPin);      // read input value and store it in val
  delay(10);                         // 10 milliseconds is a good amount of time
  int MIWval2 = digitalRead(INTbuttonPin);     // read the input again to check for bounces
  if (MIWval == MIWval2) {                 // make sure we got 2 consistant readings!
    if (MIWval != INTbuttonState) {          // the button state has changed!
      if (MIWval == LOW) {                // check if the button is pressed
        if ((INTbuttonAction == 0)  && (InUse == 0)) {          // is the light off?
          INTbuttonAction = 1;               // turn light on!
          InUse = 1;
          digitalWrite(GWswitchPin, HIGH);  //open greywater tank
          digitalWrite(NFswitchPin, HIGH);  //open NF membrane
        } else if (INTbuttonAction == 1){
          INTbuttonAction = 0;               // turn light off!
          InUse = 0;
          digitalWrite(GWswitchPin, LOW);   //close greywater tank
          digitalWrite(NFswitchPin, LOW);   //close NF membrane
        }
          //else{}
      }
    }
    INTbuttonState = MIWval;                 // save the new state in our variable
  }
}

void RinseNF() {
  int RNFval = digitalRead(RNFbuttonPin);      // read input value and store it in val
  delay(10);                         // 10 milliseconds is a good amount of time
  int RNFval2 = digitalRead(RNFbuttonPin);     // read the input again to check for bounces
  if (RNFval == RNFval2) {                 // make sure we got 2 consistant readings!
    if (RNFval != RNFbuttonState) {          // the button state has changed!
      if (RNFval == LOW) {                // check if the button is pressed
        if ((RNFbuttonAction == 0 ) && (InUse == 0)) {          // is the light off?
          RNFbuttonAction = 1;               // turn light on!
          InUse = 1;
          digitalWrite(WWswitchPin, HIGH);  //open intermediate tank
          digitalWrite(NFswitchPin, HIGH);  //open RO membrane
        } else if (RNFbuttonAction == 1 ){
          RNFbuttonAction = 0;               // turn light off!
          InUse = 0;
          digitalWrite(WWswitchPin, LOW);   //close intermediate tank
          digitalWrite(NFswitchPin, LOW);   //close RO membrane
        }
          //else{}
      }
    }
    RNFbuttonState = RNFval;                 // save the new state in our variable
  }
}

void FilterGW() {
  int Fval = digitalRead(FILTbuttonPin);      // read input value and store it in val
  delay(10);                         // 10 milliseconds is a good amount of time
  int Fval2 = digitalRead(FILTbuttonPin);     // read the input again to check for bounces
  if (Fval == Fval2) {                 // make sure we got 2 consistant readings!
    if (Fval != FILTbuttonState) {          // the button state has changed!
      if (Fval == LOW) {                // check if the button is pressed
        if ((FILTbuttonAction == 0)  && (InUse == 0)) {          // is the light off?
          FILTbuttonAction = 1;               // turn light on!
          InUse = 1;
          digitalWrite(GWswitchPin, HIGH);  //open greywater tank
        } else if (FILTbuttonAction == 1) {
          FILTbuttonAction = 0;               // turn light off!
          InUse = 0;
          digitalWrite(GWswitchPin, LOW);   //close greywater tank
        }
          //else {}
      }
    }
    FILTbuttonState = Fval;                 // save the new state in our variable
  }
}
void SendBack() {
  int sval = digitalRead(SendbuttonPin);      // read input value and store it in val
  delay(10);                         // 10 milliseconds is a good amount of time
  int sval2 = digitalRead(SendbuttonPin);     // read the input again to check for bounces
  if (sval == sval2) {                 // make sure we got 2 consistant readings!
    if (sval != SendbuttonState) {          // the button state has changed!
      if (sval == LOW) {                // check if the button is pressed
        if ((SendbuttonAction == 0)  && (InUse == 0)) {          // is the light off?
          SendbuttonAction = 1;               // turn light on!
          InUse = 1;
          digitalWrite(ITswitchPin, HIGH);  //open greywater tank
        } else if (SendbuttonAction == 1) {
          SendbuttonAction = 0;               // turn light off!
          InUse = 0;
          digitalWrite(ITswitchPin, LOW);   //close greywater tank
        }
          //else {}
      }
    }
    SendbuttonState = sval;                 // save the new state in our variable
  }
}
void SoftStart() {
  int val = digitalRead(SSbuttonPin);      // read input value and store it in val
  delay(10);                         // 10 milliseconds is a good amount of time
  int val2 = digitalRead(SSbuttonPin);     // read the input again to check for bounces
  if (val == val2) {                 // make sure we got 2 consistant readings!
    if (val != SSbuttonState) {          // the button state has changed!
      if (val == LOW) {                // check if the button is pressed
        if (SSbuttonAction == 0) {          // is the light off?
          SSbuttonAction = 1;               // turn light on!
          digitalWrite(SSswitchPin, HIGH);
        } else {
          SSbuttonAction = 0;               // turn light off!
          digitalWrite(SSswitchPin, LOW);
        }
      }
    }
    SSbuttonState = val;                 // save the new state in our variable
  }
}

//END --- functions[
