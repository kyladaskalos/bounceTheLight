#include <Adafruit_CircuitPlayground.h>
#include <AsyncDelay.h>

int buttonPlay = 5;
volatile bool buttonFlag = 0;
int switcher = 0;
int ledTracker = 0;
int totalPoints = 0;
bool continueGame = 1;

void setup() {
  CircuitPlayground.begin();
  Serial.begin(9600);
  attachInterrupt(digitalPinToInterrupt(buttonPlay), ButtonBISR, FALLING);
}

void loop() {

  //Detemine the 'bounce zone'
  if(totalPoints < 4){
    roundOne();
  } else if(totalPoints > 3 && totalPoints < 6){
    roundTwo();
  } else if(totalPoints > 5 && totalPoints < 9){
    roundThree();
  } else if(totalPoints > 8 && totalPoints < 14){
    finalRound();
  }

  while(switcher % 2 == 0 && continueGame == 1){
    for(ledTracker; ledTracker < 10; ledTracker++){ // iterates through, adding 1 to ledTracker each time
      if(totalPoints < 4){
        roundOne();
      }else if(totalPoints > 3 && totalPoints < 6){
        roundTwo();
      }else if(totalPoints > 5 && totalPoints < 9){
        roundThree();
      }else if(totalPoints > 8 && totalPoints < 14){
        finalRound();
      }

      CircuitPlayground.setPixelColor(ledTracker, 255, 255, 255);
      delay(300);
      CircuitPlayground.setPixelColor(ledTracker, 0, 0, 0);
      delay(300);

      if(buttonFlag == 1){ // checking to see if bounced
        ledTracker--;
        buttonFlag = 0;
        break;
      }
      if(ledTracker == 9){ // circles around
        ledTracker = -1;
      }
      if(ledTracker == 4){
        continueGame = 0;
        break;
      }
    }
  } 
  while(switcher % 2 != 0 && continueGame == 1){
    for(ledTracker; ledTracker > -1; ledTracker--){ // iterates through, subtracting 1 from ledTracker
      if(totalPoints < 4){
        roundOne();
      }else if(totalPoints > 3 && totalPoints < 6){
        roundTwo();
      }else if(totalPoints > 5 && totalPoints < 9){
        roundThree();
      }else if(totalPoints > 8 && totalPoints < 14){
        finalRound();
      }

      CircuitPlayground.setPixelColor(ledTracker, 255, 255, 255);
      delay(300);
      CircuitPlayground.setPixelColor(ledTracker, 0, 0, 0);
      delay(300);

      if(buttonFlag == 1){ //check if bounced
        ledTracker++;
        buttonFlag = 0;
        break;
      }
      if(ledTracker == 0){ // circles around
        ledTracker = 10;
      }
      if(ledTracker == 5){
        continueGame = 0;
        break;
      }
    } 
  }

  if(ledTracker == 4 || ledTracker == 5){ // prints loss if led is not pressed in time
    Serial.println("You lose");
    ledTracker = 0; // sets ledTracker to 0 to prevent infinit printing
  }
}

void ButtonBISR(){
  buttonFlag = 1;
  switcher++;
}

void roundOne(){
  CircuitPlayground.setPixelColor(4, 0, 0, 255);
  CircuitPlayground.setPixelColor(1, 0, 0, 255);
  CircuitPlayground.setPixelColor(2, 0, 0, 255);
  CircuitPlayground.setPixelColor(3, 0, 0, 255);
  CircuitPlayground.setPixelColor(5, 0, 0, 255);
  CircuitPlayground.setPixelColor(8, 0, 0, 255);
  CircuitPlayground.setPixelColor(7, 0, 0, 255);
  CircuitPlayground.setPixelColor(6, 0, 0, 255);
}

void roundTwo(){
  CircuitPlayground.setPixelColor(4, 0, 0, 255);
  CircuitPlayground.setPixelColor(1, 0, 0, 255);
  CircuitPlayground.setPixelColor(2, 0, 0, 255);
  CircuitPlayground.setPixelColor(5, 0, 0, 255);
  CircuitPlayground.setPixelColor(8, 0, 0, 255);
  CircuitPlayground.setPixelColor(7, 0, 0, 255);
}

void roundThree(){
  CircuitPlayground.setPixelColor(4, 0, 0, 255);
  CircuitPlayground.setPixelColor(1, 0, 0, 255);
  CircuitPlayground.setPixelColor(5, 0, 0, 255);
  CircuitPlayground.setPixelColor(8, 0, 0, 255);
}

void finalRound(){
  CircuitPlayground.setPixelColor(4, 0, 0, 255);
  CircuitPlayground.setPixelColor(5, 0, 0, 255);
}




