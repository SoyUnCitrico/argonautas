void setup()
{   Serial1.begin(115200);
    Serial.println("INICIANDO BT...");
    Serial.begin(115200);
    Serial.println("INICIANDO USB...");
    delay(100);
}

void loop()
{ //Envíamos y recibimos datos
   if (Serial.available() > 0) {
       Serial1.write(Serial.read());
       Serial1.write("DATA");
       
   }
   if (Serial1.available() > 0) {
       Serial.write(Serial1.read());
       int n = Serial1.readString().toInt();
       if(n === 0) {Serial.println(n);}
       else { Serial.println("No eres lo que busco");}
   }
}
