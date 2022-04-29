#include "BluetoothSerial.h"
BluetoothSerial SerialBT;

struct Button {
  const uint8_t pin;
  uint32_t numberKeyPresses;
  unsigned long startDebounce;
  bool pressed;
};

uint8_t address[6]  = {0x20, 0x16, 0x05, 0x10, 0x06, 0x82};
String name = "SoyUnCitrico";
char *pin = "1489"; 
unsigned long debounceTime = 200000;
bool connected;
Button buttonOn = {22, 0 , 0, false };
Button buttonOff = {23, 0 , 0, false };

void setup() {
  Serial.begin(115200);
  //SerialBT.setPin(pin);z
  SerialBT.begin("ESP32test", true); 
  SerialBT.setPin(pin);
  Serial.println(" Master MODE !!");
  Serial.println(" Buscando BT REMOTE...");
  
  connected = SerialBT.connect(name);
  //connected = SerialBT.connect(address);
  
  if(connected) {
    Serial.print("Conectado satisfactoriamente a: ");
    Serial.println(name);
  } else {
    while(!SerialBT.connected(10000)) {
      Serial.println("Fallo al conectar, revisa el estado del dispositivo BT y reinicia el ESP32"); 
    }
  }
  
}

void loop() {  
  if ( digitalRead(buttonOn.pin) && micros() - buttonOn.startDebounce > debounceTime) {
    buttonOn.startDebounce = micros();
    buttonOn.numberKeyPresses++;
    buttonOn.pressed = true;
  }
  if ( digitalRead(buttonOff.pin) && micros() - buttonOff.startDebounce > debounceTime) {
    buttonOff.startDebounce = micros();
    buttonOff.numberKeyPresses++;
    buttonOff.pressed = true;
  }
  
//  if(SerialBT.available()) {
//    Serial.write(SerialBT.read());
//    SerialBT.flush();
//  }

  if (buttonOff.pressed) {
      Serial.printf("Button 1 has been pressed %u times\n", buttonOff.numberKeyPresses);
      SerialBT.println("0");
      buttonOff.pressed = false;
  }

  if (buttonOn.pressed) {
      Serial.printf("Button 2 has been pressed %u times\n", buttonOn.numberKeyPresses);
      SerialBT.println("1");
      buttonOn.pressed = false;
  }
}
