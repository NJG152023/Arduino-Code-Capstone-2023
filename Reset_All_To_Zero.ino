// Include the library
#include <TM1637Display.h>
//Written By Nikodem Bartnik - nikodembartnik.pl
#define STEPPER_PIN_1 9
#define STEPPER_PIN_2 10
#define STEPPER_PIN_3 11
#define STEPPER_PIN_4 12
int step_number = 0;
const int buttonPin = 2;  // the number of the pushbutton pin
// variables will change:
const int buttonPin1 = 5;  // the number of the pushbutton pin
// variables will change:
const int buttonPin2 = 6;  // the number of the pushbutton pin
// variables will change:
int buttonState = 0;  // variable for reading the pushbutton status
int buttonState1 = 0;  // variable for reading the pushbutton status
int buttonState2 = 0;  // variable for reading the pushbutton status

// Define the connections pins
#define CLK 3
#define DIO 4

// Create a display object of type TM1637Display
TM1637Display display = TM1637Display(CLK, DIO);

// Create an array that turns all segments ON
const uint8_t allON[] = {0xff, 0xff, 0xff, 0xff};

// Create an array that turns all segments OFF
const uint8_t allOFF[] = {0x00, 0x00, 0x00, 0x00};

// Create an array that sets individual segments per digit to display the word "dOnE"
const uint8_t done[] = {
  SEG_B | SEG_C | SEG_D | SEG_E | SEG_G,           // d
  SEG_A | SEG_B | SEG_C | SEG_D | SEG_E | SEG_F,   // O
  SEG_C | SEG_E | SEG_G,                           // n
  SEG_A | SEG_D | SEG_E | SEG_F | SEG_G            // E
};

// Create degree celsius symbol
const uint8_t celsius[] = {
  SEG_A | SEG_B | SEG_F | SEG_G,  // Degree symbol
  SEG_A | SEG_D | SEG_E | SEG_F   // C
};

void setup() {
 pinMode(STEPPER_PIN_1, OUTPUT);
 pinMode(STEPPER_PIN_2, OUTPUT);
 pinMode(STEPPER_PIN_3, OUTPUT);
 pinMode(STEPPER_PIN_4, OUTPUT);
 Serial.begin(9600);
 pinMode(buttonPin, INPUT);
 pinMode(buttonPin1, INPUT);
 pinMode(buttonPin2, INPUT);

}
	int i=0;
void loop() {
  // read the state of the pushbutton value:
  buttonState = digitalRead(buttonPin);
  buttonState1 = digitalRead(buttonPin1);
  buttonState2 = digitalRead(buttonPin2);
	// Set the brightness to 5 (0=dimmest 7=brightest)
	display.setBrightness(5);
	// Set all segments ON
//	display.setSegments(allON);

	//delay(2000);
	//display.clear();

   if (buttonState == HIGH) {
    for (int a= 0; a< 2048; a++){
      OneStep(false);
      delay(2);
    }
    Serial.print("button1 is on");
    Serial.print('\n');
    i=i+1;
   // display.showNumberDec(i);
    //delay(1000);
  }else {
    //for (int a= 0; a< 2048; a++){
     //OneStep(true);
     //delay(2);
   //}
   
    Serial.print("button1 is off");
    Serial.print('\n');
  }
   if (buttonState1 == HIGH) {
    for (int a= 0; a< 2048; a++){
      OneStep(true);
      delay(2);
    }
    Serial.print("button2 is on");
    Serial.print('\n');
    i=i-1;
   // display.showNumberDec(i);
   // delay(1000);
  }else {
    //for (int a= 0; a< 2048; a++){
     //OneStep(true);
     //delay(2);
   //}
   
    Serial.print("button2 is off");
    Serial.print('\n');
  }
     if (buttonState2 == HIGH) {
       for (int j=0 ; j<i;j++){
         for (int a= 0; a< 2048; a++){
         OneStep(true);
         delay(2);
        }
       }
       i=0;
  }
    display.showNumberDec(i);
    delay(500);

}
void OneStep(bool dir){
    if(dir){
switch(step_number){
  case 0:
  digitalWrite(STEPPER_PIN_1, HIGH);
  digitalWrite(STEPPER_PIN_2, LOW);
  digitalWrite(STEPPER_PIN_3, LOW);
  digitalWrite(STEPPER_PIN_4, LOW);
  break;
  case 1:
  digitalWrite(STEPPER_PIN_1, LOW);
  digitalWrite(STEPPER_PIN_2, HIGH);
  digitalWrite(STEPPER_PIN_3, LOW);
  digitalWrite(STEPPER_PIN_4, LOW);
  break;
  case 2:
  digitalWrite(STEPPER_PIN_1, LOW);
  digitalWrite(STEPPER_PIN_2, LOW);
  digitalWrite(STEPPER_PIN_3, HIGH);
  digitalWrite(STEPPER_PIN_4, LOW);
  break;
  case 3:
  digitalWrite(STEPPER_PIN_1, LOW);
  digitalWrite(STEPPER_PIN_2, LOW);
  digitalWrite(STEPPER_PIN_3, LOW);
  digitalWrite(STEPPER_PIN_4, HIGH);
  break;
} 
  }else{
    switch(step_number){
  case 0:
  digitalWrite(STEPPER_PIN_1, LOW);
  digitalWrite(STEPPER_PIN_2, LOW);
  digitalWrite(STEPPER_PIN_3, LOW);
  digitalWrite(STEPPER_PIN_4, HIGH);
  break;
  case 1:
  digitalWrite(STEPPER_PIN_1, LOW);
  digitalWrite(STEPPER_PIN_2, LOW);
  digitalWrite(STEPPER_PIN_3, HIGH);
  digitalWrite(STEPPER_PIN_4, LOW);
  break;
  case 2:
  digitalWrite(STEPPER_PIN_1, LOW);
  digitalWrite(STEPPER_PIN_2, HIGH);
  digitalWrite(STEPPER_PIN_3, LOW);
  digitalWrite(STEPPER_PIN_4, LOW);
  break;
  case 3:
  digitalWrite(STEPPER_PIN_1, HIGH);
  digitalWrite(STEPPER_PIN_2, LOW);
  digitalWrite(STEPPER_PIN_3, LOW);
  digitalWrite(STEPPER_PIN_4, LOW);
} 
  }
step_number++;
  if(step_number > 3){
    step_number = 0;
  }
}