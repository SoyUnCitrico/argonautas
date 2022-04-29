#define DEBOUNCETIME 10

struct Boton {
  int PIN;
  
  uint32_t numberOfButtonInterrupts = 0;
  uint32_t debounceTimeout = 0;
  bool lastState;
  
  uint32_t saveDebounceTimeout;
  bool saveLastState;
  int save;
};

portMUX_TYPE mux = portMUX_INITIALIZER_UNLOCKED;


// Interrupt Service Routine - Keep it short!
void IRAM_ATTR handleButtonInterrupt(Boton but) {
  portENTER_CRITICAL_ISR(&mux);
  but.numberOfButtonInterrupts++;
  but.lastState = digitalRead(but.PIN);
  but.debounceTimeout = xTaskGetTickCount(); //version of millis() that works from interrupt
  portEXIT_CRITICAL_ISR(&mux);
}

int numberOfInterrupts = 2;
Boton buttonOn = (22, (unsigned int)0, 0, false, 0, false, 0);

void controlInterrupt( void * parameter)
{
//  String taskMessage = "Debounced ButtonRead Task running on core ";
//  taskMessage = taskMessage + xPortGetCoreID();
//  Serial.println(taskMessage);

  // set up button Pin
  pinMode (buttonOn.PIN, INPUT);
  
  attachInterrupt(digitalPinToInterrupt(buttonOn.PIN), handleButtonInterrupt(buttonOn), FALLING);  
  
  while (1) {

    portENTER_CRITICAL_ISR(&mux); // so that value of numberOfButtonInterrupts,l astState are atomic - Critical Section
    buttonOn.save  = buttonOn.numberOfButtonInterrupts;
    buttonOn.saveDebounceTimeout = buttonOn.debounceTimeout;
    buttonOn.saveLastState  = buttonOn.lastState;
    portEXIT_CRITICAL_ISR(&mux); // end of Critical Section

    bool currentState = digitalRead(buttonOn.PIN);

    // This is the critical IF statement
    // if Interrupt Has triggered AND Button Pin is in same state AND the debounce time has expired THEN you have the button push!
    //
    if ((buttonOn.save != 0) //interrupt has triggered
        && (currentState == buttonOn.saveLastState) // pin is still in the same state as when intr triggered
        && (millis() - buttonOn.saveDebounceTimeout > DEBOUNCETIME ))
    { // and it has been low for at least DEBOUNCETIME, then valid keypress
      
      if (currentState == LOW)
      {
        Serial.printf("Button is pressed and debounced, current tick=%d\n", millis());
      }
      else
      {
        Serial.printf("Button is released and debounced, current tick=%d\n", millis());
      }
      
      Serial.printf("Button Interrupt Triggered %d times, current State=%u, time since last trigger %dms\n", buttonOn.save, currentState, millis() - buttonOn.saveDebounceTimeout);
      
      portENTER_CRITICAL_ISR(&mux); // can't change it unless, atomic - Critical section
      buttonOn.numberOfButtonInterrupts = 0; // acknowledge keypress and reset interrupt counter
      portEXIT_CRITICAL_ISR(&mux);


      vTaskDelay(10 / portTICK_PERIOD_MS);
    }

      vTaskDelay(10 / portTICK_PERIOD_MS);

  }
}
