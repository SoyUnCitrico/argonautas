#include "Arduino.h"
#include "SoftwareSerial.h"
#include "DFRobotDFPlayerMini.h"

#define SWT1 6
#define SWT2 7
//#define SWT3 5
//#define SWT4 4

SoftwareSerial mySerial1(10, 11);
SoftwareSerial mySerial2(12, 13); 
//SoftwareSerial mySerial3(8, 9); 
//SoftwareSerial mySerial4(2, 3);

DFRobotDFPlayerMini player1, player2, player3, player4;
bool entrada, entrada2, entrada3, entrada4;
bool reproduciendo, reproduciendo2, reproduciendo3, reproduciendo4;
int pista, pista2, pista3, pista4;
 
void setup()
{
  pinMode(SWT1,INPUT);
  pinMode(SWT2,INPUT);
//  pinMode(SWT3,INPUT);
//  pinMode(SWT4,INPUT);
  
  mySerial1.begin(9600);
  mySerial2.begin(9600);
//  mySerial3.begin(9600);
//  mySerial4.begin(9600);
  
  Serial.begin(115200);
  
  entrada = 1; 
  entrada2 = 0;
  entrada3 = 0;
  entrada4 = 0;
  reproduciendo = reproduciendo2 = reproduciendo3 = reproduciendo4 = false;
  
  player1.begin(mySerial1);
  player1.volume(25);  //Set volume value (0~30).
  player1.outputDevice(DFPLAYER_DEVICE_SD);
  
  player2.begin(mySerial2);
  player2.volume(25);
  player2.outputDevice(DFPLAYER_DEVICE_SD);

//  player3.begin(mySerial3);
//  player3.volume(25);  
//  player3.outputDevice(DFPLAYER_DEVICE_SD);
//
//  player4.begin(mySerial4);
//  player4.volume(25);  
//  player4.outputDevice(DFPLAYER_DEVICE_SD);
  
}

void loop() {
////////TELEFONO 1
//entrada = digitalRead(SWT1);
//if(entrada == 0 && reproduciendo == 0) {
//  pista = int(random(1,31));
//  //delay(3000);
//  player1.play(pista);
//  Serial.println("reproduciendo");
//  Serial.println(pista);
//
//
////  PRUEBA
////  for(int i = 1; i <= 31; i++) {
////    player1.play(i);
////    delay(1000);
////    Serial.println("reproduciendo");
////    Serial.println(i);
////  }
//
//  reproduciendo = true;
//} else if(entrada == 1 && reproduciendo == 1) {
//  player1.stop();
//  reproduciendo =false;
//}




////////TELEFONO 2
entrada2 = digitalRead(SWT2);
if(entrada2 == 1 && reproduciendo2 == 0) {
  pista2 = int(random(1,31));
  //delay(3000);
  player2.play(pista2);
  Serial.println("reproduciendo");
  Serial.println(pista2);
  reproduciendo = 1;
  
} else if(entrada2 == 0 && reproduciendo2 == 1) {
  player2.stop();
  reproduciendo2 = 0;
}



////////TELEFONO 3
//entrada3 = digitalRead(SWT3);
//if(entrada3 == 1 && reproduciendo3 == 0) {
//  pista3 = int(random(1,31));
//  delay(1000);
//  player3.play(pista3);
//  Serial.println("reproduciendo");
//  Serial.println(pista3);
//  reproduciendo = 1;
//} else if(entrada3 == 0 && reproduciendo3 == 1) {
//  player3.stop();
//  reproduciendo =0;
//}


////////TELEFONO 4
//entrada4 = digitalRead(SWT4);
//if(entrada4 == 1 && reproduciendo4 == 0) {
//  pista4 = int(random(1,31));
//  delay(1000);
//  player4.play(pista4);
//  Serial.println("reproduciendo");
//  Serial.println(pista4);
//  reproduciendo4 = 1;
//
//} else if(entrada4 == 0 && reproduciendo4 == 1) {
//  player4.stop();
//  reproduciendo4 = 0;
//}


  if (player1.available()) 
    printDetail(player1.readType(), player1.read()); 
    
  if (player2.available()) 
    printDetail(player2.readType(), player2.read()); 
  
//  if (player3.available()) 
//    printDetail(player3.readType(), player3.read()); 
//    
//  if (player4.available()) 
//    printDetail(player4.readType(), player4.read()); 
  
}

void printDetail(uint8_t type, int value){
  switch (type) {
    case TimeOut:
      Serial.println(F("Time Out!"));
      break;
    case WrongStack:
      Serial.println(F("Stack Wrong!"));
      break;
    case DFPlayerCardInserted:
      Serial.println(F("Card Inserted!"));
      break;
    case DFPlayerCardRemoved:
      Serial.println(F("Card Removed!"));
      break;
    case DFPlayerCardOnline:
      Serial.println(F("Card Online!"));
      break;
    case DFPlayerPlayFinished:
      Serial.print(F("Number:"));
      Serial.print(value);
      Serial.println(F(" Play Finished!"));
      break;
    case DFPlayerError:
      Serial.print(F("DFPlayerError:"));
      switch (value) {
        case Busy:
          Serial.println(F("Card not found"));
          break;
        case Sleeping:
          Serial.println(F("Sleeping"));
          break;
        case SerialWrongStack:
          Serial.println(F("Get Wrong Stack"));
          break;
        case CheckSumNotMatch:
          Serial.println(F("Check Sum Not Match"));
          break;
        case FileIndexOut:
          Serial.println(F("File Index Out of Bound"));
          break;
        case FileMismatch:
          Serial.println(F("Cannot Find File"));
          break;
        case Advertise:
          Serial.println(F("In Advertise"));
          break;
        default:
          break;
      }
      break;
    default:
      break;
  }
}
