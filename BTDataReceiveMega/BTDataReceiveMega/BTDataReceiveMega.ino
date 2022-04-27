String lecturaBT;
int ledPIN = 13;

void setup()
{   Serial1.begin(115200);
    Serial1.write("INICIANDO BT...");
    Serial.begin(115200);
    Serial.println("INICIANDO USB...");
    pinMode(ledPIN, OUTPUT);
    delay(100);
}

void loop() { 
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
