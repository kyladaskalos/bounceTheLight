#include <Adafruit_CircuitPlayground.h>
#include <AsyncDelay.h>

int buttonPlay = 5;
volatile bool buttonFlag = 0;
bool buttonVal = 0;
int switcher = 0;
int ledTracker = 0;


void setup() {
  CircuitPlayground.begin();
  attachInterrupt(digitalPinToInterrupt(buttonPlay), ButtonBISR, FALLING);
}

void loop() {

  while(switcher % 2 == 0){
    for(ledTracker; ledTracker < 10; ledTracker++){
      CircuitPlayground.setPixelColor(ledTracker, 255, 255, 255);
      delay(300);
      CircuitPlayground.setPixelColor(ledTracker, 0, 0, 0);
      delay(300);

      if(buttonFlag == 1){
        buttonFlag = 0;
        break;
      }
    }

  } while(switcher % 2 != 0){
    for(ledTracker; ledTracker > 0; ledTracker--){
      CircuitPlayground.setPixelColor(ledTracker, 255, 255, 255);
      delay(300);
      CircuitPlayground.setPixelColor(ledTracker, 0, 0, 0);
      delay(300);

      if(buttonFlag == 1){
        buttonFlag = 0;
        break;
      }
    } 
  }
}

void ButtonBISR(){
  buttonFlag = 1;
  switcher++;
}





