#include "BluetoothSerial.h"
BluetoothSerial SerialBT;

struct Button {
  const uint8_t PIN;
  uint32_t numberKeyPresses;
  uint32_t numberKeyReleased;
  bool pressed;
};

uint8_t address[6]  = {0x20, 0x16, 0x05, 0x10, 0x06, 0x82};
String name = "SoyUnCitrico";
char *pin = "1489"; //<- standard pin would be provided by default
bool connected;

Button button1 = {22, 0 , 0 , false };
Button button2 = {23, 0 , 0 , false };


void IRAM_ATTR sendOn1() {
  button1.numberKeyPresses += 1;
  button1.pressed = true;
}

void IRAM_ATTR sendOn2() {
  button2.numberKeyPresses += 1;
  button2.pressed = true;
}

void setup() {
  Serial.begin(115200);
  //SerialBT.setPin(pin);
  SerialBT.begin("ESP32test", true); 
  SerialBT.setPin(pin);
  Serial.println(" Master MODE !!");
  Serial.println(" Searching BT REMOTE...");
  
  connected = SerialBT.connect(name);
  //connected = SerialBT.connect(address);
  
  if(connected) {
    Serial.print("Conectado satisfactoriamente a: ");
    Serial.println(name);
  } else {
    while(!SerialBT.connected(10000)) {
      Serial.println("Failed to connect. Make sure remote device is available and in range, then restart app."); 
    }
  }
  
  attachInterrupt(digitalPinToInterrupt(button1.PIN), sendOn1, RISING);
  attachInterrupt(digitalPinToInterrupt(button2.PIN), sendOn2, RISING);
  //attachInterrupt(digitalPinToInterrupt(button2.pin), sendOn(button2), RISING);
  //attachInterrupt(digitalPinToInterrupt(button2.pin), sendOff(button2), FALLING);
}

void loop() {
  //if (Serial.available()) {
    //SerialBT.write(Serial.read());
    //Serial.flush();
  //}
  
  if(SerialBT.available()) {
    Serial.write(SerialBT.read());
    SerialBT.flush();
  }

  if (button1.pressed) {
      Serial.printf("Button 1 has been pressed %u times\n", button1.numberKeyPresses);
      SerialBT.println("0");
      button1.pressed = false;
  }

  if (button2.pressed) {
      Serial.printf("Button 2 has been pressed %u times\n", button2.numberKeyPresses);
      SerialBT.println("1");
      button2.pressed = false;
  }
}
