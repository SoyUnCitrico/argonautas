#include "Arduino.h"
#include "SoftwareSerial.h"
#include "DFRobotDFPlayerMini.h"

#define SWT1 6
#define SWT2 7
#define SWT3 5
#define SWT4 4
#define SWT5 22

SoftwareSerial mySerial1(11, 10);
SoftwareSerial mySerial2(13, 12); 
SoftwareSerial mySerial3(9, 8); 
SoftwareSerial mySerial4(3, 2);


DFRobotDFPlayerMini player1, player2, player3, player4, player5;
bool entrada, entrada2, entrada3, entrada4, entrada5;
bool reproduciendo, reproduciendo2, reproduciendo3, reproduciendo4, reproduciendo5;
int pista, pista2, pista3, pista4, pista5;
String lecturaBT;
int ledPIN = 17;

void setup()
{
  pinMode(SWT1,INPUT);
  pinMode(SWT2,INPUT);
  pinMode(SWT3,INPUT);
  pinMode(SWT4,INPUT);
  pinMode(SWT5,INPUT);
  
  mySerial1.begin(9600);
  mySerial2.begin(9600);
  mySerial3.begin(9600);
  mySerial4.begin(9600);
  Serial3.begin(9600);
  // MODULO HC-05
  Serial1.begin(115200);
  Serial1.write("INICIANDO BT...");
  // SERIAL USB
  Serial.begin(115200);
  Serial.println("INICIANDO USB...");
  // Declaración de estado inicial de los telefonos
  entrada = 0; 
  entrada2 = 0;
  entrada3 = 0;
  entrada4 = 0;
  entrada5 = 0;
  
  reproduciendo = reproduciendo2 = reproduciendo3 = reproduciendo4 = reproduciendo5 = false;
  
  player1.begin(mySerial1);
  player1.volume(15);  //Set volume value (0~30).
  player1.outputDevice(DFPLAYER_DEVICE_SD);
  
  player2.begin(mySerial2);
  player2.volume(15);
  player2.outputDevice(DFPLAYER_DEVICE_SD);

  player3.begin(mySerial3);
  player3.volume(15);  
  player3.outputDevice(DFPLAYER_DEVICE_SD);

  player4.begin(mySerial4);
  player4.volume(15);  
  player4.outputDevice(DFPLAYER_DEVICE_SD);
  
  player5.begin(Serial3);
  player5.volume(15);
  player5.outputDevice(DFPLAYER_DEVICE_SD);
  
  pinMode(ledPIN, OUTPUT);
}

void loop() {
//////TELEFONO 1 
entrada = digitalRead(SWT1);
if(entrada == 0 && reproduciendo == 0) {
  pista = int(random(1,31));
  delay(200);
  player1.play(pista);
  Serial.println("reproduciendo 1");
  Serial.println(pista);
  reproduciendo = 1;

} else if(entrada == 1 && reproduciendo == 1) {
  Serial.println("STOP  1");
  player1.stop();
  reproduciendo = 0;
}


////////TELEFONO 2
entrada2 = digitalRead(SWT2);
if(entrada2 == 0 && reproduciendo2 == 0) {
  pista2 = int(random(1,31));
  delay(200);
  player2.play(pista2);
  Serial.println("reproduciendo 2");
  Serial.println(pista2); 
  reproduciendo2 = 1;
} else if(entrada2 == 1 && reproduciendo2 == 1) {
  Serial.println("STOP 2");
  player2.stop();
  reproduciendo2 = 0;
}



//////TELEFONO 3 
entrada3 = digitalRead(SWT3);
if(entrada3 == 0 && reproduciendo3 == 0) {
  pista3 = int(random(1,31));
  delay(200);
  player3.play(pista3);
  Serial.println("reproduciendo3");
  Serial.println(pista3);
  reproduciendo3 = 1;
  
} else if(entrada3 == 1 && reproduciendo3 == 1) {
  Serial.println("STOP 3");
  player3.stop();
  reproduciendo3 = 0;
}


//////TELEFONO 4
entrada4 = digitalRead(SWT4);
if(entrada4 == 0 && reproduciendo4 == 0) {
  pista4 = int(random(1,31));
  delay(200);
  player4.play(pista4);
  Serial.println("reproduciendo4");
  Serial.println(pista4);
  reproduciendo4 = 1;

} else if(entrada4 == 1 && reproduciendo4 == 1) {
  Serial.println("STOP 4");
  player4.stop();
  reproduciendo4 = 0;
}

//////TELEFONO 5
entrada5 = digitalRead(SWT5);
if(entrada5 == 0 && reproduciendo5 == 0) {
  pista5 = int(random(1,31));
  delay(200);
  player5.play(pista5);
  Serial.println("reproduciendo5");
  Serial.println(pista5);
  reproduciendo5 = 1;

} else if(entrada5 == 1 && reproduciendo5 == 1) {
  Serial.println("STOP 5");
  player5.stop();
  reproduciendo5 = 0;
}

  if (player1.available()) 
    printDetail(player1.readType(), player1.read()); 
    
  if (player2.available()) 
    printDetail(player2.readType(), player2.read()); 
  
  if (player3.available()) 
    printDetail(player3.readType(), player3.read()); 
    
  if (player4.available()) 
    printDetail(player4.readType(), player4.read()); 
  
  if (player5.available()) 
    printDetail(player5.readType(), player5.read()); 
  
if(Serial.available() > 0) {
      Serial1.write(Serial.read());
      Serial.flush();
    }
   if (Serial1.available() > 0) {
    //Serial1.println("Reescribiendo");
    lecturaBT = Serial1.readString();
    
    Serial1.println(lecturaBT);
    Serial1.println(lecturaBT.length());
    
    if (lecturaBT.length() == 3) {
      int encendido = lecturaBT.toInt();
      if(encendido == 0) {
        Serial.println("Apagar TELEFONO");
        digitalWrite(ledPIN, LOW);
      } else if (encendido == 1) {
        Serial.println("Encender TELEFONO");
        digitalWrite(ledPIN, HIGH);
      }
    } else {
    Serial.println(lecturaBT);
    Serial1.flush();
   }

}
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
