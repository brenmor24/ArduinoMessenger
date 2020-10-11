int values[64];
int term = 0;
int valuesCounter = 0;
char letters[32];
int lettersCounter = 0;
String currentValues;

#include <LiquidCrystal.h>
#include "IRremote.h"

LiquidCrystal lcd(7, 8, 9, 10, 11, 12);

int receiver = 13; 

IRrecv irrecv(receiver);  
decode_results results; 

void setup() {
  Serial.begin(9600);
  irrecv.enableIRIn();
  lcd.begin(16, 2);
  lcd.print("SEND A MESSAGE!");
}

void loop() {
  if (irrecv.decode(&results)) {
    translateIR(); 
    irrecv.resume();
  }
}

void translateIR() {
  switch(results.value){
  case 0xFF22DD: Serial.println("BACKSPACE"); //fast back button   
  term = term - 2;
  values[term] = 0;
  values[term + 1] = 0;
  displayMessage( );
  break;
  case 0xFF02FD: Serial.println("CLEARED"); // pause/playbutton
  lcd.clear();  
  for (int i = 0; i < 64; i++) {
    values[i] = 0;
  }
  for (int i = 0; i < 32; i++) {
    letters[i] = ' ';
  }
  term = 0;
  break;
  case 0xFF9867: Serial.println("SPACE"); //equal button
  values[term] = 0;
  term = term + 1;
  values[term] = 0;
  term = term + 1;
  displayMessage( );
  break;
  case 0xFF6897: Serial.println("0");    
    values[term] = 0;
    term = term + 1;
    displayMessage( );
  break;
  case 0xFF30CF: Serial.println("1");    
    values[term] = 1;
    term = term + 1;
    displayMessage( );
  break;
  case 0xFF18E7: Serial.println("2");    
    values[term] = 2;
    term = term + 1;
    displayMessage( );
  break;
  case 0xFF7A85: Serial.println("3");    
    values[term] = 3;
    term = term + 1;
    displayMessage( );
  break;
  case 0xFF10EF: Serial.println("4");    
    values[term] = 4;
    term = term + 1;
    displayMessage( );
  break;
  case 0xFF38C7: Serial.println("5");    
    values[term] = 5;
    term = term + 1;
    displayMessage( );
  break;
  case 0xFF5AA5: Serial.println("6");    
    values[term] = 6;
    term = term + 1;
    displayMessage( );
  break;
  case 0xFF42BD: Serial.println("7");    
    values[term] = 7;
    term = term + 1;
    displayMessage( );
  break;
  case 0xFF4AB5: Serial.println("8");    
    values[term] = 8;
    term = term + 1;
    displayMessage( );
  break;
  case 0xFF52AD: Serial.println("9");    
    values[term] = 9;
    term = term + 1;
    displayMessage( );
  break;
  case 0xFFFFFFFF: Serial.println("REPEAT");
  break;  
  default: 
    Serial.println("ERROR");
  }
  delay(500);
}

void displayMessage( ) {
if ( term % 2 == 0) { 
  for (int i = 0; i < 32; i++) {
    currentValues = String(values[valuesCounter]) + String(values[valuesCounter + 1]);    
    if (currentValues != "00") {
      letters[lettersCounter] = 'A' + currentValues.toInt() - 1;
    }
    else if (currentValues == "00") {
      letters[lettersCounter] = ' ';
    }
    valuesCounter = valuesCounter + 2;
    lettersCounter = lettersCounter + 1;
  } 
  for (int i = 0; i < 32; i++) {
    lcd.setCursor(i % 16, i / 16);
    lcd.print(letters[i]);
  }
valuesCounter = 0;
lettersCounter = 0;
}
}
